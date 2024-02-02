#ifndef ATARI_CPU_CYCLE_MACROS_H
#define ATARI_CPU_CYCLE_MACROS_H

#include "6507.h"

#define CYCLE_START switch (c->cycle_count) {

#define CYCLE_ADDRMODE(addrmode)                                               \
	default:                                                               \
		addrmode;                                                      \
		break;

#define CYCLE_ADD(num, task) case num: task break;

#define CYCLE_END }

#define NEXT_CYCLE	  c->cycle_count++;
#define RESET_CYCLE	  c->cycle_count = 0;
#define GOTO_CYCLE(cycle) c->cycle_count = cycle

/* oops cycle */
#define CYCLE_OOPS 0xFF

#endif
