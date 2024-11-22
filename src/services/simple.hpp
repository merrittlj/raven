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
        private:
            BLE::Char ledWriteChar;
            BLE::Char bellNotifyChar;

            GPIO::Controller *gpioCtrl;
            Sys::State *sysState;

            tBleStatus Add();
            SVCCTL_EvtAckStatus_t Event_Handler(void *pckt);

        public:
            SimpleService(GPIO::Controller *pGpioCtrl, Sys::State *pSysState);
            ~SimpleService();

            void Init();
    };
}


#endif /* SIMPLE_HPP */
