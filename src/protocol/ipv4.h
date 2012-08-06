#ifndef _IPV_4_H
#define _IPV_4_H

#include <stdint.h>
#include "../pack_list.h"

#define L3_OFFSET 14

struct ipv4_address
{
    uint8_t addr[4];
};

typedef enum
{
    RESERVED = 0,
    DONT_FRAGMENT = 0x1,
    MORE_FRAGMENTS = 0x2
} ipv4_flags;

typedef struct
{
    uint8_t  ipv4_version_header_length;
    uint8_t  ipv4_dscp_congestion;
    uint16_t ipv4_total_length;
    uint16_t ipv4_id;
    uint16_t ipv4_flags_fragment;
    uint8_t  ipv4_time_to_live;
    uint8_t  ipv4_protocol;
    uint16_t ipv4_crc;

    struct ipv4_address ipv4_sourceaddr;
    struct ipv4_address ipv4_destaddr;
} ipv4_header;

/* Note: These bit indexes are 0-indexed from the LSB of the field in which
   they reside. For example, we store the DSCP/ECN as a single octet in the
   ipv4 header struct. The DSCP takes up the "first" 6 bits, and the ECN takes
   the last two. If you were looking at a raw print out of the bits (e.g)
                          
                          00001010 
                          ------
                           DSCP --
                                ECN
                                
   then you may expect DSCP_START_BIT to be 0 and ECN_START_BIT to be 6. However,
   DSCP_START_BIT should be 2 and ECN_START_BIT should be 0, due to starting at
   the LSB */
     
       
#define HDRLENGTH_START_BIT   0
#define HDRLENGTH_END_BIT     3
#define VERSION_START_BIT     4
#define VERSION_END_BIT       7

#define ECN_START_BIT         0
#define ECN_END_BIT           1
#define DSCP_START_BIT        2
#define DSCP_END_BIT          7

#define FRAGMENT_START_BIT    0
#define FRAGMENT_END_BIT      12
#define FLAGS_START_BIT       13
#define FLAGS_END_BIT         15


extern void 
ipv4_get_sa(struct pack_cap const *, char *);

extern void 
ipv4_get_da(struct pack_cap const *, char *);

extern void 
ipv4_print(struct pack_cap const *);

#endif 
