#include "mmr_can_scs_manager.h"

static RTRresponse arr_scs[MMR_SCS_NR_TIMERS];

static RTRresponse* findResponse(MmrCanMessageId scsId, CanId receiverId);


bool SetRTRresponse(MmrCanMessageId scsId, CanId receiverId, int rtr)
{
    RTRresponse *response = findResponse(0, 0);
    if (response == NULL) return false;

    response->scsId = scsId;
    response->receiverId = receiverId;
    response->rtr = 0;

    return MMR_CAN_SetTimerSCS(response->scsId, response->receiverId, MMR_CAN_GetCurrentTime);
}

void CheckSCS()
{
    if (counter>=MMR_SCS_NR_TIMERS) counter=0;

    RTRresponse *_rtrResponse = &arr_scs[counter];

    if(!MMR_CAN_GetTimerSCS(_rtrResponse->scsId, _rtrResponse->receiverId, &_rtrResponse->rtr, MMR_CAN_GetCurrentTime, 500))
    {
      // do something
    }

    counter++;

    if (_rtrResponse->rtr==1)
    {
      // Return ritrasmission
    }

    if (_rtrResponse->rtr>1)
    {
      // Return Safe State
    }
}


TimerRange MMR_CAN_GetCurrentTime()
{
  return 0; //TODO: HAL....
}

RTRresponse* findResponse(MmrCanMessageId scsId, CanId receiverId) {
  int i = 0;
  for (; i < MMR_SCS_NR_TIMERS; i++) {
    RTRresponse *response = arr_scs + i;

    if (response->scsId == scsId && response->receiverId == receiverId) {
      return response;
    }
  }

  return NULL;
}