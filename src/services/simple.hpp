#ifndef SIMPLE_HPP
#define SIMPLE_HPP


#include "ble/char.hpp"
#include "gpio/gpio.hpp"
#include "sys/sys.hpp"

#include "ble.h"
#include "ble_common.h"
#include "ble_types.h"


namespace BLE
{
    class SimpleService : Service
    {
        /* Max_Attribute_Records = 2*no_of_char + 1
         * service_max_attribute_record = 1 for service +
         *                                2 for Write characteristic +
         *                                2 for Notify characteristic +
         *                                1 for client char configuration descriptor +
         */
#define SERVICE_MAX_ATT_RECORDS                8

#define CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET              1

        private:
            GPIO::Controller *gpioCtrl;
            Sys::State *sysState;

            tBleStatus Add();
            SVCCTL_EvtAckStatus_t Event_Handler(void *pckt);

        public:
            BLE::Char ledWriteChar;
            BLE::Char bellNotifyChar;

            SimpleService(GPIO::Controller *pGpioCtrl, Sys::State *pSysState);
            ~SimpleService();

            void Init();

            tBleStatus Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue);
    };
}


#endif /* SIMPLE_HPP */
