#include "ble/gatt_service.hpp"
#include "core/main.hpp"
#include "sys/sys.hpp"

#include "ble_common.h"
#include "ble.h"
#include "ble_types.h"


/**
 * @brief Characteristic update
 * @param UUID: UUID of the characteristic
 * @param newValueLength: Length of the new value data to be written
 * @param pNewValue: Pointer to the new value data 
 */
tBleStatus BLE::Update_Char_Value(uint16_t UUID, uint16_t newValueLength, uint8_t *pNewValue)
{
    tBleStatus ret = BLE_STATUS_INVALID_PARAMS;

    switch (UUID) {
        case NOTIFY_CHARACTERISTIC_UUID:
            if (newValueLength <= NOTIFY_CHARACTERISTIC_VALUE_LENGTH)
            {
                ret = aci_gatt_update_char_value(serviceContext.Service_Handle,
                        serviceContext.Notify_Characteristic_Handle,
                        0, /* charValOffset */
                        newValueLength, /* charValueLen */
                        (uint8_t *)pNewValue);
            }
            break;
        default:
            break;
    }

    return ret;
}
