#ifndef _LAYER_2_H
#define _LAYER_2_H

#define HARDWARE_ADDRESS_LEN 6 /* Length in halfwords */
#define HARDWARE_ADDRESS_BYTES 17 /* For printing, includes colons */
#define ETHERNET_FCS_LEN 4

#include "pack_list.h"
#include "util.h"

typedef uint16_t ethertype;

typedef struct
{
	uint8_t   eth_dest_addr[HARDWARE_ADDRESS_LEN];
	uint8_t   eth_source_addr[HARDWARE_ADDRESS_LEN];
	ethertype ether_type;
    uint8_t  *payload;  
    uint32_t  eth_fcs;
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

/* Print function for focused packet analysis */
extern void
l2_focus_print(struct pack_cap const *);

/* Parse outand return the ethernet FCS */
extern uint32_t
l2_get_fcs(struct pack_cap const *);

#endif
