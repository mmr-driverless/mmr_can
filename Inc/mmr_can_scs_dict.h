#ifndef INC_MMR_CAN_SCS_H_
#define INC_MMR_CAN_SCS_H_

#ifndef MMR_CAN_SCS_DICTIONARY_SIZE
#define MMR_CAN_SCS_DICTIONARY_SIZE 5
#endif

#include <stdint.h>
#include "mmr_can.h"


typedef struct {
  uint32_t key;
  uint32_t delayStart;
} MmrCanScsDictEntry;

typedef MmrCanScsDictEntry MmrCanScsDictionary[MMR_CAN_SCS_DICTIONARY_SIZE];
typedef void(*MmrCanScsDictAction)(MmrCanScsDictEntry *entry);


void MMR_CAN_ScsDictPut(MmrCanScsDictEntry entry);
void MMR_CAN_ScsDictRemove(uint32_t key);
void MMR_CAN_ScsDictForeach(MmrCanScsDictAction action);

uint32_t MMR_CAN_ScsGetKey(MmrCanMessage *message);

#endif // !INC_MMR_CAN_SCS_H_
