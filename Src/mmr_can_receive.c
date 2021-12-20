#include <stdbool.h>
#include "mmr_can.h"

static HalStatus receiveOne(ReceptionParams *rp);
static HalStatus receiveAll(ReceptionParams *rp);
static bool headerIsMultiFrame(MmrCanHeader *header, CanId targetId);


typedef struct {
  CanHandle *handle;
  uint8_t *result;
  struct {
    CanRxHeader rx;
    MmrCanHeader mmr;
  } headers;

  uint8_t fifo;
} ReceptionParams;


/**
 * @brief
 * Reads a CAN message and stores it inside the
 * given MmrCanMessage struct.
 *
 * If a multi-frame message is received, this function will block
 * and read every frame for that particular message.
 */
HalStatus MMR_CAN_Receive(CanHandle *hcan, MmrCanMessage *result) {
  ReceptionParams rp = {
    .handle = hcan,
    .result = interpretAs(uint8_t*, result->store),
    .fifo = MMR_CAN_RX_FIFO,
  };

  HalStatus status = receiveOne(&rp);
  if (status != HAL_OK) {
    return status;
  }

  result->senderId = rp.headers.mmr.senderId;
  if (MMR_CAN_IsMultiFrame(&rp.headers.mmr)) {
    status |= receiveAll(&rp);
  }

  return status;
}


static HalStatus receiveAll(ReceptionParams *rp) {
  CanId targetId = rp->headers.mmr.senderId;
  HalStatus status = HAL_OK;
  do {
    rp->result += MMR_CAN_MAX_DATA_LENGTH;
    status |= receiveOne(rp);
  } while (
    headerIsMultiFrame(&rp->headers.mmr, targetId) && status == HAL_OK
  );

  return status;
}


static HalStatus receiveOne(ReceptionParams *rp) {
  HalStatus status =
    HAL_CAN_GetRxMessage(rp->hcan, rp->fifo, &(rp->headers.rx), rp->result);

  rp->headers.mmr = convertTo(MmrCanHeader, header->ExtId);
  return status;
}


static always_inline bool headerIsMultiFrame(MmrCanHeader *header, CanId targetId) {
  return
    MMR_CAN_IsMultiFrame(header) &&
    !MMR_CAN_IsMultiFrameEnd(header) &&
    header->senderId == targetId;
}
