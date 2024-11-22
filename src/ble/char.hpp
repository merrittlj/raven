#ifndef CHAR_HPP
#define CHAR_HPP


#include "ble.h"
#include "ble_common.h"
#include "ble_types.h"


enum Value_Length_Type { VALUE_FIXED_LENGTH, VALUE_VARIABLE_LENGTH };

namespace BLE
{
    class Char
    {
        private:
            uintptr_t handle;

            uint8_t UUIDType;
            Char_UUID_t *UUID;
            uint16_t valueLength;
            uint8_t properties;
            uint8_t permissions;
            uint8_t gattEvtMask;
            uint8_t encKeySize;
            uint8_t isVariable;

        public:
            Char();
            Char(uint8_t pUUIDType, Char_UUID_t* pUUID, uint16_t pValueLength, uint8_t pProperties, uint8_t pPermissions, uint8_t pGattEvtMask, uint8_t pEncKeySize, uint8_t pIsVariable);
            ~Char();

            uintptr_t Get_Handle() const;
            Char_UUID_t *Get_UUID() const;
            uint16_t Get_Value_Length() const;

            tBleStatus Add(uintptr_t pServiceHandle);
    };
}


#endif /* CHAR_HPP */
