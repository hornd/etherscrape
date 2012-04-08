#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "pack_list.h"
#include "printer.h"
#include "util.h"

/*debug*/
#include "layer2.h"
#include "layer3.h"

struct d_config
{
    uint32_t display_start, display_end;
};

static struct d_config display_config = { 0, 10 };

static void
print_header();

static char*
get_string_format();

extern uint32_t
get_current_display_start() { return display_config.display_start; }

extern void 
display_grid()
{
    struct pack_cap *hd;
    uint8_t i;

    printf("Captured %d packets\n", packets_captured.len);

    print_header(); 

    FOREACH_PL_UNTIL(hd, i, PACKETS_DISPLAYED_PER_PAGE) 
    {
        print_out(hd);
    }
}

extern void
dump_packet_data(struct pack_cap *p)
{
    uint8_t i;
    uint8_t *ptr = (uint8_t *)(p->packet);

    printf("\n\nPartial Packet Data: \n");
    for(i=1; i<=52; i++)
    {
        printf("%02x ", *ptr++);
        if (!(i%4)) printf("\n");
    } 
}

extern void
print_out(struct pack_cap *pack)
{
    ethertype typ;
    layer2_header *eth_header;
    char buffer[100];

    eth_header = (layer2_header *)(pack->packet);
    typ = l2_get_ethertype(pack);
    printf("%-5d | %-8s |", pack->packet_id, "2ms"); 

/* debug */
    if (typ == 0x800)
        l3_get_da(pack, buffer);
    else
        l2_get_da(pack, buffer);

    printf(" %-24s  |", buffer);

    if (typ == 0x800)
        l3_get_sa(pack, buffer);
    else
        l2_get_sa(pack, buffer);

    printf(" %-24s  | ", buffer);
    printf("0x%-6x | ", typ);
    printf("%-5d ", pack->packet_len);

    printf("\n");
}

#define LINE_LENGTH 80

static void
print_header()
{
    uint8_t i = LINE_LENGTH;

    printf(get_string_format(), "ID", "Time Rx", "Source", "Dest", "Type", "Length");

    while(i--) printf("-");
    printf("\n");
    
}

#define ID_FORMAT "%-5s"
#define TIME_FORMAT "%-8s"
#define SOURCE_FORMAT "%-25s"
#define DEST_FORMAT SOURCE_FORMAT
#define TYPE_FORMAT "%-8s"
#define LENGTH_FORMAT "%-5s"

static char*
get_string_format()
{
    return ID_FORMAT " | " TIME_FORMAT " | " SOURCE_FORMAT " | " DEST_FORMAT " | " TYPE_FORMAT " | " LENGTH_FORMAT "\n";
}

