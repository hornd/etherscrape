#include "layer2.h"
#include "layer3.h"
#include "protocol/ipv4.h"
#include "protocol/ipv6.h"
#include <string.h>
#include <stdio.h>

static void
get_protocol(struct pack_cap const *);

extern void
l3_get_sa(struct pack_cap const *pack, char *buf)
{
    if (l2_get_ethertype(pack) == ETHERTYPE_IPV4)
    {
        ipv4_get_sa(pack, buf);
    }
    else 
    {
        ipv6_get_sa(pack, buf);
    }
}

extern void
l3_get_da(struct pack_cap const *pack, char *buf)
{
    if (l2_get_ethertype(pack) == ETHERTYPE_IPV4)
    {
        ipv4_get_da(pack, buf);
    }
    else 
    {
        ipv6_get_da(pack, buf);
    }

}

extern void
l3_focus_print(struct pack_cap const *pack)
{
    switch (l2_get_ethertype(pack)) 
    {
    case ETHERTYPE_IPV4:
        ipv4_print(pack);
        break;
    case ETHERTYPE_IPV6:
        ipv6_print(pack);
        break;
    }
}

static char*
l3_ipv4_get_payload_protocol(struct pack_cap const *pack)
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

    return "Unk.";
}

static char*
l3_ipv6_get_payload_protocol(struct pack_cap const *pack)
{
    const uint8_t *ip_begin = (pack->packet) + L3_OFFSET;
    switch(((ipv6_header *)ip_begin)->ipv6_next_hdr)
    {
    case 1:
        return "ICMP";
    case 2:
        return "IGMP";
    case 4:
        return "IP";
    case 6:
        return "TCP";
    case 8: 
        return "EGP";
    case 17:
        return "UDP";
    case 41:
    case 59:
        return "IPv6";
    case 58:
        return "ICMP";
    }    

    return "????";
}

extern char*
l3_get_payload_protocol(struct pack_cap const *pack)
{
    if (l2_get_ethertype(pack) == ETHERTYPE_IPV4)
    {
        return l3_ipv4_get_payload_protocol(pack);
    }
    else if (l2_get_ethertype(pack) == ETHERTYPE_IPV6)
    {
        return l3_ipv6_get_payload_protocol(pack);
    }

    return "NotIP";
}

static void
get_protocol(struct pack_cap const *pack)
{

}
