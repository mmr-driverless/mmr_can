#ifndef INC_MMR_CAN_SCS_MANAGER_H_
#define INC_MMR_CAN_SCS_MANAGER_H_

#include "mmr_can.h"


/**
 * Scs_timer represents the max number of counter
 * that need to checked w/current time
 */
#ifndef MMR_CAN_SCS_ENTRIES_COUNT
#define MMR_CAN_SCS_ENTRIES_COUNT 5
#endif


/**
 * @brief 
 * Maximum timeout before first retransmission,
 * in milliseconds 
 */
#ifndef MMR_CAN_MAX_TIMEOUT
#define MMR_CAN_MAX_TIMEOUT 500
#endif


/**
 * It depends on how many bits the board devotes to the timer
 * Check the datasheet
 */
typedef uint32_t TimerRange;


/**
 * @brief Represents the base-struct to manage a single RTR
 * and allows to interface with the associated SCS's timer
 */
typedef struct {
  MmrCanHeader header;
  TimerRange counter;
  int rtr;
} MmrCanScsEntry;


typedef enum {
  MMR_CAN_SCS_CHECK_OK,
  MMR_CAN_SCS_CHECK_RTR,
  MMR_CAN_SCS_CHECK_ERROR,
} MmrCanScsCheckResult;


bool MMR_CAN_MaybeHandleACK(MmrCanHeader header);
HalStatus MMR_CAN_HandleNextScs(CanHandle *hcan);
HalStatus MMR_CAN_SendSCS(
  CanHandle *hcan,
  MmrCanMessageId scsId,
  CanId senderId
);

#endif // !INC_MMR_CAN_SCS_MANAGER_H_
