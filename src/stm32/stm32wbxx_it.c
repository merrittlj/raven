/*
 * filename:	stm32wbxx_it.c
 * date:	07.02.24
 * author:	Lucas Merritt/merrittlj
 * description:	Interrupt Service Routine functions
 */

#include "main.h"
#include "stm32wbxx_it.h"


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

/* System service call via SWI instruction */
void SVC_Handler(void)
{
}

/* Debug monitor */
void DebugMon_Handler(void)
{
}

/* Pendable request for system service */
void PendSV_Handler(void)
{
}

/* SysTick timer */
void SysTick_Handler(void)
{
    HAL_IncTick();
}
