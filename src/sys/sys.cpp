#include "sys/sys.hpp"

#include "sys/state.hpp"
#include "display/controller.hpp"

#include "shci.h"
#include "hci_tl.h"
#include "shci_tl.h"
#include "stm32wbxx_hal.h"
#include "otp.h"
#include "stm32wbxx_hal.h"
#include "svc_ctl.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


RTC_HandleTypeDef *ghrtc;

void Sys::Delay(uint32_t amt)
{
    /* Safe delay: if FreeRTOS is not started yet, do not use non-blocking delay */
    if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
        vTaskDelay(amt);
    else HAL_Delay(amt);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Sys::Error_Handler()
{
    for(;;) {
        /* TODO: Toggle RED LED */
        HAL_Delay(250);
    }
}

Sys::Controller::Controller(Sys::State *state)
{
    this->sysState = state;
}

Sys::Controller::~Controller()
{}

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

void Sys::Controller::Config_RTC()
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};
    RTC_AlarmTypeDef sAlarm = {0};

    hrtc = {0};
    /** Initialize RTC Only
    */
    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = 127;
    hrtc.Init.SynchPrediv = 255;
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
    HAL_StatusTypeDef ret = HAL_RTC_Init(&hrtc);
    if (ret != HAL_OK)
        Error_Handler();

    /** Initialize RTC and set the Time and Date
    */
    sTime.Hours = 0x0;
    sTime.Minutes = 0x0;
    sTime.Seconds = 0x0;
    sTime.SubSeconds = 0x0;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
        Error_Handler();

    sDate.WeekDay = RTC_WEEKDAY_MONDAY;
    sDate.Month = RTC_MONTH_JANUARY;
    sDate.Date = 0x1;
    sDate.Year = 0x0;
    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
        Error_Handler();

    /** Enable the Alarm A
    */
    sAlarm.AlarmTime.Hours = 0;
    sAlarm.AlarmTime.Minutes = 1;
    sAlarm.AlarmTime.Seconds = 0;
    sAlarm.AlarmTime.SubSeconds = 0;
    sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
    sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY|RTC_ALARMMASK_HOURS
        |RTC_ALARMMASK_SECONDS;
    sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
    sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
    sAlarm.AlarmDateWeekDay = 0x1;
    sAlarm.Alarm = RTC_ALARM_A;
    if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
        Error_Handler();

    ghrtc = &hrtc;
}

Sys::TimeInfo Sys::Controller::Get_RTC()
{
    RTC_TimeTypeDef time = {0};
    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);

    Sys::TimeInfo info;
    info.hour = time.Hours;
    info.minute = time.Minutes;
    info.second = time.Seconds;

    return info;
}

void Sys::Controller::Set_RTC(Sys::TimeInfo info)
{
    RTC_TimeTypeDef time = {0};
    time.Hours = info.hour;
    time.Minutes = info.minute;
    time.Seconds = info.second;
    time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    time.StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN) != HAL_OK)
        Sys::Error_Handler();

    RTC_DateTypeDef date = {0};
    date.WeekDay = 1;  /* TODO */
    date.Month = info.month;
    date.Date = info.day;
    date.Year = 99;  /* TODO */
    if (HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN) != HAL_OK)
        Sys::Error_Handler();

    RTC_AlarmTypeDef alarm;
    HAL_RTC_GetAlarm(&hrtc, &alarm, RTC_ALARM_A, FORMAT_BIN);
    alarm.AlarmTime.Minutes = time.Minutes + 1;
    if (HAL_RTC_SetAlarm_IT(&hrtc, &alarm, RTC_FORMAT_BIN) != HAL_OK)
        Sys::Error_Handler();
}

extern "C" {
    void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
    {
        RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
        if(hrtc->Instance==RTC)
        {
            /** Initializes the peripherals clock
            */
            PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
            PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
            if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
            {
                Sys::Error_Handler();
            }

            /* Peripheral clock enable */
            __HAL_RCC_RTC_ENABLE();
            __HAL_RCC_RTCAPB_CLK_ENABLE();

            HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0, 0);
            HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
        }
    }

    void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
    {
        if(hrtc->Instance==RTC)
        {
            /* Peripheral clock disable */
            __HAL_RCC_RTC_DISABLE();
            __HAL_RCC_RTCAPB_CLK_DISABLE();
        }
    }

    void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
    {
        RTC_AlarmTypeDef alarm;
        HAL_RTC_GetAlarm(hrtc, &alarm, RTC_ALARM_A, FORMAT_BIN);
        if(alarm.AlarmTime.Minutes > 58) {
            alarm.AlarmTime.Minutes = 0;
        } else {
            alarm.AlarmTime.Minutes += 1;
        }
        if (HAL_RTC_SetAlarm_IT(hrtc, &alarm, RTC_FORMAT_BIN) != HAL_OK)
            Sys::Error_Handler();

        RTC_DateTypeDef date = {0};
        RTC_TimeTypeDef time = {0};

        HAL_RTC_GetTime(hrtc, &time, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(hrtc, &date, RTC_FORMAT_BIN);

        Sys::TimeInfo info;

        info.month = date.Month;
        info.day = date.Date;

        info.hour = time.Hours;
        info.minute = time.Minutes;
        info.second = time.Seconds;

        Sys::State *state = Display::Controller::Instance()->Get_State();
        state->App_Flag_Set(Sys::State::App_Flag::LOGIC_TIME_UPDATE_PENDING);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
    }

    void HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc)
    {}
};

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

