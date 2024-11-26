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

            inline static T* theInstance;

        public:
            static T* Instance(T* cur = nullptr)
            {
                if (!theInstance) theInstance = cur;
                return theInstance;
            }

            ~Service()
            {
                delete theInstance;
            }

            virtual uintptr_t Get_Handle() const = 0;
            virtual void Set_Handle(uintptr_t pHandle) = 0;

            virtual void Init() = 0;

            virtual tBleStatus Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue) = 0;
    };
}


#endif /* SERVICE_HPP */
