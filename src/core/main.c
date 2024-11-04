/* requires stm32wb5x_BLE_Stack_fw.bin binary on wireless coprocessor */

#include "main.h"

#include "core/main.h"
#include "app/app_common.h"
#include "app/app_debug.h"
#include "hw/hw_conf.h"
#include "ble/gatt_service.h"

#include "otp.h"
#include "ble.h"
#include "hci_tl.h"
#include "shci_tl.h"
#include "shci.h"


void Config_SysClk(void);
static void Config_GPIO(void);
static void Config_HSE(void);
static void Init_CPU2(void);

static void SYS_UserEventReceivedCallback(void * pData);
static void SYS_StatusNotificationCallback(SHCI_TL_CmdStatus_t status);
static void SYS_ProcessEvent(void);

void _init(){} /* To avoid linker errors */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /**
     * The OPTVERR flag is wrongly set at power on
     * It shall be cleared before using any HAL_FLASH_xxx() api
     */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);

    uint32_t prevTick = 0;

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    /* Tune the HSE internal load capacitors - P-NUCLEO-WB55.Nucleo board */
    Config_HSE();
    /* Configure the debug support if needed */
    APPD_Init();

    Config_SysClk();
    Config_GPIO();

    /* TODO: Should this be reimplemented? */
    GPIO_InitTypeDef gpio_blue;
    gpio_blue.Pin = GPIO_PIN_5;
    gpio_blue.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_blue.Pull = GPIO_PULLUP;
    gpio_blue.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_blue);

    GPIO_InitTypeDef gpio_green;
    gpio_green.Pin = GPIO_PIN_0;
    gpio_green.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_green.Pull = GPIO_PULLUP;
    gpio_green.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_green);

    GPIO_InitTypeDef gpio_red;
    gpio_red.Pin = GPIO_PIN_1;
    gpio_red.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_red.Pull = GPIO_PULLUP;
    gpio_red.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_red);

    /* Initialize all transport layers */
    Init_CPU2();

    /* Set the red LED On to indicate that the CPU2 is initializing */
    /* BSP_LED_On(LED_RED); */ 

    /* Wait until the CPU2 gets initialized */
    while((APP_FLAG_GET(APP_FLAG_CPU2_INITIALIZED) == 0) \
            || (APP_FLAG_GET(APP_FLAG_WIRELESS_FW_RUNNING) == 0))
    {
        /* Process pending SYSTEM event coming from CPU2 (if any) */
        SYS_ProcessEvent();
    }

    /* Configure the CPU2 Debug (Optional) */
    APPD_EnableCPU2();

    /* Set the red LED Off to indicate that the CPU2 is initialized */
    /* BSP_LED_Off(LED_RED); */

    /* Set the green LED On to indicate that the wireless stack FW is running */
    /* BSP_LED_On(LED_GREEN); */

    /* At this point it is still unknown from the app perspective, which wireless stack
       and which version is installed on CPU2. It is expected that a BLE stack is installed.
       In order to check that, SHCI_GetWirelessFwInfo(...) can be used to read out
       the information about the CM0+ wireless stack FW running since the Device Information Table
       is initialized. For more information on this topic, please refer to AN5289 and AN5185. */

    /* Initialize BLE (BLE TL, BLE stack, HAL, HCI, GATT, GAP) */
    BLE_Init();

    /* Set the blue LED On to indicate that the BLE stack is initialized */
    /* BSP_LED_On(LED_BLUE); */

    /* Initialize My Very Own GATT Service - user may also implement SVCCTL_InitCustomSvc()
       interface function as explained in AN5289. SVCCTL_InitCustomSvc() is called at the end of
       SVCCTL_Init() called from BLE_Init() */
    MyVeryOwnService_Init();

    /* Reset BLUE LED => Will be used by the example */
    /* BSP_LED_Off(LED_BLUE); */

    /* Start BLE advertising */
    BLE_Advertising(SET);


    for(;;)
    {
        /* Process pending BLE event coming from CPU2 (if any) */
        BLE_ProcessEvent();
        /* Process pending SYSTEM event coming from CPU2 (if any) */
        SYS_ProcessEvent();

        /* Update the My Very Own Notify Characteristic every ~1 second and only if BLE connected.
           It might be also done only after the GATT client enables the notifications,
           but that is out of scope of this basic example */
        if (APP_FLAG_GET(APP_FLAG_BLE_CONNECTED) != 0x00)
        {
            if ((HAL_GetTick() - prevTick) > 1000)
            {
                prevTick = HAL_GetTick();
                myVeryOwnNotifyCharacteristicData[1] ^= 0x01;
                if (MyVeryOwnWriteCharacteristic_Update(MY_VERY_OWN_NOTIFY_CHARACTERISTIC_UUID,
                            MY_VERY_OWN_NOTIFY_CHARACTERISTIC_VALUE_LENGTH,
                            myVeryOwnNotifyCharacteristicData) != BLE_STATUS_SUCCESS)
                {
                    Error_Handler(); /* UNEXPECTED */
                }
            }
        }
    }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void Config_SysClk(void)
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
    {
        Error_Handler();
    }
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
    {
        Error_Handler();
    }
    /** Initializes the peripherals clocks 
    */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS|RCC_PERIPHCLK_RFWAKEUP;
    PeriphClkInitStruct.RFWakeUpClockSelection = RCC_RFWKPCLKSOURCE_LSE;
    PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSE;
    PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE1;

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief Configure GPIO
 * @param None
 * @retval None
 */
