#ifndef INC_MMR_CAN_UTIL_H_
#define INC_MMR_CAN_UTIL_H_

#include <stdint.h>
#include <string.h>

#define sizeofarray(array) \
  (sizeof(array) / sizeof(*(array)))

#define stringArrayLength(array) \
  stringBufferLength((array), sizeofarray(array))

#define stringBufferLength(pbuffer, maxLen) \
  strnlen((const char*)(pbuffer), maxLen)

#define min(a, b) ((a) < (b) ? a : b);
#define mask(value, bits) (value & bits)
#define convertTo(resultType, lvalue) (*interpretAs(resultType*, &(lvalue)))
#define interpretAs(resultType, lvalue) ((resultType)(lvalue))


/**
 * @brief
 * Represents the result of an asynchronous computation
 *
 * Either
 *  - Error: the computation resulted in error
 *  - Pending: the computation is still undergoing
 *  - Completed: the computation has completed succesfully
 *               and its results can be read
 *
 * Asynchronous logig can be easily implemented using State Machines
 */
typedef enum {
  MMR_ASYNC_RESULT_ERROR,
  MMR_ASYNC_RESULT_PENDING,
  MMR_ASYNC_RESULT_COMPLETED,
} MmrAsyncResult;


#endif /* INC_MMR_CAN_UTIL_H_ */
