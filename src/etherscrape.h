#ifndef _ETHERSCRAPE_H
#define _ETHERSCRAPE_H

#include <stdint.h>
#include <stdarg.h>

#if defined(DEBUG_MODE)

#if !defined(DEBUG_LEVEL) || DEBUG_LEVEL < 1
#error "Must define DEBUG_LEVEL between [1,3]"
#endif

#define DEBUG_LOW 3
#define DEBUG_MED 2
#define DEBUG_HIGH 1

#define DEBUG(r) do{(r);}while(0)
/* n is a priority value. The lower the value of n, the higher priority the debug statement
   has; i.e. more important debug statements should send a lower value to this macro */
#define DEBUG_PRINT(r, n) do { if ((n) <= DEBUG_LEVEL) DEBUG_PRINT_(r); } while(0)
#define DEBUG_PRINT_(r) do { printf(" > [DEBUG] %s %d\n", __FILE__, __LINE__); printf(" > "); printf r; printf("\n"); } while(0)

#else

#define DEBUG(r)
#define DEBUG_PRINT(r, n)
#define DEBUG_PRINT_(r)
#define DEBUG_LOW
#define DEBUG_MED
#define DEBUG_HIGH

#endif

#endif
