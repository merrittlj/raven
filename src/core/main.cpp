/* requires stm32wb5x_BLE_Stack_fw.bin binary on wireless coprocessor */

#include "main.hpp"

#include "core/main.hpp"
#include "app/app.hpp"
#include "app/common.hpp"
#include "app/debug.hpp"
#include "hw/conf.hpp"
#include "gpio/gpio.hpp"
#include "ble/ble.hpp"
#include "ble/gatt_service.hpp"
#include "sys/sys.hpp"


extern "C" void _init(){} /* To avoid linker errors */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main()
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
    BLE::App bleApp = new BLE::App(gpioCtrl, sysState);
    BLE::Gatt_Service myService = new BLE::Gatt_Service(gpioCtrl, sysState);
    App::Debug_Controller debugCtrl = new App::Debug_Controller();

    /* Tune the HSE internal load capacitors - P-NUCLEO-WB55.Nucleo board */
    sysCtrl.Config_HSE();

    sysState.Register_LED_Red(gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 1), GPIO::Types::LED)));
    gpioCtrl.Config();
    gpioCtrl.Init();

    /* Configure the debug support if needed */
    debugCtrl.Init();

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
    debugCtrl.EnableCPU2();

    /* Set the red LED Off to indicate that the CPU2 is initialized */
    gpioCtrl.Write_Component(sysState.Fetch_LED_Red(), RESET);

    /* Set the green LED On to indicate that the wireless stack FW is running */
    gpioCtrl.Write_Component(sysState.Fetch_LED_Green(), SET);

    bleApp.Init(myService);
    bleApp.Advertising(SET);

    for(;;)
    {
        /* Process pending BLE event coming from CPU2 (if any) */
        sysEvtP.BLE_ProcessEvent();
        /* Process pending SYSTEM event coming from CPU2 (if any) */
        sysEvtP.Sys_ProcessEvent();

        /* Update the Notify Characteristic every ~1 second and only if BLE connected.
           It might be also done only after the GATT client enables the notifications,
           but that is out of scope of this basic example */
        if (APP_FLAG_GET(APP_FLAG_BLE_CONNECTED) != 0x00)
        {
            if ((HAL_GetTick() - prevTick) > 1000)
            {
                prevTick = HAL_GetTick();
                notifyCharacteristicData[1] ^= 0x01;
                if (myService.Write_Characteristic_Update(NOTIFY_CHARACTERISTIC_UUID,
                            NOTIFY_CHARACTERISTIC_VALUE_LENGTH,
                            notifyCharacteristicData) != BLE_STATUS_SUCCESS)
                    Sys::Error_Handler(); /* UNEXPECTED */
            }
        }
    }
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
