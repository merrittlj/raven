#include "sys/sys.hpp"

#include "app/app.hpp"


/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Sys::Error_Handler()
{
    for(;;) {
        /* Toggle RED LED */
        HAL_Delay(250);
    }
}

void Sys::Controller::Controller()
{

}

void Sys::Controller::~Controller()
{

}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void Sys::Controller::Config_SysClk()
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /** Configure LSE Drive Capability 
    */
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
    /** Configure the main internal regulator output voltage 
    */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE
        |RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
        Error_Handler();
    /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers 
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK4|RCC_CLOCKTYPE_HCLK2
        |RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
        |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLK4Divider = RCC_SYSCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
        Error_Handler();
    /** Initializes the peripherals clocks 
    */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS|RCC_PERIPHCLK_RFWAKEUP;
    PeriphClkInitStruct.RFWakeUpClockSelection = RCC_RFWKPCLKSOURCE_LSE;
    PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSE;
    PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE1;

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        Error_Handler();
}

/**
 * @brief Read the HSE trimming value from OTP memory
 * @param None
 * @retval None
 */
void Sys::Controller::Config_HSE()
{
    /* !!! WARNING !!! Following code is valid only for P-NUCLEO-WB55 boards. 
       Code must be reviewed and optionally reimplemented depending on the target HW 
       and HSE capacitor tuning value storage location. 
       Please read AN5042 - HSE trimming for RF applications using the STM32WB series. */

    OTP_ID0_t * p_otp;

    /* Read HSE_Tuning from OTP */
    p_otp = (OTP_ID0_t *) OTP_Read(0);
    if (p_otp)
    {
        LL_RCC_HSE_SetCapacitorTuning(p_otp->hse_tuning);
    }
}

/**
 * @brief This function initializes and releases the CPU2 subsystem
 * @param None
 * @retval None
 */
void Sys::Controller::Init_CPU2()
{
    TL_MM_Config_t tl_mm_config;
    SHCI_TL_HciInitConf_t SHci_Tl_Init_Conf;

    /**< Reference table initialization */
    TL_Init();

    /**< System channel initialization */
    SHci_Tl_Init_Conf.p_cmdbuffer = (uint8_t*)&SystemCmdBuffer;
    SHci_Tl_Init_Conf.StatusNotCallBack = SYS_StatusNotificationCallback;
    shci_init(SYS_UserEventReceivedCallback, (void*)&SHci_Tl_Init_Conf);

    /**< Memory Manager channel initialization */
    tl_mm_config.p_AsynchEvtPool = EvtPool;
    tl_mm_config.p_BleSpareEvtBuffer = BleSpareEvtBuffer; /* UNUSED, but kept for future compatibility */
    tl_mm_config.p_SystemSpareEvtBuffer = SystemSpareEvtBuffer; /* UNUSED, but kept for future compatibility, but used by FUS today only */
    tl_mm_config.AsynchEvtPoolSize = EVENT_POOL_SIZE;
    TL_MM_Init(&tl_mm_config);

    /**< Release the CPU2 */
    TL_Enable();
}

void Sys::Controller::Controller()
{

}

void Sys::Controller::~Controller()
{

}

/**
 * @brief As stated in AN5289, this is the system event user callback. It is
 *        registered and passed as argument to shci_init() function.
 *        This reports the received system user event.
 *        The buffer holding the received event is freed on return
 *        of this function.
 * @param pData: pointer to a structure of tSHCI_UserEvtRxParam type
 *
 *               typedef struct
 *               {
 *                 SHCI_TL_UserEventFlowStatus_t status;
 *                 TL_EvtPacket_t *pckt;
 *               } tSHCI_UserEvtRxParam;
 *
 *               pckt: holds the address of the received event
 *               status: provides a way for user to notify the system transport layer that the received packet
 *                       has not been processed and must not be thrown away. When not filled by the user on return
 *                       of UserEvtRx(), this parameter is set to SHCI_TL_UserEventFlow_Enable, which means the
 *                       user has processed the received event
 * @retval None
 */
