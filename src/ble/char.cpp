#include "ble/char.hpp"

BLE::Char::Char(uint8_t pUUIDType,
        Char_UUID_t* pUUID,
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

uint16_t Get_Handle() const
{
    return this->handle;
}
Char_UUID_t *Get_UUID() const 
{
    return this->UUID;
}

tBleStatus BLE::Char::Add(uint16_t pServiceHandle);
{
    COPY_WRITE_CHARACTERISTIC_UUID(uuid16.Char_UUID_128);
    return aci_gatt_add_char(pServiceHandle,
            this->UUIDType, this->UUID,
            this->valueLength,                                   
            this->properties,
            this->permissions,
            this->gattEvtMask,
            this->encKeySize,
            this->isVariable,
            &(this->handle));
}
