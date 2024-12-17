#ifndef STATE_HPP
#define STATE_HPP


#include "app/common.hpp"

#include "tl.h"
#include "lvgl.h"

#include <cstdint>
#include <string>
#include <vector>


#define EVENT_POOL_SIZE                    (CFG_TLBLE_EVT_QUEUE_LENGTH*4U*DIVC(( sizeof(TL_PacketHeader_t) + TL_BLE_EVENT_FRAME_SIZE ), 4U))

namespace Sys
{
    struct Time {
        uint8_t month;
        uint8_t day;

        uint8_t hour;
        uint8_t minute;
        uint8_t second;
    };

    struct Alert {
        std::string source;
        std::string title;
        std::string body;
    };

    enum class Scheme {
        LIGHT,
        DARK
    };
    struct Preferences {
        /* Flipped/inverted when using dark mode */
        lv_color_t userWhite;
        lv_color_t userBlack;

        void Color_Scheme(Scheme scheme);
    };

    class State
    {
        private:
            volatile uint32_t App_State = 0x00000000;

            Preferences pref;

            Time Current_Time;

            std::vector<Alert> alerts;
            Alert Alert_Builder;

            /* Component index of the Red LED */
            uint32_t LED_Red_Index;
            /* Component index of the Green LED */
            uint32_t LED_Green_Index;
            /* Component index of the Blue LED */
            uint32_t LED_Blue_Index;
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
                NOT_SET,
                SET
            };

            State();
            ~State();

            Flag_Val App_Flag_Get(App_Flag flag);
            void App_Flag_Set(App_Flag flag);
            void App_Flag_Reset(App_Flag flag);

            Preferences *Get_Pref();

            /* Setting time, vs updating(setting & displaying) */
            void Set_Time(Time value);
            void Update_Time(Time value);

            void Alert_Build_Source(std::string str);
            void Alert_Build_Title(std::string str);
            void Alert_Build_Body(std::string str);
            void Alert_Send();
            void Alert_Dismiss();
            std::vector<Alert> *Get_Alerts();

            void Register_LED_Red(uint32_t pIndex);
            uint32_t Fetch_LED_Red();

            void Register_LED_Green(uint32_t pIndex);
            uint32_t Fetch_LED_Green();

            void Register_LED_Blue(uint32_t pIndex);
            uint32_t Fetch_LED_Blue();
    };
}


#endif /* STATE_HPP */
