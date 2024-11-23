#ifndef SERVICE_HPP
#define SERVICE_HPP


#include "ble/char.hpp"

#include "ble.h"
#include "ble_common.h"
#include "ble_types.h"


namespace BLE
{
    template <typename T>
    class Service
    {
        protected:
            uintptr_t handle;

        private:
            virtual tBleStatus Add() = 0;

            /* Must have a static event handler as well for RegisterSvcHandler! */
            virtual SVCCTL_EvtAckStatus_t Event_Handler(void *pckt) = 0;

        public:
            static T* theInstance;
            
            static T* Instance();

            virtual uintptr_t Get_Handle() const;
            virtual void Set_Handle(uintptr_t pHandle);

            virtual void Init() = 0;

            virtual tBleStatus Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue) = 0;
    };
}


#endif /* SERVICE_HPP */
