#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdint.h>
#include "pack_list.h"

#define GET_MASK_BITS(num)              ((1U << (num))-1)
#define GET_BITS(val, start, end)       (((val) >> start) &  \
                                            GET_MASK_BITS((end)-(start)+1))
#define PUT_BITS(val, start, end, put)  (((put) << (start)) |    \
                                            ((val) & ~GET_BITS((val),(start),(end))))
#define NUM_BITS(t)                     ((t##_END_BIT)-(t##_START_BIT)+1)

#define ARRLEN(s)                       (sizeof(s) / sizeof(s[0]))

#define TRUE 1
#define FALSE 0

#ifdef ETHERTYPE_IPV4
#undef ETHERTYPE_IPV4
#endif

#define ETHERTYPE_IPV4    0x0800

#ifdef ETHERTYPE_IPV6
#undef ETHERTYPE_IPV6
#endif

#define ETHERTYPE_IPV6    0x86DD

#define FOCUS_STRING_INDENT  "%-21s"

typedef uint8_t bool;

extern char*
strethertype(uint16_t);

extern bool 
is_numeric(const char *);

extern char* 
get_divider();

#endif
