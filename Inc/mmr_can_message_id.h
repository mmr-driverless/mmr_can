#ifndef INC_MMR_CAN_MESSAGE_ID_H_
#define INC_MMR_CAN_MESSAGE_ID_H_

#include <stdbool.h>
#include "mmr_can_binary_literals.h"

/**
 * @brief
 * Message ids are 10 bits wide
 * The first 3 bits determine the message id type, while
 * the other 7 determine the subtype.
 * 
 * Ids scheme:
 *
 *  id  | type | subtype
 * -----|------|---------
 *  SCS | 000  | xxxxxxx
 */
typedef enum MmrCanMessageId MmrCanMessageId;

typedef enum {
  MMR_CAN_MESSAGE_ID_TYPE_SCS = 0,
} MmrCanMessageIdType;


uint8_t MMR_CAN_GetMessageIdType(MmrCanMessageId msgId);
uint8_t MMR_CAN_GetMessageIdSubtype(MmrCanMessageId msgId);

bool MMR_CAN_IsMessageIdOfType(MmrCanMessageId msgId, MmrCanMessageIdType type);
bool MMR_CAN_IsMessageIdSCS(MmrCanMessageId msgId);


enum MmrCanMessageId {
// SCS
  MMR_CAN_MESSAGE_ID_SCS_PPA = 0x1,
  MMR_CAN_MESSAGE_ID_SCS_PLF,
  MMR_CAN_MESSAGE_ID_SCS_LV12,
  MMR_CAN_MESSAGE_ID_SCS_LV24,
  MMR_CAN_MESSAGE_ID_SCS_PF,
  MMR_CAN_MESSAGE_ID_SCS_FRBPS,
  MMR_CAN_MESSAGE_ID_SCS_EBS,
  MMR_CAN_MESSAGE_ID_SCS_APPS,
  MMR_CAN_MESSAGE_ID_SCS_TPS,
  
  MMR_CAN_MESSAGE_ID_SCS_AS_R2D,
  MMR_CAN_MESSAGE_ID_SCS_AS_TS,
  MMR_CAN_MESSAGE_ID_SCS_AS_FINISHED,
  MMR_CAN_MESSAGE_ID_SCS_AS_EMERGENCY,
  MMR_CAN_MESSAGE_ID_SCS_AS_READY,
  MMR_CAN_MESSAGE_ID_SCS_AS_DRIVING,
  MMR_CAN_MESSAGE_ID_SCS_AS_OFF,
  
  MMR_CAN_MESSAGE_ID_SCS_AM_MANUAL_DRIVING,
  MMR_CAN_MESSAGE_ID_SCS_AM_ACCELERATION,
  MMR_CAN_MESSAGE_ID_SCS_AM_SKIDPAD,
  MMR_CAN_MESSAGE_ID_SCS_AM_AUTOCROSS,
  MMR_CAN_MESSAGE_ID_SCS_AM_TRACKDRIVE,
  MMR_CAN_MESSAGE_ID_SCS_AM_EBS_TEST,
  MMR_CAN_MESSAGE_ID_SCS_AM_INSPECTION = 0x17,
// !SCS
};

#endif // !INC_MMR_CAN_MESSAGE_ID_H_
