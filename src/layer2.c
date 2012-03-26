#include <stdio.h>
#include <stdint.h>
#include "layer2.h"
/*debug
#include <net/ethernet.h>
  #include "pack_list.h"

static void testfunc(struct pack_cap *pack);*/

extern void
debug_print_l2(struct pack_cap *frame)
{
    print_layer2(frame->packet);
    /*   print_layer2(frame); */
}



/*static void testfunc(struct pack_cap *pack)
{
    struct ether_header *eptr;
    eptr = (struct ehter_header *)(pack->packet);


    printf("DA 1: ");
    printf("%s\n", ether_ntoa((const struct ether_addr *)&eptr->ether_dhost));

    }*/


extern void
print_layer2(const uint8_t *packet)
{
	int i;
	layer2_header *eth_header;
	uint8_t *ptr;

	printf("Data Link Layer \n");

    printf("%d\n",*packet); 
	eth_header = (layer2_header *)packet;

	ptr = eth_header->dest_addr;

	printf("Destination Address: ");
	for(i = 0; i<HARDWARE_ADDRESS_LEN; i++)
	{
		printf("%s%02x", i == 0 ? " " : ":", *ptr++);
	}

	printf("\nSource Address: ");
    printf("Debug 3...\n");
	for(i = 0; i<HARDWARE_ADDRESS_LEN; i++)
	{
		printf("%s%02x", i == 0 ? " " : ":", *ptr++);
	}
	printf("\nEther-Type: %04x\n", *ptr);  
}

