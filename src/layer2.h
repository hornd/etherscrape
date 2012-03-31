#ifndef _LAYER_2_H
#define _LAYER_2_H

/* Size of hardware address in octets */
#define HARDWARE_ADDRESS_LEN 6

#include "pack_list.h"
#include "util.h"

typedef uint16_t ethertype;


typedef struct
{
	uint8_t dest_addr[HARDWARE_ADDRESS_LEN];
	uint8_t source_addr[HARDWARE_ADDRESS_LEN];
	ethertype ether_type; 
    uint32_t fcs;
    char *encapsulated;
} layer2_header;

typedef enum
{
    DEST_ADDR,
    SOURCE_ADDR,
    ETHERTYPE,
    PAYLOAD,
    FCS
} l2_components;

/* Parse out the L2 destination address and store it in string
   representation in the second argument. */
extern void
l2_get_da(struct pack_cap const *, char *);

/* Parse out the L2 source address and store it in string
   representation in the second argument. */
extern void
l2_get_sa(struct pack_cap const *, char *);

/* Parse out and return the frame ethertype. */
extern ethertype
l2_get_ethertype(struct pack_cap const *);

#endif
