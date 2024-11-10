#include "ble/gatt_service.hpp"
#include "core/main.hpp"
#include "sys/sys.hpp"

#include "ble_common.h"
#include "ble.h"
#include "ble_types.h"


BLE::Gatt_Service::Gatt_Service(GPIO::Controller &gpioCtrl, Sys::State &sysState)
{
    this.gpioCtrl = gpioCtrl;
    this.sysState = sysState;
}

BLE::Gatt_Service::~Gatt_Service()
{

}

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
SVCCTL_EvtAckStatus_t BLE::Gatt_Service::Event_Handler(void *Event)
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
                                this.gpioCtrl.Write_Component(this.sysState.Fetch_LED_Blue(), SET);
                            } else {
                                this.gpioCtrl.Write_Component(this.sysState.Fetch_LED_Blue(), RESET);
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
void BLE::Gatt_Service::Init()
{
    tBleStatus ret = BLE_STATUS_SUCCESS;
    Char_UUID_t uuid16;

    /* Register the event handler to the BLE controller */
    SVCCTL_RegisterSvcHandler(this.Event_Handler);

    /* Add Service */
    COPY_SERVICE_UUID(uuid16.Char_UUID_128);
    ret = aci_gatt_add_service(UUID_TYPE_128,
            (Service_UUID_t *)&uuid16,
            PRIMARY_SERVICE,
            SERVICE_MAX_ATT_RECORDS,
            &(serviceContext.Service_Handle));
    if (ret != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    /* Add Write Characteristic */
    COPY_WRITE_CHARACTERISTIC_UUID(uuid16.Char_UUID_128);
    ret = aci_gatt_add_char(serviceContext.Service_Handle,
            UUID_TYPE_128, &uuid16,
            WRITE_CHARACTERISTIC_VALUE_LENGTH,                                   
            CHAR_PROP_WRITE_WITHOUT_RESP|CHAR_PROP_READ,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE, /* gattEvtMask */
            10, /* encryKeySize */
            1, /* isVariable */
            &(serviceContext.Write_Characteristic_Handle));
    if (ret != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    /* Add Notify Characteristic */
    COPY_NOTIFY_CHARACTERISTIC_UUID(uuid16.Char_UUID_128);
    ret = aci_gatt_add_char(serviceContext.Service_Handle,
            UUID_TYPE_128, &uuid16,
            NOTIFY_CHARACTERISTIC_VALUE_LENGTH,
            CHAR_PROP_NOTIFY,
            ATTR_PERMISSION_NONE,
            GATT_NOTIFY_ATTRIBUTE_WRITE, /* gattEvtMask */
            10, /* encryKeySize */
            1, /* isVariable: 1 */
            &(serviceContext.Notify_Characteristic_Handle));
    if (ret != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */
}

/**
 * @brief Characteristic update
 * @param UUID: UUID of the characteristic
 * @param newValueLength: Length of the new value data to be written
 * @param pNewValue: Pointer to the new value data 
 */
tBleStatus BLE::Gatt_Service::Write_Characteristic_Update(uint16_t UUID, uint16_t newValueLength, uint8_t *pNewValue)
{
    tBleStatus ret = BLE_STATUS_INVALID_PARAMS;

    switch (UUID) {
        case NOTIFY_CHARACTERISTIC_UUID:
            if (newValueLength <= NOTIFY_CHARACTERISTIC_VALUE_LENGTH)
            {
                ret = aci_gatt_update_char_value(serviceContext.Service_Handle,
                        serviceContext.Notify_Characteristic_Handle,
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