static void Config_GPIO(void)
{

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
}

/**
 * @brief This function initializes and releases the CPU2 subsystem
 * @param None
 * @retval None
 */
static void Init_CPU2( void )
{
    TL_MM_Config_t tl_mm_config;
    SHCI_TL_HciInitConf_t SHci_Tl_Init_Conf;

    /**< Reference table initialization */
    TL_Init();

    /**< System channel initialization */
    SHci_Tl_Init_Conf.p_cmdbuffer = (uint8_t*)&SystemCmdBuffer;
    SHci_Tl_Init_Conf.StatusNotCallBack = SYS_StatusNotificationCallback;
    shci_init(SYS_UserEventReceivedCallback, (void*) &SHci_Tl_Init_Conf);

    /**< Memory Manager channel initialization */
    tl_mm_config.p_AsynchEvtPool = EvtPool;
    tl_mm_config.p_BleSpareEvtBuffer = BleSpareEvtBuffer; /* UNUSED, but kept for future compatibility */
    tl_mm_config.p_SystemSpareEvtBuffer = SystemSpareEvtBuffer; /* UNUSED, but kept for future compatibility, but used by FUS today only */
    tl_mm_config.AsynchEvtPoolSize = EVENT_POOL_SIZE;
    TL_MM_Init( &tl_mm_config );

    /**< Release the CPU2 */
    TL_Enable();

    return;
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
static void SYS_UserEventReceivedCallback( void * pData )
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
static void SYS_StatusNotificationCallback( SHCI_TL_CmdStatus_t status )
{
    /* Callback not implemented - code flow under control of the developer */
    UNUSED(status);
    return;
}

/**
 * @brief This function is used to process all events coming from BLE stack by executing the related callback
 * @param None
 * @retval None
 */
static void SYS_ProcessEvent(void)
{
    if (APP_FLAG_GET(APP_FLAG_SHCI_EVENT_PENDING) == 1)
    {
        APP_FLAG_RESET(APP_FLAG_SHCI_EVENT_PENDING);
        shci_user_evt_proc();
    }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    for(;;) {
        /* Toggle RED LED */
        HAL_Delay(250);
    }
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{ 
    /* Add some sort of printing/logging functionality */
}
#endif /* USE_FULL_ASSERT */
