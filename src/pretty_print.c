#include <stdio.h>
#include <stdint.h>
#include <net/ethernet.h>
#include "pack_list.h"
#include "pretty_print.h"

/*debug*/
#include "layer2.h"

static char* 
get_asterisks();

extern void
print_out(struct pack_cap *pack)
{
    printf("%s\n", get_asterisks());
    printf("Packet Length: %u\n", pack->packet_len);
    printf("%s\n", get_asterisks());

    debug_print_l2(pack); 
}


static char*
get_asterisks()
{
    return "******************************";
}
