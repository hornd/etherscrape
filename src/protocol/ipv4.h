#ifndef _IPV_4_H
#define _IPV_4_H

typedef struct
{
    unsigned char stub;
} ipv4_header;

#define DSCPSTART_BIT 8
#define DSCPEND_BIT   13

#define ECNSTART_BIT 14
#define ECNEND_BIT 15

#define TOTALLENGTHSTART_BIT 19
#define TOTALLENGTHEND_BIT   31 /* Todo, wrong */

#endif 
