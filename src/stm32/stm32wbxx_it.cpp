/*
 * filename:	stm32wbxx_it.c
 * date:	07.02.24
 * author:	Lucas Merritt/merrittlj
 * description:	Interrupt Service Routine functions
 */

#include "stm32/stm32wbxx_it.h"
#include "core/main.hpp"
#include "sys/sys.hpp"

#include "hw.h"

#include "FreeRTOS.h"
#include "semphr.h"


extern "C" {
    void xPortSysTickHandler(void);

    /* Non-Maskable Interrupt */
    void NMI_Handler(void)
    {
        for(;;);
    }

    /* Hard fault */
    void HardFault_Handler(void)
    {
        for (;;);
    }

    /* Memory management fault */
    void MemManage_Handler(void)
    {
        for (;;);
    }

    /* Prefetch fault, memory access fault */
    void BusFault_Handler(void)
    {
        for (;;);
    }

    /* Undefined instruction or illegal state */
    void UsageFault_Handler(void)
    {
        for (;;);
    }

    /* /1* System service call via SWI instruction *1/ */
    /* void SVC_Handler(void) */
    /* { */
    /* } */

    /* Debug monitor */
    void DebugMon_Handler(void)
    {
    }

    /* /1* Pendable request for system service *1/ */
    /* void PendSV_Handler(void) */
    /* { */
    /* } */

    /* /1* SysTick timer *1/ */
    /* void SysTick_Handler(void) */
    /* { */
    /*     HAL_IncTick(); */
    /* } */
    void SysTick_Handler(void)
    {
        HAL_IncTick();
        if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
            xPortSysTickHandler();
    }

    void IPCC_C1_TX_IRQHandler(void)
    {
        HW_IPCC_Tx_Handler();
    }

    void IPCC_C1_RX_IRQHandler(void)
    {
        HW_IPCC_Rx_Handler();
    }

    void RTC_Alarm_IRQHandler(void)
    {
        HAL_RTC_AlarmIRQHandler(ghrtc);
    }
}
