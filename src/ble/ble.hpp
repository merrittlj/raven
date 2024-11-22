#ifndef BLE_HPP
#define BLE_HPP


#include "services/simple.hpp"
#include "gpio/gpio.hpp"
#include "sys/state.hpp"

#define EVT_END_OF_RADIO_ACTIVITY           0x0004

#define BD_ADDR_SIZE_LOCAL                  6
#define APP_BLE_GAP_DEVICE_NAME_LENGTH      sizeof(gap_device_name)
#define EVENT_POOL_SIZE                    (CFG_TLBLE_EVT_QUEUE_LENGTH*4U*DIVC(( sizeof(TL_PacketHeader_t) + TL_BLE_EVENT_FRAME_SIZE ), 4U))

namespace BLE
{
    class App
    {
        private:
            PLACE_IN_SECTION("MB_MEM2") ALIGN(4) static uint8_t EvtPool[EVENT_POOL_SIZE];
            PLACE_IN_SECTION("MB_MEM2") ALIGN(4) static TL_CmdPacket_t SystemCmdBuffer;
            PLACE_IN_SECTION("MB_MEM2") ALIGN(4) static TL_CmdPacket_t BleCmdBuffer;
            PLACE_IN_SECTION("MB_MEM1") ALIGN(4) static uint8_t SystemSpareEvtBuffer[sizeof(TL_PacketHeader_t) + TL_EVT_HDR_SIZE + 255];
            PLACE_IN_SECTION("MB_MEM2") ALIGN(4) static uint8_t BleSpareEvtBuffer[sizeof(TL_PacketHeader_t) + TL_EVT_HDR_SIZE + 255];

            static uint8_t bd_address_udn[BD_ADDR_SIZE_LOCAL];

            /* Generic Access GATT Service Characteristics configuration data  */
            static const char gap_device_name[] = { 'R', 'a', 'v', 'e', 'n', ' ', 'S', 'W' };
            static const uint16_t gap_appearance = BLE_CFG_GAP_APPEARANCE;

            /* GAP Advertising data */
            static const char ad_local_name[] = { AD_TYPE_COMPLETE_LOCAL_NAME, 'R', 'a', 'v', 'e', 'n', ' ', 'S', 'W' };
            static uint8_t ad_manufacturer_specific_data[14] = { /* Manufacturer specific data used to get compliant with ST BLE Sensor smart phone apk */
                sizeof(ad_manufacturer_specific_data)-1,
                AD_TYPE_MANUFACTURER_SPECIFIC_DATA, 
                0x01, /* BlueST Protocol version */
                0x83, /* BlueST Device Id: 0x83 - P2PServer1 - for more details please see BLE_p2pServer example project */
                0x00, /* BlueST Feature Mask bits 24~31 */
                0x00, /* BlueST Feature Mask bits 16~23 */
                0x00, /* BlueST Feature Mask bits 8~15 */
                0x00, /* BlueST Feature Mask bits 0~7 */
                0x00, /* BlueST Device MAC byte 5 */
                0x00, /* BlueST Device MAC byte 4 */
                0x00, /* BlueST Device MAC byte 3 */
                0x00, /* BlueST Device MAC byte 2 */
                0x00, /* BlueST Device MAC byte 1 */
                0x00  /* BlueST Device MAC byte 0 */
            };

            static const uint8_t a_MBdAddr[BD_ADDR_SIZE_LOCAL] =
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

            SVCCTL_UserEvtFlowStatus_t SVCCTL_App_Notification(void *pckt);

        public:
            App(GPIO::Controller *pGpioCtrl, Sys::State *pSysState);
            ~App();

            uint8_t notifyCharacteristicData[NOTIFY_CHARACTERISTIC_VALUE_LENGTH] = {0x00, 0x00};

            void Init(BLE::SimpleService simpleService);
            void Advertising(FlagStatus setReset);
    };
}


#endif /* BLE_HPP */
