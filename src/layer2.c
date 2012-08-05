#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "layer2.h"
#include "util.h"

extern void
l2_focus_print(struct pack_cap const *pack_cap)
{
    char da_buffer[HARDWARE_ADDRESS_WITH_COLON_LEN];
    char sa_buffer[HARDWARE_ADDRESS_WITH_COLON_LEN];

    l2_get_da(pack_cap, da_buffer);
    l2_get_sa(pack_cap, sa_buffer);

    printf(FOCUS_STRING_INDENT " %s", "Destination Address: ", da_buffer);
    printf("\n" FOCUS_STRING_INDENT " %s", "Source Address: ", sa_buffer);
    printf("\n" FOCUS_STRING_INDENT " 0x%04x", "Ether-Type: ", l2_get_ethertype(pack_cap));
    printf("\n" FOCUS_STRING_INDENT " 0x%08x\n", "FCS: ", l2_get_fcs(pack_cap));
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
    const uint8_t *ptr = pack_cap->packet + pack_cap->packet_len - ETHERNET_FCS_LEN;
    return ntohl(*((uint32_t *)ptr));
}
