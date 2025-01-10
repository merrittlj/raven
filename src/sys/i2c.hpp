#ifndef I2C_HPP
#define I2C_HPP


#include <cstddef>


namespace Sys
{
    struct I2C_Manager {
        uint8_t scl;
        uint8_t sda;
    };

    class I2C_Controller
    {
        private:
            I2C_HandleTypeDef *i2c;
            uint8_t addr;
            GPIO::Controller *gpioCtrl;
            I2C_Manager manager;

        public:
            I2C_Controller();
            I2C_Controller(I2C_HandleTypeDef *handle, uint8_t address, GPIO::Controller *gpio, I2C_Manager i2cM);

            // This generic function handles I2C write commands for modifying individual
            // bits in an eight bit register. Paramaters include the register's address, a mask
            // for bits that are ignored, the bits to write, and the bits' starting
            // position.
            bool writeRegister(uint8_t reg, uint8_t mask, uint8_t bits, uint8_t pos);
            bool writeRegister(uint8_t reg, uint8_t data[]);

            // Consecutive Write Mode: I2C_WR_MODE = 0
            // Allows for n-number of writes on consecutive registers, beginning at the
            // given register.
            // This particular write does not care what is currently in the register and
            // overwrites whatever is there.
            bool writeConsReg(uint8_t regs[], size_t);

            // Non-Consecutive Write Mode: I2C_WR_MODE = 1
            // Allows for n-number of writes on non-consecutive registers, beginning at the
            // given register but able to jump locations by giving another address.
            // This particular write does not care what is currently in the register and
            // overwrites whatever is there.
            bool writeNonConsReg(uint8_t regs[], size_t);

            bool writeWaveFormMemory(uint8_t waveFormArray[], size_t numSnippets);

            // This generic function reads an eight bit register. It takes the register's
            // address as its' parameter.
            uint8_t readRegister(uint8_t);

            bool readConsReg(uint8_t regs[], size_t);
            bool readNonConsReg(uint8_t regs[], size_t);
    }
}

extern "C" {
    void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
    void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c);
}


#endif  /* I2C_HPP */
