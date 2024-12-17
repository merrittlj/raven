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
#include "services/notify.hpp"
#include "services/pref.hpp"
#include "services/nav.hpp"
#include "services/music.hpp"
#include "display/controller.hpp"

#include "FreeRTOS.h" /* Must come first. */
#include "task.h" /* RTOS task related API prototypes. */
#include "queue.h" /* RTOS queue related API prototypes. */
#include "timers.h" /* Software timer related API prototypes. */

#include "button_debounce.h"


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
    BLE::NotifyService notifyService = BLE::NotifyService(&gpioCtrl, &sysState);
    BLE::PrefService prefService = BLE::PrefService(&gpioCtrl, &sysState);
    BLE::NavService navService = BLE::PrefService(&gpioCtrl, &sysState);
    BLE::MusicService musicService = BLE::PrefService(&gpioCtrl, &sysState);

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
    uint8_t cs = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOA, 6), GPIO::Types::SPI));
    uint8_t pwr = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOA, 8), GPIO::Types::SPI));

    uint8_t btn1 = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 12), GPIO::Types::Button));
    uint8_t btn2 = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 13), GPIO::Types::Button));
    uint8_t btn3 = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 14), GPIO::Types::Button));
    uint8_t btn4 = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 15), GPIO::Types::Button));

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

    bleApp.Init();
    timeService.Init();
    notifyService.Init();
    prefService.Init();
    navService.Init();
    musicService.Init();
    bleApp.Advertising(SET);

    Display::Controller displayCtrl = Display::Controller(200, 200, spiCtrl, &sysState);
    displayCtrl.Init();

    Debouncer btnPort(BUTTON_PIN_0 | BUTTON_PIN_1 | BUTTON_PIN_2 | BUTTON_PIN_3);

    for(;;)
    {
        sysEvtP.BLE_ProcessEvent();
        sysEvtP.Sys_ProcessEvent();

        displayCtrl.Process();

        if ((HAL_GetTick() - prevTick) >= 1) {
            prevTick = HAL_GetTick();

            btnPort.ButtonProcess(gpioCtrl.Read_Component(btn1) | (gpioCtrl.Read_Component(btn2) << 1) | (gpioCtrl.Read_Component(btn3) << 2) | (gpioCtrl.Read_Component(btn4) << 3));
            if (btnPort.ButtonPressed(BUTTON_PIN_0)) {
                gpioCtrl.Write_Component(sysState.Fetch_LED_Red(), SET);
                displayCtrl.Button_One();
            } else gpioCtrl.Write_Component(sysState.Fetch_LED_Red(), RESET);
            if (btnPort.ButtonPressed(BUTTON_PIN_1)) {
                displayCtrl.Button_Two();
            }
            if (btnPort.ButtonPressed(BUTTON_PIN_2)) {
                displayCtrl.Button_Three();
            }
            if (btnPort.ButtonPressed(BUTTON_PIN_3)) {
                displayCtrl.Button_Four();
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
