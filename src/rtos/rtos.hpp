#ifndef RTOS_HPP
#define RTOS_HPP

#include "sys/sys.hpp"
#include "sys/state.hpp"
#include "display/controller.hpp"
#include "gpio/gpio.hpp"

#include "button_debounce.h"


namespace RTOS
{
    struct Process_Params {
        Sys::Event_Processor *evtP;
        Display::Controller *displayCtrl;

        Process_Params();
    };

    struct Button_Params {
        Debouncer *btnPort;
        GPIO::Controller *gpioCtrl;
        Display::Controller *displayCtrl;
        Sys::State *sysState;

        uint8_t button;  /* 1..4 */
        uint8_t buttonIndex;  /* the index of the button to use */

        Button_Params();
    };

    /* Event processing(CPU2, BLE, display) task, runs processing whenever possible, but w/ low priority */
    void Process_Task(void *params);

    /* Button processing task, runs every ms, with higher priority then process */
    void Button_Task(void *params);
}


#endif /* RTOS_HPP */
