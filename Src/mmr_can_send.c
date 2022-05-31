#include <stdbool.h>
#include "mmr_can.h"
#include "mmr_can_util.h"

#define MAILBOXES_COUNT 3

static MmrCanHeader buildDefaultHeader(MmrCan *can, MmrCanMessageId msgId);
static CanTxHeader buildTxHeader(MmrCan *can, MmrCanPacket *packet);
static CanMailbox *getNextMailbox(MmrCan *can);


HalStatus MMR_CAN_SendString(MmrCan *can, MmrCanMessageId msgId, const char *data) {
  uint8_t len =
    strnlen(data, MMR_CAN_MAX_DATA_LENGTH);

  return MMR_CAN_SendRaw(can, msgId, &data, len);
}


HalStatus MMR_CAN_SendInt(MmrCan *can, MmrCanMessageId msgId, int data) {
  return MMR_CAN_SendRaw(can, msgId, &data, sizeof(data))
}


HalStatus MMR_CAN_SendFloat(MmrCan *can, MmrCanMessageId msgId, float data) {
  return MMR_CAN_SendRaw(can, msgId, &data, sizeof(data));
}


HalStatus MMR_CAN_SendRaw(
  MmrCan *can,
  MmrCanMessageId msgId,
  void *data,
  uint8_t length
) {
  return MMR_CAN_SendPacket(can, (MmrCanPacket){
    .header = buildDefaultHeader(can, msgId),
    .data = data,
    .length = length,
  });
}


HalStatus MMR_CAN_SendPacket(MmrCan *can, MmrCanPacket packet) {
  CanTxHeader txHeader =
    buildTxHeader(can, &packet);

  return HAL_CAN_AddTxMessage(
    can->handle,
    &txHeader,
    (uint8_t*)packet.data,
    getNextMailbox(can)
  );
}


static MmrCanHeader buildDefaultHeader(MmrCan *can, MmrCanMessageId msgId) {
  return (MmrCanHeader){
    .messageId = msgId,
    .senderId = can->id,
    .priority = MMR_CAN_MESSAGE_PRIORITY_NORMAL,
    .messageType = MMR_CAN_MESSAGE_TYPE_NORMAL,
  };
}


static CanTxHeader buildTxHeader(MmrCan *can, MmrCanPacket *packet) {
  return (CanTxHeader){
    .ExtId = MMR_CAN_HeaderToBits(packet->header),
    .IDE = CAN_ID_EXT,
    .RTR = CAN_RTR_DATA,
    .DLC = packet->length,
    .TransmitGlobalTime = DISABLE,
  };
}


static CanMailbox *getNextMailbox(MmrCan *can) {
  can->currentMailbox++;
  can->currentMailbox %= MAILBOXES_COUNT;

  return can->mailboxes + can->currentMailbox;
}
