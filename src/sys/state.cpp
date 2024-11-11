#include "sys/state.hpp"

#include <cstdint>


Sys::State::State()
{

}

Sys::State::~State()
{

}

void Sys::State::Register_LED_Red(uint32_t pIndex)
{
    this->LED_Red_Index = pIndex;
}

uint32_t Sys::State::Fetch_LED_Red()
{
    return this->LED_Red_Index;
}

void Sys::State::Register_LED_Green(uint32_t pIndex)
{
    this->LED_Green_Index = pIndex;
}

uint32_t Sys::State::Fetch_LED_Green()
{
    return this->LED_Green_Index;
}

void Sys::State::Register_LED_Blue(uint32_t pIndex)
{
    this->LED_Blue_Index = pIndex;
}

uint32_t Sys::State::Fetch_LED_Blue()
{
    return this->LED_Blue_Index;
}
