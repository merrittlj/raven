#include "ble/char.hpp"


BLE::Char::Char()
{}

BLE::Char::Char(uint8_t pUUIDType,
        Char_UUID_t *pUUID,
        uint16_t pValueLength,
        uint8_t pProperties,
        uint8_t pPermissions,
        uint8_t pGattEvtMask,
        uint8_t pEncKeySize,
        uint8_t pIsVariable)
    : UUIDType(pUUIDType),
    UUID(pUUID),
    valueLength(pValueLength),
    properties(pProperties),
    permissions(pPermissions),
    gattEvtMask(pGattEvtMask),
    encKeySize(pEncKeySize),
    isVariable(pIsVariable)
{}

BLE::Char::~Char()
{}

uintptr_t BLE::Char::Get_Handle() const
{
    return this->handle;
}

Char_UUID_t *BLE::Char::Get_UUID() const 
{
    return this->UUID;
}

uint16_t BLE::Char::Get_Value_Length() const
{
    return this->valueLength;
}

tBleStatus BLE::Char::Add(uintptr_t pServiceHandle)
{
    uint16_t retHandle;
    tBleStatus ret = aci_gatt_add_char(pServiceHandle,
            this->UUIDType, this->UUID,
            this->valueLength,                                   
            this->properties,
            this->permissions,
            this->gattEvtMask,
            this->encKeySize,
            this->isVariable,
            &retHandle);
    this->handle = (uintptr_t)retHandle;
    return ret;
}
