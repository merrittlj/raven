#ifndef TIME_HPP
#define TIME_HPP


#include "ble/service.hpp"
#include "ble/char.hpp"
#include "gpio/gpio.hpp"
#include "sys/state.hpp"

#include "ble.h"
#include "ble_common.h"
#include "ble_types.h"


namespace BLE
{
    class TimeService : BLE::Service<TimeService>
    {
        /* Max_Attribute_Records = 2*no_of_char + 1
         * service_max_attribute_record = 1 for service +
         *                                2 for Write characteristic +
         *                                2 for Notify characteristic +
         *                                1 for client char configuration descriptor +
         */
#define SERVICE_MAX_ATT_RECORDS                8

#define CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET              1

        protected:
            uintptr_t handle;

        private:
            GPIO::Controller *gpioCtrl;
            Sys::State *sysState;

            tBleStatus Add();

            static SVCCTL_EvtAckStatus_t Static_Event_Handler(void *Event);
            SVCCTL_EvtAckStatus_t Event_Handler(void *pckt);

        public:
            /* Following the CTS(Current Time Service) spec: */
            BLE::Char currentTime;
            BLE::Char localTime;

            TimeService(GPIO::Controller *pGpioCtrl, Sys::State *pSysState);
            ~TimeService();

            uintptr_t Get_Handle() const;
            void Set_Handle(uintptr_t pHandle);

            void Init();

            tBleStatus Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue);
    };
}


#endif /* TIME_HPP */