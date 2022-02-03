#include "mmr_can_scs_dict.h"

static MmrCanScsDictionary _dictionary;


void MMR_CAN_ScsDictPut(MmrCanScsDictEntry entry) {
  _dictionary[entry.key % MMR_CAN_SCS_DICTIONARY_SIZE] = entry;
}

void MMR_CAN_ScsDictRemove(uint32_t key) {
  _dictionary[key] = (MmrCanScsDictEntry){};
}

void MMR_CAN_ScsDictForeach(MmrCanScsDictAction action) {
  int i = 0;
  for (; i < MMR_CAN_SCS_DICTIONARY_SIZE; i++) {
    MmrCanScsDictEntry entry = _dictionary[i];
    if (entry.key != 0) {
      action(&entry);
    }
  }
}


uint32_t MMR_CAN_ScsMessageAsKey(MmrCanMessage *message) {
  uint16_t upperHalf = message->header.messageId;
  uint16_t lowerHalf = message->header.messageType;

  return (upperHalf << 16) | lowerHalf;
}
