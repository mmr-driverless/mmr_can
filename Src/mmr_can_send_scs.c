#include "mmr_can.h"
#include "mmr_can_scs_manager.h" 


HalStatus MMR_CAN_SendSCS(
  CanHandle *hcan,
  MmrCanMessageId scsId,
  CanMailbox *mailbox,
  CanId senderId
) {
  MmrCanPacket packet = {
    .header = {
      .senderId = senderId,
      .messageId = scsId,
      .priority = MMR_CAN_MESSAGE_PRIORITY_HIGH,
    },
    .mailbox = mailbox,
    .length = 0,
  };

  if(!MMR_CAN_SetRTRresponse()) 
  {
    // do something
  }
  
  return MMR_CAN_Send(hcan, packet);
}
