#include <stdio.h>
#include <stdint.h>
#include "layer2.h"

extern void
debug_print_l2(struct pack_cap *frame)
{
    print_layer2(frame->packet);
}

extern void
print_layer2(const uint8_t *packet)
{
	int i;
	layer2_header *eth_header;
	uint8_t *ptr;

	printf("Data Link Layer \n");

	eth_header = (layer2_header *)packet;
	ptr = eth_header->dest_addr;

	printf("Destination Address: ");
	for(i = 0; i<HARDWARE_ADDRESS_LEN; i++)
	{
		printf("%s%02x", i == 0 ? " " : ":", *ptr++);
	}
	printf("\nSource Address: ");
	for(i = 0; i<HARDWARE_ADDRESS_LEN; i++)
	{
		printf("%s%02x", i == 0 ? " " : ":", *ptr++);
	}
	printf("\nEther-Type: %04x\n", *ptr);
}

