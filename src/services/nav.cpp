#include "services/nav.hpp"

#include "ble/char.hpp"
#include "ble/uuid.hpp"
#include "gpio/gpio.hpp"
#include "sys/sys.hpp"
#include "sys/state.hpp"

#include "ble_common.h"
#include "ble.h"
#include "ble_types.h"


BLE::NavService::NavService(GPIO::Controller *pGpioCtrl, Sys::State *pSysState)
{
    this->gpioCtrl = pGpioCtrl;
    this->sysState = pSysState;

    BLE::NavService::Instance(this);
}

BLE::NavService::~NavService()
{}

tBleStatus BLE::NavService::Add()
{
    uint16_t retHandle;
    Char_UUID_t serviceUUID = BLE::UUID::CreateCharUUID({0x84,0xd7,0x3b,0xe0,0xbc,0x48,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    tBleStatus ret = aci_gatt_add_service(UUID_TYPE_128, (Service_UUID_t *)&serviceUUID,
            PRIMARY_SERVICE,
            SERVICE_MAX_ATT_RECORDS,
            &retHandle);
    this->Set_Handle((uintptr_t)retHandle);
    return ret;
}

SVCCTL_EvtAckStatus_t BLE::NavService::Static_Event_Handler(void *Event)
{
    return BLE::NavService::Instance()->Event_Handler(Event);
}

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
SVCCTL_EvtAckStatus_t BLE::NavService::Event_Handler(void *Event)
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
                        if (attribute_modified->Attr_Handle == (instruction.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Nav_Build_Instruction(std::string((const char *)data, (size_t)length));
                        }
                        if (attribute_modified->Attr_Handle == (distance.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Nav_Build_Distance(std::string((const char *)data, (size_t)length));
                        }
                        if (attribute_modified->Attr_Handle == (eta.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Nav_Build_ETA(std::string((const char *)data, (size_t)length));
                        }
                        if (attribute_modified->Attr_Handle == (action.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Nav_Build_Action(std::string((const char *)data, (size_t)length));
                        }
                        if (attribute_modified->Attr_Handle == (trigger.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Nav_Trigger();
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

uintptr_t BLE::NavService::Get_Handle() const
{
    return this->handle;
}

void BLE::NavService::Set_Handle(uintptr_t pHandle)
{
    this->handle = pHandle;
}

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void BLE::NavService::Init()
{
    /* Register the event handler to the BLE controller */
    SVCCTL_RegisterSvcHandler(BLE::NavService::Static_Event_Handler);

    /* Add Service */
    if (this->Add() != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t instructionUUID = BLE::UUID::CreateCharUUID({0x84,0xd7,0x3b,0xe1,0xbc,0x48,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    instruction = BLE::Char(UUID_TYPE_128, &instructionUUID,
            40,
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (instruction.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t distanceUUID = BLE::UUID::CreateCharUUID({0x84,0xd7,0x3b,0xe2,0xbc,0x48,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    distance = BLE::Char(UUID_TYPE_128, &distanceUUID,
            7,
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (distance.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t etaUUID = BLE::UUID::CreateCharUUID({0x84,0xd7,0x3b,0xe3,0xbc,0x48,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    eta = BLE::Char(UUID_TYPE_128, &etaUUID,
            5,
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (eta.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t actionUUID = BLE::UUID::CreateCharUUID({0x84,0xd7,0x3b,0xe4,0xbc,0x48,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
    action = BLE::Char(UUID_TYPE_128, &actionUUID,
            20,
            CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (action.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t triggerUUID = BLE::UUID::CreateCharUUID({0x84,0xd7,0x3b,0xe5,0xbc,0x48,0x11,0xef,0x99,0x08,0x08,0x00,0x20,0x0c,0x9a,0x66});
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
tBleStatus BLE::NavService::Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue)
{
    tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
    return ret;
}
