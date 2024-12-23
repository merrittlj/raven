#include "services/event.hpp"

#include "ble/char.hpp"
#include "ble/uuid.hpp"
#include "gpio/gpio.hpp"
#include "sys/sys.hpp"
#include "sys/state.hpp"

#include "ble_common.h"
#include "ble.h"
#include "ble_types.h"


BLE::EventService::EventService(GPIO::Controller *pGpioCtrl, Sys::State *pSysState)
{
    this->gpioCtrl = pGpioCtrl;
    this->sysState = pSysState;

    BLE::EventService::Instance(this);
}

BLE::EventService::~EventService()
{}

tBleStatus BLE::EventService::Add()
{
    uint16_t retHandle;
    
    Char_UUID_t serviceUUID = BLE::UUID::CreateCharUUID({0x00,0xa9,0x70,0xd0,0xc0,0xdb,0x11,0xef,0xa8,0xfa,0x08,0x00,0x20,0x0c,0x9a,0x66});
    tBleStatus ret = aci_gatt_add_service(UUID_TYPE_128, (Service_UUID_t *)&serviceUUID,
            PRIMARY_SERVICE,
            SERVICE_MAX_ATT_RECORDS,
            &retHandle);
    this->Set_Handle((uintptr_t)retHandle);
    return ret;
}

SVCCTL_EvtAckStatus_t BLE::EventService::Static_Event_Handler(void *Event)
{
    return BLE::EventService::Instance()->Event_Handler(Event);
}

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
SVCCTL_EvtAckStatus_t BLE::EventService::Event_Handler(void *Event)
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
                        if (attribute_modified->Attr_Handle == (type.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            /* Set type */
                        }
                        if (attribute_modified->Attr_Handle == (id.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            /* Set id */
                        }
                        if (attribute_modified->Attr_Handle == (title.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            /* Set title */
                        }
                        if (attribute_modified->Attr_Handle == (desc.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            /* Set desc */
                        }
                        if (attribute_modified->Attr_Handle == (timestamp.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            /* Set timestamp */
                        }
                        if (attribute_modified->Attr_Handle == (repDur.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            /* Set repDur */
                        }
                        if (attribute_modified->Attr_Handle == (trigger.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            /* Set trigger */
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

uintptr_t BLE::EventService::Get_Handle() const
{
    return this->handle;
}

void BLE::EventService::Set_Handle(uintptr_t pHandle)
{
    this->handle = pHandle;
}

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void BLE::EventService::Init()
{
    /* Register the event handler to the BLE controller */
    SVCCTL_RegisterSvcHandler(BLE::EventService::Static_Event_Handler);

    /* Add Service */
    if (this->Add() != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t typeUUID = BLE::UUID::CreateCharUUID({0x00,0xa9,0x70,0xd1,0xc0,0xdb,0x11,0xef,0xa8,0xfa,0x08,0x00,0x20,0x0c,0x9a,0x66});
    type = BLE::Char(UUID_TYPE_128, &typeUUID,
            1 + 1,
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (type.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t idUUID = BLE::UUID::CreateCharUUID({0x00,0xa9,0x70,0xd2,0xc0,0xdb,0x11,0xef,0xa8,0xfa,0x08,0x00,0x20,0x0c,0x9a,0x66});
    id = BLE::Char(UUID_TYPE_128, &idUUID,
            1 + 1,
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (id.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t titleUUID = BLE::UUID::CreateCharUUID({0x00,0xa9,0x70,0xd3,0xc0,0xdb,0x11,0xef,0xa8,0xfa,0x08,0x00,0x20,0x0c,0x9a,0x66});
    title = BLE::Char(UUID_TYPE_128, &titleUUID,
            1 + 1,
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (title.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t descUUID = BLE::UUID::CreateCharUUID({0x00,0xa9,0x70,0xd4,0xc0,0xdb,0x11,0xef,0xa8,0xfa,0x08,0x00,0x20,0x0c,0x9a,0x66});
    desc = BLE::Char(UUID_TYPE_128, &descUUID,
            1 + 1,
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (desc.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t timestampUUID = BLE::UUID::CreateCharUUID({0x00,0xa9,0x70,0xd5,0xc0,0xdb,0x11,0xef,0xa8,0xfa,0x08,0x00,0x20,0x0c,0x9a,0x66});
    timestamp = BLE::Char(UUID_TYPE_128, &timestampUUID,
            1 + 1,
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (timestamp.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t repDurUUID = BLE::UUID::CreateCharUUID({0x00,0xa9,0x70,0xd6,0xc0,0xdb,0x11,0xef,0xa8,0xfa,0x08,0x00,0x20,0x0c,0x9a,0x66});
    repDur = BLE::Char(UUID_TYPE_128, &repDurUUID,
            1 + 1,
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (repDur.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t triggerUUID = BLE::UUID::CreateCharUUID({0x00,0xa9,0x70,0xd7,0xc0,0xdb,0x11,0xef,0xa8,0xfa,0x08,0x00,0x20,0x0c,0x9a,0x66});
    trigger = BLE::Char(UUID_TYPE_128, &triggerUUID,
            1 + 1,
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
tBleStatus BLE::EventService::Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue)
{
    tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
    return ret;
}
