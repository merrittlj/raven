/*
 * filename:	main.h
 * date:	07.02.24
 * author:	Lucas Merritt/merrittlj
 * description:	main.c functions
 */

#ifndef MAIN_HPP
#define MAIN_HPP

#include "stm32wbxx_hal.h"


void Error_Handler(void);

#define RAM_BASE 0x20000000
#define RAM_BB_BASE 0x22000000
#define VariableBit_Reset_BB(VariableAddress, BitNumber) \
(*(volatile uint32_t *) (RAM_BB_BASE | ((VariableAddress - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0)
#define VariableBit_Set_BB(VariableAddress, BitNumber) \
(*(volatile uint32_t *) (RAM_BB_BASE | ((VariableAddress - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1)
#define VariableBit_Get_BB(VariableAddress, BitNumber) \
(*(volatile uint32_t *) (RAM_BB_BASE | ((VariableAddress - RAM_BASE) << 5) | ((BitNumber) << 2)))

#endif /* MAIN_HPP */
