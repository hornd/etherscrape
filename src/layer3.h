#ifndef _LAYER_3_H
#define _LAYER_3_H

#include "protocol/ipv4.h"
#include "protocol/ipv6.h"
#include "util.h"
#include "pack_list.h"

#define L3_OFFSET 14

typedef enum 
{
    IPv4,
    IPv6, /* ... */
    NUM_PROTOCOLS
} l3_protocols;

typedef struct 
{
    l3_protocols protocol;
    union 
    {
        ipv4_header ipv4;
        ipv6_header ipv6;
    } l3_type;
} layer3_header;

extern void 
l3_get_sa(struct pack_cap const *, char *);

extern void
l3_get_da(struct pack_cap const *, char *);

#endif
