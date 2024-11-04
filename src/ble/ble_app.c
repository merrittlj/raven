#include "ble/ble_app.h"

/**
 * @brief This function initializes the BLE stack
 * @param None
 * @retval None
 */
static void BLE_Init( void )
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
    Ble_Tl_Init( );

    /**
     * Starts the BLE Stack on CPU2
     */
    ret = SHCI_C2_BLE_Init( &ble_init_cmd_packet );
    if (ret != SHCI_Success)
    {
        Error_Handler(); /* UNEXPECTED */
    }

    /**
     * Initialization of HCI & GATT & GAP layer
     */
    Ble_Hci_Gap_Gatt_Init();

    /**
     * Initialization of the BLE Services
     */
    SVCCTL_Init();

    return;
}

/**
 * @brief This function is used to process all events coming from BLE stack by executing the related callback
 * @param None
 * @retval None
 */
static void BLE_ProcessEvent(void)
{
    if (APP_FLAG_GET(APP_FLAG_HCI_EVENT_PENDING) == 1)
    {
        APP_FLAG_RESET(APP_FLAG_HCI_EVENT_PENDING);
        hci_user_evt_proc();
    }
}

/**
 * @brief This function initializes the BLE Transport Layer
 * @param None
 * @retval None
 */
static void Ble_Tl_Init( void )
{
    HCI_TL_HciInitConf_t Hci_Tl_Init_Conf;

    /**< BLE channel initialization */
    Hci_Tl_Init_Conf.p_cmdbuffer = (uint8_t*)&BleCmdBuffer;
    Hci_Tl_Init_Conf.StatusNotCallBack = BLE_StatusNotificationCallback;
    hci_init(BLE_UserEventReceivedCallback, (void*) &Hci_Tl_Init_Conf);

    return;
}

/**
 * @brief This function starts or stops the BLE advertising
 * @param newState: SET to start the advertising, RESET to stop
 * @retval None
 */
static void BLE_Advertising(FlagStatus newState)
{
    tBleStatus ret = BLE_STATUS_SUCCESS;

    if (newState == SET)
    {
        if (APP_FLAG_GET(APP_FLAG_BLE_ADVERTISING) == 0)
        {
            /**
             * Put the device in a advertising & connectable mode.
             */
            ret = aci_gap_set_discoverable(ADV_IND,                                       /*< Advertise as connectable, undirected. */
                    CFG_FAST_CONN_ADV_INTERVAL_MIN,                /*< Set the advertising interval min value. */
                    CFG_FAST_CONN_ADV_INTERVAL_MAX,                /*< Set the advertising interval max value. */
                    GAP_PUBLIC_ADDR,                                   /*< Use the public address. */
                    NO_WHITE_LIST_USE,                             /*< No white list. */
                    sizeof(ad_local_name), (uint8_t*)ad_local_name,/*< Use a local name. */
                    0, NULL,                                       /*< Do not include the service UUID list. (no adopted services) */
                    0x0000, 0x0000);                               /*< NaN, do not put in advertising data. */
            if (ret != BLE_STATUS_SUCCESS)
            {
                Error_Handler(); /* UNEXPECTED */
            }

            /**
             * Update the advertising data.
             */
            ret = aci_gap_update_adv_data(sizeof(ad_manufacturer_specific_data), (uint8_t*)ad_manufacturer_specific_data);
            if (ret != BLE_STATUS_SUCCESS)
            {
                Error_Handler(); /* UNEXPECTED */
            }
            APP_FLAG_SET(APP_FLAG_BLE_ADVERTISING);
        }
    }
    else {
        /**
         * Stop device advertising.
         */
        ret = aci_gap_set_non_discoverable();
        if (ret != BLE_STATUS_SUCCESS)
        {
            Error_Handler(); /* UNEXPECTED */
        }
        APP_FLAG_RESET(APP_FLAG_BLE_ADVERTISING);
    }

    return;
}

/**
 * @brief This function initializes the BLE stack and all its modules
 * @param None
 * @retval None
 */
