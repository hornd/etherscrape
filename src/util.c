#include <stdint.h>
#include "util.h"
#include "ethertype.h"

#define ARRLEN(s) (sizeof(s) / sizeof(s[0]))

char *packet_types_str[] = 
{
    "Plain Ethernet",
    "IPv4",
    "IPv6",
    "MPLS",
    "ARP",
    "Unknown"
};


extern char* 
strethertype(uint16_t type)
{
	uint8_t i;
	for(i=0; i<NUM_ETHERTYPES - 1; i++)
	{
		if(ethertypes[i].ethertype == type) return ethertypes[i].etherstring;
	}
	return ethertypes[i].etherstring;
}
