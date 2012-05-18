#ifndef _IPV_4_H
#define _IPV_4_H

#include <stdint.h>
#include "../pack_list.h"

#define L3_OFFSET 14

struct ipv4_address
{
    uint8_t addr[4];
};

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

#define HDRLENGTH_START_BIT   0
#define HDRLENGTH_END_BIT     3
#define VERSION_START_BIT     4
#define VERSION_END_BIT       7
#define DSCP_START_BIT        8
#define DSCP_END_BIT          13
#define ECN_START_BIT         14
#define ECN_END_BIT           15

extern void 
ipv4_get_sa(struct pack_cap const *, char *);

extern void 
ipv4_get_da(struct pack_cap const *, char *);

extern void 
ipv4_print(struct pack_cap const *);

#endif 
