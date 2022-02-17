#include "mmr_can_timer_scs.h"

static MmrTimerSCS arr_timer[MMR_SCS_NR_TIMERS];

static MmrTimerSCS* findTimer(MmrCanMessageId scsId, CanId receiverId);


void MMR_CAN_InitTimerSCS() {
  for (int i = 0; i < MMR_SCS_NR_TIMERS; i++)
  {
    arr_timer[i].scsId = 0;
    arr_timer[i].receiverId = 0;
    arr_timer[i].counter = 0;
  }
}


bool MMR_CAN_ClearTimerSCS(MmrCanMessageId scsId, CanId receiverId) {
  MmrTimerSCS *timer = findTimer(scsId, receiverId);
  if (timer == NULL) return false;

  timer->scsId = 0;
  timer->receiverId = 0;
  timer->counter = 0;
  return true;
}


bool MMR_CAN_SetTimerSCS(MmrCanMessageId scsId, CanId receiverId, TimerRange currentTime) {
  MmrTimerSCS *timer = findTimer(0, 0);
  if (timer == NULL) return false;

  timer->scsId = scsId;
  timer->receiverId = receiverId;
  timer->counter = currentTime;
  return true;
}


bool MMR_CAN_GetTimerSCS(MmrCanMessageId scsId, CanId receiverId, int *rtr, TimerRange currentTime, TimerRange thresholdDelay) {
  MmrTimerSCS *timer = findTimer(scsId, receiverId);
  if (timer == NULL) return false;

  if (currentTime - timer->counter >= thresholdDelay) {
    rtr++;
  }
  return true;
}


MmrTimerSCS* findTimer(MmrCanMessageId scsId, CanId receiverId) {
  int i = 0;
  for (; i < MMR_SCS_NR_TIMERS; i++) {
    MmrTimerSCS *timer = arr_timer + i;

    if (timer->scsId == scsId && timer->receiverId == receiverId) {
      return timer;
    }
  }

  return NULL;
}
