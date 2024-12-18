#include "sys/state.hpp"

#include "app/common.hpp"
#include "display/controller.hpp"

#include "lvgl.h"

#include <cstddef>


namespace Sys
{
    State::State()
    {
        pref.scheme = Scheme::LIGHT;
    }

    State::~State()
    {}

    State::Flag_Val State::App_Flag_Get(App_Flag flag)
    {
        return (State::Flag_Val)VariableBit_Get_BB((uint32_t)&(this->App_State), (uint8_t)flag);
    }

    void State::App_Flag_Set(App_Flag flag)
    {
        VariableBit_Set_BB((uint32_t)&(this->App_State), (uint8_t)flag);
    }

    void State::App_Flag_Reset(App_Flag flag)
    {
        VariableBit_Reset_BB((uint32_t)&(this->App_State), (uint8_t)flag);
    }

    Preferences *State::Get_Pref()
    {
        return &pref;
    }

    void State::Set_Time(TimeInfo value)
    {
        Current_Time = value;
    }

    void State::Update_Time(TimeInfo value)
    {
        Set_Time(value);
        Display::Controller::Instance()->Update_Time(value);
    }

    void State::Screen_Activate(Screen s)
    {
        screens.at((size_t)s) = 1;
    }

    void State::Screen_Deactivate(Screen s)
    {
        screens.at((size_t)s) = 0;
    }

    uint8_t State::Is_Screen_Active(Screen s)
    {
        return screens.at((size_t)s);
    }

    std::array<uint8_t, (size_t)Screen::Enum_Length> State::Get_Active_Screens()
    {
        return screens;
    }

    void State::Alert_Build_Source(std::string str)
    {
        Alert_Builder.source = str;
    }

    void State::Alert_Build_Title(std::string str)
    {
        Alert_Builder.title = str;
    }

    void State::Alert_Build_Body(std::string str)
    {
        Alert_Builder.body = str;
    }

    void State::Alert_Send()
    {
        alerts.push_back(Alert_Builder);
        Display::Controller::Instance()->Alert_Send(alerts.back());
        Alert_Builder = {"", "", ""};
    }

    void State::Alert_Dismiss()
    {
        alerts.pop_back();
    }

    std::vector<AlertInfo> *State::Get_Alerts()
    {
        return &alerts;
    }

    void State::Register_LED_Red(uint32_t pIndex)
    {
        this->LED_Red_Index = pIndex;
    }

    uint32_t State::Fetch_LED_Red()
    {
        return this->LED_Red_Index;
    }

    void State::Register_LED_Green(uint32_t pIndex)
    {
        this->LED_Green_Index = pIndex;
    }

    uint32_t State::Fetch_LED_Green()
    {
        return this->LED_Green_Index;
    }

    void State::Register_LED_Blue(uint32_t pIndex)
    {
        this->LED_Blue_Index = pIndex;
    }

    uint32_t State::Fetch_LED_Blue()
    {
        return this->LED_Blue_Index;
    }
}
