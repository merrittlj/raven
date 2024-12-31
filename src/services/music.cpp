#include "services/music.hpp"

#include "ble/char.hpp"
#include "ble/uuid.hpp"
#include "gpio/gpio.hpp"
#include "sys/sys.hpp"
#include "sys/state.hpp"

#include "ble_common.h"
#include "ble.h"
#include "ble_types.h"


BLE::MusicService::MusicService(GPIO::Controller *pGpioCtrl, Sys::State *pSysState)
{
    this->gpioCtrl = pGpioCtrl;
    this->sysState = pSysState;

    BLE::MusicService::Instance(this);
}

BLE::MusicService::~MusicService()
{}

tBleStatus BLE::MusicService::Add()
{
    uint16_t retHandle;
    Char_UUID_t serviceUUID = BLE::UUID::CreateCharUUID({0x98,0x2f,0xc7,0x70,0xbc,0x48,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    tBleStatus ret = aci_gatt_add_service(UUID_TYPE_128, (Service_UUID_t *)&serviceUUID,
            PRIMARY_SERVICE,
            SERVICE_MAX_ATT_RECORDS,
            &retHandle);
    this->Set_Handle((uintptr_t)retHandle);
    return ret;
}

SVCCTL_EvtAckStatus_t BLE::MusicService::Static_Event_Handler(void *Event)
{
    return BLE::MusicService::Instance()->Event_Handler(Event);
}

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
SVCCTL_EvtAckStatus_t BLE::MusicService::Event_Handler(void *Event)
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
                        uint16_t length;
                        data = attribute_modified->Attr_Data;
                        length = attribute_modified->Attr_Data_Length;
                        if (attribute_modified->Attr_Handle == (artist.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Music_Build_Artist(std::string((const char *)data, (size_t)length));
                        }
                        if (attribute_modified->Attr_Handle == (track.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Music_Build_Track(std::string((const char *)data, (size_t)length));
                        }
                        if (attribute_modified->Attr_Handle == (album.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Music_Build_Album(std::string((const char *)data, (size_t)length));
                        }
                        if (attribute_modified->Attr_Handle == (albumArt.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Music_Build_Album_Art(data);
                        }
                        if (attribute_modified->Attr_Handle == (trigger.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Music_Trigger();
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

uintptr_t BLE::MusicService::Get_Handle() const
{
    return this->handle;
}

void BLE::MusicService::Set_Handle(uintptr_t pHandle)
{
    this->handle = pHandle;
}

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void BLE::MusicService::Init()
{
    /* Register the event handler to the BLE controller */
    SVCCTL_RegisterSvcHandler(BLE::MusicService::Static_Event_Handler);

    /* Add Service */
    if (this->Add() != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t artistUUID = BLE::UUID::CreateCharUUID({0x98,0x2f,0xc7,0x71,0xbc,0x48,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    artist = BLE::Char(UUID_TYPE_128, &artistUUID,
            30,  /* TODO: need to truncate and determine UI parity */
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (artist.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t trackUUID = BLE::UUID::CreateCharUUID({0x98,0x2f,0xc7,0x72,0xbc,0x48,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    track = BLE::Char(UUID_TYPE_128, &trackUUID,
            30,  /* TODO: see prev */
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (track.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t albumUUID = BLE::UUID::CreateCharUUID({0x98,0x2f,0xc7,0x73,0xbc,0x48,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    album = BLE::Char(UUID_TYPE_128, &albumUUID,
            30,  /* TODO: see prev */
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (album.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t albumArtUUID = BLE::UUID::CreateCharUUID({0x98,0x2f,0xc7,0x74,0xbc,0x48,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    albumArt = BLE::Char(UUID_TYPE_128, &albumArtUUID,
            512,  /* TODO: receive in chunks */
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (albumArt.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t triggerUUID = BLE::UUID::CreateCharUUID({0x98,0x2f,0xc7,0x75,0xbc,0x48,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    trigger = BLE::Char(UUID_TYPE_128, &triggerUUID,
            1,
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (trigger.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */
}

/**
 * @brief Characteristic update
 * @param UUID: UUID of the characteristic
 * @param newValueLength: Length of the new value data to be written
 * @param pNewValue: Pointer to the new value data 
 */
tBleStatus BLE::MusicService::Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue)
{
    tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
    return ret;
}
