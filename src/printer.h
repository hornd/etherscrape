#ifndef _PRINTER_H
#define _PRINTER_H

#include "pack_list.h"
#include "layer2.h"

extern void
display_grid();

extern void
print_out(struct pack_cap *);

extern void
dump_packet_data(struct pack_cap *);

#endif