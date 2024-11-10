#ifndef SYS_HPP
#define SYS_HPP


namespace Sys
{
    void Error_Handler();

    class Controller
    {
        public:
            Controller();
            ~Controller();

            void Config_SysClk();
            void Config_HSE();
            void Init_CPU2();
    };

    class Event_Processor
    {
        private:
            void Sys_StatusNotificationCallback(SHCI_TL_CmdStatus_t status);
            void Sys_UserEventReceivedCallback(void *pData);

            void BLE_StatusNotificationCallback(HCI_TL_CmdStatus_t status);
            void BLE_UserEventReceivedCallback(void *pData);

        public:
            Event_Processor();
            ~Event_Processor();

            void Sys_ProcessEvent();
            void BLE_ProcessEvent();

            void shci_notify_asynch_evt(void* pdata);
            void hci_notify_asynch_evt(void* pdata);
    };
}


#endif /* SYS_HPP */
