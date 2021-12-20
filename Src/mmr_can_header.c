#include "mmr_can_header.h"
#include "mmr_can_optimize.h"


bool MMR_CAN_IsMultiFrame(MmrCanHeader *header) {
  return header->messageType == MMR_CAN_MESSAGE_TYPE_MULTI_FRAME;
}

bool MMR_CAN_IsMultiFrameEnd(MmrCanHeader *header) {
  return header->messageType == MMR_CAN_MESSAGE_TYPE_MULTI_FRAME_END;
}
