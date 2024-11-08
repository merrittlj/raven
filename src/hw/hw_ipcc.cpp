/* Hardware IPCC source file for STM32WPAN Middleware. */

#include "app/app_common.h"

#include "mbox_def.h"

#define HW_IPCC_TX_PENDING(channel) (!(LL_C1_IPCC_IsActiveFlag_CHx(IPCC, channel)) ) &&  (((~(IPCC->C1MR)) & (channel << 16U)))
#define HW_IPCC_RX_PENDING(channel)  (LL_C2_IPCC_IsActiveFlag_CHx(IPCC, channel)) && (((~(IPCC->C1MR)) & (channel << 0U)))

static void (*FreeBufCb)();

static void HW_IPCC_BLE_EvtHandler();
static void HW_IPCC_BLE_AclDataEvtHandler();
static void HW_IPCC_MM_FreeBufHandler();
static void HW_IPCC_SYS_CmdEvtHandler();
static void HW_IPCC_SYS_EvtHandler();
static void HW_IPCC_TRACES_EvtHandler();

#ifdef THREAD_WB
static void HW_IPCC_OT_CmdEvtHandler();
static void HW_IPCC_THREAD_NotEvtHandler();
static void HW_IPCC_THREAD_CliNotEvtHandler();
#endif

#ifdef LLD_TESTS_WB
static void HW_IPCC_LLDTESTS_ReceiveCliRspHandler();
static void HW_IPCC_LLDTESTS_ReceiveM0CmdHandler();
#endif
#ifdef LLD_BLE_WB
static void HW_IPCC_LLD_BLE_ReceiveRspHandler();
static void HW_IPCC_LLD_BLE_ReceiveM0CmdHandler();
#endif

#ifdef MAC_802_15_4_WB
static void HW_IPCC_MAC_802_15_4_CmdEvtHandler();
static void HW_IPCC_MAC_802_15_4_NotEvtHandler();
#endif

#ifdef ZIGBEE_WB
static void HW_IPCC_ZIGBEE_CmdEvtHandler();
static void HW_IPCC_ZIGBEE_StackNotifEvtHandler();
static void HW_IPCC_ZIGBEE_StackM0RequestHandler();
#endif

/* Interrupt Handler */
void HW_IPCC_Rx_Handler()
{
    if (HW_IPCC_RX_PENDING( HW_IPCC_SYSTEM_EVENT_CHANNEL ))
    {
        HW_IPCC_SYS_EvtHandler();
    }
#ifdef MAC_802_15_4_WB
    else if (HW_IPCC_RX_PENDING( HW_IPCC_MAC_802_15_4_NOTIFICATION_ACK_CHANNEL ))
    {
        HW_IPCC_MAC_802_15_4_NotEvtHandler();
    }
#endif /* MAC_802_15_4_WB */
#ifdef THREAD_WB
    else if (HW_IPCC_RX_PENDING( HW_IPCC_THREAD_NOTIFICATION_ACK_CHANNEL ))
    {
        HW_IPCC_THREAD_NotEvtHandler();
    }
    else if (HW_IPCC_RX_PENDING( HW_IPCC_THREAD_CLI_NOTIFICATION_ACK_CHANNEL ))
    {
        HW_IPCC_THREAD_CliNotEvtHandler();
    }
#endif /* THREAD_WB */
#ifdef LLD_TESTS_WB
    else if (HW_IPCC_RX_PENDING( HW_IPCC_LLDTESTS_CLI_RSP_CHANNEL ))
    {
        HW_IPCC_LLDTESTS_ReceiveCliRspHandler();
    }
    else if (HW_IPCC_RX_PENDING( HW_IPCC_LLDTESTS_M0_CMD_CHANNEL ))
    {
        HW_IPCC_LLDTESTS_ReceiveM0CmdHandler();
    }
#endif /* LLD_TESTS_WB */
#ifdef LLD_BLE_WB
    else if (HW_IPCC_RX_PENDING( HW_IPCC_LLD_BLE_RSP_CHANNEL ))
    {
        HW_IPCC_LLD_BLE_ReceiveRspHandler();
    }
    else if (HW_IPCC_RX_PENDING( HW_IPCC_LLD_BLE_M0_CMD_CHANNEL ))
    {
        HW_IPCC_LLD_BLE_ReceiveM0CmdHandler();
    }
#endif /* LLD_TESTS_WB */
#ifdef ZIGBEE_WB
    else if (HW_IPCC_RX_PENDING( HW_IPCC_ZIGBEE_APPLI_NOTIF_ACK_CHANNEL ))
    {
        HW_IPCC_ZIGBEE_StackNotifEvtHandler();
    }
    else if (HW_IPCC_RX_PENDING( HW_IPCC_ZIGBEE_M0_REQUEST_CHANNEL ))
    {
        HW_IPCC_ZIGBEE_StackM0RequestHandler();
    }
#endif /* ZIGBEE_WB */
    else if (HW_IPCC_RX_PENDING( HW_IPCC_BLE_EVENT_CHANNEL ))
    {
        HW_IPCC_BLE_EvtHandler();
    }
    else if (HW_IPCC_RX_PENDING( HW_IPCC_TRACES_CHANNEL ))
    {
        HW_IPCC_TRACES_EvtHandler();
    }
}

