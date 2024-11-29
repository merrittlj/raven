/* requires stm32wb5x_BLE_Stack_fw.bin binary on wireless coprocessor */

#include "main.hpp"

#include "core/main.hpp"
#include "app/common.hpp"
#include "app/debug.hpp"
#include "hw/conf.hpp"
#include "gpio/gpio.hpp"
#include "ble/ble.hpp"
#include "ble/uuid.hpp"
#include "sys/sys.hpp"
#include "sys/state.hpp"
#include "services/simple.hpp"


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

    /* Tune the HSE internal load capacitors - P-NUCLEO-WB55.Nucleo board */
    Sys::State sysState = Sys::State();
    Sys::Controller sysCtrl = Sys::Controller(&sysState);
    sysCtrl.Config_HSE();

    App::Debug_Controller debugCtrl = App::Debug_Controller();
    GPIO::Controller gpioCtrl = GPIO::Controller();
    Sys::Event_Processor sysEvtP = Sys::Event_Processor(&sysState);
    BLE::App bleApp = BLE::App(&gpioCtrl, &sysState);
    BLE::SimpleService simpleService = BLE::SimpleService(&gpioCtrl, &sysState);

    __disable_irq();
    /* Configure the debug support if needed */
    debugCtrl.Init();

    sysCtrl.Config_SysClk();
    sysCtrl.Init_CPU2();

    GPIO::Component redCmp = GPIO::Component(GPIO::Pin(GPIOB, 1), GPIO::Types::LED);
    sysState.Register_LED_Red(gpioCtrl.Add_Component(redCmp));
    gpioCtrl.Config();
    gpioCtrl.Init();

    /* Set the red LED On to indicate that the CPU2 is initializing */
    gpioCtrl.Write_Component(sysState.Fetch_LED_Red(), SET);
    __enable_irq(); /* DANGER ZONE */

    /* Wait until the CPU2 gets initialized */
    while((sysState.App_Flag_Get(Sys::State::App_Flag::CPU2_INITIALIZED) == Sys::State::Flag_Val::NOT_SET) \
            || (sysState.App_Flag_Get(Sys::State::App_Flag::WIRELESS_FW_RUNNING) == Sys::State::Flag_Val::NOT_SET))
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

    bleApp.Init(simpleService);
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
        if (sysState.App_Flag_Get(Sys::State::App_Flag::BLE_CONNECTED) == Sys::State::Flag_Val::SET)
        {
            if ((HAL_GetTick() - prevTick) > 1000)
            {
                prevTick = HAL_GetTick();
                bleApp.notifyCharacteristicData[1] ^= 0x01;
                if (simpleService.Update_Char_Value(BLE::UUID::ExtractUUID16FromLE(simpleService.bellNotifyChar.Get_UUID()),
                            simpleService.bellNotifyChar.Get_Value_Length(),
                            bleApp.notifyCharacteristicData) != BLE_STATUS_SUCCESS)
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
