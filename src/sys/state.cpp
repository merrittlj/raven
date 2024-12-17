#include "sys/state.hpp"

#include "app/common.hpp"
#include "display/controller.hpp"

#include "lvgl.h"

#include <cstdint>


void Sys::Preferences::Color_Scheme(Scheme scheme)
{
    if (scheme == Scheme::LIGHT) {
        userWhite = lv_color_hex(0xffffff);
        userBlack = lv_color_hex(0x000000);
    } else if (scheme == Scheme::DARK) {
        userWhite = lv_color_hex(0x000000);
        userBlack = lv_color_hex(0xffffff);
    }
}

Sys::State::State()
{
    pref.Color_Scheme(Scheme::LIGHT);
}

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

Sys::Preferences *Sys::State::Get_Pref()
{
    return &pref;
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
    Alert_Builder.source = str;
}

void Sys::State::Alert_Build_Title(std::string str)
{
    Alert_Builder.title = str;
}

void Sys::State::Alert_Build_Body(std::string str)
{
    Alert_Builder.body = str;
}

void Sys::State::Alert_Send()
{
    alerts.push_back(Alert_Builder);
    Display::Controller::Instance()->Alert_Send(alerts.back());
    Alert_Builder = {"", "", ""};
}


void Sys::State::Alert_Dismiss()
{
    alerts.pop_back();
}

std::vector<Sys::Alert> *Sys::State::Get_Alerts()
{
    return &alerts;
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
