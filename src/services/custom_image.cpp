#include "services/custom_image.hpp"

#include "ble/char.hpp"
#include "ble/uuid.hpp"
#include "sys/sys.hpp"
#include "sys/state.hpp"

#include "ble_common.h"
#include "ble.h"
#include "ble_types.h"


BLE::CustomImageService::CustomImageService()
{
    BLE::CustomImageService::Instance(this);
}

BLE::CustomImageService::~CustomImageService()
{}

tBleStatus BLE::CustomImageService::Add()
{
    uint16_t retHandle;
    Char_UUID_t serviceUUID = BLE::UUID::CreateCharUUID({0x30,0xcf,0xc2,0x3b,0x55,0xf0,0x41,0x2b,0xb3,0xbc,0x25,0x33,0xdb,0xf8,0xe2,0x8e});
    tBleStatus ret = aci_gatt_add_service(UUID_TYPE_128, (Service_UUID_t *)&serviceUUID,
            PRIMARY_SERVICE,
            SERVICE_MAX_ATT_RECORDS,
            &retHandle);
    this->Set_Handle((uintptr_t)retHandle);
    return ret;
}

SVCCTL_EvtAckStatus_t BLE::CustomImageService::Static_Event_Handler(void *Event)
{
    return BLE::CustomImageService::Instance()->Event_Handler(Event);
}

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
SVCCTL_EvtAckStatus_t BLE::CustomImageService::Event_Handler(void *Event)
{
    SVCCTL_EvtAckStatus_t return_value;
    hci_event_pckt *event_pckt;
    evt_blecore_aci *blecore_evt;
    aci_gatt_attribute_modified_event_rp0 *attribute_modified;
    return_value = SVCCTL_EvtNotAck;
    event_pckt = (hci_event_pckt *)(((hci_uart_pckt*)Event)->data);

    Sys::State *state = Sys::Controller::Instance()->sysState;
    switch (event_pckt->evt) {
        case HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE:
            {
                blecore_evt = (evt_blecore_aci*)event_pckt->data;
                switch (blecore_evt->ecode) {
                    case ACI_GATT_INDICATION_VSEVT_CODE:
                        // Confirm the indication to prevent timeout
                        aci_gatt_confirm_indication((*reinterpret_cast<aci_gatt_indication_event_rp0*>(blecore_evt->data)).Connection_Handle);
                        break;

                    case ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE:
                        attribute_modified = (aci_gatt_attribute_modified_event_rp0*)blecore_evt->data;
                        uint8_t *data;
                        size_t length;
                        data = attribute_modified->Attr_Data;
                        length = (size_t)(attribute_modified->Attr_Data_Length);

                        if (attribute_modified->Attr_Handle == (image.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            state->Custom_Image_Build(data, length);
                        }
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

uintptr_t BLE::CustomImageService::Get_Handle() const
{
    return this->handle;
}

void BLE::CustomImageService::Set_Handle(uintptr_t pHandle)
{
    this->handle = pHandle;
}

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void BLE::CustomImageService::Init()
{
    /* Register the event handler to the BLE controller */
    SVCCTL_RegisterSvcHandler(BLE::CustomImageService::Static_Event_Handler);

    /* Add Service */
    if (this->Add() != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t imageUUID = BLE::UUID::CreateCharUUID({0x30,0xcf,0xc2,0x3b,0x56,0xf0,0x41,0x2b,0xb3,0xbc,0x25,0x33,0xdb,0xf8,0xe2,0x8e});
    image = BLE::Char(UUID_TYPE_128, &imageUUID,
            240,  /* multiple 240 byte chunks */
            CHAR_PROP_READ | CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (image.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t readyUUID = BLE::UUID::CreateCharUUID({0x30,0xcf,0xc2,0x3b,0x57,0xf0,0x41,0x2b,0xb3,0xbc,0x25,0x33,0xdb,0xf8,0xe2,0x8e});
    ready = BLE::Char(UUID_TYPE_128, &readyUUID,
            1,
            CHAR_PROP_NOTIFY,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (ready.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */
}

/**
 * @brief Characteristic update
 * @param UUID: UUID of the characteristic
 * @param newValueLength: Length of the new value data to be written
 * @param pNewValue: Pointer to the new value data 
 */
tBleStatus BLE::CustomImageService::Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue)
{
    tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
    if (UUID16 == BLE::UUID::ExtractUUID16FromLE(ready.Get_UUID())) {
        if (newValueLength <= ready.Get_Value_Length())
        {
            ret = aci_gatt_update_char_value(this->Get_Handle(),
                    ready.Get_Handle(),
                    0, /* charValOffset */
                    newValueLength, /* charValueLen */
                    (uint8_t *)pNewValue);
        }
    }
    return ret;
}
