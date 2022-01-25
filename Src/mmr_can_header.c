#include "mmr_can_header.h"
#include "mmr_can_util.h"
#include "mmr_can_optimize.h"

uint32_t *MMR_CAN_HeaderToBits(MmrCanHeader *header) {
  return (uint32_t*)header;
}

MmrCanHeader *MMR_CAN_HeaderFromBits(uint32_t *bits) {
  return (MmrCanHeader*)bits;
}


bool MMR_CAN_IsMultiFrame(MmrCanHeader *header) {
  return header->messageType == MMR_CAN_MESSAGE_TYPE_MULTI_FRAME;
}

bool MMR_CAN_IsMultiFrameEnd(MmrCanHeader *header) {
  return header->messageType == MMR_CAN_MESSAGE_TYPE_MULTI_FRAME_END;
}
