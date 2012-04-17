#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "pack_list.h"
#include "printer.h"
#include "util.h"
#include "layer2.h"
#include "layer3.h"

static bool print_packet(uint32_t);

static uint32_t cur_packet;

extern bool
focused_raw_print()
{
    uint8_t i, len, *ptr;
    struct pack_cap *p;
    
    if (cur_packet > packets_captured.len)
        return FALSE;

    p = find_node_by_id(cur_packet);

    len = p->packet_len * 2;
    ptr = (uint8_t *)(p->packet);

    printf("\nRaw Packet Data: \n");
    for(i=1; i<=len; i++)
    {
        printf("%02x ", *ptr++);
        if (!(i%16)) printf("\n");
    } 
    
    return TRUE;
}

extern void
dump_packet_data(struct pack_cap *p)
{
    uint8_t i, len = p->packet_len * 2;
    uint8_t *ptr = (uint8_t *)(p->packet);

    printf("\nRaw Packet Data: \n");
    for(i=1; i<=len; i++)
    {
        printf("%02x ", *ptr++);
        if (!(i%8)) printf("\n");
    } 
    printf("\n");
}

extern bool
grid_focus(uint32_t id)
{
    if (id > packets_captured.len) return FALSE;
    cur_packet = id;
    return print_packet(id);
}

static bool 
print_packet(uint32_t id)
{
    struct pack_cap *hd = find_node_by_id(id);
    if(!hd) return FALSE;

    printf("\n\n");
    l2_focus_print(hd);
    return TRUE;
}
