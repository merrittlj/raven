#ifndef RTOS_HPP
#define RTOS_HPP

#include "sys/sys.hpp"
#include "display/controller.hpp"


namespace RTOS
{
    struct Process_Params {
        Sys::Event_Processor evtP;
        Display::Controller displayCtrl;

        Process_Params();
    };

    /* Event processing(CPU2, BLE, display) task, runs processing whenever possible, but w/ low priority */
    void Process_Task(void *params);
}


#endif /* RTOS_HPP */
