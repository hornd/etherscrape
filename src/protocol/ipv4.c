#include <stdio.h>
#include <netinet/in.h>
#include "ipv4.h"
#include "../etherscrape.h"
#include "../util.h"

static uint8_t ipv4_get_version(const ipv4_header *);
static uint8_t ipv4_get_headerlength(const ipv4_header *);
static uint8_t ipv4_get_dscp(const ipv4_header *);
static uint8_t ipv4_get_ecn(const ipv4_header *);
static uint16_t ipv4_get_total_length(const ipv4_header *);
static uint16_t ipv4_get_identification(const ipv4_header *);
static uint8_t  ipv4_get_flags(const ipv4_header *);
static char* ipv4_flags_to_str(const uint8_t);
static uint16_t ipv4_get_fragment(const ipv4_header *);
static uint8_t ipv4_get_ttl(const ipv4_header *);
static uint8_t ipv4_get_protocol(const ipv4_header *);
static uint16_t ipv4_get_hdr_checksum(const ipv4_header *);

extern void 
ipv4_get_sa(struct pack_cap const *pack, char *buf)
{
    const uint8_t *ip_begin = (pack->packet) + L3_OFFSET;
    struct ipv4_address sa = ((ipv4_header *)ip_begin)->ipv4_sourceaddr;
    sprintf(buf, "%d.%d.%d.%d", sa.addr[0], sa.addr[1], sa.addr[2], sa.addr[3]);
}

extern void 
ipv4_get_da(struct pack_cap const *pack, char *buf)
{
    const uint8_t *ip_begin = (pack->packet) + L3_OFFSET;
    struct ipv4_address da = ((ipv4_header *)ip_begin)->ipv4_destaddr;
    sprintf(buf, "%d.%d.%d.%d", da.addr[0], da.addr[1], da.addr[2], da.addr[3]);
}

extern void 
ipv4_print(struct pack_cap const *pack)
{
    const ipv4_header *ip_begin = ((ipv4_header *)((pack->packet) + L3_OFFSET));
    char ip_da_buffer[20], ip_sa_buffer[20];

    ipv4_get_da(pack, ip_da_buffer);
    ipv4_get_sa(pack, ip_sa_buffer);

    printf(get_divider());
    printf("IP PDU\n");
    printf(get_divider());
    printf(FOCUS_STRING_INDENT " %d\n", "Version: ", ipv4_get_version(ip_begin));
    printf(FOCUS_STRING_INDENT " %d\n", "Header Length: ", ipv4_get_headerlength(ip_begin));
    printf(FOCUS_STRING_INDENT " %d\n", "DSCP: ", ipv4_get_dscp(ip_begin));
    printf(FOCUS_STRING_INDENT " %d\n", "ECN: ", ipv4_get_ecn(ip_begin));
    printf(FOCUS_STRING_INDENT " %d\n", "Total Length: ", ipv4_get_total_length(ip_begin));
    printf(FOCUS_STRING_INDENT " %d\n", "ID: ", ipv4_get_identification(ip_begin));
    printf(FOCUS_STRING_INDENT " %s\n", "Flags: ", ipv4_flags_to_str(ipv4_get_flags(ip_begin)));
    printf(FOCUS_STRING_INDENT " %d\n", "Fragment: ", ipv4_get_fragment(ip_begin));
    printf(FOCUS_STRING_INDENT " %d\n", "TTL: ", ipv4_get_ttl(ip_begin));
    printf(FOCUS_STRING_INDENT " %d\n", "Protocol: ", ipv4_get_protocol(ip_begin));
    printf(FOCUS_STRING_INDENT " %d\n", "Header CRC: ", ipv4_get_hdr_checksum(ip_begin));

    printf(FOCUS_STRING_INDENT " %s\n", "Source IP:", ip_sa_buffer);
    printf(FOCUS_STRING_INDENT " %s\n", "Dest IP:", ip_da_buffer);

    if (ipv4_get_headerlength(ip_begin) > 5) {
        printf("TODO: Implement IPv4 Options\n");
    }

}

static uint8_t ipv4_get_ttl(const ipv4_header *pack)
{
    return pack->ipv4_time_to_live;
}

static uint8_t ipv4_get_protocol(const ipv4_header *pack)
{
    return pack->ipv4_protocol;
}

static uint16_t ipv4_get_hdr_checksum(const ipv4_header *pack)
{
    return ntohs(pack->ipv4_crc);
}

static uint16_t ipv4_get_fragment(const ipv4_header *pack)
{
    return GET_BITS(pack->ipv4_flags_fragment, FRAGMENT_START_BIT, FRAGMENT_END_BIT);
}  

static uint8_t ipv4_get_flags(const ipv4_header *pack)
{
    return GET_BITS(pack->ipv4_flags_fragment, FLAGS_START_BIT, FLAGS_END_BIT);
}

static char* ipv4_flags_to_str(const uint8_t flags)
{
    switch (flags) 
    {
    case 0:
        return "None";
    case 1:
        return "Don't Fragment";
    case 2:
        return "More Fragments";
    case 3:
        return "Don't Fragment | More Fragments";
    }

    DEBUG_PRINT(("ipv4_flags_to_str received a value of %d which is not expected", flags), DEBUG_HIGH);
    return "None";
}

static uint16_t ipv4_get_identification(const ipv4_header *pack)
{
    DEBUG_PRINT(("Reading ID: 0x%04x\n", pack->ipv4_id), DEBUG_LOW);
    return ntohs(pack->ipv4_id);
}

static uint16_t ipv4_get_total_length(const ipv4_header *pack)
{
    DEBUG_PRINT(("Reading length: 0x%04x\n", pack->ipv4_total_length), DEBUG_LOW);
    return ntohs(pack->ipv4_total_length);
}

static uint8_t ipv4_get_ecn(const ipv4_header *pack)
{
    DEBUG_PRINT(("Pulling bits %d - %d out of 0x%02x\n", ECN_START_BIT, ECN_END_BIT, pack->ipv4_dscp_congestion), DEBUG_LOW);
    return GET_BITS(pack->ipv4_dscp_congestion, ECN_START_BIT, ECN_END_BIT);
}

static uint8_t ipv4_get_dscp(const ipv4_header *pack)
{
    DEBUG_PRINT(("Pulling bits %d - %d out of 0x%02x\n", DSCP_START_BIT, DSCP_END_BIT, pack->ipv4_dscp_congestion), DEBUG_LOW);
    return GET_BITS(pack->ipv4_dscp_congestion, DSCP_START_BIT, DSCP_END_BIT);
}

static uint8_t ipv4_get_version(const ipv4_header *pack)
{
    return GET_BITS(pack->ipv4_version_header_length, VERSION_START_BIT, VERSION_END_BIT);
}

static uint8_t ipv4_get_headerlength(const ipv4_header *pack)
{
    return GET_BITS(pack->ipv4_version_header_length, HDRLENGTH_START_BIT, HDRLENGTH_END_BIT);
}
