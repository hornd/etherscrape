#ifndef _PRINTER_H
#define _PRINTER_H

#include "pack_list.h"
#include "util.h"

extern void
dump_packet_data(struct pack_cap *);

extern bool
focused_raw_print();

extern bool
grid_focus(uint32_t);

#endif
