#include "services/simple.hpp"

#include "ble/char.hpp"
#include "ble/uuid.hpp"
#include "gpio/gpio.hpp"
#include "sys/sys.hpp"

#include "ble_common.h"
#include "ble.h"
#include "ble_types.h"


BLE::SimpleService::SimpleService(GPIO::Controller *pGpioCtrl, Sys::State *pSysState)
{
    this->gpioCtrl = pGpioCtrl;
    this->sysState = pSysState;
}

BLE::SimpleService::~SimpleService()
{}

tBleStatus BLE::SimpleService::Add()
{
    uint16_t retHandle;
    Char_UUID_t serviceUUID = BLE::UUID::CreateCharUUID({0x00,0x00,0xfe,0x40,0xcc,0x7a,0x48,0x2a,0x98,0x4a,0x7f,0x2e,0xd5,0xb3,0xe5,0x8f});
    tBleStatus ret = aci_gatt_add_service(UUID_TYPE_128, (Service_UUID_t *)&serviceUUID,
            PRIMARY_SERVICE,
            SERVICE_MAX_ATT_RECORDS,
            &retHandle);
    this->Set_Handle((uintptr_t)retHandle);
    return ret;
}

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
SVCCTL_EvtAckStatus_t BLE::SimpleService::Event_Handler(void *Event)
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
                        if(attribute_modified->Attr_Handle == (ledWriteChar.Get_Handle() + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
                        {
                            if (attribute_modified->Attr_Data[1] == 0x01)
                            {
                                this->gpioCtrl->Write_Component(this->sysState->Fetch_LED_Blue(), SET);
                            } else {
                                this->gpioCtrl->Write_Component(this->sysState->Fetch_LED_Blue(), RESET);
                            }
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

uintptr_t BLE::SimpleService::Get_Handle() const
{
    return this->handle;
}

void BLE::SimpleService::Set_Handle(uintptr_t pHandle)
{
    this->handle = handle;
}

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void BLE::SimpleService::Init()
{
    /* Register the event handler to the BLE controller */
    SVCCTL_RegisterSvcHandler(SimpleService::Event_Handler);

    /* Add Service */
    if (this->Add() != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    /* Add LED Write Characteristic */
    ledWriteChar = BLE::Char(UUID_TYPE_128, BLE::UUID::CreateCharUUID({0x00,0x00,0xfe,0x41,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19}),
            2,
            CHAR_PROP_WRITE_WITHOUT_RESP|CHAR_PROP_READ,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            VALUE_VARIABLE_LENGTH);
    if (ledWriteChar.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    /* Add Notify Characteristic */
    bellNotifyChar = BLE::Char(UUID_TYPE_128, BLE::UUID::CreateCharUUID({0x00,0x00,0xfe,0x42,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19}),
            2,
            CHAR_PROP_NOTIFY,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            VALUE_VARIABLE_LENGTH);
    if (bellNotifyChar.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */
}

/**
 * @brief Characteristic update
 * @param UUID: UUID of the characteristic
 * @param newValueLength: Length of the new value data to be written
 * @param pNewValue: Pointer to the new value data 
 */
tBleStatus BLE::SimpleService::Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue)
{
    tBleStatus ret = BLE_STATUS_INVALID_PARAMS;

    switch (UUID16) {
        case BLE::UUID::ExtractUUID16FromLE(bellNotifyChar.Get_UUID()):
            if (newValueLength <= bellNotifyChar.Get_Value_Length())
            {
                ret = aci_gatt_update_char_value(this->Get_Handle(),
                        bellNotifyChar.Get_Handle(),
                        0, /* charValOffset */
                        newValueLength, /* charValueLen */
                        (uint8_t *)pNewValue);
            }
            break;
        default:
            break;
    }

    return ret;
}
