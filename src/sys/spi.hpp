#ifndef SPI_HPP
#define SPI_HPP


#include "gpio/gpio.hpp"

#include <cstddef>


namespace Sys
{
    struct SPI_Manager
    {
        uint8_t busy;
        uint8_t rst;
        uint8_t dc;
        uint8_t cs;
        uint8_t pwr;
    };

    class SPI_Controller
    {
        private:
            SPI_HandleTypeDef *spi;
            GPIO::Controller *gpioCtrl;
            SPI_Manager manager;

        public:
            SPI_Controller();
            SPI_Controller(SPI_HandleTypeDef *handle, GPIO::Controller *gpio, SPI_Manager spiM);

            void WriteByte(uint8_t value);
            void WriteBytes(uint8_t *value, uint16_t len);
            void SendCommand(uint8_t reg);
            void SendData(uint8_t data);
            void Reset();
            void BlockBusy();

            void Enable();
            void Disable();
    };
}

extern "C" {
    void HAL_SPI_MspInit(SPI_HandleTypeDef *spiHandle);
    void HAL_SPI_MspDeInit(SPI_HandleTypeDef *spiHandle);
}


#endif /* SPI_HPP */
