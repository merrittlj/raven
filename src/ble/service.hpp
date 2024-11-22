#ifndef SERVICE_HPP
#define SERVICE_HPP


#include "ble/char.hpp"

#include "ble.h"
#include "ble_common.h"
#include "ble_types.h"


namespace BLE
{
    class Service
    {
        private:
            uint16_t handle;

            virtual tBleStatus Add() = 0;
            virtual SVCCTL_EvtAckStatus_t Event_Handler(void *pckt) = 0;

        public:
            virtual void Init() = 0;

            virtual tBleStatus Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue) = 0;
    };
}


#endif /* SERVICE_HPP */
