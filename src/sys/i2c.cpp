#include "sys/i2c.hpp"


namespace Sys
{
    I2C_Controller::I2C_Controller()
    {}

    I2C_Controller::I2C_Controller(I2C_HandleTypeDef *handle, uint8_t address, GPIO::Controller *gpio, I2C_Manager i2cM)
    {
        i2c = handle;
        addr = address;
        gpioCtrl = gpio;
        manager = i2cM;
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

        writeRegister(reg, &write);
    }

    bool I2C_Controller::writeRegister(uint8_t reg, uint8_t data[])
    {
        if (HAL_I2C_Mem_Write(&i2c, addr, reg, 1, &data, 1, 1000) != HAL_OK) return false;
        else return true;
    }

    // This generic function reads an eight bit register. It takes the register's
    // address as its' parameter.
    uint8_t I2C_Controller::readRegister(uint8_t reg)
    {
        uint8_t data;
        if (HAL_I2C_Mem_Read(&i2c, addr, reg, 1, &data, 1, 1000) != HAL_OK) Sys::Error_Handler();
        return data;
    }

    // Consecutive Write Mode: I2C_WR_MODE = 0
    // Allows for n-number of writes on consecutive registers, beginning at the
    // given register.
    // This particular write does not care what is currently in the register and
    // overwrites whatever is there.
    bool I2C_Controller::writeConsReg(uint8_t regs[], size_t numWrites)
    {
        writeRegister(CIF_I2C1, 0x7F, 0, 7);

        for (size_t i = 0; i <= numWrites; ++i)
        {
            HAL_StatusTypeDef regTransmit = HAL_I2C_Master_Transmit(i2c, addr, regs[i], 1, 1000);
            if (regTransmit != HAL_OK) return false;
        }

        return true;
    }

    // Non-Consecutive Write Mode: I2C_WR_MODE = 1
    // Allows for n-number of writes on non-consecutive registers, beginning at the
    // given register but able to jump locations by giving another address.
    // This particular write does not care what is currently in the register and
    // overwrites whatever is there.
    bool I2C_Controller::writeNonConsReg(uint8_t regs[], size_t numWrites)
    {
        writeRegister(CIF_I2C1, 0x7F, 1, 7);

        for (size_t i = 0; i <= numWrites; ++i)
        {
            // Here's to hoping that the register pointer will indeed jump locations as
            // advertised.
            HAL_StatusTypeDef regTransmit = HAL_I2C_Master_Transmit(i2c, addr, regs[i], 1, 1000);
            if (regTransmit != HAL_OK) return false;
        }

        return true;
    }

    bool I2C_Controller::writeWaveFormMemory(uint8_t waveFormArray[], size_t numSnippets)
    {
        HAL_StatusTypeDef snippetsTransmit = HAL_I2C_Master_Transmit(i2c, addr, (uint16_t)numSnippets, 1, 1000);  /* Move pointer to register */
        if (snippetsTransmit != HAL_OK) return false;
        for (size_t i = BEGIN_SNP_MEM; i < TOTAL_MEM_REGISTERS; ++i)
        {
            HAL_StatusTypeDef regTransmit = HAL_I2C_Master_Transmit(i2c, addr, waveFormArray[i], 1, 1000);
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
