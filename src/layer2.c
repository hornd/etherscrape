#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "layer2.h"

extern void
print_l2(const uint8_t *packet)
{
	int i;
	layer2_header *eth_header;
	uint8_t *ptr;

	printf("Data Link Layer \n");

    printf("%d\n",*packet); 
	eth_header = (layer2_header *)packet;

	ptr = eth_header->eth_dest_addr;

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

extern void
l2_get_sa(struct pack_cap const *pack_cap, char *buf)
{
    uint8_t i, loc_ptr = 0;
    uint8_t *ptr = ((layer2_header *)(pack_cap->packet))->eth_source_addr;
    
    for(i=0; i<HARDWARE_ADDRESS_LEN; i++)
    {
        loc_ptr += sprintf(buf+loc_ptr, "%s%02x", i==0 ? " " : ":", *ptr++);
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
        loc_ptr += sprintf(buf+loc_ptr, "%s%02x", i==0 ? " " : ":", *ptr++);
    }

    buf[loc_ptr] = '\0';
}

extern ethertype
l2_get_ethertype(struct pack_cap const *pack_cap)
{
    return ntohs(((layer2_header *)(pack_cap->packet))->ether_type);
}
