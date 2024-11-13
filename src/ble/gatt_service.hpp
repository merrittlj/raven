#ifndef GATT_SERVICE_HPP
#define GATT_SERVICE_HPP


#include "gpio/gpio.hpp"
#include "sys/state.hpp"

#include "ble.h"
#include "ble_common.h"
#include "ble_types.h"


#define SERVICE_UUID                                      (0xFE40)
#define WRITE_CHARACTERISTIC_UUID                         (0xFE41)
#define NOTIFY_CHARACTERISTIC_UUID                        (0xFE42)

#define NOTIFY_CHARACTERISTIC_VALUE_LENGTH     2
#define WRITE_CHARACTERISTIC_VALUE_LENGTH      2

namespace BLE
{
    class Gatt_Service
    {
        private:
            typedef struct {
                uint16_t Service_Handle;              /**< Service handle */
                uint16_t Write_Characteristic_Handle;  /**< Write Characteristic handle */
                uint16_t Notify_Characteristic_Handle; /**< Notify Characteristic handle */
            } ServiceContext_t;

            /* Service and Characteristics UUIDs */
#define COPY_SERVICE_UUID(uuid_struct)                 COPY_UUID_128(uuid_struct,0x00,0x00,0xfe,0x40,0xcc,0x7a,0x48,0x2a,0x98,0x4a,0x7f,0x2e,0xd5,0xb3,0xe5,0x8f)
#define COPY_WRITE_CHARACTERISTIC_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xfe,0x41,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_NOTIFY_CHARACTERISTIC_UUID(uuid_struct)   COPY_UUID_128(uuid_struct,0x00,0x00,0xfe,0x42,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)

            /* Max_Attribute_Records = 2*no_of_char + 1
             * service_max_attribute_record = 1 for service +
             *                                2 for Write characteristic +
             *                                2 for Notify characteristic +
             *                                1 for client char configuration descriptor +
             */
#define SERVICE_MAX_ATT_RECORDS                8

#define CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET              1

#define COPY_UUID_128(uuid_struct, uuid_15, uuid_14, uuid_13, uuid_12, uuid_11, uuid_10, uuid_9, uuid_8, uuid_7, uuid_6, uuid_5, uuid_4, uuid_3, uuid_2, uuid_1, uuid_0) \
            do {\
                uuid_struct[0] = uuid_0; uuid_struct[1] = uuid_1; uuid_struct[2] = uuid_2; uuid_struct[3] = uuid_3; \
                uuid_struct[4] = uuid_4; uuid_struct[5] = uuid_5; uuid_struct[6] = uuid_6; uuid_struct[7] = uuid_7; \
                uuid_struct[8] = uuid_8; uuid_struct[9] = uuid_9; uuid_struct[10] = uuid_10; uuid_struct[11] = uuid_11; \
                uuid_struct[12] = uuid_12; uuid_struct[13] = uuid_13; uuid_struct[14] = uuid_14; uuid_struct[15] = uuid_15; \
            }while(0)


            ServiceContext_t serviceContext;
            GPIO::Controller *gpioCtrl;
            Sys::State *sysState;

            static SVCCTL_EvtAckStatus_t Event_Handler(void *pckt);

        public:
            Gatt_Service(GPIO::Controller *pGpioCtrl, Sys::State *pSysState);
            ~Gatt_Service();

            void Init();
            tBleStatus Write_Characteristic_Update(uint16_t UUID, uint16_t newValueLength, uint8_t *pNewValue);
    };
}


#endif /* GATT_SERVICE_HPP */
