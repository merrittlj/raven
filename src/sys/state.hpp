#ifndef STATE_HPP
#define STATE_HPP


#include "app/common.hpp"

#include "tl.h"
#include "lvgl.h"

#include <cstddef>
#include <string>
#include <vector>
#include <array>


#define EVENT_POOL_SIZE                    (CFG_TLBLE_EVT_QUEUE_LENGTH*4U*DIVC(( sizeof(TL_PacketHeader_t) + TL_BLE_EVENT_FRAME_SIZE ), 4U))

namespace Sys
{
    enum class Screen : uint8_t {
        TAG,  /* Default active */
        FACE,  /* Default active */
        ALERT,  /* Default active */
        ACTIVE,  /* Default active */
        ALERTS_LIST,  /* Default inactive */
        EVENTS_LIST, /* Default inactive */
        NAVIGATION,  /* Default inactive */
        MUSIC,  /* Default inactive */
        ABOUT,  /* Default active */
        Enum_Length
    };

    struct TimeInfo {
        uint8_t month;
        uint8_t day;

        uint8_t hour;
        uint8_t minute;
        uint8_t second;
    };

    struct AlertInfo {
        std::string source;
        std::string title;
        std::string body;
    };

    struct EventInfo {
        uint8_t type;
        uint8_t id;
        std::string title;
        std::string desc;
        uint16_t timestamp;
        uint8_t repDur;
    };

    struct NavInfo {
        std::string instruction;
        std::string distance;
        std::string eta;
        std::string action;
    };

    struct MusicInfo {
        std::string track;
        std::string artist;
        std::string album;
        uint8_t *albumArt;  /* Make sure to initialize!(done in State) */
    };

    enum class Scheme {
        LIGHT,
        DARK
    };
    struct Preferences {
        /* Flipped/inverted when using dark mode */
        Scheme scheme;
    };

    class State
    {
        private:
            volatile uint32_t App_State = 0x00000000;

            /* Stores 0 or 1 values for if a screen is active */
            /* Not used to track current state, but rather track what stays open */
            std::array<uint8_t, (size_t)Screen::Enum_Length> screens = {};

            Preferences pref;

            TimeInfo Current_Time;

            std::vector<AlertInfo> alerts;
            AlertInfo Alert_Builder;

            std::vector<EventInfo> events;
            EventInfo Event_Builder;

            MusicInfo Music_Builder;
            const size_t capacity = 5000;
            size_t chunkOffset = 0;

            NavInfo Nav_Builder;

            /* Component index of the Red LED */
            uint32_t LED_Red_Index = 0;
            /* Component index of the Green LED */
            uint32_t LED_Green_Index = 0;
            /* Component index of the Blue LED */
            uint32_t LED_Blue_Index = 0;
        public:
            /* PLACE_IN_SECTION("MB_MEM2") ALIGN(4) static uint8_t EvtPool[EVENT_POOL_SIZE]; */
            PLACE_IN_SECTION("MB_MEM2") ALIGN(4) inline static uint8_t EvtPool[EVENT_POOL_SIZE];
            PLACE_IN_SECTION("MB_MEM2") ALIGN(4) inline static TL_CmdPacket_t SysCmdBuffer;
            PLACE_IN_SECTION("MB_MEM2") ALIGN(4) inline static TL_CmdPacket_t BLECmdBuffer;
            PLACE_IN_SECTION("MB_MEM1") ALIGN(4) inline static uint8_t SysSpareEvtBuffer[sizeof(TL_PacketHeader_t) + TL_EVT_HDR_SIZE + 255];
            PLACE_IN_SECTION("MB_MEM2") ALIGN(4) inline static uint8_t BLESpareEvtBuffer[sizeof(TL_PacketHeader_t) + TL_EVT_HDR_SIZE + 255];

            enum class App_Flag : uint8_t {
                CPU2_INITIALIZED = 0,
                WIRELESS_FW_RUNNING,
                FUS_FW_RUNNING,
                BLE_INITIALIZED,
                BLE_ADVERTISING,
                BLE_CONNECTED,
                HCI_EVENT_PENDING = 18,
                SHCI_EVENT_PENDING,
                CPU2_ERROR = 24,
                BLE_INITIALIZATION_ERROR
            };

            enum class Flag_Val : uint8_t {
                NOT_SET = 0,
                SET
            };

            State();
            ~State();

            Flag_Val App_Flag_Get(App_Flag flag);
            void App_Flag_Set(App_Flag flag);
            void App_Flag_Reset(App_Flag flag);

            Preferences *Get_Pref();

            /* Setting time, vs updating(setting & displaying) */
            void Set_Time(TimeInfo value);
            void Update_Time(TimeInfo value);

            void Screen_Activate(Screen s);
            void Screen_Deactivate(Screen s);
            /* 0 or 1 depending on if a screen is active(ran) */
            uint8_t Is_Screen_Active(Screen s);
            std::array<uint8_t, (size_t)Screen::Enum_Length> Get_Active_Screens();

            void Alert_Build_Source(std::string str);
            void Alert_Build_Title(std::string str);
            void Alert_Build_Body(std::string str);
            void Alert_Trigger();
            void Alert_Dismiss(size_t index);
            std::vector<AlertInfo> *Get_Alerts();

            void Event_Build_Type(uint8_t value);
            void Event_Build_Id(uint8_t value);
            void Event_Build_Title(std::string str);
            void Event_Build_Desc(std::string str);
            void Event_Build_Timestamp(uint16_t value);
            void Event_Build_RepDur(uint8_t value);
            void Event_Trigger();
            void Event_Dismiss(size_t index);
            std::vector<EventInfo> Get_Events();

            void Nav_Build_Instruction(std::string str);
            void Nav_Build_Distance(std::string str);
            void Nav_Build_ETA(std::string str);
            void Nav_Build_Action(std::string str);
            void Nav_Trigger();

            void Music_Build_Artist(std::string str);
            void Music_Build_Track(std::string str);
            void Music_Build_Album(std::string str);
            void Music_Build_Album_Art(uint8_t *arr, size_t length);
            void Music_Trigger();

            void Register_LED_Red(uint32_t pIndex);
            uint32_t Fetch_LED_Red();

            void Register_LED_Green(uint32_t pIndex);
            uint32_t Fetch_LED_Green();

            void Register_LED_Blue(uint32_t pIndex);
            uint32_t Fetch_LED_Blue();
    };
}


#endif /* STATE_HPP */
