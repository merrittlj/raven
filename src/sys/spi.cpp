#include "sys/spi.hpp"

#include "sys/sys.hpp"

#include "stm32wbxx_hal.h"


Sys::SPIController::SPIController()
{

}

Sys::SPIController::SPIController(SPI_HandleTypeDef *handle, GPIO::Controller *gpio, SPIManager spiM)
{
    this->spi = handle;
    this->gpioCtrl = gpio;
    this->manager = spiM;
}


void Sys::SPIController::WriteByte(uint8_t value)
{
    /* 1(1000ms) second timeout */
    HAL_StatusTypeDef ret = HAL_SPI_Transmit(spi, &value, 1, 1000);
    if (ret != HAL_OK)
        Error_Handler();
}

void Sys::SPIController::WriteBytes(uint8_t *value, uint16_t len)
{
    /* 1(1000ms) second timeout */
    HAL_StatusTypeDef ret = HAL_SPI_Transmit(spi, value, len, 1000);
    if (ret != HAL_OK)
        Error_Handler();
}

void Sys::SPIController::SendCommand(uint8_t reg)
{
    gpioCtrl->Write_Component(manager.dc, RESET);
    gpioCtrl->Write_Component(manager.cs, RESET);
    WriteByte(reg);
    gpioCtrl->Write_Component(manager.cs, SET);
}

void Sys::SPIController::SendData(uint8_t data)
{
    gpioCtrl->Write_Component(manager.dc, SET);
    gpioCtrl->Write_Component(manager.cs, RESET);
    WriteByte(data);
    gpioCtrl->Write_Component(manager.cs, SET);
}

void Sys::SPIController::Reset()
{
    gpioCtrl->Write_Component(manager.rst, SET);
    HAL_Delay(20);
    gpioCtrl->Write_Component(manager.rst, RESET);
    HAL_Delay(5);
    gpioCtrl->Write_Component(manager.rst, SET);
    HAL_Delay(20);
}

void Sys::SPIController::BlockBusy()
{
    while (gpioCtrl->Read_Component(manager.busy) == SET)
        HAL_Delay(10);
}

extern "C" {
    /**
     * @brief SPI MSP Initialization
     * This function configures the hardware resources used in this example
     * @param hspi: SPI handle pointer
     * @retval None
     */
    void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
    {
        GPIO_InitTypeDef GPIO_InitStruct = { 0 };
        if(hspi->Instance == SPI1)
        {
            /* Peripheral clock enable */
            __HAL_RCC_SPI1_CLK_ENABLE();

            __HAL_RCC_GPIOA_CLK_ENABLE();
            /**SPI1 GPIO Configuration
              PA1     ------> SPI1_SCK
              PA7     ------> SPI1_MOSI
              */
            GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7;
            GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            /* GPIO_InitStruct.Pull = GPIO_NOPULL; */
            /* GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; */
            GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        }
    }

    /**
     * @brief SPI MSP De-Initialization
     * This function freeze the hardware resources used in this example
     * @param hspi: SPI handle pointer
     * @retval None
     */
    void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
    {
        if(hspi->Instance == SPI1)
        {
            /* Peripheral clock disable */
            __HAL_RCC_SPI1_CLK_DISABLE();

            /**SPI1 GPIO Configuration
              PA1     ------> SPI1_SCK
              PA7     ------> SPI1_MOSI
              */
            HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_7);
        }
    }
}
