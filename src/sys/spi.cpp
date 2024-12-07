#include "sys/spi.hpp"

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
    HAL_SPI_Transmit(spi, &value, 1, 1000);
}

void Sys::SPIController::WriteBytes(uint8_t *value, uint16_t len)
{
    /* 1(1000ms) second timeout */
    HAL_SPI_Transmit(spi, value, len, 1000);
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
    HAL_Delay(200);
    gpioCtrl->Write_Component(manager.rst, RESET);
    HAL_Delay(2);
    gpioCtrl->Write_Component(manager.rst, SET);
    HAL_Delay(200);
}

void Sys::SPIController::BlockBusy()
{
    while (gpioCtrl->Read_Component(manager.busy) == SET)
        HAL_Delay(10);
}
