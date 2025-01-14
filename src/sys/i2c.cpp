#include "sys/i2c.hpp"
#include "sys/sys.hpp"


namespace Sys
{
    I2C_Controller::I2C_Controller()
    {}

    I2C_Controller::I2C_Controller(I2C_HandleTypeDef *handle, uint8_t address, GPIO::Controller *gpio)
    {
        i2c = handle;
        addr = address;
        gpioCtrl = gpio;
    }

    // This generic function handles I2C write commands for modifying individual
    // bits in an eight bit register. Paramaters include the register's address, a mask
    // for bits that are ignored, the bits to write, and the bits' starting
    // position.
    bool I2C_Controller::writeRegister(uint8_t reg, uint8_t mask, uint8_t bits, uint8_t pos)
    {
        uint8_t write;
        write = readRegister(reg);       // Get the current value of the register
        write &= (mask);                   // Mask the position we want to write to.
        write |= (bits << pos); // Write the given bits to the variable

        return writeRegister(reg, &write);
    }

    bool I2C_Controller::writeRegister(uint8_t reg, uint8_t data[])
    {
        if (HAL_I2C_IsDeviceReady(i2c, addr, 1, 1000) != HAL_OK) Sys::Error_Handler();
        if (HAL_I2C_Mem_Write(i2c, addr, reg, 1, data, 1, 1000) != HAL_OK) return false;
        else return true;
    }

    // This generic function reads an eight bit register. It takes the register's
    // address as its' parameter.
    uint8_t I2C_Controller::readRegister(uint8_t reg)
    {
        uint8_t data = 0;
        if (HAL_I2C_IsDeviceReady(i2c, addr, 1, 1000) != HAL_OK) Sys::Error_Handler();
        if (HAL_I2C_Mem_Read(i2c, addr, reg, 1, &data, 1, 1000) != HAL_OK) Sys::Error_Handler();
        return data;
    }

    bool I2C_Controller::writeWaveFormMemory(uint8_t waveFormArray[], uint8_t numSnippetsReg, size_t begin, size_t end)
    {
        HAL_StatusTypeDef snippetsTransmit = HAL_I2C_Master_Transmit(i2c, addr, &numSnippetsReg, 1, 1000);  /* Move pointer to register */
        if (snippetsTransmit != HAL_OK) return false;
        for (size_t i = begin; i < end; ++i)
        {
            HAL_StatusTypeDef regTransmit = HAL_I2C_Master_Transmit(i2c, addr, &waveFormArray[i], 1, 1000);
            if (regTransmit != HAL_OK) return false;
        }

        return true;
    }

    extern "C" {
        void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
        {
            GPIO_InitTypeDef GPIO_InitStruct = {0};
            RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
            if(hi2c->Instance==I2C1)
            {
                /** Initializes the peripherals clock
                */
                PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
                PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
                if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
                    Error_Handler();

                __HAL_RCC_GPIOB_CLK_ENABLE();
                /**I2C1 GPIO Configuration
                  PB8     ------> I2C1_SCL
                  PB9     ------> I2C1_SDA
                  */
                GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
                GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
                GPIO_InitStruct.Pull = GPIO_NOPULL;
                GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
                GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
                HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

                /* Peripheral clock enable */
                __HAL_RCC_I2C1_CLK_ENABLE();
            }
        }

        void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
        {
            if(hi2c->Instance==I2C1)
            {
                /* Peripheral clock disable */
                __HAL_RCC_I2C1_CLK_DISABLE();

                /**I2C1 GPIO Configuration
                  PB8     ------> I2C1_SCL
                  PB9     ------> I2C1_SDA
                  */
                HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

                HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);
            }
        }
    }
}
