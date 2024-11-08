/* requires stm32wb5x_BLE_Stack_fw.bin binary on wireless coprocessor */

#include "main.h"

#include "core/main.hpp"
#include "app/app_common.h"
#include "app/app_debug.h"
#include "hw/hw_conf.h"
#include "ble/gatt_service.h"
#include "gpio/gpio.hpp"
#include "ble/ble.hpp"
#include "sys/sys.hpp"

#include "otp.h"
#include "ble.h"
#include "hci_tl.h"
#include "shci_tl.h"
#include "shci.h"


extern "C" void _init(){} /* To avoid linker errors */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /**
     * The OPTVERR flag is wrongly set at power on
     * It shall be cleared before using any HAL_FLASH_xxx() api
     */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);

    uint32_t prevTick = 0;

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    Sys::Controller sysCtrl = new Sys::Controller();
    Sys::Event_Processor sysEvtP = new Sys::Event_Processor();
    Sys::State sysState = new Sys::State();
    GPIO::Controller gpioCtrl = new GPIO::Controller();
    BLE::Application bleApp = new BLE::Application();

    /* Tune the HSE internal load capacitors - P-NUCLEO-WB55.Nucleo board */
    sysCtrl.Config_HSE();

    sysState.Register_LED_Red(gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 3), GPIO::Types::LED)));
    gpioCtrl.Config();
    gpioCtrl.Init();

    /* Configure the debug support if needed */
    APPD_Init();

    sysCtrl.Config_SysClk();
    sysCtrl.Init_CPU2();

    /* Set the red LED On to indicate that the CPU2 is initializing */
    gpioCtrl.Write_Component(sysState.Fetch_LED_Red(), SET);

    /* Wait until the CPU2 gets initialized */
    while((APP_FLAG_GET(APP_FLAG_CPU2_INITIALIZED) == 0) \
            || (APP_FLAG_GET(APP_FLAG_WIRELESS_FW_RUNNING) == 0))
    {
        /* Process pending SYSTEM event coming from CPU2 (if any) */
        sysEvtP.Sys_ProcessEvent();
    }

    /* Configure the CPU2 Debug (Optional) */
    APPD_EnableCPU2();

    /* Set the red LED Off to indicate that the CPU2 is initialized */
    gpioCtrl.Write_Component(sysState.Fetch_LED_Red(), RESET);

    /* Set the green LED On to indicate that the wireless stack FW is running */
    gpioCtrl.Write_Component(sysState.Fetch_LED_Green(), SET);

    bleApp.Init();
    bleApp.Advertising(SET);

    for(;;)
    {
        /* Process pending BLE event coming from CPU2 (if any) */
        sysEvtP.BLE_ProcessEvent();
        /* Process pending SYSTEM event coming from CPU2 (if any) */
        sysEvtP.Sys_ProcessEvent();

        /* Update the My Very Own Notify Characteristic every ~1 second and only if BLE connected.
           It might be also done only after the GATT client enables the notifications,
           but that is out of scope of this basic example */
        if (APP_FLAG_GET(APP_FLAG_BLE_CONNECTED) != 0x00)
        {
            if ((HAL_GetTick() - prevTick) > 1000)
            {
                prevTick = HAL_GetTick();
                myVeryOwnNotifyCharacteristicData[1] ^= 0x01;
                if (MyVeryOwnWriteCharacteristic_Update(MY_VERY_OWN_NOTIFY_CHARACTERISTIC_UUID,
                            MY_VERY_OWN_NOTIFY_CHARACTERISTIC_VALUE_LENGTH,
                            myVeryOwnNotifyCharacteristicData) != BLE_STATUS_SUCCESS)
                    Sys::Error_Handler(); /* UNEXPECTED */
            }
        }
    }
}

