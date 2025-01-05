#include "ble/ble.hpp"

#include "app/common.hpp"
#include "services/time.hpp"
#include "sys/sys.hpp"
#include "sys/state.hpp"
#include "display/controller.hpp"

#include "shci.h"
#include "otp.h"


BLE::App::App(GPIO::Controller *pGpioCtrl, Sys::State *pSysState)
{
    this->gpioCtrl = pGpioCtrl;
    this->sysState = pSysState;

    BLE::App::Instance(this);
}

BLE::App::~App()
{
    delete theInstance;
}

BLE::App *BLE::App::Instance(App *cur)
{
    if (!theInstance) theInstance = cur;
    return theInstance;
}

void BLE::App::Init()
{
    /* At this point it is still unknown from the app perspective, which wireless stack
       and which version is installed on CPU2. It is expected that a BLE stack is installed.
       In order to check that, SHCI_GetWirelessFwInfo(...) can be used to read out
       the information about the CM0+ wireless stack FW running since the Device Information Table
       is initialized. For more information on this topic, please refer to AN5289 and AN5185. */

    /* Initialize BLE (BLE TL, BLE stack, HAL, HCI, GATT, GAP) */
    BLE_Init();

    this->gpioCtrl->Write_Component(this->sysState->Fetch_LED_Blue(), SET);
    /* TODO: add more */
}

/**
 * @brief This function starts or stops the BLE advertising
 * @param newState: SET to start the advertising, RESET to stop
 * @retval None
 */
void BLE::App::Advertising(FlagStatus newState)
{
    tBleStatus ret = BLE_STATUS_SUCCESS;

    if (newState == SET)
    {
        if (this->sysState->App_Flag_Get(Sys::State::App_Flag::BLE_ADVERTISING) == Sys::State::Flag_Val::NOT_SET)
        {
            /* Put(set) the device in a advertising & connectable mode. */
            ret = aci_gap_set_discoverable(ADV_IND,                                       /*< Advertise as connectable, undirected. */
                    CFG_FAST_CONN_ADV_INTERVAL_MIN,                /*< Set the advertising interval min value. */
                    CFG_FAST_CONN_ADV_INTERVAL_MAX,                /*< Set the advertising interval max value. */
                    GAP_PUBLIC_ADDR,                                   /*< Use the public address. */
                    NO_WHITE_LIST_USE,                             /*< No white list. */
                    sizeof(ad_local_name), (uint8_t*)ad_local_name,/*< Use a local name. */
                    0, NULL,                                       /*< Do not include the service UUID list. (no adopted services) */
                    0x0000, 0x0000);                               /*< NaN, do not put in advertising data. */
            if (ret != BLE_STATUS_SUCCESS)
                Sys::Error_Handler(); /* UNEXPECTED */

            this->sysState->App_Flag_Set(Sys::State::App_Flag::BLE_ADVERTISING);
        }
    } else {
        /* Stop(reset) device advertising. */
        ret = aci_gap_set_non_discoverable();
        if (ret != BLE_STATUS_SUCCESS)
            Sys::Error_Handler(); /* UNEXPECTED */
        this->sysState->App_Flag_Reset(Sys::State::App_Flag::BLE_ADVERTISING);
    }
}

/**
 * @brief This function initializes the BLE stack
 * @param None
 * @retval None
 */
void BLE::App::BLE_Init()
{
    SHCI_CmdStatus_t ret;

    SHCI_C2_Ble_Init_Cmd_Packet_t ble_init_cmd_packet =
    {
        {{0,0,0}},                          /**< Header unused */
        {0,                                 /** pBleBufferAddress not used */
            0,                                  /** BleBufferSize not used */
            CFG_BLE_NUM_GATT_ATTRIBUTES,
            CFG_BLE_NUM_GATT_SERVICES,
            CFG_BLE_ATT_VALUE_ARRAY_SIZE,
            CFG_BLE_NUM_LINK,
            CFG_BLE_DATA_LENGTH_EXTENSION,
            CFG_BLE_PREPARE_WRITE_LIST_SIZE,
            CFG_BLE_MBLOCK_COUNT,
            CFG_BLE_MAX_ATT_MTU,
            CFG_BLE_PERIPHERAL_SCA,
            CFG_BLE_CENTRAL_SCA,
            CFG_BLE_LS_SOURCE,
            CFG_BLE_MAX_CONN_EVENT_LENGTH,
            CFG_BLE_HSE_STARTUP_TIME,
            CFG_BLE_VITERBI_MODE,
            CFG_BLE_OPTIONS,
            0,
            CFG_BLE_MAX_COC_INITIATOR_NBR,
            CFG_BLE_MIN_TX_POWER,
            CFG_BLE_MAX_TX_POWER,
            CFG_BLE_RX_MODEL_CONFIG,
            CFG_BLE_MAX_ADV_SET_NBR, 
            CFG_BLE_MAX_ADV_DATA_LEN,
            CFG_BLE_TX_PATH_COMPENS,
            CFG_BLE_RX_PATH_COMPENS,
            CFG_BLE_CORE_VERSION,
            CFG_BLE_OPTIONS_EXT
        }
    };

    /**
     * Initialize Ble Transport Layer
     */
    Tl_Init();

    /**
     * Starts the BLE Stack on CPU2
     */
    ret = SHCI_C2_BLE_Init(&ble_init_cmd_packet);
    if (ret != SHCI_Success)
        Sys::Error_Handler(); /* UNEXPECTED */

    /**
     * Initialization of HCI & GATT & GAP layer
     */
    Hci_Gap_Gatt_Init();

    /**
     * Initialization of the BLE Services
     */
    SVCCTL_Init();
}

