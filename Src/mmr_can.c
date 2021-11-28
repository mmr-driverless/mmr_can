#include "mmr_can.h"


HalStatus MMR_CAN_FilterConfig(CanHandle *hcan, MmrCanFilterSettings settings) {
  CAN_FilterTypeDef filter = {
    .FilterActivation = settings.enabled
      ? CAN_FILTER_ENABLE
      : CAN_FILTER_DISABLE,

    .FilterIdHigh = settings.idMask,
    .FilterMaskIdHigh = settings.idMask,
    .FilterFIFOAssignment = settings.fifo,
    .FilterBank = settings.bank,
    .SlaveStartFilterBank = settings.slaveBankStart,
    .FilterMode = CAN_FILTERMODE_IDMASK,
    .FilterScale = CAN_FILTERSCALE_32BIT,
  };

  return HAL_CAN_ConfigFilter(hcan, &filter);
}

CanFilterMask MMR_CAN_AlignStandardMask(CanFilterMask baseMask) {
  static const uint8_t extendedMaskSurplusBytes = 5;
  return baseMask << extendedMaskSurplusBytes;
}

MmrCanFilterSettings MMR_CAN_GetDefaultFilterSettings() {
  return (MmrCanFilterSettings) {
    .enabled = true,
    .fifo = MMR_CAN_RX_FIFO,
    .idMask = 0,
    .bank = 0,
    .slaveBankStart = 14,
  };
}


HalStatus MMR_CAN_Send(CanHandle *hcan, MmrCanPacket packet) {
  CAN_TxHeaderTypeDef header = {
    .IDE = CAN_ID_STD,
    .RTR = CAN_RTR_DATA,
    .DLC = packet.length,
    .StdId = packet.remoteId,
    .TransmitGlobalTime = DISABLE,
  };

  return HAL_CAN_AddTxMessage(hcan, &header, packet.data, packet.mailbox);
}


static void __handleCanRxInterrupt(CAN_HandleTypeDef *hcan) {
  static CAN_RxHeaderTypeDef rxHeader = {};
  static CanRxBuffer rxData = {};

  HAL_CAN_GetRxMessage(hcan, MMR_CAN_RX_FIFO, &rxHeader, rxData);
}

#if MMR_CAN_RX_FIFO == CAN_RX_FIFO0
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
  __handleCanRxInterrupt(hcan);
}
#elif MMR_CAN_RX_FIFO == CAN_RX_FIFO1
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) {
  __handleCanRxInterrupt(hcan);
}
#endif
