#include "services/info.hpp"

#include "ble/char.hpp"
#include "ble/uuid.hpp"
#include "gpio/gpio.hpp"
#include "sys/sys.hpp"
#include "sys/state.hpp"

#include "ble_common.h"
#include "ble.h"
#include "ble_types.h"


BLE::InfoService::InfoService(GPIO::Controller *pGpioCtrl, Sys::State *pSysState)
{
    this->gpioCtrl = pGpioCtrl;
    this->sysState = pSysState;

    BLE::InfoService::Instance(this);
}

BLE::InfoService::~InfoService()
{}

tBleStatus BLE::InfoService::Add()
{
    uint16_t retHandle;
    
    Char_UUID_t serviceUUID = BLE::UUID::CreateCharUUID({0xb2,0x6b,0x80,0xc0,0xcb,0x1b,0x11,0xef,0xa8,0xfa,0x08,0x00,0x20,0x0c,0x9a,0x66});
    tBleStatus ret = aci_gatt_add_service(UUID_TYPE_128, (Service_UUID_t *)&serviceUUID,
            PRIMARY_SERVICE,
            SERVICE_MAX_ATT_RECORDS,
            &retHandle);
    this->Set_Handle((uintptr_t)retHandle);
    return ret;
}

SVCCTL_EvtAckStatus_t BLE::InfoService::Static_Event_Handler(void *Event)
{
    return BLE::InfoService::Instance()->Event_Handler(Event);
}

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
SVCCTL_EvtAckStatus_t BLE::InfoService::Event_Handler(void *Event)
{
    SVCCTL_EvtAckStatus_t return_value;
    hci_event_pckt *event_pckt;
    evt_blecore_aci *blecore_evt;
    aci_gatt_attribute_modified_event_rp0 *attribute_modified;
    return_value = SVCCTL_EvtNotAck;
    event_pckt = (hci_event_pckt *)(((hci_uart_pckt*)Event)->data);

    switch (event_pckt->evt) {
        case HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE:
            {
                blecore_evt = (evt_blecore_aci*)event_pckt->data;
                switch (blecore_evt->ecode) {
                    case ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE:
                        attribute_modified = (aci_gatt_attribute_modified_event_rp0*)blecore_evt->data;
                        uint8_t *data;
                        data = attribute_modified->Attr_Data;
                        break;

                    default:
                        break;
                }
            }
            break; /* HCI_HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE_SPECIFIC */

        default:
            break;
    }

    return(return_value);
}

uintptr_t BLE::InfoService::Get_Handle() const
{
    return this->handle;
}

void BLE::InfoService::Set_Handle(uintptr_t pHandle)
{
    this->handle = pHandle;
}

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void BLE::InfoService::Init()
{
    /* Register the event handler to the BLE controller */
    SVCCTL_RegisterSvcHandler(BLE::InfoService::Static_Event_Handler);

    /* Add Service */
    if (this->Add() != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t deviceResetUUID = BLE::UUID::CreateCharUUID({0xb2,0x6b,0x80,0xc1,0xcb,0x1b,0x11,0xef,0xa8,0xfa,0x08,0x00,0x20,0x0c,0x9a,0x66});
    deviceReset = BLE::Char(UUID_TYPE_128, &deviceResetUUID,
            1,
            CHAR_PROP_NOTIFY,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (deviceReset.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t musicButtonUUID = BLE::UUID::CreateCharUUID({0xb2,0x6b,0x80,0xc2,0xcb,0x1b,0x11,0xef,0xa8,0xfa,0x08,0x00,0x20,0x0c,0x9a,0x66});
    musicButton = BLE::Char(UUID_TYPE_128, &musicButtonUUID,
            1,  /* Enough options */
            CHAR_PROP_NOTIFY,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (musicButton.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */
}

/**
 * @brief Characteristic update
 * @param UUID: UUID of the characteristic
 * @param newValueLength: Length of the new value data to be written
 * @param pNewValue: Pointer to the new value data 
 */
tBleStatus BLE::InfoService::Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue)
{
    tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
    if (UUID16 == BLE::UUID::ExtractUUID16FromLE(deviceReset.Get_UUID())) {
        if (newValueLength <= deviceReset.Get_Value_Length())
        {
            ret = aci_gatt_update_char_value(this->Get_Handle(),
                    deviceReset.Get_Handle(),
                    0, /* charValOffset */
                    newValueLength, /* charValueLen */
                    (uint8_t *)pNewValue);
        }
    }
    else if (UUID16 == BLE::UUID::ExtractUUID16FromLE(musicButton.Get_UUID())) {
        if (newValueLength <= musicButton.Get_Value_Length())
        {
            ret = aci_gatt_update_char_value(this->Get_Handle(),
                    musicButton.Get_Handle(),
                    0, /* charValOffset */
                    newValueLength, /* charValueLen */
                    (uint8_t *)pNewValue);
        }
    }
    return ret;
}
