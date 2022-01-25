#ifndef INC_MMR_CAN_QUEUE_H_
#define INC_MMR_CAN_QUEUE_H_

#include <stdint.h>
#include "mmr_can.h"

#define MMR_CAN_QUEUE_SIZE 10

typedef struct {
  MmrCanMessage messages[MMR_CAN_QUEUE_SIZE];
  size_t count;
} MmrCanQueue;

#endif /* INC_MMR_CAN_QUEUE_H_ */
