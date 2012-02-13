#include <stdlib.h>
#include "pack_list.h"

static void insert_node(struct pack_cap *);
static struct pack_cap * find_leaf();

extern struct pack_cap*
construct_node(const struct pcap_pkthdr *header, 
	       const uint8_t *packet)
{
    static uint32_t cur_id = 0;

    struct pack_cap *cur = malloc(sizeof(struct pack_cap));
    if (!cur) 
        return NULL;

    cur->header = header;
    cur->packet = packet;
    cur->packet_len = header->len;
    cur->packet_id = cur_id++;
    cur->next = NULL;

    insert_node(cur);

    return cur;         
}

extern struct pack_cap *
find_node_by_id(uint32_t node_id)
{
    struct pack_cap *hd;
    FOREACH_PL(hd) 
    {
        if(hd->packet_id == node_id)
            return hd;
    }
    return NULL;
}

static void
insert_node(struct pack_cap * cur)
{
    if (packets_captured.head == NULL)
    {
        packets_captured.head = cur;
    }
    else
    {
        struct pack_cap *leaf = find_leaf();
        leaf->next = cur;
    }
    packets_captured.len++;
}

static struct pack_cap *
find_leaf()
{
    struct pack_cap *hd;
    FOREACH_PL(hd);
    return hd;
}

