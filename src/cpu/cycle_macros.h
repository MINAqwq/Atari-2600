#ifndef ATARI_CPU_CYCLE_MACROS_H
#define ATARI_CPU_CYCLE_MACROS_H

#include "6507.h"

#define CYCLE_START(c) switch (c->cycle_count) {
#define CYCLE_ADD(num, task)                                                   \
	case num:                                                              \
		task break;

#define CYCLE_END                                                              \
	default:                                                               \
		break;                                                         \
		}

#define NEXT_CYCLE(c) c->cycle_count++;
#define RESET_CYCLE(c) c->cycle_count = 0;
#define SET_CYCLE(cycle, c) c->cycle_count = cycle;

#endif