static void Ble_Hci_Gap_Gatt_Init(void)
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
    bd_address = Ble_GetBdAddress();
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
    {
        Error_Handler(); /* UNEXPECTED */
    }

    /**
     * Set Radio activity event mask.
     */
    ret = aci_hal_set_radio_activity_mask(CFG_RADIO_ACTIVITY_EVENT_MASK);
    if (ret != BLE_STATUS_SUCCESS)
    {
        Error_Handler(); /* UNEXPECTED */
    }

    /**
     * Initialize GATT
     */
    ret = aci_gatt_init();
    if (ret != BLE_STATUS_SUCCESS)
    {
        Error_Handler(); /* UNEXPECTED */
    }

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
    {
        Error_Handler(); /* UNEXPECTED */
    }

    /**
     * Update GAP Service Device Name characteristic value
     */
    ret = aci_gatt_update_char_value(gap_service_handle,
            gap_dev_name_char_handle,
            0,
            sizeof(gap_device_name),
            (uint8_t *)gap_device_name);
    if (ret != BLE_STATUS_SUCCESS)
    {
        Error_Handler(); /* UNEXPECTED */
    }

    /**
     * Update GAP Service Appearance  characteristic value
     */
    ret = aci_gatt_update_char_value(gap_service_handle,
            gap_appearance_char_handle,
            0,
            sizeof(gap_appearance),
            (uint8_t *)&gap_appearance);
    if (ret != BLE_STATUS_SUCCESS)
    {
        Error_Handler(); /* UNEXPECTED */
    }

    return;
}

/**
 * @brief This function generates the unique BD address from the UDN
 * @param None
 * @retval Pointer to the array holding the BD address
 */
const uint8_t* Ble_GetBdAddress(void)
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
        }
        else
        {
            p_bd_addr = a_MBdAddr;
        }
    }

    return p_bd_addr;
}

/**
 * @brief  Interrupt service routine that must be called when the system channel
 *         reports a packet has been received
 *         As stated in AN5289, this API notifies the user that a system user event has been received.
 *         The user has to call the shci_user_evt_proc() to process
 *         the notification in the system transport layer.
 *         As the shci_notify_asynch_evt() notification is called from the IPCC
 *         Interrupt Service Routine, it is strongly recommended to implement
 *         a background mechanism to call shci_user_evt_proc()
 *         (out of IPCC Interrupt Service Routine).
 * @param  pdata: Pointer to the packet or event data
 * @retval None
 */
void shci_notify_asynch_evt(void* pdata)
{
    APP_FLAG_SET(APP_FLAG_SHCI_EVENT_PENDING);
    return;
}

/**
 * @brief  Callback called from related IPCC RX Interrupt Service Routine, called when the BLE core (CPU2)
 *         reports a packet received or an event to the host.
 *         As stated in AN5289, this API notifies the user that a BLE user event has been received.
 *         The user has to call the hci_user_evt_proc() to process
 *         the notification in the BLE transport layer.
 *         As the hci_notify_asynch_evt() notification is called from the IPCC
 *         Interrupt Service Routine, it is strongly recommended to implement
 *         a background mechanism to call hci_user_evt_proc()
 *         (out of IPCC Interrupt Service Routine).
 * @param  pdata: Pointer to the packet or event data
 * @retval None
 */
void hci_notify_asynch_evt(void* pdata)
{
    APP_FLAG_SET(APP_FLAG_HCI_EVENT_PENDING);
    return;
}

/**
 * @brief As stated in AN5289, this is the BLE event user callback. It is
 *        registered and passed as argument to hci_init() function.
 *        This reports the received BLE user event.
 *        The buffer holding the received event is freed on return
 *        of this function.
 * @param pData: pointer to a structure of tHCI_UserEvtRxParam type
 *
 *               typedef struct
 *               {
 *                 HCI_TL_UserEventFlowStatus_t status;
 *                 TL_EvtPacket_t *pckt;
 *               } tHCI_UserEvtRxParam;
 *
 *               pckt: holds the address of the received event
 *               status: provides a way for the user to notify the HCI transport layer that the received packet has not been processed and
 *               must not be thrown away. When not filled by the user on return of UserEvtRx(), this parameter is set to HCI_TL_UserEventFlow_Enable
 *               which means the user has processed the received event.
 * @retval None
 */
