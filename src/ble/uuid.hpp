#ifndef UUID_HPP
#define UUID_HPP


#include "ble/char.hpp"

#include "ble.h"
#include "ble_common.h"
#include "ble_types.h"

#include <initializer_list>

namespace BLE
{
    namespace UUID
    {
        /* Char_UUID_t is big-endian! */
        Char_UUID_t CreateCharUUID(std::initializer_list<uint8_t> values128);
        Char_UUID_t CreateCharUUID(uint16_t values16);
        /* Get big-endian UUID16 from little-endian UUID128 */
        uint16_t ExtractUUID16FromLE(Char_UUID_t *uuid);
    }
}


#endif /* UUID_HPP */
