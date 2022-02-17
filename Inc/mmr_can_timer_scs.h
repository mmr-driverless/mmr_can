#ifndef INC_MMR_CAN_TIMER_SCS_H_
#define INC_MMR_CAN_TIMER_SCS_H_

#include "mmr_can_message_id.h"
#include "mmr_can_types.h"

/**
 * Scs_timer represents the max number of counter
 * that need to checked w/current time
 */
#ifndef MMR_SCS_NR_TIMERS
#define MMR_SCS_NR_TIMERS 5
#endif

/**
 * It depends on how many bits the board devotes to the timer
 * Check the datasheet
 */
typedef uint32_t TimerRange;

typedef struct {
  MmrCanMessageId scsId;
  CanId receiverId;
  TimerRange counter;
} MmrTimerSCS;


/**
 * All time units are to be considered as milliseconds (1ms)
 */
bool MMR_CAN_ClearTimerSCS(MmrCanMessageId scsId, CanId receiverId);
bool MMR_CAN_SetTimerSCS(MmrCanMessageId scsId, CanId receiverId, TimerRange currentTime);

/**
 * @brief The delay is taken individually so that the 'manager' 
 * can first check the ACK and eventually reset the associated arr_timer
 * 
 * @param rtrResponse the 'manager' will have to manage an array of struct RTRresponse
 * @param currentTime from __HAL_TIM_GET_COUNTER(&htimX) or directly from the CNT register
 * @param thresholdDelay by rules 500ms
 */
bool MMR_CAN_GetTimerSCS(MmrCanMessageId scsId, CanId receiverId, int *rtr, TimerRange currentTime, TimerRange thresholdDelay);


#endif // !INC_MMR_CAN_TIMER_SCS_H_