static void BLE_UserEventReceivedCallback( void * pData )
{
    SVCCTL_UserEvtFlowStatus_t svctl_return_status;
    tHCI_UserEvtRxParam *pParam;

    pParam = (tHCI_UserEvtRxParam *)pData; 

    svctl_return_status = SVCCTL_UserEvtRx((void *)&(pParam->pckt->evtserial));
    if (svctl_return_status != SVCCTL_UserEvtFlowDisable)
    {
        pParam->status = HCI_TL_UserEventFlow_Enable;
    }
    else
    {
        pParam->status = HCI_TL_UserEventFlow_Disable;
    }
}

/**
 * @brief As stated in AN5289, this is the callback used to acknowledge
 *        if a BLE command can be sent. It is registered in hci_init()
 *        It must be used in a multi-thread application where the BLE commands
 *        may be sent from different threads.
 *  
 *        switch (status)
 *        {
 *        case HCI_TL_CmdBusy:
 *          break;
 *        case HCI_TL_CmdAvailable:
 *          break;
 *        default:
 *          break;
 *
 * @param status: HCI_TL_CmdBusy in case HCI transport layer is busy and no new
 *        BLE command can be sent, HCI_TL_CmdAvailable otherwise
 * @retval None
 */
static void BLE_StatusNotificationCallback(HCI_TL_CmdStatus_t status)
{
    /* Callback not implemented - code flow under control of the developer */
    UNUSED(status);
    return;
}

/**
 * @brief Read the HSE trimming value from OTP memory
 * @param None
 * @retval None
 */
static void Config_HSE(void)
{
    /* !!! WARNING !!! Following code is valid only for P-NUCLEO-WB55 boards. 
       Code must be reviewed and optionally reimplemented depending on the target HW 
       and HSE capacitor tuning value storage location. 
       Please read AN5042 - HSE trimming for RF applications using the STM32WB series. */

    OTP_ID0_t * p_otp;

    /**
     * Read HSE_Tuning from OTP
     */
    p_otp = (OTP_ID0_t *) OTP_Read(0);
    if (p_otp)
    {
        LL_RCC_HSE_SetCapacitorTuning(p_otp->hse_tuning);
    }

    return;
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
SVCCTL_UserEvtFlowStatus_t SVCCTL_App_Notification( void *pckt )
{
    hci_event_pckt *event_pckt;
    evt_blecore_aci *blecore_evt;
    evt_le_meta_event *le_meta_evt;

    event_pckt = (hci_event_pckt*) ((hci_uart_pckt *) pckt)->data;

    switch (event_pckt->evt)
    {
        case HCI_DISCONNECTION_COMPLETE_EVT_CODE:
            APP_FLAG_RESET(APP_FLAG_BLE_CONNECTED);
            /* Start advertising */
            BLE_Advertising(SET);
            break; /* HCI_DISCONNECTION_COMPLETE_EVT_CODE */
        case HCI_LE_META_EVT_CODE:
            le_meta_evt = (evt_le_meta_event *)(event_pckt->data);
            switch (le_meta_evt->subevent)
            {
                case HCI_LE_CONNECTION_COMPLETE_SUBEVT_CODE:
                    APP_FLAG_RESET(APP_FLAG_BLE_ADVERTISING);
                    APP_FLAG_SET(APP_FLAG_BLE_CONNECTED);
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
                    /* BSP_LED_Toggle(LED_GREEN); */
                    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
                    break; /* EVT_END_OF_RADIO_ACTIVITY */
            }
            break; /* HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE */

        default:
            break;
    }

    return (SVCCTL_UserEvtFlowEnable);
}
