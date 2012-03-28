#ifndef _LAYER_3_H
#define _LAYER_3_H

#define NUM_BITS(t) ((t##END_BIT)-(t##START_BIT)+1)

#define DSCPSTART_BIT 8
#define DSCPEND_BIT   13

#define ECNSTART_BIT 14
#define ECNEND_BIT   15

#define TOTALLENGTH_START_BIT 19
#define TOTALLENGTH_NUM_BITS  31

#endif
