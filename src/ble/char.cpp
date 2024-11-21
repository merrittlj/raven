#include "ble/char.hpp"

BLE::Char::Char(uint16_t *pHandle, Char_UUID_t* pUUID, uint8_t pUUIDType, uint16_t pValueLength, uint8_t pProperties, uint8_t pPermissions, uint8_t pGattEvtMask, uint8_t pEncKeySize, uint8_t pIsVariable)
    : handle(pHandle), UUID(pUUID), UUIDType(pUUIDType), valueLength(pValueLength), properties(pProperties), permissions(pPermissions), gattEvtMask(pGattEvtMask), encKeySize(pEncKeySize), isVariable(pIsVariable)
{}

BLE::Char::~Char()
{}

tBleStatus BLE::Char::Add_To_Service(uint16_t pServiceHandle)
{

}
