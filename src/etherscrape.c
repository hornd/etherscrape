#define APP_NAME "etherscrape"

#include <stdio.h>
#include <pcap.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "pack_list.h"
#include "layer2.h"
#include "etherscrape.h"
#include "ethertype.h"
#include "util.h"
#include "pretty_print.h"

/* Standard ethernet defines max packet length of 1518 octets (1500 octet payload, 12 octet CRC, 8 octet preamble+SFD).
   Jumbo frames are not actually supported by IEEE, but are seen out in the wild. 
   9000 is the decided maximum jumbo frame length */
#define MAX_PACKET_LEN 9000

struct
{
	uint32_t packets;
} config;


static void
handle_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    struct pack_cap *cur_packet = construct_node(header, packet);
    if (!cur_packet)
    {
        printf("Out of memory\n");
        exit(EXIT_FAILURE);
    }
}

static void
dump_packets()
{
    struct pack_cap *hd;
    FOREACH_PL(hd)
    {
        //    debug_print_l2(hd);
        print_out(hd);
        printf("\n[Enter] to continue...\n");
        getchar();
    }
}

void usage()
{
	printf("etherscrape [-c packets]\n");
	exit(1);
}

void init(int argc, char* argv[])
{
	int i = 1;
	config.packets = 10;
	while(i < argc)
	{
		if (strcmp("-c", argv[i]) == 0)
		{
			int atemp;
//			if(argv[i+1] == NULL || ((config.packets = atoi(argv[i+1])) == 0))
//				usage();
			if(argv[i+1] == NULL) usage();
			atemp = atoi(argv[i+1]);
			printf("%s :  %d\n", argv[i+1], atemp);
			i++;
		}
		else
		{
			printf("Aborting.. %d\n", i);
			usage();
		}
		i++;
	}

    packets_captured.head = NULL;
    packets_captured.len = 0;
}

int main(int argc, char* argv[])
{
	char *device; /* Device name to capture on. */
	char errbuf[PCAP_ERRBUF_SIZE]; /* Error buffer */
	pcap_t *handle; /* Packet capture handle */

	init(argc, argv);
	
	device = pcap_lookupdev(errbuf);
	if (device == NULL)
	{
		fprintf(stderr, "Could not find default device: %s\n", errbuf);
		exit(EXIT_FAILURE);
	}
	
	handle = pcap_open_live(device, MAX_PACKET_LEN, 1, 1000, errbuf);

	if (handle == NULL)
	{
		fprintf(stderr, "Could not open device %s: %s\n", device, errbuf);
		exit(EXIT_FAILURE);
	}

	if (pcap_datalink(handle) != DLT_EN10MB) 
	{
		fprintf(stderr, "%s is not an Ethernet device.\n", device);
		exit(EXIT_FAILURE);
	}

    printf("Capturing packets......\n");
	pcap_loop(handle, config.packets, handle_packet, NULL);

	pcap_close(handle);
  
    dump_packets();

	return 0;
}



