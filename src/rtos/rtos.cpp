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

    void Button_Task(void *params)
    {
        Button_Params *p = (Button_Params *)params;
        for (;;) {
            p->btnPort->ButtonProcess(p->gpioCtrl->Read_Component(p->buttonIndex) << p->button);  /* WE ARE NOT SHIFTING!!!! BUG!!! */
            if (p->btnPort->ButtonPressed(1 << p->button)) {  /* Check this */
                BITNSET(p->buttonState, p->button, 1);

                uint8_t db = 0;
                for(uint8_t i = 0; i < DOUBLE_PRESS_TIMEOUT; ++i) {
                    if ((p->button == 1 && BITN(p->buttonState, (2 - 1))) || (p->button == 2 && BITN(p->buttonState, (1 - 1)))) {
                        p->displayCtrl->Button_Double(1, 2);
                        db = 1;
                        break;
                    }
                    if ((p->button == 3 && BITN(p->buttonState, (4 - 1))) || (p->button == 4 && BITN(p->buttonState, (3 - 1)))) {
                        p->displayCtrl->Button_Double(3, 4);
                        db = 1;
                        break;
                    }
                    vTaskDelay(1);
                }
                if (!db) p->displayCtrl->Button(p->button);
            } else BITNSET(p->buttonState, p->button, 0);

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
