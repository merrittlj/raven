#ifndef STATE_HPP
#define STATE_HPP


#include "app/common.hpp"

#include "tl.h"

#include <cstdint>


#define EVENT_POOL_SIZE                    (CFG_TLBLE_EVT_QUEUE_LENGTH*4U*DIVC(( sizeof(TL_PacketHeader_t) + TL_BLE_EVENT_FRAME_SIZE ), 4U))

namespace Sys
{
    class State
    {
        private:
            volatile uint32_t App_State = 0x00000000;

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

            void Register_LED_Red(uint32_t pIndex);
            uint32_t Fetch_LED_Red();

            void Register_LED_Green(uint32_t pIndex);
            uint32_t Fetch_LED_Green();

            void Register_LED_Blue(uint32_t pIndex);
            uint32_t Fetch_LED_Blue();
    };
}


#endif /* STATE_HPP */
