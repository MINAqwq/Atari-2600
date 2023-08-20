#ifndef ATARI_CPU_CYCLE_MACROS_H
#define ATARI_CPU_CYCLE_MACROS_H

#include "6507.h"

#define CYCLE_START(c) switch (c->cycle_count) {

#define CYCLE_ADDRMODE(addrmode)                                               \
	default:                                                               \
		addrmode(c);                                                   \
		break;

#define CYCLE_ADD(num, task)                                                   \
	case num:                                                              \
		task break;

#define CYCLE_END }

#define NEXT_CYCLE c->cycle_count++;
#define RESET_CYCLE c->cycle_count = 0;
#define GOTO_CYCLE(cycle) c->cycle_count = cycle;

#endif
