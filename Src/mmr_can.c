#include "mmr_can.h"
#include "mmr_can_util.h"


MmrCanTickProvider __mmr_can_tickProvider;


void MMR_CAN_SetTickProvider(MmrCanTickProvider tickProvider) {
  __mmr_can_tickProvider = tickProvider;
}


/**
 * @brief
 * Initializes the filter using the values
 * from MMR_CAN_GetDefaultFilterSettings, and then
 * starts the CAN
 */
HalStatus MMR_CAN_BasicSetupAndStart(CanHandle *hcan) {
  return
    MMR_CAN_FilterConfigDefault(hcan) |
    HAL_CAN_Start(hcan)
    ;
}


HalStatus MMR_CAN_FilterConfig(CanHandle *hcan, MmrCanFilterSettings settings) {
  CanFilter filter = {
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


MmrCanFilterSettings MMR_CAN_GetDefaultFilterSettings() {
  return (MmrCanFilterSettings) {
    .enabled = true,
    .fifo = MMR_CAN_FILTER_FIFO,
    .idMask = 0,
    .bank = 0,
    .slaveBankStart = 14,
  };
}
