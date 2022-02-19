#include "mmr_can_scs_manager.h"

static MmrCanScsEntry __scsEntries[MMR_CAN_SCS_ENTRIES_COUNT];

static void maybeIncrementRTR(MmrCanScsEntry *entry);

static MmrCanScsEntry* putEntry(MmrCanHeader header);
static MmrCanScsEntry* clearEntry(MmrCanHeader header);
static MmrCanScsEntry* findEntry(MmrCanHeader header);

static TimerRange getCurrentTime();
static HalStatus sendScs(CanHandle *hcan, MmrCanHeader header);
static MmrCanScsCheckResult checkScs(MmrCanScsEntry *entry);


bool MMR_CAN_MaybeHandleAck(MmrCanHeader header) {
  if (header.messageType != MMR_CAN_MESSAGE_TYPE_ACK) {
    return false;
  }

  header.messageType = MMR_CAN_MESSAGE_TYPE_NORMAL;
  MmrCanScsEntry *entry = findEntry(header);
  if (entry == NULL) {
    return false;
  }

  clearEntry(header);
  return true;
}


HalStatus MMR_CAN_SendScs(
  CanHandle *hcan,
  MmrCanMessageId scsId,
  CanId senderId
) {
  MmrCanHeader header = {
    .senderId = senderId,
    .messageId = scsId,
    .priority = MMR_CAN_MESSAGE_PRIORITY_HIGH,
  };

  putEntry(header);
  return sendScs(hcan, header);
}


HalStatus MMR_CAN_HandleNextScs(CanHandle *hcan) {
  static int counter = 0;
  MmrCanScsEntry *entry = &__scsEntries[counter++ % MMR_CAN_SCS_ENTRIES_COUNT];

  switch (checkScs(entry)) {
  case MMR_CAN_SCS_CHECK_ERROR: return HAL_ERROR;
  case MMR_CAN_SCS_CHECK_OK: return HAL_OK;
  default: break;
  }

  entry->counter = getCurrentTime();
  return sendScs(hcan, entry->header);
}


HalStatus sendScs(CanHandle *hcan, MmrCanHeader header) {
  static CanMailbox scsMailbox = 0;
  MmrCanPacket packet = {
    .header = header,
    .mailbox = &scsMailbox,
    .length = 0,
  };

  return MMR_CAN_Send(hcan, packet);
}


MmrCanScsCheckResult checkScs(MmrCanScsEntry *entry) {
  maybeIncrementRTR(entry);
  return
    entry->rtr == 1 ? MMR_CAN_SCS_CHECK_RTR :
    entry->rtr > 1 ? MMR_CAN_SCS_CHECK_ERROR :
    MMR_CAN_SCS_CHECK_OK;
}


TimerRange getCurrentTime() {
  return __mmr_can_tickProvider();
}


void maybeIncrementRTR(MmrCanScsEntry *entry) {
  TimerRange delay =
    getCurrentTime() - entry->counter;

  if (delay >= MMR_CAN_MAX_TIMEOUT) {
    entry->rtr++;
  }
}


MmrCanScsEntry* putEntry(MmrCanHeader header) {
  MmrCanScsEntry *entry = findEntry((MmrCanHeader){});
  if (entry == NULL) {
    return NULL;
  }

  *entry = (MmrCanScsEntry){
    .header = header,
    .counter = getCurrentTime(),
  };

  return entry;
}

MmrCanScsEntry* clearEntry(MmrCanHeader header) {
  MmrCanScsEntry *entry = findEntry(header);
  if (entry == NULL) {
    return NULL;
  }

  *entry = (MmrCanScsEntry){};
  return entry;
}

MmrCanScsEntry* findEntry(MmrCanHeader header) {
  uint32_t *target = MMR_CAN_HeaderToBits(&header);
  uint32_t i = 0;

  for (; i < MMR_CAN_SCS_ENTRIES_COUNT; i++) {
    MmrCanScsEntry *entry = __scsEntries + i;
    uint32_t *curr = MMR_CAN_HeaderToBits(&entry->header);

    if (*curr == *target) {
      return entry;
    }
  }

  return NULL;
}
