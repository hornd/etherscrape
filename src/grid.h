#ifndef _GRID_H
#define _GRID_H

#include "util.h"

#define PACKETS_DISPLAYED_PER_PAGE  10

extern void
display_grid();

extern bool
grid_next();

extern bool
grid_prev();

extern uint32_t
get_current_display_start();

extern void
print_out(const struct pack_cap *);

#endif
