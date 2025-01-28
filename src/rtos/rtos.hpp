#ifndef RTOS_HPP
#define RTOS_HPP

#include "sys/sys.hpp"
#include "sys/state.hpp"
#include "display/controller.hpp"
#include "gpio/gpio.hpp"
#include "services/info.hpp"

#include "button_debounce.h"


#define DOUBLE_PRESS_TIMEOUT 50

namespace RTOS
{
    struct Process_Params {
        Sys::Event_Processor *evtP;
        Display::Controller *displayCtrl;

        Process_Params();
    };

    struct Startup_Params {
        Sys::State *sysState;
        BLE::InfoService *info;
    };

    struct Button_Params {
        Debouncer *btnPort;
        GPIO::Controller *gpioCtrl;
        Display::Controller *displayCtrl;
        Sys::State *sysState;

        uint8_t btn1;
        uint8_t btn2;
        uint8_t btn3;
        uint8_t btn4;

        Button_Params();
    };

    /* Event processing(CPU2, BLE, display) task, runs processing whenever possible, but w/ low priority */
    void Process_Task(void *params);

    /* Startup code, such as sending reset notify char */
    void Startup_Task(void *params);

    uint8_t Is_Double(uint8_t button, uint32_t *state);
    /* Button processing task, runs every ms, with higher priority then process */
    void Button_Task(void *params);
}


#endif /* RTOS_HPP */
