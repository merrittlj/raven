#include "services/pref.hpp"

#include "ble/char.hpp"
#include "ble/uuid.hpp"
#include "gpio/gpio.hpp"
#include "sys/sys.hpp"
#include "sys/state.hpp"

#include "ble_common.h"
#include "ble.h"
#include "ble_types.h"


BLE::PrefService::PrefService(GPIO::Controller *pGpioCtrl, Sys::State *pSysState)
{
    this->gpioCtrl = pGpioCtrl;
    this->sysState = pSysState;

    BLE::PrefService::Instance(this);
}

BLE::PrefService::~PrefService()
{}

tBleStatus BLE::PrefService::Add()
{
    uint16_t retHandle;
    Char_UUID_t serviceUUID = BLE::UUID::CreateCharUUID({0xbd,0x77,0x11,0xb0,0xbb,0x11,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    tBleStatus ret = aci_gatt_add_service(UUID_TYPE_128, (Service_UUID_t *)&serviceUUID,
            PRIMARY_SERVICE,
            SERVICE_MAX_ATT_RECORDS,
            &retHandle);
    this->Set_Handle((uintptr_t)retHandle);
    return ret;
}

SVCCTL_EvtAckStatus_t BLE::PrefService::Static_Event_Handler(void *Event)
{
    return BLE::PrefService::Instance()->Event_Handler(Event);
}

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
SVCCTL_EvtAckStatus_t BLE::PrefService::Event_Handler(void *Event)
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
                        if (attribute_modified->Attr_Handle == (colorScheme.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Get_Pref()->scheme = ((Sys::Scheme)data[0]);
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

uintptr_t BLE::PrefService::Get_Handle() const
{
    return this->handle;
}

void BLE::PrefService::Set_Handle(uintptr_t pHandle)
{
    this->handle = pHandle;
}

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void BLE::PrefService::Init()
{
    /* Register the event handler to the BLE controller */
    SVCCTL_RegisterSvcHandler(BLE::PrefService::Static_Event_Handler);

    /* Add Service */
    if (this->Add() != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t colorSchemeUUID = BLE::UUID::CreateCharUUID({0xbd,0x77,0x11,0xb1,0xbb,0x11,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    colorScheme = BLE::Char(UUID_TYPE_128, &colorSchemeUUID,
            1 + 1,
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (colorScheme.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

}

/**
 * @brief Characteristic update
 * @param UUID: UUID of the characteristic
 * @param newValueLength: Length of the new value data to be written
 * @param pNewValue: Pointer to the new value data 
 */
tBleStatus BLE::PrefService::Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue)
{
    tBleStatus ret = BLE_STATUS_INVALID_PARAMS;

    /* if (UUID16 == BLE::UUID::ExtractUUID16FromLE(syncRequestChar.Get_UUID())) { */
    /*     if (newValueLength <= syncRequestChar.Get_Value_Length()) */
    /*     { */
    /*         ret = aci_gatt_update_char_value(this->Get_Handle(), */
    /*                 syncRequestChar.Get_Handle(), */
    /*                 0, /1* charValOffset *1/ */
    /*                 newValueLength, /1* charValueLen *1/ */
    /*                 (uint8_t *)pNewValue); */
    /*     } */
    /* } */
    return ret;
}
