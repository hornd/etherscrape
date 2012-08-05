#define APP_NAME "etherscrape"

#include <stdio.h>
#include <pcap.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include "pack_list.h"
#include "layer2.h"
#include "etherscrape.h"
#include "ethertype.h"
#include "util.h"
#include "printer.h"
#include "grid.h"
#include "interactive.h"

#define MAX_PACKET_LEN 9000

struct
{
    uint32_t packets;
    bool read_from_save_file;
    char *save_file_name;
} config;

extern struct captured packets_captured;

static pcap_t* get_pcap_handle(char *, char *);
static void handle_packet(u_char *, const struct pcap_pkthdr *, const u_char *);
static void usage();
static void cleanup();
static void init(int, char**);

static void
handle_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{ 
    struct pack_cap *cur_packet;

    cur_packet = construct_node(header, packet);

    if (!cur_packet)
    {
        printf("Out of memory\n");
        exit(EXIT_FAILURE);
    } 
}

static void 
usage()
{
    printf("etherscrape [-c packets] [-o save_file]\n");
    exit(1);
}

static void 
cleanup()
{
    free(config.save_file_name);
}

static void 
init(int argc, char* argv[])
{
    int i = 1;
    config.packets = 10;

    /* Disable stdout buffering to avoid long lags in the callback */
    setbuf(stdout, NULL); 

    while(i < argc)
    {
        if (strcmp("-c", argv[i]) == 0)
        {
            if (argv[i+1] == NULL || ((config.packets = atoi(argv[i+1])) == 0) ||
                !is_numeric(argv[i+1]))
                usage();

            config.packets = atoi(argv[i+1]);
            i++;
        }
        else if (strcmp("-o", argv[i]) == 0)
        {
            if (argv[i+1] == NULL)
                usage();

            DEBUG(printf("Reading from save file: %s\n", argv[i+1]));
            config.read_from_save_file = TRUE;
            config.save_file_name = malloc(strlen(argv[i+1]) * sizeof(char));
            strcpy(config.save_file_name, argv[i+1]);
            DEBUG(printf("Captured filename: %s\n", config.save_file_name));
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

static pcap_t *
get_pcap_handle(char *device, char *errbuf)
{
    if (config.read_from_save_file)
    {
        return pcap_open_offline(config.save_file_name, errbuf);
    }

    return pcap_open_live(device, MAX_PACKET_LEN, 1, 1000, errbuf);
}

int 
main(int argc, char* argv[])
{
    char *device; /* Device name to capture on. */
    char errbuf[PCAP_ERRBUF_SIZE]; /* Error buffer */
    pcap_t *handle; /* Packet capture handle */
    int loop_return;

    init(argc, argv);
	
    device = pcap_lookupdev(errbuf);
    if (device == NULL)
    {
        fprintf(stderr, "Could not find default device: %s\n", errbuf);
        exit(EXIT_FAILURE);
    }
	
    handle = get_pcap_handle(device, errbuf);

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

    loop_return = pcap_loop(handle, config.packets, handle_packet, NULL);
    DEBUG(printf("Packet capture complete\n"));
    
    if (loop_return == -1)
    {
        printf("An error occurred when capturing %s\n", pcap_geterr(handle));
    }

    cleanup();

    go_interactive();

    pcap_close(handle);
    return 0;
}



