#include <stdio.h>
#include "ipv6.h"

extern void 
ipv6_get_sa(struct pack_cap const *pack, char *buf)
{
    const uint8_t *ip_begin = (pack->packet) + L3_OFFSET;
    struct ipv6_address sa = ((ipv6_header *)ip_begin)->ipv6_sourceaddr;
    uint8_t i, bufloc = 0;
    uint8_t zero_group = 0;

    for(i=0; i<16; i+=2)
    {
        uint16_t two_byte = (sa.addr[i] << 8) | sa.addr[i+1];
        if (!two_byte && !zero_group)
        {
            sprintf(buf+bufloc, ":");
            zero_group = 1;
            bufloc += 1;
        }
        else if (two_byte)
        {
            sprintf(buf+bufloc, "%04x:", two_byte);
            bufloc += 5;
            zero_group = 0;
        }
    }
    
    if (!zero_group) buf[bufloc-1] = '\0';

}

extern void 
ipv6_get_da(struct pack_cap const *pack, char *buf)
{

    const uint8_t *ip_begin = (pack->packet) + L3_OFFSET;
    struct ipv6_address da = ((ipv6_header *)ip_begin)->ipv6_destaddr;
    uint8_t i, bufloc = 0;
    uint8_t zero_group = 0;

    for(i=0; i<16; i+=2)
    {
        uint16_t two_byte = (da.addr[i] << 8) | da.addr[i+1];
        if (!two_byte && !zero_group)
        {
            sprintf(buf+bufloc, ":");
            zero_group = 1;
            bufloc += 1;
        }
        else if (two_byte)
        {
            sprintf(buf+bufloc, "%04x:", two_byte);
            bufloc += 5;
            zero_group = 0;
        }
    }
    
    if (!zero_group) buf[bufloc-1] = '\0';
}

extern void 
ipv6_print(struct pack_cap const *pack)
{
}
