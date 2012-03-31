#ifndef _UTIL_H_
#define _UTIL_H_

#include <time.h>
#include <stdint.h>


#define GET_MASK_BITS(num)              ((1U << (num))-1)

#define GET_BITS(val, start, end)       (((val) >> start) &  \
                                          GET_MASK_BITS((end)-(start)+1))

#define PUT_BITS(val, start, end, put)  (((put) << (start)) |    \
                                          ((val) & ~GET_BITS((val),(start),(end))))

#define GET_CLOCK_MS()                  (clock() / (CLOCKS_PER_SEC / 1000))

extern char*
strethertype(uint16_t);

#endif
