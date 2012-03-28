#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdint.h>

#define GET_MASK_BITS(num) ((1U << (num))-1)
#define GET_BITS(val, start, end) (((val) >> start) &  \
                                   GET_MASK_BITS((end)-(start)+1))

extern char*
strethertype(uint16_t);

#endif
