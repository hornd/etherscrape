#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "layer2.h"

#define L2_STR_INDENT "%-21s"

extern void
l2_focus_print(struct pack_cap const *pack_cap)
{
    char buf[100];

    l2_get_da(pack_cap, buf);

    printf(L2_STR_INDENT " %s", "Destination Address: ", buf);
    l2_get_sa(pack_cap, buf);

    printf("\n" L2_STR_INDENT " %s", "Source Address: ", buf);
    printf("\n" L2_STR_INDENT " 0x%04x\n", "Ether-Type: ", l2_get_ethertype(pack_cap));
}

extern void
l2_get_sa(struct pack_cap const *pack_cap, char *buf)
{
    uint8_t i, loc_ptr = 0;
    uint8_t *ptr = ((layer2_header *)(pack_cap->packet))->eth_source_addr;
    
    for(i=0; i<HARDWARE_ADDRESS_LEN; i++)
    {
        loc_ptr += sprintf(buf+loc_ptr, "%s%02x", i==0 ? "" : ":", *ptr++);
    }
    buf[loc_ptr] = '\0';
}

extern void
l2_get_da(struct pack_cap const *pack_cap, char *buf)
{
    uint8_t i, loc_ptr = 0;
    uint8_t *ptr = ((layer2_header *)(pack_cap->packet))->eth_dest_addr;

    for(i=0; i<HARDWARE_ADDRESS_LEN; i++)
    {
        loc_ptr += sprintf(buf+loc_ptr, "%s%02x", i==0 ? "" : ":", *ptr++);
    }
    buf[loc_ptr] = '\0';
}

extern ethertype
l2_get_ethertype(struct pack_cap const *pack_cap)
{
    return ntohs(((layer2_header *)(pack_cap->packet))->ether_type);
}

extern uint32_t
l2_get_fcs(struct pack_cap const *pack_cap)
{
    return 0x12345678;
}
