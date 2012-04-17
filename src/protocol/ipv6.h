#ifndef _IPV_6_H
#define _IPV_6_H

struct ipv6_address
{
    uint8_t addr[16];
};

typedef struct
{
    union {
        uint16_t ipv6_version_traffic_class;
        uint32_t ipv6_flow_label;
    } ipv6_v_tc_fl;

    uint16_t ipv6_payload_len;
    uint8_t  ipv6_next_hdr;
    uint8_t  ipv6_hop_limit;
    struct ipv6_address ipv6_sourceaddr;
    struct ipv6_address ipv6_destaddr;
} ipv6_header;

#define VERSION_START_BIT         0
#define VERSION_END_BIT           3
#define TRAFFIC_CLASS_START_BIT   4
#define TRAFFIC_CLASS_END_BIT     11
#define FLOW_LABEL_START_BIT      12
#define FLOW_LABEL_END_BIT        31

#endif
