#ifndef SPI_HPP
#define SPI_HPP


#include "gpio/gpio.hpp"

#include <cstddef>


namespace Sys
{
    struct SPIManager
    {
        uint8_t busy;
        uint8_t rst;
        uint8_t dc;
        uint8_t cs;
        uint8_t pwr;
    };

    class SPIController
    {
        private:
            GPIO::Controller *gpioCtrl;
            SPIManager manager;

        public:
            SPIController();
            SPIController(GPIO::Controller *gpio, SPIManager spiM);

            void SendCommand(uint8_t reg);
            void SendData(uint8_t data);
            void ResetDevice();
            void DelayBusy();
    };
}


#endif /* SPI_HPP */
