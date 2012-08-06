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

/* TODO: Finish this list... */
typedef enum
{
    HOPOPT,
    ICMP,
    IGMP,
    GGP,
/*    IPv4, */
    ST,
    TCP,
    CBT,
    EGP,
    IGP,
    BBN_RCC_MON,
    NVP_II,
    PUP,
    ARGUS,
    EMCON,
    EXNET,
    CHAOS,
    UDP,
    MUX,
    DCN_MEAS,
    HMP,
    PRM,
    XNS_IDP,
    TRUNK_1,
    TRUNK_2,
    LEAF_1,
    LEAF_2,
    RDP,
    IRTP,
    ISO_TP4,
    NETBLT,
    MFE_NSP,
    MERIT_INP,
    DCCP,
    THREEPC,
    IDPR,
    XTP,
    DDP,
    IDPR_CMTP,
    TPPLUSPLUS,
    IL,
/*    IPv6, */
    SDRP,
    IPv6_ROUTE,
    IPv6_FRAG,
    IDRP,
    RSVP,
    GRE,
    MHRP,
    BNA,
    ESP,
    AH,
    I_NLSP,
    SWIPE,
    NARP,
    MOBILE,
    TLSP,
    SKIP,
    ICv6_ICMP,
    IPv6_NONEXT,
    IPv6_OPTS,
    ANY_HOST,
    CFTP,
    ANY_LOCAL,
    SAT_EXPAK,
    KRYPTOLAN,
    RVD
} l3_header_protocols;

typedef struct 
{
    union 
    {
        ipv4_header ipv4;
        ipv6_header ipv6;
    } l3_type;
    l3_protocols protocol;
} layer3_header;

extern void 
l3_get_sa(struct pack_cap const *, char *);

extern void
l3_get_da(struct pack_cap const *, char *);

extern char *
l3_get_payload_protocol(struct pack_cap const *);

extern void
l3_focus_print(struct pack_cap const *);

#endif
