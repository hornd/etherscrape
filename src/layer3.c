#include "layer2.h"
#include "layer3.h"
#include <string.h>
#include <stdio.h>

extern void
l3_get_sa(struct pack_cap const *pack, char *buf)
{
    if (l2_get_ethertype(pack) == 0x800)
    {
        const uint8_t *ip_begin = (pack->packet) + L3_OFFSET;
        ip_address sa = ((ipv4_header *)ip_begin)->ipv4_sourceaddr;
        sprintf(buf, "%d.%d.%d.%d", sa.addr[0], sa.addr[1], sa.addr[2], sa.addr[3]);
    }
    else 
    {
        sprintf(buf, "%04x:%04x:%04x:%04x:%04x:%04x", 0xffff, 0, 0x1234, 0xff00, 0x6655, 0x987a);
    }
}

extern void
l3_get_da(struct pack_cap const *pack, char *buf)
{
    if (l2_get_ethertype(pack) == 0x800)
    {
        const uint8_t *ip_begin = (pack->packet) + L3_OFFSET;
        ip_address da = ((ipv4_header *)ip_begin)->ipv4_destaddr;
        sprintf(buf, "%d.%d.%d.%d", da.addr[0], da.addr[1], da.addr[2], da.addr[3]);
    }
    else 
    {
        sprintf(buf, "%04x:%04x:%04x:%04x:%04x:%04x", 0xffff, 0, 0x1234, 0xff00, 0x6655, 0x987a);
    }

}

extern char*
l3_get_payload_protocol(struct pack_cap const *pack)
{
    const uint8_t *ip_begin = (pack->packet) + L3_OFFSET;
    switch(((ipv4_header *)ip_begin)->ipv4_protocol)
    {
    case 1:
        return "ICMP";
    case 2:
        return "IGMP";
    case 6:
        return "TCP";
    case 17:
        return "UDP";
      
    }
/*    return NULL; */
    return "Unk.";
}
