#ifndef I2C_HPP
#define I2C_HPP


#include "gpio/gpio.hpp"

#include <cstddef>
#include <cstdint>

#include "stm32wbxx_hal.h"


namespace Sys
{
    class I2C_Controller
    {
        private:
            I2C_HandleTypeDef *i2c;
            uint8_t addr;
            GPIO::Controller *gpioCtrl;

        public:
            I2C_Controller();
            I2C_Controller(I2C_HandleTypeDef *handle, uint8_t address, GPIO::Controller *gpio);

            // This generic function handles I2C write commands for modifying individual
            // bits in an eight bit register. Paramaters include the register's address, a mask
            // for bits that are ignored, the bits to write, and the bits' starting
            // position.
            bool writeRegister(uint8_t reg, uint8_t mask, uint8_t bits, uint8_t pos);
            bool writeRegister(uint8_t reg, uint8_t data[]);

            bool writeWaveFormMemory(uint8_t waveFormArray[], uint8_t numSnippetsReg, size_t begin, size_t end);

            // This generic function reads an eight bit register. It takes the register's
            // address as its' parameter.
            uint8_t readRegister(uint8_t);

            bool readConsReg(uint8_t regs[], size_t);
            bool readNonConsReg(uint8_t regs[], size_t);
    };
}

extern "C" {
    void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
    void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c);
}


#endif  /* I2C_HPP */
