#include "services/notify.hpp"

#include "ble/char.hpp"
#include "ble/uuid.hpp"
#include "gpio/gpio.hpp"
#include "sys/sys.hpp"
#include "sys/state.hpp"

#include "ble_common.h"
#include "ble.h"
#include "ble_types.h"


BLE::NotifyService::NotifyService(GPIO::Controller *pGpioCtrl, Sys::State *pSysState)
{
    this->gpioCtrl = pGpioCtrl;
    this->sysState = pSysState;

    BLE::NotifyService::Instance(this);
}

BLE::NotifyService::~NotifyService()
{}

tBleStatus BLE::NotifyService::Add()
{
    uint16_t retHandle;
    Char_UUID_t serviceUUID = BLE::UUID::CreateCharUUID({0x68,0x4A,0x49,0x60,0xB6,0xA6,0x11,0xEF,0xBE,0x87,0x08,0x00,0x20,0x0C,0x9A,0x66});
    tBleStatus ret = aci_gatt_add_service(UUID_TYPE_128, (Service_UUID_t *)&serviceUUID,
            PRIMARY_SERVICE,
            SERVICE_MAX_ATT_RECORDS,
            &retHandle);
    this->Set_Handle((uintptr_t)retHandle);
    return ret;
}

SVCCTL_EvtAckStatus_t BLE::NotifyService::Static_Event_Handler(void *Event)
{
    return BLE::NotifyService::Instance()->Event_Handler(Event);
}

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
SVCCTL_EvtAckStatus_t BLE::NotifyService::Event_Handler(void *Event)
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
                        if (attribute_modified->Attr_Handle == (source.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Alert_Build_Source(std::string((const char *)data, (size_t)length));
                        }
                        if (attribute_modified->Attr_Handle == (title.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Alert_Build_Title(std::string((const char *)data, (size_t)length));
                        }
                        if (attribute_modified->Attr_Handle == (body.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Alert_Build_Body(std::string((const char *)data, (size_t)length));
                        }
                        if (attribute_modified->Attr_Handle == (trigger.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Alert_Trigger();
                            /* gpioCtrl->Write_Component(this->sysState->Fetch_LED_Red(), SET); */
                            /* Sys::Delay(50); */
                            /* gpioCtrl->Write_Component(this->sysState->Fetch_LED_Red(), RESET); */
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

uintptr_t BLE::NotifyService::Get_Handle() const
{
    return this->handle;
}

void BLE::NotifyService::Set_Handle(uintptr_t pHandle)
{
    this->handle = pHandle;
}

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void BLE::NotifyService::Init()
{
    /* Register the event handler to the BLE controller */
    SVCCTL_RegisterSvcHandler(BLE::NotifyService::Static_Event_Handler);

    /* Add Service */
    if (this->Add() != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t sourceUUID = BLE::UUID::CreateCharUUID({0x68,0x4A,0x49,0x61,0xB6,0xA6,0x11,0xEF,0xBE,0x87,0x08,0x00,0x20,0x0C,0x9A,0x66});
    source = BLE::Char(UUID_TYPE_128, &sourceUUID,
            15,
            CHAR_PROP_READ | CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (source.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t titleUUID = BLE::UUID::CreateCharUUID({0x68,0x4A,0x49,0x62,0xB6,0xA6,0x11,0xEF,0xBE,0x87,0x08,0x00,0x20,0x0C,0x9A,0x66});
    title = BLE::Char(UUID_TYPE_128, &titleUUID,
            15,
            CHAR_PROP_READ | CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (title.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t bodyUUID = BLE::UUID::CreateCharUUID({0x68,0x4A,0x49,0x63,0xB6,0xA6,0x11,0xEF,0xBE,0x87,0x08,0x00,0x20,0x0C,0x9A,0x66});
    body = BLE::Char(UUID_TYPE_128, &bodyUUID,
            90,
            CHAR_PROP_READ | CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (body.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t triggerUUID = BLE::UUID::CreateCharUUID({0x68,0x4A,0x49,0x64,0xB6,0xA6,0x11,0xEF,0xBE,0x87,0x08,0x00,0x20,0x0C,0x9A,0x66});
    trigger = BLE::Char(UUID_TYPE_128, &triggerUUID,
            1,
            CHAR_PROP_READ | CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    tBleStatus ret = trigger.Add(this->Get_Handle());
    if (ret != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */
}

/**
 * @brief Characteristic update
 * @param UUID: UUID of the characteristic
 * @param newValueLength: Length of the new value data to be written
 * @param pNewValue: Pointer to the new value data 
 */
tBleStatus BLE::NotifyService::Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue)
{
    tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
    return ret;
}
