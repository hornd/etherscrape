#include <stdio.h>
#include "ipv4.h"
#include "../util.h"

static uint8_t ipv4_get_version(const ipv4_header *);
static uint8_t ipv4_get_headerlength(const ipv4_header *);

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
    printf(get_divider());
    printf("IP PDU\n");
    printf(get_divider());
    printf(FOCUS_STRING_INDENT " %d\n", "Version: ", ipv4_get_version(ip_begin));
    printf(FOCUS_STRING_INDENT " %d\n", "Header Length: ", ipv4_get_headerlength(ip_begin));
}


static uint8_t ipv4_get_version(const ipv4_header *pack)
{
    return GET_BITS(pack->ipv4_version_header_length, VERSION_START_BIT, VERSION_END_BIT);
}

static uint8_t ipv4_get_headerlength(const ipv4_header *pack)
{
    return GET_BITS(pack->ipv4_version_header_length, HDRLENGTH_START_BIT, HDRLENGTH_END_BIT);
}
