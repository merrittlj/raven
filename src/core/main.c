/*
 * filename:	main.c
 * date:	07.01.24
 * author:	Lucas Merritt/merrittlj
 * description:	Program core.
 */

#include <stdint.h>

#include "stm32wb55xx.h"

#include "main.h"
#include "prog.h"
#include "hal.h"
#include "state.h"
#include "seg.h"
#include "tfp.h"


void SystemInit(void)
{
	s_ticks = 0;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
	SysTick_Config(FREQ / 1000);
	NVIC_SetPriority(SysTick_IRQn, 0);
}

int main()
{
	uint32_t debounce_timer, debounce_period = 20;
	uint32_t idle_timer, idle_period = 10000;
	uint8_t is_idle = 0;
	uint32_t seg_timer, seg_period = 5;
	uint32_t status_timer, status_period = 5000;

	uint8_t button_pressed = 0;
	gpio_set_mode(STATEBTN_PIN, GPIO_MODE_INPUT);
	
	gpio_set_mode(SHIFT_SER_PIN, GPIO_MODE_OUTPUT);
	gpio_set_mode(SHIFT_RCLK_PIN, GPIO_MODE_OUTPUT);
	gpio_set_mode(SHIFT_SRCLK_PIN, GPIO_MODE_OUTPUT);
	
	gpio_set_mode(DP1_PIN, GPIO_MODE_OUTPUT);
	gpio_set_mode(DP2_PIN, GPIO_MODE_OUTPUT);
	gpio_set_mode(DP3_PIN, GPIO_MODE_OUTPUT);
	gpio_set_mode(DP4_PIN, GPIO_MODE_OUTPUT);

	gpio_set_mode(STATUS_PIN, GPIO_MODE_OUTPUT);
	gpio_write(STATUS_PIN, GPIO_OUTPUT_SET);
	
	uart_init(USART1, 9600);
		
	struct fsm machine;
	fsm_init(&machine, DEFAULT_FSM, STATE_MAX_SPEED);
	
	tfp_printf("\r\n\r\n[prog] ready to run!\r\n");
	for (;;) {
		/* To prevent debounce, simply poll the button every 50ms or so. */
		if (timer_expired(&debounce_timer, debounce_period, s_ticks)) {
			if (!gpio_read(STATEBTN_PIN) && !button_pressed) {  /* Button input is pull-up. */
				button_pressed = 1;
				/* Capture first button press and re-do the action. */
				if (is_idle) {
					is_idle = 0;
					enable_timer(&idle_timer, &idle_period, 10000, s_ticks);
					fsm_action(&machine);
					tfp_printf("[idle] disabling idle mode\r\n");
					continue;
				}

				idle_timer = s_ticks + idle_period;
				fsm_next(&machine);
			} else if (gpio_read(STATEBTN_PIN)) button_pressed = 0;
		}
		if (timer_expired(&idle_timer, idle_period, s_ticks) && !is_idle) {
			is_idle = 1;
			gpio_write(LED_RED_PIN, GPIO_OUTPUT_CLEAR);
			gpio_write(LED_GREEN_PIN, GPIO_OUTPUT_CLEAR);
			gpio_write(LED_BLUE_PIN, GPIO_OUTPUT_CLEAR);
			seg_clear_output();
			disable_timer(&idle_period);
			tfp_printf("[idle] enabling idle mode\r\n");
		}
		if (timer_expired(&seg_timer, seg_period, s_ticks) && !is_idle) {
			seg_display_next();
		}
		if (timer_expired(&status_timer, status_period, s_ticks)) {
			uint8_t led_on = gpio_read(STATUS_PIN);
			
			gpio_write(STATUS_PIN, led_on ^ 1);
			tfp_printf("[heartbeat] LED = %d, tick = %lu\r\n", led_on, s_ticks);
		}
	}

	return 0;
}

void WWDG_IRQHandler() {}
void USB_IRQHandler() {}
void USART3_4_IRQHandler() {}
void USART2_IRQHandler() {}
void USART1_IRQHandler() {}
void TSC_IRQHandler() {}
void TIM7_IRQHandler() {}
void TIM6_DAC_IRQHandler() {}
void TIM3_IRQHandler() {}
void TIM2_IRQHandler() {}
void TIM1_CC_IRQHandler() {}
void TIM1_BRK_UP_TRG_COM_IRQHandler() {}
void TIM17_IRQHandler() {}
void TIM16_IRQHandler() {}
void TIM15_IRQHandler() {}
void TIM14_IRQHandler() {}
void SVC_Handler() {}
void SPI2_IRQHandler() {}
void SPI1_IRQHandler() {}
void RTC_IRQHandler() {}
void RCC_CRS_IRQHandler() {}
void PendSV_Handler() {}
void PVD_VDDIO2_IRQHandler() {}
void NMI_Handler() {}
void I2C2_IRQHandler() {}
void I2C1_IRQHandler() {}
void HardFault_Handler() {}
