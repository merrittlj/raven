#include "sys/state.hpp"

#include "sys/sys.hpp"
#include "app/common.hpp"
#include "display/controller.hpp"
#include "services/music.hpp"
#include "services/custom_image.hpp"
#include "ble/uuid.hpp"

#include "lvgl.h"

#include <cstddef>
#include <bitset>


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

    TimeInfo State::Get_Time()
    {
        return Display::Controller::Instance()->Get_RTC();
    }

    void State::Set_Time(TimeInfo value)
    {
        Display::Controller::Instance()->Set_RTC(value);
    }

    void State::Display_Time()
    {
        Display::Controller::Instance()->Time(Get_Time());
    }

    WeatherInfo State::Get_Weather()
    {
        return weather;
    }

    void State::Set_Weather(WeatherInfo value)
    {
        weather = value;
    }

    void State::Screens_Clear()
    {
        screens.fill(0);
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

    std::array<uint8_t, (size_t)Screen::Enum_Length> State::Get_Screens()
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

    void State::Alert_Trigger()
    {
        alerts.push_back(Alert_Builder);
        Display::Controller::Instance()->Alert_Send(alerts.back());
        /* Alert_Builder = {"", "", ""}; */
    }

    void State::Alert_Dismiss(size_t index)
    {
        alerts.erase(alerts.begin() + index);
    }

    std::vector<AlertInfo> *State::Get_Alerts()
    {
        return &alerts;
    }

    void State::Event_Build_Type(uint8_t value)
    {
        Event_Builder.type = value;
    }

    void State::Event_Build_Id(uint64_t value)
    {
        Event_Builder.id = value;
    }

    void State::Event_Build_Title(std::string str)
    {
        Event_Builder.title = str;
    }

    void State::Event_Build_Desc(std::string str)
    {
        Event_Builder.desc = str;
    }

    void State::Event_Build_Time(std::string value)
    {
        Event_Builder.time = value;
    }

    void State::Event_Build_RepDur(std::string value)
    {
        Event_Builder.repDur = value;
    }

    void State::Event_Trigger()
    {
        /* If trigger is used, this is in alert mode */
        Event_Builder.mode = 0;
        events.push_back(Event_Builder);
        Display::Controller::Instance()->Event_Send(events.back());
        /* Event_Builder = {0, 0, "", "", 0, 0}; */
    }

    void State::Event_Dismiss(size_t index)
    {
        events.erase(events.begin() + index);
    }

    std::vector<EventInfo> State::Get_Events()
    {
        return events;
    }

    void State::Nav_Build_Instruction(std::string str)
    {
        Nav_Builder.instruction = str;
    }

    void State::Nav_Build_Distance(std::string str)
    {
        Nav_Builder.distance = str;
    }

    void State::Nav_Build_ETA(std::string str)
    {
        Nav_Builder.eta = str;
    }

    void State::Nav_Build_Action(std::string str)
    {
        Nav_Builder.action = str;
    }

    void State::Nav_Trigger()
    {
        Display::Controller::Instance()->Nav_Send(Nav_Builder);
        /* Nav_Builder = {"", "", "", ""}; */
    }

    void State::Music_Build_Artist(std::string str)
    {
        Music_Builder.artist = str;
    }

    void State::Music_Build_Track(std::string str)
    {
        Music_Builder.track = str;
    }

    void State::Music_Build_Album(std::string str)
    {
        Music_Builder.album = str;
    }

    void State::Music_Build_Album_Art(uint8_t *arr, size_t length)
    {
       bool isComplete = musicAlbumArtHandler.ProcessChunk(arr, length);
    
        // Update the ready characteristic
        BLE::MusicService *musicService = BLE::MusicService::Instance();
        uint8_t readyData = musicAlbumArtHandler.GetReadyStatus();
        
        if (musicService->Update_Char_Value(
                BLE::UUID::ExtractUUID16FromLE(musicService->ready.Get_UUID()),
                musicService->ready.Get_Value_Length(),
                &readyData) != BLE_STATUS_SUCCESS)
            Sys::Error_Handler();
        
        // Reset for next image if complete
        if (isComplete) {
            Music_Builder.imageSize = musicAlbumArtHandler.GetImageSize();
            Music_Builder.albumArt = musicAlbumArtHandler.GetImageData();
            Display::Controller::Instance()->Music_Send(Music_Builder);

            musicAlbumArtHandler.Reset();
        } 
    }

    void State::Custom_Image_Build(uint8_t *arr, size_t length)
    {
        bool isComplete = customImageHandler.ProcessChunk(arr, length);

        // Update the ready characteristic
        BLE::CustomImageService *customImageService = BLE::CustomImageService::Instance();
        uint8_t readyData = customImageHandler.GetReadyStatus();
        
        if (customImageService->Update_Char_Value(
                BLE::UUID::ExtractUUID16FromLE(customImageService->ready.Get_UUID()),
                customImageService->ready.Get_Value_Length(),
                &readyData) != BLE_STATUS_SUCCESS)
            Sys::Error_Handler();

        
        if (isComplete) {
            CustomImageInfo info;
            info.imageSize = customImageHandler.GetImageSize(),
            info.image = customImageHandler.GetImageData(),
            Display::Controller::Instance()->Custom_Image_Send(info);

            customImageHandler.Reset();
        }
    }
    
    void State::Register_LED_Batt(uint32_t pIndex)
    {
        this->LED_Batt_Index = pIndex;
    }

    uint32_t State::Fetch_LED_Batt()
    {
        return this->LED_Batt_Index;
    }

    void State::Register_LED_F1(uint32_t pIndex)
    {
        this->LED_F1_Index = pIndex;
    }

    uint32_t State::Fetch_LED_F1()
    {
        return this->LED_F1_Index;
    }

    void State::Register_LED_F2(uint32_t pIndex)
    {
        this->LED_F2_Index = pIndex;
    }

    uint32_t State::Fetch_LED_F2()
    {
        return this->LED_F2_Index;
    }
    }
