#include <stdbool.h>
#include "mmr_can.h"


MmrResult MMR_CAN_TryReceive(MmrCan *can, MmrCanMessage *result) {
  size_t pendingMessages =
    HAL_CAN_GetRxFifoFillLevel(hcan, MMR_CAN_RX_FIFO);

  if (pendingMessages > 0) {
    return MMR_CAN_Receive(hcan, result) != HAL_OK
      ? MMR_RESULT_COMPLETED
      : MMR_RESULT_ERROR;
  }

  return MMR_RESULT_PENDING;
}


HalStatus MMR_CAN_Receive(MmrCan *can, MmrCanMessage *result) {
  CanRxHeader rxHeader = {};
  HalStatus status = HAL_CAN_GetRxMessage(
    can->handle,
    can->fifo,
    &rxHeader,
    result->store
  );

  result->header = MMR_CAN_HeaderFromBits(rxHeader.ExtId);
  return status;
}
