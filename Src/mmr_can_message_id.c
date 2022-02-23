#include <stdint.h>
#include "mmr_can_message_id.h"


bool MMR_CAN_IsMessageIdOfType(
  MmrCanMessageId msgId,
  MmrCanMessageIdType type
) {
  return MMR_CAN_GetMessageIdType(msgId) == type;
}


uint8_t MMR_CAN_GetMessageIdType(MmrCanMessageId msgId) {
  return msgId >> 7;
}

uint8_t MMR_CAN_GetMessageIdSubtype(MmrCanMessageId msgId) {
  return msgId & B8_(0111, 1111);
}
