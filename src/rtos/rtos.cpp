#include "rtos/rtos.hpp"

#include "sys/state.hpp"
#include "ble/uuid.hpp"
#include "services/info.hpp"

#include "lvgl.h"
#include "FreeRTOS.h"
#include "task.h"


namespace RTOS
{
    Process_Params::Process_Params()
    {}

    Button_Params::Button_Params()
    {}

    void Process_Task(void *params)
    {
        Process_Params *p = (Process_Params *)params;
        for (;;) {
            p->evtP->BLE_ProcessEvent();
            p->evtP->Sys_ProcessEvent();

            p->displayCtrl->Process();
        }
    }

    void Startup_Task(void *params)
    {
        uint8_t sentReset = 0;
        Startup_Params *p = (Startup_Params *)params;
        for (;;) {
            vTaskDelay(1000);
            if (!sentReset && p->sysState->App_Flag_Get(Sys::State::App_Flag::BLE_CONNECTED) == Sys::State::Flag_Val::SET) {
                /* This is a ridiculous hack, but to properly reset GB variables through a reset(even if a BLE connection is maintained), we have to notify it */
                vTaskDelay(1000);

                /* Writing device reset info char for GB */
                uint8_t resetData = 0x01;
                if (p->info->Update_Char_Value(BLE::UUID::ExtractUUID16FromLE(p->info->deviceReset.Get_UUID()),
                            p->info->deviceReset.Get_Value_Length(),
                            &resetData) != BLE_STATUS_SUCCESS)
                    Sys::Error_Handler();

                sentReset = 1;
            }
        }
    }

    uint8_t Is_Double(uint8_t button, uint32_t *state)
    {
        if ((button == 1 && READ_BIT(*state, (2 - 1))) || (button == 2 && READ_BIT(*state, (1 - 1)))) return 1;
        if ((button == 3 && READ_BIT(*state, (4 - 1))) || (button == 4 && READ_BIT(*state, (3 - 1)))) return 2;
        return 0;
    }

    void Button_Task(void *params)
    {
        Button_Params *p = (Button_Params *)params;
        for (;;) {
            p->btnPort->ButtonProcess(p->gpioCtrl->Read_Component(p->btn1) | (p->gpioCtrl->Read_Component(p->btn2) << 1) | (p->gpioCtrl->Read_Component(p->btn3) << 2) | (p->gpioCtrl->Read_Component(p->btn4) << 3));

            if (p->btnPort->ButtonPressed(BUTTON_PIN_0)) {
                /* Button 1, wait for 2 double */

                bool db = false;
                for (uint8_t i = 0; i < DOUBLE_PRESS_TIMEOUT; ++i) {
                    p->btnPort->ButtonProcess(p->gpioCtrl->Read_Component(p->btn1) | (p->gpioCtrl->Read_Component(p->btn2) << 1) | (p->gpioCtrl->Read_Component(p->btn3) << 2) | (p->gpioCtrl->Read_Component(p->btn4) << 3));
                    if (p->btnPort->ButtonPressed(BUTTON_PIN_1)) {
                        db = true;
                        p->displayCtrl->Button_Double(1, 2);
                    }
                    vTaskDelay(1);
                }
                if (!db) p->displayCtrl->Button(1);
            }
            else if (p->btnPort->ButtonPressed(BUTTON_PIN_1)) {
                /* Button 2, wait for 1 double */

                bool db = false;
                for (uint8_t i = 0; i < DOUBLE_PRESS_TIMEOUT; ++i) {
                    p->btnPort->ButtonProcess(p->gpioCtrl->Read_Component(p->btn1) | (p->gpioCtrl->Read_Component(p->btn2) << 1) | (p->gpioCtrl->Read_Component(p->btn3) << 2) | (p->gpioCtrl->Read_Component(p->btn4) << 3));
                    if (p->btnPort->ButtonPressed(BUTTON_PIN_0)) {
                        db = true;
                        p->displayCtrl->Button_Double(2, 1);
                    }
                    vTaskDelay(1);
                }
                if (!db) p->displayCtrl->Button(2);
            }
            else if (p->btnPort->ButtonPressed(BUTTON_PIN_2)) {
                /* Button 3, wait for 4 double */

                bool db = false;
                for (uint8_t i = 0; i < DOUBLE_PRESS_TIMEOUT; ++i) {
                    p->btnPort->ButtonProcess(p->gpioCtrl->Read_Component(p->btn1) | (p->gpioCtrl->Read_Component(p->btn2) << 1) | (p->gpioCtrl->Read_Component(p->btn3) << 2) | (p->gpioCtrl->Read_Component(p->btn4) << 3));
                    if (p->btnPort->ButtonPressed(BUTTON_PIN_3)) {
                        db = true;
                        p->displayCtrl->Button_Double(3, 4);
                    }
                    vTaskDelay(1);
                }
                if (!db) p->displayCtrl->Button(3);
            }
            else if (p->btnPort->ButtonPressed(BUTTON_PIN_3)) {
                /* Button 4, wait for 3 double */

                bool db = false;
                for (uint8_t i = 0; i < DOUBLE_PRESS_TIMEOUT; ++i) {
                    p->btnPort->ButtonProcess(p->gpioCtrl->Read_Component(p->btn1) | (p->gpioCtrl->Read_Component(p->btn2) << 1) | (p->gpioCtrl->Read_Component(p->btn3) << 2) | (p->gpioCtrl->Read_Component(p->btn4) << 3));
                    if (p->btnPort->ButtonPressed(BUTTON_PIN_2)) {
                        db = true;
                        p->displayCtrl->Button_Double(4, 3);
                    }
                    vTaskDelay(1);
                }
                if (!db) p->displayCtrl->Button(4);
            }

            vTaskDelay(1);
        }
    }
}

extern "C"
{
    void vApplicationTickHook()
    {
        lv_tick_inc(1);
    }

    void vApplicationMallocFailedHook()
    {
        /* vApplicationMallocFailedHook() will only be called if
         * configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
         * function that will get called if a call to pvPortMalloc() fails.
         * pvPortMalloc() is called internally by the kernel whenever a task, queue,
         * timer or semaphore is created.  It is also called by various parts of the
         * demo application.  If heap_1.c or heap_2.c are used, then the size of the
         * heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
         * FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
         * to query the size of free heap space that remains (although it does not
         * provide information on how the remaining heap might be fragmented). */
        taskDISABLE_INTERRUPTS();

        for(;;) {}
    }

    void vApplicationIdleHook()
    {
        /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
         * to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
         * task.  It is essential that code added to this hook function never attempts
         * to block in any way (for example, call xQueueReceive() with a block time
         * specified, or call vTaskDelay()).  If the application makes use of the
         * vTaskDelete() API function (as this demo application does) then it is also
         * important that vApplicationIdleHook() is permitted to return to its calling
         * function, because it is the responsibility of the idle task to clean up
         * memory allocated by the kernel to any task that has since been deleted. */
    }

    void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
    {
        (void)pcTaskName;
        (void)pxTask;

        /* Run time stack overflow checking is performed if
         * configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
         * function is called if a stack overflow is detected. */
        taskDISABLE_INTERRUPTS();

        for(;;) {}
    }
}
