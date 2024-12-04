#include "ble/uuid.hpp"

#include "ble/char.hpp"

#include "ble.h"
#include "ble_common.h"
#include "ble_types.h"

#include <algorithm>


Char_UUID_t BLE::UUID::CreateCharUUID(std::initializer_list<uint8_t> values128)
{
    Char_UUID_t uuid;
    std::reverse_copy(values128.begin(), values128.end(), uuid.Char_UUID_128);
    return uuid;
}
Char_UUID_t BLE::UUID::CreateCharUUID(uint16_t values16)
{
    Char_UUID_t uuid;
    uuid.Char_UUID_16 = values16;
    return uuid;
}

uint16_t BLE::UUID::ExtractUUID16FromLE(Char_UUID_t *uuid)
{
    return ((uint16_t)uuid->Char_UUID_128[13] << 8) | uuid->Char_UUID_128[12];
}
