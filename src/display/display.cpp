#include "display/display.hpp"

#include "sys/spi.hpp"

#include "stm32wbxx_hal.h"


Display::EInk::EInk(Sys::SPIController ctrl)
{
    this->spi = ctrl;
}

void Display::EInk::Init()
{

}

void Display::EInk::Init_Partial()
{

}

void Display::EInk::Clear()
{

}

void Display::EInk::Display(uint8_t *image)
{

}

void Display::EInk::DisplayPartBaseImage(uint8_t *image)
{

}

void Display::EInk::DisplayPart(uint8_t *image)
{

}

void Display::EInk::Sleep()
{
    spi.SendCommand(0x10);
    spi.SendData(0x01);
    HAL_Delay(100);
}
