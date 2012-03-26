#include <stdio.h>
#include <stdint.h>
#include "pack_list.h"
#include "pretty_print.h"

/*debug*/
#include "layer2.h"

static void
print_asterisks();

static void
print_header();

static char*
get_string_format();

extern void 
display_grid()
{
    struct pack_cap *hd;
    
    print_header();

    FOREACH_PL(hd)
    {
        print_out(hd);
    }
}

extern void
print_out(struct pack_cap *pack)
{

    layer2_header *eth_header;
    uint8_t *ptr, i;
    eth_header = (layer2_header *)(pack->packet);
    ptr = eth_header->dest_addr;

    printf("%-5d | %-8s |", pack->packet_id, "2ms");

    /* Debug only... needs to be IP */
    for(i=0; i<HARDWARE_ADDRESS_LEN; i++)
    {
        printf("%s%02x", i==0?" ":":", *ptr++);
    }

    printf("\n");
}

#define ID_FORMAT "%-5s"
#define TIME_FORMAT "%-8s"
#define SOURCE_FORMAT "%-18s"
#define DEST_FORMAT SOURCE_FORMAT
#define TYPE_FORMAT "%-10s"
#define LENGTH_FORMAT "%-5s"

static void
print_header()
{
    #define LINE_LENGTH 72

    uint8_t i = LINE_LENGTH;

    printf(get_string_format(), "ID", "Time Rx", "Source IP", "Dest IP", "Type", "Length");

    while(i--) printf("-");
    printf("\n");
    
}

static char*
get_string_format()
{
    return ID_FORMAT " | " TIME_FORMAT " | " SOURCE_FORMAT " | " DEST_FORMAT " | " TYPE_FORMAT " | " LENGTH_FORMAT " |\n";
}

static void
print_asterisks()
{
    printf("******************************\n");
}
