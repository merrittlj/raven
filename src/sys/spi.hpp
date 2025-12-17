#ifndef SPI_HPP
#define SPI_HPP


#include "hw/if.hpp"

#include "FreeRTOS.h" /* Must come first. */
#include "task.h" /* RTOS task related API prototypes. */

#include <cstddef>
#include <cstdint>
#include <functional>


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

            std::function<void()> busyCallback;
            TaskHandle_t busyTaskHandle;
    
            static void BusyPollTask(void* params);

        public:
            SPI_Manager manager;

            SPI_Controller();
            SPI_Controller(SPI_HandleTypeDef *handle, SPI_Manager spiM);

            void WriteByte(uint8_t value);
            void WriteBytes(uint8_t *value, uint16_t len);
            void SendCommand(uint8_t reg);
            void SendData(uint8_t data);
            void Reset();

            void BlockBusy();
            void BlockBusyAsync(std::function<void()> callback);

            void Enable();
            void Disable();
    };
}

extern "C" {
    void HAL_SPI_MspInit(SPI_HandleTypeDef *spiHandle);
    void HAL_SPI_MspDeInit(SPI_HandleTypeDef *spiHandle);
}


#endif /* SPI_HPP */
