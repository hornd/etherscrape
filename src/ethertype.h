#include <inttypes.h>

#ifndef _ETHERTYPE_H
#define _ETHERTYPE_H

#define NUM_ETHERTYPES    4

#ifndef ETHERTYPE_IPV4
#define ETHERTYPE_IPV4    0x0800
#endif

#ifndef ETHERTYPE_ARP
#define ETHERTYPE_ARP     0x0806
#endif

#ifndef ETHERTYPE_IPV6
#define ETHERTYPE_IPV6    0x86DD
#endif

#ifndef ETHERTYPE_UNKNOWN
#define ETHERTYPE_UNKNOWN 0xFFFF
#endif

typedef struct
{
	uint16_t ethertype;
	char* etherstring;
} ethertype_string;

static const
ethertype_string ethertypes[] =
{
	{ ETHERTYPE_IPV4,       "IPv4" },
	{ ETHERTYPE_ARP,        "ARP"  },
	{ ETHERTYPE_IPV6,       "IPv6" },
	{ ETHERTYPE_UNKNOWN,    "Unknown" },
};

#endif