void Sys::Event_Processor::Sys_UserEventReceivedCallback(void *pData)
{
    TL_AsynchEvt_t *p_sys_event;
    SHCI_C2_Ready_Evt_t *p_sys_ready_event;
    SCHI_SystemErrCode_t *p_sys_error_code;

    p_sys_event = (TL_AsynchEvt_t*)(((tSHCI_UserEvtRxParam*)pData)->pckt->evtserial.evt.payload);

    /* We have received some event from CPU2, so CPU2 to be considered as running and responding */
    APP_FLAG_SET(APP_FLAG_CPU2_INITIALIZED);

    switch(p_sys_event->subevtcode)
    {
        case SHCI_SUB_EVT_CODE_READY:
            p_sys_ready_event = (SHCI_C2_Ready_Evt_t*)p_sys_event->payload;
            if (p_sys_ready_event->sysevt_ready_rsp == WIRELESS_FW_RUNNING)
            {
                APP_FLAG_RESET(APP_FLAG_FUS_FW_RUNNING);
                APP_FLAG_SET(APP_FLAG_WIRELESS_FW_RUNNING);
                /* RF stack installed and ready */
            }
            else if (p_sys_ready_event->sysevt_ready_rsp == FUS_FW_RUNNING)
            {
                APP_FLAG_SET(APP_FLAG_FUS_FW_RUNNING);
                APP_FLAG_RESET(APP_FLAG_WIRELESS_FW_RUNNING);

                /* No RF stack installed most probably */
                Error_Handler(); /* UNEXPECTED */
            }
            else {
                APP_FLAG_SET(APP_FLAG_CPU2_ERROR);
                Error_Handler(); /* UNEXPECTED */
            }
            break; /* SHCI_SUB_EVT_CODE_READY */
        case SHCI_SUB_EVT_ERROR_NOTIF:
            APP_FLAG_SET(APP_FLAG_CPU2_ERROR);

            p_sys_error_code = (SCHI_SystemErrCode_t*)p_sys_event->payload;
            if (p_sys_error_code == ERR_BLE_INIT)
            {
                /* Error during BLE stack initialization */
                APP_FLAG_SET(APP_FLAG_BLE_INITIALIZATION_ERROR);
                Error_Handler(); /* UNEXPECTED */
            }
            else {
                Error_Handler(); /* UNEXPECTED */
            }
            break; /* SHCI_SUB_EVT_ERROR_NOTIF */
        default:
            break;
    }

    ((tSHCI_UserEvtRxParam *)pData)->status = SHCI_TL_UserEventFlow_Disable;

    return;
}

/**
 * @brief As stated in AN5289, this is the callback used to acknowledge
 *        if a system command can be sent. It is registered in shci_init()
 *        It must be used in a multi-thread application where the system commands
 *        may be sent from different threads.
 *  
 *        switch (status)
 *        {
 *        case SHCI_TL_CmdBusy:
 *          break;
 *        case SHCI_TL_CmdAvailable:
 *          break;
 *        default:
 *          break;
 *
 * @param status: SHCI_TL_CmdBusy in case the system transport layer is busy and no
 *                new system command are be sent, SHCI_TL_CmdAvailable otherwise
 * @retval None
 */
void Sys::Event_Processor::Sys_StatusNotificationCallback(SHCI_TL_CmdStatus_t status)
{
    /* Callback not implemented - code flow under control of the developer */
    UNUSED(status);
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
void Sys::Event_Processor::BLE_UserEventReceivedCallback(void *pData)
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
void Sys::Event_Processor::BLE_StatusNotificationCallback(HCI_TL_CmdStatus_t status)
{
    /* Callback not implemented - code flow under control of the developer */
    UNUSED(status);
}

/**
 * @brief This function is used to process all events coming from BLE stack by executing the related callback
 * @param None
 * @retval None
 */
void Sys::Event_Processor::Sys_ProcessEvent()
{
    if (APP_FLAG_GET(APP_FLAG_SHCI_EVENT_PENDING) == 1)
    {
        APP_FLAG_RESET(APP_FLAG_SHCI_EVENT_PENDING);
        shci_user_evt_proc();
    }
}

/**
 * @brief This function is used to process all events coming from BLE stack by executing the related callback
 * @param None
 * @retval None
 */
void Sys::Event_Processor::BLE_ProcessEvent()
{
    if (APP_FLAG_GET(APP_FLAG_HCI_EVENT_PENDING) == 1)
    {
        APP_FLAG_RESET(APP_FLAG_HCI_EVENT_PENDING);
        hci_user_evt_proc();
    }
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
void Sys::Event_Processor::shci_notify_asynch_evt(void* pdata)
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
void Sys::Event_Processor::hci_notify_asynch_evt(void* pdata)
{
    APP_FLAG_SET(APP_FLAG_HCI_EVENT_PENDING);
    return;
}