void HW_IPCC_Tx_Handler()
{
    if (HW_IPCC_TX_PENDING( HW_IPCC_SYSTEM_CMD_RSP_CHANNEL ))
    {
        HW_IPCC_SYS_CmdEvtHandler();
    }
#ifdef MAC_802_15_4_WB
    else if (HW_IPCC_TX_PENDING( HW_IPCC_MAC_802_15_4_CMD_RSP_CHANNEL ))
    {
        HW_IPCC_MAC_802_15_4_CmdEvtHandler();
    }
#endif /* MAC_802_15_4_WB */
#ifdef THREAD_WB
    else if (HW_IPCC_TX_PENDING( HW_IPCC_THREAD_OT_CMD_RSP_CHANNEL ))
    {
        HW_IPCC_OT_CmdEvtHandler();
    }
#endif /* THREAD_WB */
#ifdef LLD_TESTS_WB
    // No TX handler for LLD tests
#endif /* LLD_TESTS_WB */
#ifdef ZIGBEE_WB
    if (HW_IPCC_TX_PENDING( HW_IPCC_ZIGBEE_CMD_APPLI_CHANNEL ))
    {
        HW_IPCC_ZIGBEE_CmdEvtHandler();
    }
#endif /* ZIGBEE_WB */

    else if (HW_IPCC_TX_PENDING( HW_IPCC_MM_RELEASE_BUFFER_CHANNEL ))
    {
        HW_IPCC_MM_FreeBufHandler();
    }
    else if (HW_IPCC_TX_PENDING( HW_IPCC_HCI_ACL_DATA_CHANNEL ))
    {
        HW_IPCC_BLE_AclDataEvtHandler();
    }
}

/* General */
void HW_IPCC_Enable()
{
    /**
     * Such as IPCC IP available to the CPU2, it is required to keep the IPCC clock running
     when FUS is running on CPU2 and CPU1 enters deep sleep mode
     */
    LL_C2_AHB3_GRP1_EnableClock(LL_C2_AHB3_GRP1_PERIPH_IPCC);

    /* When the device is out of standby, it is required to use the EXTI mechanism to wakeup CPU2 */
    LL_EXTI_EnableRisingTrig_32_63( LL_EXTI_LINE_41 );
    /* It is required to have at least a system clock cycle before a SEV after LL_EXTI_EnableRisingTrig_32_63() */
    LL_C2_EXTI_EnableEvent_32_63( LL_EXTI_LINE_41 );

    /**
     * In case the SBSFU is implemented, it may have already set the C2BOOT bit to startup the CPU2.
     * In that case, to keep the mechanism transparent to the user application, it shall call the system command
     * SHCI_C2_Reinit( ) before jumping to the application.
     * When the CPU2 receives that command, it waits for its event input to be set to restart the CPU2 firmware.
     * This is required because once C2BOOT has been set once, a clear/set on C2BOOT has no effect.
     * When SHCI_C2_Reinit( ) is not called, generating an event to the CPU2 does not have any effect
     * So, by default, the application shall both set the event flag and set the C2BOOT bit.
     */
    __SEV( );       /* Set the internal event flag and send an event to the CPU2 */
    __WFE( );       /* Clear the internal event flag */
    LL_PWR_EnableBootC2( );
}

void HW_IPCC_Init()
{
    LL_AHB3_GRP1_EnableClock( LL_AHB3_GRP1_PERIPH_IPCC );

    LL_C1_IPCC_EnableIT_RXO( IPCC );
    LL_C1_IPCC_EnableIT_TXF( IPCC );

    HAL_NVIC_EnableIRQ(IPCC_C1_RX_IRQn);
    HAL_NVIC_EnableIRQ(IPCC_C1_TX_IRQn);
}

