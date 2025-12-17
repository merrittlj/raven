#include "sys/spi.hpp"

#include "sys/sys.hpp"
#include "gpio/gpio.hpp"

#include "stm32wbxx_hal.h"


Sys::SPI_Controller::SPI_Controller() : busyCallback(nullptr), busyTaskHandle(nullptr)
{

}

Sys::SPI_Controller::SPI_Controller(SPI_HandleTypeDef *handle, SPI_Manager spiM) : busyCallback(nullptr), busyTaskHandle(nullptr)
{
    this->spi = handle;
    this->manager = spiM;
}

void Sys::SPI_Controller::WriteByte(uint8_t value)
{
    /* 1(1000ms) second timeout */
    HAL_StatusTypeDef ret = HAL_SPI_Transmit(spi, &value, 1, 1000);
    if (ret != HAL_OK)
        Error_Handler();
}

void Sys::SPI_Controller::WriteBytes(uint8_t *value, uint16_t len)
{
    /* 1(1000ms) second timeout */
    HAL_StatusTypeDef ret = HAL_SPI_Transmit(spi, value, len, 1000);
    if (ret != HAL_OK)
        Error_Handler();
}

void Sys::SPI_Controller::SendCommand(uint8_t reg)
{
    GPIO::Controller *gpioCtrl = GPIO::Controller::Instance();
    gpioCtrl->Write_Component(manager.dc, RESET);
    gpioCtrl->Write_Component(manager.cs, RESET);
    WriteByte(reg);
    gpioCtrl->Write_Component(manager.cs, SET);
}

void Sys::SPI_Controller::SendData(uint8_t data)
{
    GPIO::Controller *gpioCtrl = GPIO::Controller::Instance();
    gpioCtrl->Write_Component(manager.dc, SET);
    gpioCtrl->Write_Component(manager.cs, RESET);
    WriteByte(data);
    gpioCtrl->Write_Component(manager.cs, SET);
}

void Sys::SPI_Controller::Reset()
{
    GPIO::Controller *gpioCtrl = GPIO::Controller::Instance();
    gpioCtrl->Write_Component(manager.rst, SET);
    gpioCtrl->Write_Component(manager.rst, RESET);
    Delay(10);
    gpioCtrl->Write_Component(manager.rst, SET);
    Delay(10);
}

void Sys::SPI_Controller::BusyPollTask(void* params)
{
    Sys::SPI_Controller *self = static_cast<Sys::SPI_Controller*>(params);
    GPIO::Controller *gpioCtrl = GPIO::Controller::Instance();
    
    // Poll until busy clears
    while (gpioCtrl->Read_Component(self->manager.busy) == SET) {
        vTaskDelay(pdMS_TO_TICKS(10));  // Check every 10ms
    }
    
    // Busy cleared - execute callback
    if (self->busyCallback) {
        self->busyCallback();
        self->busyCallback = nullptr;
    }
    
    // Delete this task
    self->busyTaskHandle = nullptr;
    vTaskDelete(NULL);
}

void Sys::SPI_Controller::BlockBusy()
{
    GPIO::Controller *gpioCtrl = GPIO::Controller::Instance();
    while (gpioCtrl->Read_Component(manager.busy) == SET)
        Delay(10);
}

void Sys::SPI_Controller::BlockBusyAsync(std::function<void()> callback)
{
    busyCallback = callback;

    xTaskCreate(
        BusyPollTask,           // Task function
        "BusyPoll",            // Name
        2048,                   // Stack size (words)
        this,                // Parameter
        tskIDLE_PRIORITY + 1,  // Priority
        &busyTaskHandle        // Task handle
    );
}

void Sys::SPI_Controller::Enable()
{
    GPIO::Controller *gpioCtrl = GPIO::Controller::Instance();
    gpioCtrl->Write_Component(manager.pwr, SET);
}

void Sys::SPI_Controller::Disable()
{
    GPIO::Controller *gpioCtrl = GPIO::Controller::Instance();
    gpioCtrl->Write_Component(manager.pwr, RESET);
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
              PA5     ------> SPI1_SCK
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
              PA5     ------> SPI1_SCK
              PA7     ------> SPI1_MOSI
              */
            HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_7);
        }
    }
}
