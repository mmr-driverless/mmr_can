#include <stdbool.h>
#include <stdint.h>
#include "mmr_can.h"


#define cast(pmsg, to) (*(to*)(pmsg->store))


uint16_t MMR_CAN_GetUInt16(MmrCanMessage *message) {
  return cast(message, uint16_t);
}

uint32_t MMR_CAN_GetUInt32(MmrCanMessage *message) {
  return cast(message, uint32_t);
}

uint64_t MMR_CAN_GetUInt64(MmrCanMessage *message) {
  return cast(message, uint64_t);
}

float MMR_CAN_GetFloat(MmrCanMessage *message) {
  return cast(message, float);
}


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
