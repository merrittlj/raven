#include "ble/uuid.hpp"

#include "ble/char.hpp"

#include "ble.h"
#include "ble_common.h"
#include "ble_types.h"


Char_UUID_t CreateCharUUID(std::initializer_list<uint8_t> values128);
{
    Char_UUID_t uuid;
    std::reverse_copy(values128.begin(), values128.end(), uuid.Char_UUID_128);
    return uuid;
}

uint16_t ExtractUUID16FromLE(Char_UUID_t uuid)
{
    return ((uint16_t)uuid.Char_UUID_128[13] << 8) | uuid.Char_UUID_128[12];
}