/* BLE */
void HW_IPCC_BLE_Init()
{
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_BLE_EVENT_CHANNEL );
}

void HW_IPCC_BLE_SendCmd()
{
    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_BLE_CMD_CHANNEL );
}

static void HW_IPCC_BLE_EvtHandler()
{
    HW_IPCC_BLE_RxEvtNot();

    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_BLE_EVENT_CHANNEL );
}

void HW_IPCC_BLE_SendAclData()
{
    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_HCI_ACL_DATA_CHANNEL );
    LL_C1_IPCC_EnableTransmitChannel( IPCC, HW_IPCC_HCI_ACL_DATA_CHANNEL );
}

static void HW_IPCC_BLE_AclDataEvtHandler()
{
    LL_C1_IPCC_DisableTransmitChannel( IPCC, HW_IPCC_HCI_ACL_DATA_CHANNEL );

    HW_IPCC_BLE_AclDataAckNot();
}

__weak void HW_IPCC_BLE_AclDataAckNot(){};
__weak void HW_IPCC_BLE_RxEvtNot(){};

/* System */
void HW_IPCC_SYS_Init()
{
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_SYSTEM_EVENT_CHANNEL );
}

void HW_IPCC_SYS_SendCmd()
{
    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_SYSTEM_CMD_RSP_CHANNEL );
    LL_C1_IPCC_EnableTransmitChannel( IPCC, HW_IPCC_SYSTEM_CMD_RSP_CHANNEL );
}

static void HW_IPCC_SYS_CmdEvtHandler()
{
    LL_C1_IPCC_DisableTransmitChannel( IPCC, HW_IPCC_SYSTEM_CMD_RSP_CHANNEL );

    HW_IPCC_SYS_CmdEvtNot();
}

static void HW_IPCC_SYS_EvtHandler()
{
    HW_IPCC_SYS_EvtNot();

    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_SYSTEM_EVENT_CHANNEL );
}

__weak void HW_IPCC_SYS_CmdEvtNot(){};
__weak void HW_IPCC_SYS_EvtNot(){};

/* MAC 802.15.4 */
#ifdef MAC_802_15_4_WB
void HW_IPCC_MAC_802_15_4_Init()
{
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_MAC_802_15_4_NOTIFICATION_ACK_CHANNEL );
}

void HW_IPCC_MAC_802_15_4_SendCmd()
{
    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_MAC_802_15_4_CMD_RSP_CHANNEL );
    LL_C1_IPCC_EnableTransmitChannel( IPCC, HW_IPCC_MAC_802_15_4_CMD_RSP_CHANNEL );
}

void HW_IPCC_MAC_802_15_4_SendAck()
{
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_MAC_802_15_4_NOTIFICATION_ACK_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_MAC_802_15_4_NOTIFICATION_ACK_CHANNEL );
}

static void HW_IPCC_MAC_802_15_4_CmdEvtHandler()
{
    LL_C1_IPCC_DisableTransmitChannel( IPCC, HW_IPCC_MAC_802_15_4_CMD_RSP_CHANNEL );

    HW_IPCC_MAC_802_15_4_CmdEvtNot();
}

static void HW_IPCC_MAC_802_15_4_NotEvtHandler()
{
    LL_C1_IPCC_DisableReceiveChannel( IPCC, HW_IPCC_MAC_802_15_4_NOTIFICATION_ACK_CHANNEL );

    HW_IPCC_MAC_802_15_4_EvtNot();
}
__weak void HW_IPCC_MAC_802_15_4_CmdEvtNot(){};
__weak void HW_IPCC_MAC_802_15_4_EvtNot(){};
#endif

/* Thread */
#ifdef THREAD_WB
void HW_IPCC_THREAD_Init()
{
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_THREAD_NOTIFICATION_ACK_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_THREAD_CLI_NOTIFICATION_ACK_CHANNEL );
}

void HW_IPCC_OT_SendCmd()
{
    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_THREAD_OT_CMD_RSP_CHANNEL );
    LL_C1_IPCC_EnableTransmitChannel( IPCC, HW_IPCC_THREAD_OT_CMD_RSP_CHANNEL );
}