SPI_HandleTypeDef *Sys::Controller::Config_SPI()
{
    spi1 = { 0 };
    spi1.Instance = SPI1;
    spi1.Init.Mode = SPI_MODE_MASTER;
    spi1.Init.Direction = SPI_DIRECTION_2LINES;
    spi1.Init.DataSize = SPI_DATASIZE_8BIT;
    spi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    spi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    spi1.Init.NSS = SPI_NSS_SOFT;
    spi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    spi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    spi1.Init.TIMode = SPI_TIMODE_DISABLE;
    spi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi1.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&spi1) != HAL_OK)
        Error_Handler();

    return &spi1;
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
    SHci_Tl_Init_Conf.p_cmdbuffer = (uint8_t*)&(this->sysState->SysCmdBuffer);
    SHci_Tl_Init_Conf.StatusNotCallBack = Sys::Event_Processor::Sys_StatusNotificationCallback;
    shci_init(Sys::Event_Processor::Sys_UserEventReceivedCallback, (void*)&SHci_Tl_Init_Conf);

    /**< Memory Manager channel initialization */
    tl_mm_config.p_AsynchEvtPool = this->sysState->EvtPool;
    tl_mm_config.p_BleSpareEvtBuffer = this->sysState->BLESpareEvtBuffer; /* UNUSED, but kept for future compatibility */
    tl_mm_config.p_SystemSpareEvtBuffer = this->sysState->SysSpareEvtBuffer; /* UNUSED, but kept for future compatibility, but used by FUS today only */
    tl_mm_config.AsynchEvtPoolSize = EVENT_POOL_SIZE;
    TL_MM_Init(&tl_mm_config);

    /**< Release the CPU2 */
    TL_Enable();
}

Sys::Event_Processor::Event_Processor()
{}

Sys::Event_Processor::Event_Processor(Sys::State *state)
{
    this->sysState = state;

    Sys::Event_Processor::Instance(this);
}

Sys::Event_Processor::~Event_Processor()
{
    delete theInstance;
}

Sys::Event_Processor *Sys::Event_Processor::Instance(Event_Processor *cur)
{
    if (!theInstance) theInstance = cur;
    return theInstance;
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

    Sys::State *state = Sys::Event_Processor::Instance()->sysState;

    p_sys_event = (TL_AsynchEvt_t*)(((tSHCI_UserEvtRxParam*)pData)->pckt->evtserial.evt.payload);

    /* We have received some event from CPU2, so CPU2 to be considered as running and responding */
    state->App_Flag_Set(Sys::State::App_Flag::CPU2_INITIALIZED);

    switch(p_sys_event->subevtcode)
    {
        case SHCI_SUB_EVT_CODE_READY:
            p_sys_ready_event = (SHCI_C2_Ready_Evt_t*)p_sys_event->payload;
            if (p_sys_ready_event->sysevt_ready_rsp == WIRELESS_FW_RUNNING)
            {
                state->App_Flag_Reset(Sys::State::App_Flag::FUS_FW_RUNNING);
                state->App_Flag_Set(Sys::State::App_Flag::WIRELESS_FW_RUNNING);
                /* RF stack installed and ready */
            }
            else if (p_sys_ready_event->sysevt_ready_rsp == FUS_FW_RUNNING)
            {
                state->App_Flag_Set(Sys::State::App_Flag::FUS_FW_RUNNING);
                state->App_Flag_Reset(Sys::State::App_Flag::WIRELESS_FW_RUNNING);

                /* No RF stack installed most probably */
                Error_Handler(); /* UNEXPECTED */
            }
            else {
                state->App_Flag_Set(Sys::State::App_Flag::CPU2_ERROR);
                Error_Handler(); /* UNEXPECTED */
            }
            break; /* SHCI_SUB_EVT_CODE_READY */
        case SHCI_SUB_EVT_ERROR_NOTIF:
            state->App_Flag_Set(Sys::State::App_Flag::CPU2_ERROR);

            p_sys_error_code = (SCHI_SystemErrCode_t*)p_sys_event->payload;
            if (*p_sys_error_code == ERR_BLE_INIT)
            {
                /* Error during BLE stack initialization */
                state->App_Flag_Set(Sys::State::App_Flag::BLE_INITIALIZATION_ERROR);
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
    if (this->sysState->App_Flag_Get(Sys::State::App_Flag::SHCI_EVENT_PENDING) == Sys::State::Flag_Val::SET)
    {
        this->sysState->App_Flag_Reset(Sys::State::App_Flag::SHCI_EVENT_PENDING);
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
    if (this->sysState->App_Flag_Get(Sys::State::App_Flag::HCI_EVENT_PENDING) == Sys::State::Flag_Val::SET)
    {
        this->sysState->App_Flag_Reset(Sys::State::App_Flag::HCI_EVENT_PENDING);
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
void Sys::Event_Processor::SHCI_Notify_Event_Handler(void* pdata)
{
    this->sysState->App_Flag_Set(Sys::State::App_Flag::SHCI_EVENT_PENDING);
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
void Sys::Event_Processor::HCI_Notify_Event_Handler(void* pdata)
{
    this->sysState->App_Flag_Set(Sys::State::App_Flag::HCI_EVENT_PENDING);
    return;
}

void shci_notify_asynch_evt(void *pdata)
{
    return Sys::Event_Processor::Instance()->SHCI_Notify_Event_Handler(pdata);
}

void hci_notify_asynch_evt(void *pdata)
{
    return Sys::Event_Processor::Instance()->HCI_Notify_Event_Handler(pdata);
}
