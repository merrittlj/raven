/*
 * filename:	main.cpp
 * date:	07.02.24
 * author:	Lucas Merritt/merrittlj
 * description:	Main and init
 */

#include "main.h"


static void init_sysclk();
static void init_periphclk();

extern "C" void _init() {}
int main()
{
	/* Reset of all peripherals, initializes the flash interface and SysTick */
	HAL_Init();

	init_sysclk();
	init_periphclk();

    GPIO_InitTypeDef gpio_blue;
    gpio_blue.Pin = GPIO_PIN_5;
    gpio_blue.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_blue.Pull = GPIO_PULLUP;
    gpio_blue.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_blue);

    GPIO_InitTypeDef gpio_green;
    gpio_green.Pin = GPIO_PIN_0;
    gpio_green.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_green.Pull = GPIO_PULLUP;
    gpio_green.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_green);

    GPIO_InitTypeDef gpio_red;
    gpio_red.Pin = GPIO_PIN_1;
    gpio_red.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_red.Pull = GPIO_PULLUP;
    gpio_red.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_red);

	for (;;) {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
        HAL_Delay(100);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
        HAL_Delay(100);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
        HAL_Delay(500);
    }
}

static void init_sysclk()
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/* Configure the main internal regulator output voltage */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Initializes the RCC Oscillators according to the specified parameters in the RCC_OscInitTypeDef structure */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) Error_Handler();

	/* Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK4|RCC_CLOCKTYPE_HCLK2
				      |RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
				      |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.AHBCLK4Divider = RCC_SYSCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) Error_Handler();

    __HAL_RCC_GPIOB_CLK_ENABLE();
}

static void init_periphclk()
{
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

	/* Initializes the peripherals clock */
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS;
	PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSI;
	PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE1;

	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) Error_Handler();
}

void Error_Handler()
{
	/* Add implementation to report the HAL error return state */
	__disable_irq();
	for (;;);
}

#ifdef	USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{
	/* Add implementation to report the file name and line number,
	ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}

#endif /* USE_FULL_ASSERT */