void HW_IPCC_CLI_SendCmd()
{
    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_THREAD_CLI_CMD_CHANNEL );
}

void HW_IPCC_THREAD_SendAck()
{
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_THREAD_NOTIFICATION_ACK_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_THREAD_NOTIFICATION_ACK_CHANNEL );
}

void HW_IPCC_THREAD_CliSendAck()
{
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_THREAD_CLI_NOTIFICATION_ACK_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_THREAD_CLI_NOTIFICATION_ACK_CHANNEL );
}

static void HW_IPCC_OT_CmdEvtHandler()
{
    LL_C1_IPCC_DisableTransmitChannel( IPCC, HW_IPCC_THREAD_OT_CMD_RSP_CHANNEL );

    HW_IPCC_OT_CmdEvtNot();
}

static void HW_IPCC_THREAD_NotEvtHandler()
{
    LL_C1_IPCC_DisableReceiveChannel( IPCC, HW_IPCC_THREAD_NOTIFICATION_ACK_CHANNEL );

    HW_IPCC_THREAD_EvtNot();
}

static void HW_IPCC_THREAD_CliNotEvtHandler()
{
    LL_C1_IPCC_DisableReceiveChannel( IPCC, HW_IPCC_THREAD_CLI_NOTIFICATION_ACK_CHANNEL );

    HW_IPCC_THREAD_CliEvtNot();
}

__weak void HW_IPCC_OT_CmdEvtNot(){};
__weak void HW_IPCC_CLI_CmdEvtNot(){};
__weak void HW_IPCC_THREAD_EvtNot(){};

#endif /* THREAD_WB */

/* LLD Tests */
#ifdef LLD_TESTS_WB
void HW_IPCC_LLDTESTS_Init()
{
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_LLDTESTS_CLI_RSP_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_LLDTESTS_M0_CMD_CHANNEL );
}

void HW_IPCC_LLDTESTS_SendCliCmd()
{
    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_LLDTESTS_CLI_CMD_CHANNEL );
}

static void HW_IPCC_LLDTESTS_ReceiveCliRspHandler()
{
    LL_C1_IPCC_DisableReceiveChannel( IPCC, HW_IPCC_LLDTESTS_CLI_RSP_CHANNEL );
    HW_IPCC_LLDTESTS_ReceiveCliRsp();
}

void HW_IPCC_LLDTESTS_SendCliRspAck()
{
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_LLDTESTS_CLI_RSP_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_LLDTESTS_CLI_RSP_CHANNEL );
}

static void HW_IPCC_LLDTESTS_ReceiveM0CmdHandler()
{
    LL_C1_IPCC_DisableReceiveChannel( IPCC, HW_IPCC_LLDTESTS_M0_CMD_CHANNEL );
    HW_IPCC_LLDTESTS_ReceiveM0Cmd();
}


void HW_IPCC_LLDTESTS_SendM0CmdAck()
{
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_LLDTESTS_M0_CMD_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_LLDTESTS_M0_CMD_CHANNEL );
}
__weak void HW_IPCC_LLDTESTS_ReceiveCliRsp(){};
__weak void HW_IPCC_LLDTESTS_ReceiveM0Cmd(){};
#endif /* LLD_TESTS_WB */

/* LLD BLE */
#ifdef LLD_BLE_WB
void HW_IPCC_LLD_BLE_Init()
{
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_LLD_BLE_RSP_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_LLD_BLE_M0_CMD_CHANNEL );
}

void HW_IPCC_LLD_BLE_SendCliCmd()
{
    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_LLD_BLE_CLI_CMD_CHANNEL );
}

void HW_IPCC_LLD_BLE_SendCliRspAck()
{
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_LLD_BLE_CLI_RSP_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_LLD_BLE_CLI_RSP_CHANNEL );
}

static void HW_IPCC_LLD_BLE_ReceiveM0CmdHandler()
{
    HW_IPCC_LLD_BLE_ReceiveM0Cmd();
}


void HW_IPCC_LLD_BLE_SendM0CmdAck()
{
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_LLD_BLE_M0_CMD_CHANNEL );
}
__weak void HW_IPCC_LLD_BLE_ReceiveCliRsp(){};
__weak void HW_IPCC_LLD_BLE_ReceiveM0Cmd(){};

/* Transparent Mode */
void HW_IPCC_LLD_BLE_SendCmd()
{
    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_LLD_BLE_CMD_CHANNEL );
}

