#include "services/time.hpp"

#include "ble/char.hpp"
#include "ble/uuid.hpp"
#include "gpio/gpio.hpp"
#include "sys/sys.hpp"
#include "sys/state.hpp"

#include "ble_common.h"
#include "ble.h"
#include "ble_types.h"


BLE::TimeService::TimeService(GPIO::Controller *pGpioCtrl, Sys::State *pSysState)
{
    this->gpioCtrl = pGpioCtrl;
    this->sysState = pSysState;

    BLE::TimeService::Instance(this);
}

BLE::TimeService::~TimeService()
{}

tBleStatus BLE::TimeService::Add()
{
    uint16_t retHandle;
    /* 0x1805: Current Time Service */
    Char_UUID_t serviceUUID = BLE::UUID::CreateCharUUID(0x1805);
    tBleStatus ret = aci_gatt_add_service(UUID_TYPE_16, (Service_UUID_t *)&serviceUUID,
            PRIMARY_SERVICE,
            SERVICE_MAX_ATT_RECORDS,
            &retHandle);
    this->Set_Handle((uintptr_t)retHandle);
    return ret;
}

SVCCTL_EvtAckStatus_t BLE::TimeService::Static_Event_Handler(void *Event)
{
    return BLE::TimeService::Instance()->Event_Handler(Event);
}

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
SVCCTL_EvtAckStatus_t BLE::TimeService::Event_Handler(void *Event)
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
                        if (attribute_modified->Attr_Handle == (currentTime.Get_Handle() + CHAR_VALUE_OFFSET)) {
                            sysState->Update_Time(Sys::Time{data[4], data[5], data[6]});
                            gpioCtrl->Write_Component(this->sysState->Fetch_LED_Blue(), SET);
                            HAL_Delay(50);
                            gpioCtrl->Write_Component(this->sysState->Fetch_LED_Blue(), RESET);
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

uintptr_t BLE::TimeService::Get_Handle() const
{
    return this->handle;
}

void BLE::TimeService::Set_Handle(uintptr_t pHandle)
{
    this->handle = pHandle;
}

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void BLE::TimeService::Init()
{
    /* Register the event handler to the BLE controller */
    SVCCTL_RegisterSvcHandler(BLE::TimeService::Static_Event_Handler);

    /* Add Service */
    if (this->Add() != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t *currentTimeUUID = new Char_UUID_t;
    /* 0x2A2B: Current Time Characteristic */
    *currentTimeUUID = BLE::UUID::CreateCharUUID(0x2A2B);
    currentTime = BLE::Char(UUID_TYPE_16, currentTimeUUID,
            10,
            CHAR_PROP_READ | CHAR_PROP_WRITE | CHAR_PROP_NOTIFY,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (currentTime.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    Char_UUID_t *localTimeUUID = new Char_UUID_t;
    /* 0x2A0F: Local Time Information Characteristic */
    *localTimeUUID = BLE::UUID::CreateCharUUID(0x2A0F);
    localTime = BLE::Char(UUID_TYPE_16, localTimeUUID,
            18,
            CHAR_PROP_READ | CHAR_PROP_WRITE,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            (uint8_t)VALUE_VARIABLE_LENGTH);
    if (localTime.Add(this->Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */
}

/**
 * @brief Characteristic update
 * @param UUID: UUID of the characteristic
 * @param newValueLength: Length of the new value data to be written
 * @param pNewValue: Pointer to the new value data 
 */
tBleStatus BLE::TimeService::Update_Char_Value(uint16_t UUID16, uint16_t newValueLength, uint8_t *pNewValue)
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
