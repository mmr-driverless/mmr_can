#ifndef INC_MMR_CAN_HEADER_H_
#define INC_MMR_CAN_HEADER_H_

#include <stdbool.h>
#include "mmr_can_util.h"
#include "mmr_can_binary_literals.h"

/**
 * @brief
 * These values can be appended to the extended-id
 * portion of the CAN bus message (that is, the lower 5 bits
 * of the standard id)
 * 
 * They are used to check if a message is either standalone
 * or split into multiple frames
 * 
 * When the priority and id fields are the same, multi-frame
 * messages have a higher priority over normal ones
 */
typedef enum {
  MMR_CAN_MESSAGE_TYPE_MULTI_FRAME = B_(0010),
  MMR_CAN_MESSAGE_TYPE_MULTI_FRAME_END = B_(0011),
  MMR_CAN_MESSAGE_TYPE_NORMAL = B_(1000),
} MmrCanMessageType;


/**
 * @brief
 * This struct encodes the values stored inside the
 * extended id field of a CAN packet.
 */
typedef struct {
  uint32_t priority : 5;
  uint32_t senderId : 23;
  MmrCanMessageType messageType : 4;
} MmrCanHeader;


bool MMR_CAN_IsMultiFrame(MmrCanHeader *header);
bool MMR_CAN_IsMultiFrameEnd(MmrCanHeader *header);

#endif /* INC_MMR_CAN_HEADER_H_ */
