#ifndef _PACK_LIST_H
#define _PACK_LIST_H

#include <stdint.h>
#include "pcap.h"

#define FOREACH_PL(nd)  for((nd) = packets_captured.head;   \
                            (nd)->next != NULL;             \
                            (nd) = (nd)->next)

struct pack_cap
{
    const struct pcap_pkthdr *header;
    const uint8_t *packet;
    struct pack_cap* next;
    uint32_t packet_len;
    uint32_t packet_id;
};

struct captured
{
    struct pack_cap *head;
    uint32_t len;
} packets_captured;

extern struct pack_cap *
construct_node(const struct pcap_pkthdr *, 
	       const uint8_t *);

extern struct pack_cap *
find_node_by_id(uint32_t);

#endif
