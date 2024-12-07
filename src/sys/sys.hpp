#ifndef SYS_HPP
#define SYS_HPP


#include "sys/state.hpp"

#include "hci_tl.h"
#include "shci_tl.h"
#include "stm32wbxx_hal.h"


namespace Sys
{
    void Error_Handler();

    class Controller
    {
        private:
            Sys::State *sysState;
            SPI_HandleTypeDef spi1;

        public:
            Controller(Sys::State *state);
            ~Controller();

            void Config_SysClk();
            void Config_HSE();
            SPI_HandleTypeDef *Config_SPI();
            void Init_CPU2();
    };


    class Event_Processor
    {
        private:
            inline static Event_Processor *theInstance;

            Sys::State *sysState;

        public:
            Event_Processor(Sys::State *state);
            ~Event_Processor();

            static Event_Processor *Instance(Event_Processor *cur = nullptr);

            static void Sys_StatusNotificationCallback(SHCI_TL_CmdStatus_t status);
            static void Sys_UserEventReceivedCallback(void *pData);
            void Sys_ProcessEvent();

            static void BLE_StatusNotificationCallback(HCI_TL_CmdStatus_t status);
            static void BLE_UserEventReceivedCallback(void *pData);
            void BLE_ProcessEvent();

            void SHCI_Notify_Event_Handler(void *pdata);
            void HCI_Notify_Event_Handler(void *pdata);
    };
}

/* As the library requires these functions globally??? */
void shci_notify_asynch_evt(void *pdata);
void hci_notify_asynch_evt(void *pdata);


#endif /* SYS_HPP */
