#include "ble/ble.hpp"

#include "sys/sys.cpp"


BLE::Application()
{

}

BLE::~Application()
{

}

void BLE::Application::Init()
{
    /* At this point it is still unknown from the app perspective, which wireless stack
       and which version is installed on CPU2. It is expected that a BLE stack is installed.
       In order to check that, SHCI_GetWirelessFwInfo(...) can be used to read out
       the information about the CM0+ wireless stack FW running since the Device Information Table
       is initialized. For more information on this topic, please refer to AN5289 and AN5185. */

    /* Initialize BLE (BLE TL, BLE stack, HAL, HCI, GATT, GAP) */
    BLE_Init();

    /* Set the blue LED On to indicate that the BLE stack is initialized */
    gpioCtrl.Write_Component(sysState.Fetch_LED_Blue(), SET);

    /* Initialize My Very Own GATT Service - user may also implement SVCCTL_InitCustomSvc()
       interface function as explained in AN5289. SVCCTL_InitCustomSvc() is called at the end of
       SVCCTL_Init() called from BLE_Init() */
    MyVeryOwnService_Init();

    /* Reset BLUE LED => Will be used by the example */
    gpioCtrl.Write_Component(sysState.Fetch_LED_Blue(), RESET);
}

/**
 * @brief This function starts or stops the BLE advertising
 * @param newState: SET to start the advertising, RESET to stop
 * @retval None
 */
void BLE::Application::Advertising(FlagStatus newState)
{
    tBleStatus ret = BLE_STATUS_SUCCESS;

    if (newState == SET)
    {
        if (APP_FLAG_GET(APP_FLAG_BLE_ADVERTISING) == 0)
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

            /* Update the advertising data. */
            ret = aci_gap_update_adv_data(sizeof(ad_manufacturer_specific_data), (uint8_t*)ad_manufacturer_specific_data);
            if (ret != BLE_STATUS_SUCCESS)
                Sys::Error_Handler(); /* UNEXPECTED */
            APP_FLAG_SET(APP_FLAG_BLE_ADVERTISING);
        }
    } else {
        /* Stop(reset) device advertising. */
        ret = aci_gap_set_non_discoverable();
        if (ret != BLE_STATUS_SUCCESS)
            Sys::Error_Handler(); /* UNEXPECTED */
        APP_FLAG_RESET(APP_FLAG_BLE_ADVERTISING);
    }
}

/**
 * @brief This function initializes the BLE stack
 * @param None
 * @retval None
 */
void BLE::Application::BLE_Init()
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
void BLE::Application::Tl_Init()
{
    HCI_TL_HciInitConf_t Hci_Tl_Init_Conf;

    /**< BLE channel initialization */
    Hci_Tl_Init_Conf.p_cmdbuffer = (uint8_t*)&BleCmdBuffer;
    Hci_Tl_Init_Conf.StatusNotCallBack = StatusNotificationCallback;
    hci_init(UserEventReceivedCallback, (void*)&Hci_Tl_Init_Conf);
}

/**
 * @brief This function initializes the BLE stack and all its modules
 * @param None
 * @retval None
 */
void BLE::Application::Hci_Gap_Gatt_Init()
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
     * Put the BD address in the manufacturer specific advertising data (for iOS devices)
     */
    ad_manufacturer_specific_data[sizeof(ad_manufacturer_specific_data)-6] = bd_address[5];
    ad_manufacturer_specific_data[sizeof(ad_manufacturer_specific_data)-5] = bd_address[4];
    ad_manufacturer_specific_data[sizeof(ad_manufacturer_specific_data)-4] = bd_address[3];
    ad_manufacturer_specific_data[sizeof(ad_manufacturer_specific_data)-3] = bd_address[2];
    ad_manufacturer_specific_data[sizeof(ad_manufacturer_specific_data)-2] = bd_address[1];
    ad_manufacturer_specific_data[sizeof(ad_manufacturer_specific_data)-1] = bd_address[0];

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
const uint8_t* BLE::Application::GetBdAddress()
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

