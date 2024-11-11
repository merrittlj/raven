#ifndef APP_HPP
#define APP_HPP


#include <cstdint>


#define APP_FLAG_CPU2_INITIALIZED           0
#define APP_FLAG_CPU2_ERROR                24
#define APP_FLAG_WIRELESS_FW_RUNNING        1
#define APP_FLAG_FUS_FW_RUNNING             2
#define APP_FLAG_BLE_INITIALIZATION_ERROR  25
#define APP_FLAG_BLE_INITIALIZED            3
#define APP_FLAG_BLE_ADVERTISING            4
#define APP_FLAG_BLE_CONNECTED              5
#define APP_FLAG_HCI_EVENT_PENDING         18
#define APP_FLAG_SHCI_EVENT_PENDING        19
#define APP_FLAG_GET(flag)                  VariableBit_Get_BB(((uint32_t)&App::APP_State), flag)
#define APP_FLAG_SET(flag)                  VariableBit_Set_BB(((uint32_t)&App::APP_State), flag)
#define APP_FLAG_RESET(flag)                VariableBit_Reset_BB(((uint32_t)&App::APP_State), flag)

namespace App
{
    volatile uint32_t APP_State = 0x00000000;
}


#endif /* APP_HPP */
