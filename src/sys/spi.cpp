#include "sys/spi.hpp"

#include "stm32wbxx_hal.h"


Sys::SPIController::SPIController()
{

}

Sys::SPIController::SPIController(GPIO::Controller *gpio, SPIManager spiM)
{
    this->gpioCtrl = gpio;
    this->manager = spiM;
}

void Sys::SPIController::SendCommand(uint8_t reg)
{
    gpioCtrl->Write_Component(manager.dc, RESET);
    gpioCtrl->Write_Component(manager.cs, RESET);
    /* Write SPI Byte */
    gpioCtrl->Write_Component(manager.cs, SET);
}

void Sys::SPIController::SendData(uint8_t data)
{
    gpioCtrl->Write_Component(manager.dc, SET);
    gpioCtrl->Write_Component(manager.cs, RESET);
    /* Write SPI Byte */
    gpioCtrl->Write_Component(manager.cs, SET);
}

void Sys::SPIController::ResetDevice()
{
    gpioCtrl->Write_Component(manager.rst, SET);
    HAL_Delay(200);
    gpioCtrl->Write_Component(manager.rst, RESET);
    HAL_Delay(2);
    gpioCtrl->Write_Component(manager.rst, SET);
    HAL_Delay(200);
}

void Sys::SPIController::DelayBusy()
{
    while (gpioCtrl->Read_Component(manager.busy) == SET)
        HAL_Delay(10);
}
