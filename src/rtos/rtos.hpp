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

        uint8_t button;  /* 1..4 */
        uint8_t buttonIndex;  /* the index of the button to use */
        uint32_t *buttonState;  /* Little-endian state, where 0 is button 0, 1 is button 1, etc., 0 is not set 1 is set */

        Button_Params();
    };

    /* Event processing(CPU2, BLE, display) task, runs processing whenever possible, but w/ low priority */
    void Process_Task(void *params);

    /* Startup code, such as sending reset notify char */
    void Startup_Task(void *params);

    /* Button processing task, runs every ms, with higher priority then process */
    void Button_Task(void *params);
}


#endif /* RTOS_HPP */
