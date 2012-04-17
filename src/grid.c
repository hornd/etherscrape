#include <stdio.h>
#include "grid.h"
#include "pack_list.h"
#include "util.h"
#include "layer2.h"
#include "layer3.h"

struct d_config
{
    uint32_t display_start, display_end;
};

static struct d_config display_config = { 1, 10 };

static void print_header();
static char* get_string_format();

extern bool
grid_next()
{
    if (display_config.display_end >= packets_captured.len)
        return FALSE;

    display_config.display_start += PACKETS_DISPLAYED_PER_PAGE;
    if (display_config.display_end + PACKETS_DISPLAYED_PER_PAGE > packets_captured.len)
    {
        display_config.display_end = packets_captured.len;
    }
    else
    {
        display_config.display_end += PACKETS_DISPLAYED_PER_PAGE;
    }

    display_grid();

    return TRUE;
}

extern bool
grid_prev()
{
    if (display_config.display_start == 1)
        return FALSE;

    display_config.display_end -= PACKETS_DISPLAYED_PER_PAGE;
    if (display_config.display_start < PACKETS_DISPLAYED_PER_PAGE)
    {
        display_config.display_start = 1;
    }
    else
    {
        display_config.display_start -= PACKETS_DISPLAYED_PER_PAGE;
    }

    display_grid();

    return TRUE;
}

extern void 
display_grid()
{
    struct pack_cap *hd = find_node_by_id(display_config.display_start);
    uint8_t i = 0;

    print_header(); 

    while(i++ < PACKETS_DISPLAYED_PER_PAGE &&
          hd != NULL)
    {
        print_out(hd);
        hd = hd->next;
    }
}

extern void
print_out(struct pack_cap *pack)
{
    ethertype typ;
    layer2_header *eth_header;
    char buffer[100];
    char *temp_test;

    eth_header = (layer2_header *)(pack->packet);
    typ = l2_get_ethertype(pack);
    printf("%-5d | %-8s |", pack->packet_id, "2ms"); 

    l3_get_da(pack, buffer);
    printf(" %-32s  |", buffer);
    l3_get_sa(pack, buffer);

    printf(" %-32s  | ", buffer);
    temp_test = l3_get_payload_protocol(pack);
    if (temp_test) 
        printf("%-6s | ", temp_test);
    else
        printf("0x%-6x | ", typ);
    printf("%-5d ", pack->packet_len);

    printf("\n");
}


extern uint32_t
get_current_display_start() { return display_config.display_start; }

#define LINE_LENGTH 109

static void
print_header()
{
    uint8_t i = LINE_LENGTH;

    printf("\n");
    printf(get_string_format(), "ID", "Time Rx", "Source", "Dest", "Type", "Length");

    while(i--) printf("-");
    printf("\n");
    
}

#define ID_FORMAT "%-5s"
#define TIME_FORMAT "%-8s"
#define SOURCE_FORMAT "%-33s"
#define DEST_FORMAT SOURCE_FORMAT
#define TYPE_FORMAT "%-8s"
#define LENGTH_FORMAT "%-5s"

static char*
get_string_format()
{
    return ID_FORMAT " | " TIME_FORMAT " | " SOURCE_FORMAT " | " DEST_FORMAT " | " TYPE_FORMAT " | " LENGTH_FORMAT "\n";
}
