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
#include "sys/spi.hpp"
#include "services/time.hpp"
#include "display/display.hpp"


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
    BLE::TimeService timeService = BLE::TimeService(&gpioCtrl, &sysState);

    /* Configure the debug support if needed */
    debugCtrl.Init();

    sysCtrl.Config_SysClk();
    sysCtrl.Init_CPU2();

    sysState.Register_LED_Red(gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 1), GPIO::Types::LED)));
    sysState.Register_LED_Green(gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 0), GPIO::Types::LED)));
    sysState.Register_LED_Blue(gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 5), GPIO::Types::LED)));

    uint8_t busy = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOA, 2), { .Mode = GPIO_MODE_INPUT, .Pull = GPIO_NOPULL, }));
    uint8_t rst = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOA, 3), GPIO::Types::SPI));
    uint8_t dc = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOA, 4), GPIO::Types::SPI));
    uint8_t cs = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOA, 5), GPIO::Types::SPI));
    uint8_t pwr = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOA, 6), GPIO::Types::SPI));

    gpioCtrl.Config();
    gpioCtrl.Init();
    SPI_HandleTypeDef *spi = sysCtrl.Config_SPI();
    Sys::SPIController spiCtrl = Sys::SPIController(spi, &gpioCtrl, Sys::SPIManager{busy,rst,dc,cs,pwr});
    
    /* Set the red LED On to indicate that the CPU2 is initializing */
    gpioCtrl.Write_Component(sysState.Fetch_LED_Red(), SET);

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

    bleApp.Init(&timeService);
    bleApp.Advertising(SET);

    Display::EInk eInk = Display::EInk(spiCtrl);
    eInk.Init();
    eInk.Clear();
    HAL_Delay(500);
    uint8_t image[25] = { 0 };
    eInk.Test();
    eInk.Display(image);

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
            if ((HAL_GetTick() - prevTick) > 5000)
            {
                prevTick = HAL_GetTick();
                /* bleApp.notifyCharacteristicData[1] ^= 0x01; */
                /* if (timeService.Update_Char_Value(BLE::UUID::ExtractUUID16FromLE(timeService.syncNotifyChar.Get_UUID()), */
                /*             timeService.syncNotifyChar.Get_Value_Length(), */
                /*             bleApp.notifyCharacteristicData) != BLE_STATUS_SUCCESS) */
                /*     Sys::Error_Handler(); /1* UNEXPECTED *1/ */
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