/**
 * @brief This function initializes the BLE Transport Layer
 * @param None
 * @retval None
 */
void BLE::App::Tl_Init()
{
    HCI_TL_HciInitConf_t Hci_Tl_Init_Conf;

    /**< BLE channel initialization */
    Hci_Tl_Init_Conf.p_cmdbuffer = (uint8_t *)&(this->sysState->BLECmdBuffer);
    Hci_Tl_Init_Conf.StatusNotCallBack = Sys::Event_Processor::BLE_StatusNotificationCallback;

    hci_init(Sys::Event_Processor::BLE_UserEventReceivedCallback, (void*)&Hci_Tl_Init_Conf);
}

/**
 * @brief This function initializes the BLE stack and all its modules
 * @param None
 * @retval None
 */
void BLE::App::Hci_Gap_Gatt_Init()
{
    uint16_t gap_service_handle, gap_dev_name_char_handle, gap_appearance_char_handle;
    const uint8_t *bd_address;
    uint32_t srd_bd_address[2];
    tBleStatus ret = BLE_STATUS_SUCCESS;

    /**
     * BLE HCI Reset to synchronize BLE Stack
     */
    hci_reset();

    /**
     * Write the BD Address
     */
    bd_address = GetBdAddress();
    aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET,
            CONFIG_DATA_PUBADDR_LEN,
            (uint8_t*) bd_address);

    /**
     * Static random Address
     * The two upper bits shall be set to 1
     * The lowest 32bits is read from the UDN to differentiate between devices
     * The RNG may be used to provide a random number on each power on
     */
    srd_bd_address[1] =  0x0000ED6E;
    srd_bd_address[0] =  LL_FLASH_GetUDN( );
    ret = aci_hal_write_config_data(CONFIG_DATA_RANDOM_ADDRESS_OFFSET,
            CONFIG_DATA_RANDOM_ADDRESS_LEN,
            (uint8_t*)srd_bd_address);

    /**
     * Set TX Power.
     */
    ret = aci_hal_set_tx_power_level(0, CFG_TX_POWER);
    if (ret != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    /**
     * Set Radio activity event mask.
     */
    ret = aci_hal_set_radio_activity_mask(CFG_RADIO_ACTIVITY_EVENT_MASK);
    if (ret != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    /**
     * Initialize GATT
     */
    ret = aci_gatt_init();
    if (ret != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    /**
     * Initialize GAP
     */
    ret = aci_gap_init(GAP_PERIPHERAL_ROLE,
            PRIVACY_DISABLED,
            APP_BLE_GAP_DEVICE_NAME_LENGTH,
            &gap_service_handle,
            &gap_dev_name_char_handle,
            &gap_appearance_char_handle);
    if (ret != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    /**
     * Update GAP Service Device Name characteristic value
     */
    ret = aci_gatt_update_char_value(gap_service_handle,
            gap_dev_name_char_handle,
            0,
            sizeof(gap_device_name),
            (uint8_t *)gap_device_name);
    if (ret != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */

    /**
     * Update GAP Service Appearance  characteristic value
     */
    ret = aci_gatt_update_char_value(gap_service_handle,
            gap_appearance_char_handle,
            0,
            sizeof(gap_appearance),
            (uint8_t *)&gap_appearance);
    if (ret != BLE_STATUS_SUCCESS)
        Sys::Error_Handler(); /* UNEXPECTED */
}

/**
 * @brief This function generates the unique BD address from the UDN
 * @param None
 * @retval Pointer to the array holding the BD address
 */
const uint8_t* BLE::App::GetBdAddress()
{
    uint8_t *p_otp_addr;
    const uint8_t *p_bd_addr;
    uint32_t udn;
    uint32_t company_id;
    uint32_t device_id;

    udn = LL_FLASH_GetUDN();

    if (udn != 0xFFFFFFFF)
    {
        company_id = LL_FLASH_GetSTCompanyID();
        device_id = LL_FLASH_GetDeviceID();

        /**
         * Public Address with the ST company ID
         * bit[47:24] : 24bits (OUI) equal to the company ID
         * bit[23:16] : Device ID.
         * bit[15:0] : The last 16bits from the UDN
         * Note: In order to use the Public Address in a final product, a dedicated
         * 24bits company ID (OUI) shall be bought.
         */
        bd_address_udn[0] = (uint8_t)(udn & 0x000000FF);
        bd_address_udn[1] = (uint8_t)((udn & 0x0000FF00) >> 8);
        bd_address_udn[2] = (uint8_t)device_id;
        bd_address_udn[3] = (uint8_t)(company_id & 0x000000FF);
        bd_address_udn[4] = (uint8_t)((company_id & 0x0000FF00) >> 8);
        bd_address_udn[5] = (uint8_t)((company_id & 0x00FF0000) >> 16);

        p_bd_addr = (const uint8_t *)bd_address_udn;
    }
    else
    {
        p_otp_addr = OTP_Read(0);
        if (p_otp_addr)
        {
            p_bd_addr = ((OTP_ID0_t*)p_otp_addr)->bd_address;
        } else
        {
            p_bd_addr = a_MBdAddr;
        }
    }

    return p_bd_addr;
}

/**
 * @brief This callback is triggered when either
 *          + a GAP event is received from the BLE core device.
 *          + a GATT event that has not been positively acknowledged by the registered handler is received from the
 *            BLE core device.
 *        The event is returned in a HCI packet. The full HCI packet is stored in a single buffer and is available when
 *        this callback is triggered. However, an ACI event may be longer than a HCI packet and could be fragmented over
 *        several HCI packets. The HCI layer only handles HCI packets so when an ACI packet is split over several HCI
 *        packets, this callback is triggered for each HCI fragment. It is the responsibility of the application to
 *        reassemble the ACI event.
 *        This callback is triggered in the TL_BLE_HCI_UserEvtProc() context
 *
 * @param  pckt: The user event received from the BLE core device
 * @retval None
 */
SVCCTL_UserEvtFlowStatus_t BLE::App::SVCCTL_Notification_Handler(void *pckt)
{
    hci_event_pckt *event_pckt;
    evt_blecore_aci *blecore_evt;
    evt_le_meta_event *le_meta_evt;

    event_pckt = (hci_event_pckt*) ((hci_uart_pckt *) pckt)->data;

    switch (event_pckt->evt)
    {
        case HCI_DISCONNECTION_COMPLETE_EVT_CODE:
            this->sysState->App_Flag_Reset(Sys::State::App_Flag::BLE_CONNECTED);

            Display::Controller::Instance()->Tag_Screen();

            /* Start advertising */
            this->Advertising(SET);
            break; /* HCI_DISCONNECTION_COMPLETE_EVT_CODE */
        case HCI_LE_META_EVT_CODE:
            le_meta_evt = (evt_le_meta_event *)(event_pckt->data);
            switch (le_meta_evt->subevent)
            {
                case HCI_LE_CONNECTION_COMPLETE_SUBEVT_CODE:
                    this->sysState->App_Flag_Reset(Sys::State::App_Flag::BLE_ADVERTISING);
                    this->sysState->App_Flag_Set(Sys::State::App_Flag::BLE_CONNECTED);
                    break; /* HCI_LE_CONNECTION_COMPLETE_SUBEVT_CODE */
                default:
                    break;
            }
            break; /* HCI_LE_CONNECTION_COMPLETE_SUBEVT_CODE */
        case HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE:
            blecore_evt = (evt_blecore_aci*) event_pckt->data;
            switch (blecore_evt->ecode)
            {
                case EVT_END_OF_RADIO_ACTIVITY:
                    this->gpioCtrl->Toggle_Component(this->sysState->Fetch_LED_Green());
                    break; /* EVT_END_OF_RADIO_ACTIVITY */
            }
            break; /* HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE */

        default:
            break;
    }

    return (SVCCTL_UserEvtFlowEnable);
}

SVCCTL_UserEvtFlowStatus_t SVCCTL_App_Notification(void *pckt)
{
    return BLE::App::Instance()->SVCCTL_Notification_Handler(pckt);
}
