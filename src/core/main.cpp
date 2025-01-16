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
#include "sys/i2c.hpp"
#include "services/time.hpp"
#include "services/notify.hpp"
#include "services/pref.hpp"
#include "services/nav.hpp"
#include "services/music.hpp"
#include "services/event.hpp"
#include "services/info.hpp"
#include "display/controller.hpp"
#include "rtos/rtos.hpp"
#include "haptic/haptic.hpp"

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
    BLE::TimeService timeService = BLE::TimeService(&gpioCtrl, &sysState);
    BLE::NotifyService notifyService = BLE::NotifyService(&gpioCtrl, &sysState);
    BLE::PrefService prefService = BLE::PrefService(&gpioCtrl, &sysState);
    BLE::NavService navService = BLE::NavService(&gpioCtrl, &sysState);
    BLE::MusicService musicService = BLE::MusicService(&gpioCtrl, &sysState);
    BLE::EventService eventService = BLE::EventService(&gpioCtrl, &sysState);
    BLE::InfoService infoService = BLE::InfoService(&gpioCtrl, &sysState);
    BLE::App bleApp = BLE::App(&gpioCtrl, &sysState);

    /* Configure the debug support if needed */
    debugCtrl.Init();

    sysCtrl.Config_SysClk();
    sysCtrl.Init_CPU2();

    uint8_t red = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 1), GPIO::Types::LED));
    uint8_t green = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 0), GPIO::Types::LED));
    uint8_t blue = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 5), GPIO::Types::LED));
    sysState.Register_LED_Red(red);
    sysState.Register_LED_Green(green);
    sysState.Register_LED_Blue(blue);

    uint8_t busy = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOA, 2), { .Mode = GPIO_MODE_INPUT, .Pull = GPIO_NOPULL, }));
    uint8_t rst = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOA, 3), GPIO::Types::SPI));
    uint8_t dc = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOA, 4), GPIO::Types::SPI));
    uint8_t cs = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOA, 6), GPIO::Types::SPI));
    uint8_t pwr = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOA, 8), GPIO::Types::SPI));

    std::array<uint8_t, 4> btns;
    btns.at(0) = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 12), GPIO::Types::Button));
    btns.at(1) = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 13), GPIO::Types::Button));
    btns.at(2) = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 14), GPIO::Types::Button));
    btns.at(3) = gpioCtrl.Add_Component(GPIO::Component(GPIO::Pin(GPIOB, 15), GPIO::Types::Button));

    gpioCtrl.Config();
    gpioCtrl.Init();
    SPI_HandleTypeDef *spi = sysCtrl.Config_SPI();
    Sys::SPI_Controller spiCtrl = Sys::SPI_Controller(spi, &gpioCtrl, Sys::SPI_Manager{busy,rst,dc,cs,pwr});

    TIM_HandleTypeDef *tim2 = sysCtrl.Config_TIM2();
    __HAL_TIM_SetCompare(tim2, TIM_CHANNEL_1, (uint64_t)I2C_ARR_IDEAL);
    HAL_TIM_PWM_Start(tim2, TIM_CHANNEL_1);

    I2C_HandleTypeDef *i2c = sysCtrl.Config_I2C();
    Sys::I2C_Controller i2cCtrl = Sys::I2C_Controller(i2c, 0x4A << 1, &gpioCtrl);
    Haptic::Driver driver = Haptic::Driver(&i2cCtrl);
    Haptic::Controller hapticCtrl = Haptic::Controller(&driver);

    if (!driver.begin()) Sys::Error_Handler();
    if (!driver.defaultMotor()) Sys::Error_Handler();
    driver.enableFreqTrack(false);
    driver.setOperationMode(Haptic::INACTIVE);
    driver.clearIrq(driver.getIrqEvent());  /* I hate this */

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
    infoService.Init();
    musicService.Init();
    eventService.Init();

    bleApp.Advertising(SET);

    Display::Controller displayCtrl = Display::Controller(200, 200, spiCtrl, &sysState, &sysCtrl, &hapticCtrl, &infoService);
    displayCtrl.Init();

    Debouncer btnPort(BUTTON_PIN_0 | BUTTON_PIN_1 | BUTTON_PIN_2 | BUTTON_PIN_3);

    sysCtrl.Config_RTC();

    /* FreeRTOS */
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    RTOS::Process_Params *processParams = new RTOS::Process_Params;
    processParams->evtP = &sysEvtP;
    processParams->displayCtrl = &displayCtrl;
    xTaskCreate(RTOS::Process_Task, "Process", configMINIMAL_STACK_SIZE, (void *)processParams, tskIDLE_PRIORITY + 1, (TaskHandle_t *)NULL);

    RTOS::Startup_Params *startupParams = new RTOS::Startup_Params;
    startupParams->sysState = &sysState;
    startupParams->info = &infoService;
    xTaskCreate(RTOS::Startup_Task, "Startup", configMINIMAL_STACK_SIZE, (void *)startupParams, tskIDLE_PRIORITY, (TaskHandle_t *)NULL);

    uint32_t buttonState = 0;
    RTOS::Button_Params *buttonParams = new RTOS::Button_Params;
    buttonParams->btnPort = &btnPort;
    buttonParams->gpioCtrl = &gpioCtrl;
    buttonParams->displayCtrl = &displayCtrl;
    buttonParams->sysState = &sysState;
    buttonParams->buttonState = &buttonState;
    for (uint8_t i = 0; i < 4; ++i) {
        buttonParams->button = i;
        buttonParams->buttonIndex = btns.at(i);
        xTaskCreate(RTOS::Button_Task, "ButtonX", configMINIMAL_STACK_SIZE, (void *)buttonParams, tskIDLE_PRIORITY + 2, (TaskHandle_t *)NULL);
    }

    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
     * will never be reached.  If the following line does execute, then there was
     * insufficient FreeRTOS heap memory available for the idle and/or timer tasks
     * to be created.  See the memory management section on the FreeRTOS web site
     * for more details. */
    for (;;) {}
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
