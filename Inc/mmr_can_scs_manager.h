#ifndef INC_MMR_CAN_SCS_MANAGER_H_
#define INC_MMR_CAN_SCS_MANAGER_H_

#include "mmr_can.h"
#include "mmr_can_timer_scs.h"

/**
 * TODO:
 * - GetCurrentTime
 * - ACK
 * - Reset timer
 * - Setup method
 */


/**
 * @brief Represents the base-struct to manage a single RTR
 * and allows to interface with the associated SCS's timer
 */
typedef struct {
  MmrCanMessageId scsId;
  CanId receiverId;
  int rtr;
} RTRresponse;


/**
 * It is used to iterate the RTRresponse array in the CheckSCS function 
 */
static int counter;


bool MMR_CAN_SetRTRresponse(MmrCanMessageId scsId, CanId receiverId, int rtr);
TimerRange MMR_CAN_GetCurrentTime();
void MMR_CAN_CheckSCS(); // What is necessary to do ritrasmission (mmr_can_send_scs)

#endif // !INC_MMR_CAN_SCS_MANAGER_H_