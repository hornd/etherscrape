#include <stdio.h>
#include "ipv4.h"

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

}
