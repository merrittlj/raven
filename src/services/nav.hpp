#ifndef NAV_HPP
#define NAV_HPP


#include "ble/service.hpp"
#include "ble/char.hpp"

#include "ble.h"
#include "ble_common.h"
#include "ble_types.h"


namespace BLE
{
    class NavService : BLE::Service<NavService>
    {
        protected:
            uintptr_t handle;

        private:
            /* Max_Attribute_Records = 2*no_of_char + 2
             * service_max_attribute_record = 1 for service +
             *                                2 for each Write/Notify characteristic +
             *                                1 for client char configuration descriptor + */
            const uint8_t SERVICE_MAX_ATT_RECORDS = 12;

            tBleStatus Add();

            static SVCCTL_EvtAckStatus_t Static_Event_Handler(void *Event);
            SVCCTL_EvtAckStatus_t Event_Handler(void *pckt);

        public:
            BLE::Char instruction;
            BLE::Char distance;
            BLE::Char eta;
            BLE::Char action;
            BLE::Char trigger;

            NavService();
            ~NavService();

            uintptr_t Get_Handle() const;
            void Set_Handle(uintptr_t pHandle);

            void Init();

            tBleStatus Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue);
    };
}


#endif /* NAV_HPP */
