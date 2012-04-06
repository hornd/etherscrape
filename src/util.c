/* debug */
#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
#include "util.h"
#include "ethertype.h"

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

extern bool
is_numeric(char *str)
{
    while(*str) 
    {
        switch(*str) 
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            break;
        default:
            return FALSE;
        }
        str++;
    }
    return TRUE;
}
