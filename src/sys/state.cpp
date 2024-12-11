#include "sys/state.hpp"

#include "app/common.hpp"
#include "display/display.hpp"

#include <cstdint>


Sys::State::State()
{}

Sys::State::~State()
{}

Sys::State::Flag_Val Sys::State::App_Flag_Get(App_Flag flag)
{
    return (Sys::State::Flag_Val)VariableBit_Get_BB((uint32_t)&(this->App_State), (uint8_t)flag);
}

void Sys::State::App_Flag_Set(App_Flag flag)
{
    VariableBit_Set_BB((uint32_t)&(this->App_State), (uint8_t)flag);
}

void Sys::State::App_Flag_Reset(App_Flag flag)
{
    VariableBit_Reset_BB((uint32_t)&(this->App_State), (uint8_t)flag);
}

void Sys::State::Set_Time(Time value)
{
    Current_Time = value;
}

void Sys::State::Update_Time(Time value)
{
    Set_Time(value);
    Display::Controller::Instance()->Update_Time(value);
}

void Sys::State::Alert_Build_Source(std::string str)
{
    Current_Alert.source = str;
}

void Sys::State::Alert_Build_Title(std::string str)
{
    Current_Alert.title = str;
}

void Sys::State::Alert_Build_Body(std::string str)
{
    Current_Alert.body = str;
}

void Sys::State::Alert_Send()
{
    Display::Controller::Instance()->Alert_Send(Current_Alert);
    Current_Alert = {"", "", ""};
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
