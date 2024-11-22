#include "services/simple.hpp"

#include "gpio/gpio.hpp"
#include "sys/sys.hpp"

#include "ble_common.h"
#include "ble.h"
#include "ble_types.h"


BLE::SimpleService::SimpleService(GPIO::Controller *pGpioCtrl, Sys::State *pSysState)
    : gpioCtrl(pGpioCtrl),
    sysState(pSysState)
{}

BLE::SimpleService::~SimpleService()
{}

tBleStatus BLE::SimpleService::Add()
{
    COPY_SERVICE_UUID(uuid16.Char_UUID_128);
    return aci_gatt_add_service(UUID_TYPE_128,
            (Service_UUID_t *)&uuid16,
            PRIMARY_SERVICE,
            SERVICE_MAX_ATT_RECORDS,
            &(serviceContext.Service_Handle));
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
                        if(attribute_modified->Attr_Handle == (serviceContext.Write_Characteristic_Handle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
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

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void BLE::SimpleService::Init()
{
    Char_UUID_t uuid16;

    /* Register the event handler to the BLE controller */
    SVCCTL_RegisterSvcHandler(SimpleService::Event_Handler);

    /* Add Service */
    if (this.Add() != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    /* Add LED Write Characteristic */
    COPY_WRITE_CHARACTERISTIC_UUID(uuid16.Char_UUID_128);
    ledWriteChar = BLE::Char(UUID_TYPE_128, &uuid16,
            2,
            CHAR_PROP_WRITE_WITHOUT_RESP|CHAR_PROP_READ,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            VALUE_VARIABLE_LENGTH);
    if (ledWriteChar.Add(this.Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    /* Add Notify Characteristic */
    COPY_NOTIFY_CHARACTERISTIC_UUID(uuid16.Char_UUID_128);
    bellNotifyChar = BLE::Char(UUID_TYPE_128, &uuid16,
            2,
            CHAR_PROP_NOTIFY,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE,
            10,
            VALUE_VARIABLE_LENGTH);
    if (bellNotifyChar.Add(this.Get_Handle()) != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */
}