static void HW_IPCC_LLD_BLE_ReceiveRspHandler()
{
    LL_C1_IPCC_DisableReceiveChannel( IPCC, HW_IPCC_LLD_BLE_RSP_CHANNEL );
    HW_IPCC_LLD_BLE_ReceiveRsp();
}

void HW_IPCC_LLD_BLE_SendRspAck()
{
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_LLD_BLE_RSP_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_LLD_BLE_RSP_CHANNEL );
}

#endif /* LLD_BLE_WB */

/* ZigBee */
#ifdef ZIGBEE_WB
void HW_IPCC_ZIGBEE_Init()
{
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_ZIGBEE_APPLI_NOTIF_ACK_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_ZIGBEE_M0_REQUEST_CHANNEL );
}

void HW_IPCC_ZIGBEE_SendM4RequestToM0()
{
    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_ZIGBEE_CMD_APPLI_CHANNEL );
    LL_C1_IPCC_EnableTransmitChannel( IPCC, HW_IPCC_ZIGBEE_CMD_APPLI_CHANNEL );
}

void HW_IPCC_ZIGBEE_SendM4AckToM0Notify()
{
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_ZIGBEE_APPLI_NOTIF_ACK_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_ZIGBEE_APPLI_NOTIF_ACK_CHANNEL );
}

static void HW_IPCC_ZIGBEE_CmdEvtHandler()
{
    LL_C1_IPCC_DisableTransmitChannel( IPCC, HW_IPCC_ZIGBEE_CMD_APPLI_CHANNEL );

    HW_IPCC_ZIGBEE_RecvAppliAckFromM0();
}

static void HW_IPCC_ZIGBEE_StackNotifEvtHandler()
{
    LL_C1_IPCC_DisableReceiveChannel( IPCC, HW_IPCC_ZIGBEE_APPLI_NOTIF_ACK_CHANNEL );

    HW_IPCC_ZIGBEE_RecvM0NotifyToM4();
}

static void HW_IPCC_ZIGBEE_StackM0RequestHandler()
{
    LL_C1_IPCC_DisableReceiveChannel( IPCC, HW_IPCC_ZIGBEE_M0_REQUEST_CHANNEL );

    HW_IPCC_ZIGBEE_RecvM0RequestToM4();
}

void HW_IPCC_ZIGBEE_SendM4AckToM0Request()
{
    LL_C1_IPCC_ClearFlag_CHx( IPCC, HW_IPCC_ZIGBEE_M0_REQUEST_CHANNEL );
    LL_C1_IPCC_EnableReceiveChannel( IPCC, HW_IPCC_ZIGBEE_M0_REQUEST_CHANNEL );
}

__weak void HW_IPCC_ZIGBEE_RecvAppliAckFromM0(){};
__weak void HW_IPCC_ZIGBEE_RecvM0NotifyToM4(){};
__weak void HW_IPCC_ZIGBEE_RecvM0RequestToM4(){};
#endif /* ZIGBEE_WB */

/* Memory Manager */
void HW_IPCC_MM_SendFreeBuf( void (*cb)() )
{
    if ( LL_C1_IPCC_IsActiveFlag_CHx( IPCC, HW_IPCC_MM_RELEASE_BUFFER_CHANNEL ) )
    {
        FreeBufCb = cb;
        LL_C1_IPCC_EnableTransmitChannel( IPCC, HW_IPCC_MM_RELEASE_BUFFER_CHANNEL );
    } else
    {
        cb();

        LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_MM_RELEASE_BUFFER_CHANNEL );
    }
}

static void HW_IPCC_MM_FreeBufHandler()
{
    LL_C1_IPCC_DisableTransmitChannel( IPCC, HW_IPCC_MM_RELEASE_BUFFER_CHANNEL );

    FreeBufCb();

    LL_C1_IPCC_SetFlag_CHx( IPCC, HW_IPCC_MM_RELEASE_BUFFER_CHANNEL );
}

/* Traces */
void HW_IPCC_TRACES_Init()
{
    LL_C1_IPCC_EnableReceiveChannel(IPCC, HW_IPCC_TRACES_CHANNEL);
}

static void HW_IPCC_TRACES_EvtHandler()
{
    HW_IPCC_TRACES_EvtNot();

    LL_C1_IPCC_ClearFlag_CHx(IPCC, HW_IPCC_TRACES_CHANNEL);
}

__weak void HW_IPCC_TRACES_EvtNot(){};
