#ifndef _LAYER_2_H
#define _LAYER_2_H

/* Size of hardware address in octets */
#define HARDWARE_ADDRESS_LEN 6

#include "pack_list.h"
#include "util.h"

typedef struct
{
	uint8_t dest_addr[HARDWARE_ADDRESS_LEN];
	uint8_t source_addr[HARDWARE_ADDRESS_LEN];
	uint16_t ether_type; 
    uint32_t fcs;
    char *encapsulated;
} layer2_header;

extern void
debug_print_l2(struct pack_cap *);

extern void
print_layer2(const uint8_t *);

#endif