/**
 * @brief This callback is triggered when either
 *          + a GAP event is received from the BLE core device.
 *          + a GATT event that has not been positively acknowledged by the registered handler is received from the
 *            BLE core device.
 *        The event is returned in a HCI packet. The full HCI packet is stored in a single buffer and is available when
 *        this callback is triggered. However, an ACI event may be longer than a HCI packet and could be fragmented over
 *        several HCI packets. The HCI layer only handles HCI packets so when an ACI packet is split over several HCI
 *        packets, this callback is triggered for each HCI fragment. It is the responsibility of the application to
 *        reassemble the ACI event.
 *        This callback is triggered in the TL_BLE_HCI_UserEvtProc() context
 *
 * @param  pckt: The user event received from the BLE core device
 * @retval None
 */
SVCCTL_UserEvtFlowStatus_t SVCCTL_App_Notification( void *pckt )
{
    hci_event_pckt *event_pckt;
    evt_blecore_aci *blecore_evt;
    evt_le_meta_event *le_meta_evt;

    event_pckt = (hci_event_pckt*) ((hci_uart_pckt *) pckt)->data;

    switch (event_pckt->evt)
    {
        case HCI_DISCONNECTION_COMPLETE_EVT_CODE:
            APP_FLAG_RESET(APP_FLAG_BLE_CONNECTED);
            /* Start advertising */
            BLE_Advertising(SET);
            break; /* HCI_DISCONNECTION_COMPLETE_EVT_CODE */
        case HCI_LE_META_EVT_CODE:
            le_meta_evt = (evt_le_meta_event *)(event_pckt->data);
            switch (le_meta_evt->subevent)
            {
                case HCI_LE_CONNECTION_COMPLETE_SUBEVT_CODE:
                    APP_FLAG_RESET(APP_FLAG_BLE_ADVERTISING);
                    APP_FLAG_SET(APP_FLAG_BLE_CONNECTED);
                    break; /* HCI_LE_CONNECTION_COMPLETE_SUBEVT_CODE */
                default:
                    break;
            }
            break; /* HCI_LE_CONNECTION_COMPLETE_SUBEVT_CODE */
        case HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE:
            blecore_evt = (evt_blecore_aci*) event_pckt->data;
            switch (blecore_evt->ecode)
            {
                case EVT_END_OF_RADIO_ACTIVITY:
                    gpioCtrl.Write_Component(sysState.Fetch_LED_Green(), TOGGLE);
                    break; /* EVT_END_OF_RADIO_ACTIVITY */
            }
            break; /* HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE */

        default:
            break;
    }

    return (SVCCTL_UserEvtFlowEnable);
}

/**
 * @brief  Interrupt service routine that must be called when the system channel
 *         reports a packet has been received
 *         As stated in AN5289, this API notifies the user that a system user event has been received.
 *         The user has to call the shci_user_evt_proc() to process
 *         the notification in the system transport layer.
 *         As the shci_notify_asynch_evt() notification is called from the IPCC
 *         Interrupt Service Routine, it is strongly recommended to implement
 *         a background mechanism to call shci_user_evt_proc()
 *         (out of IPCC Interrupt Service Routine).
 * @param  pdata: Pointer to the packet or event data
 * @retval None
 */
void shci_notify_asynch_evt(void* pdata)
{
    APP_FLAG_SET(APP_FLAG_SHCI_EVENT_PENDING);
    return;
}

/**
 * @brief  Callback called from related IPCC RX Interrupt Service Routine, called when the BLE core (CPU2)
 *         reports a packet received or an event to the host.
 *         As stated in AN5289, this API notifies the user that a BLE user event has been received.
 *         The user has to call the hci_user_evt_proc() to process
 *         the notification in the BLE transport layer.
 *         As the hci_notify_asynch_evt() notification is called from the IPCC
 *         Interrupt Service Routine, it is strongly recommended to implement
 *         a background mechanism to call hci_user_evt_proc()
 *         (out of IPCC Interrupt Service Routine).
 * @param  pdata: Pointer to the packet or event data
 * @retval None
 */
void hci_notify_asynch_evt(void* pdata)
{
    APP_FLAG_SET(APP_FLAG_HCI_EVENT_PENDING);
    return;
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{ 
    /* Add some sort of printing/logging functionality */
}
#endif /* USE_FULL_ASSERT */
