#ifndef BLE_HPP
#define BLE_HPP


#include "services/time.hpp"
#include "gpio/gpio.hpp"
#include "sys/state.hpp"
#include "sys/sys.hpp"

#define EVT_END_OF_RADIO_ACTIVITY           0x0004

#define BD_ADDR_SIZE_LOCAL                  6
#define APP_BLE_GAP_DEVICE_NAME_LENGTH      sizeof(gap_device_name)

namespace BLE
{
    class App
    {
        private:
            inline static App *theInstance;

            uint8_t bd_address_udn[BD_ADDR_SIZE_LOCAL];

            /* Generic Access GATT Service Characteristics configuration data  */
            const char gap_device_name[10] = { 'R', 'a', 'v', 'e', 'n', ' ', 'V', '0', '.', '3' };
            const uint16_t gap_appearance = BLE_CFG_GAP_APPEARANCE;

            /* GAP Advertising data */
            /* There's no specific limit on the name length, but there is on the advertising data as a whole. 
             * That limit is 31 bytes: 6 bytes are taken up by the Tx power and flags fields (3 bytes each),
             * a further 14 by the manuf_data[] array, 
             * and the remaining 11 are what's left for the name. 
             * As there's a 2-byte overhead on that (one for field length, one for field type), 
             * you've got a limit of 9 characters for the name itself.
             * If you don't need the manuf_data[] to be advertised in your application,
             * you can safely omit it and get those 14 bytes back.
             *
             * Here, we do not use manufacturer data, freeing space for the name */ 
            const char ad_local_name[11] = { AD_TYPE_COMPLETE_LOCAL_NAME, 'R', 'a', 'v', 'e', 'n', ' ', 'V', '0', '.', '3' };
            
            const uint8_t a_MBdAddr[BD_ADDR_SIZE_LOCAL] =
            {
                (uint8_t)((CFG_ADV_BD_ADDRESS & 0x0000000000FF)),
                (uint8_t)((CFG_ADV_BD_ADDRESS & 0x00000000FF00) >> 8),
                (uint8_t)((CFG_ADV_BD_ADDRESS & 0x000000FF0000) >> 16),
                (uint8_t)((CFG_ADV_BD_ADDRESS & 0x0000FF000000) >> 24),
                (uint8_t)((CFG_ADV_BD_ADDRESS & 0x00FF00000000) >> 32),
                (uint8_t)((CFG_ADV_BD_ADDRESS & 0xFF0000000000) >> 40)
            };

            /* More details about BlueST protocol and how it is used in our demos and examples
               can be found in the related documentation, e.g. in UM2496 */


            GPIO::Controller *gpioCtrl;
            Sys::State *sysState;

            void BLE_Init();
            void Tl_Init();
            void Hci_Gap_Gatt_Init();
            const uint8_t* GetBdAddress();

        public:
            uint8_t notifyCharacteristicData[2] = {0x00, 0x00};

            static App *Instance(App *cur = nullptr);

            App(GPIO::Controller *pGpioCtrl, Sys::State *pSysState);
            ~App();

            void Init(BLE::TimeService *timeService);
            void Advertising(FlagStatus setReset);

            SVCCTL_UserEvtFlowStatus_t SVCCTL_Notification_Handler(void *pckt);
    };
}
SVCCTL_UserEvtFlowStatus_t SVCCTL_App_Notification(void *pckt);


#endif /* BLE_HPP */
