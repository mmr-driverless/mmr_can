#ifndef INC_MMR_CAN_HEADER_H_
#define INC_MMR_CAN_HEADER_H_

#include <stdbool.h>
#include "mmr_can_util.h"
#include "mmr_can_binary_literals.h"
#include "mmr_can_message_id.h"

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
  MMR_CAN_MESSAGE_ACK = B_(0001),
  MMR_CAN_MESSAGE_TYPE_MULTI_FRAME = B_(0010),
  MMR_CAN_MESSAGE_TYPE_MULTI_FRAME_END = B_(0011),
  MMR_CAN_MESSAGE_TYPE_NORMAL = B_(1000),
} MmrCanMessageType;


typedef enum {
  MMR_CAN_MESSAGE_PRIORITY_LOW = B_(0010),
  MMR_CAN_MESSAGE_PRIORITY_NORMAL = B_(0001),
  MMR_CAN_MESSAGE_PRIORITY_HIGH = B_(0000),
} MmrCanMessagePriority;


/**
 * @brief
 * This struct encodes the values stored inside the
 * extended id field of a CAN packet.
 */
typedef struct {
  MmrCanMessagePriority priority : 3;
  MmrCanMessageId messageId : 10;
  uint32_t senderId : 12;
  MmrCanMessageType messageType : 4;
} MmrCanHeader;


uint32_t *MMR_CAN_HeaderToBits(MmrCanHeader *header);
MmrCanHeader *MMR_CAN_HeaderFromBits(uint32_t *bits);

bool MMR_CAN_IsMultiFrame(MmrCanHeader *header);
bool MMR_CAN_IsMultiFrameEnd(MmrCanHeader *header);

#endif /* INC_MMR_CAN_HEADER_H_ */
