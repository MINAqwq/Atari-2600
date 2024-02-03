#ifndef ATARI_CPU_CYCLE_MACROS_H
#define ATARI_CPU_CYCLE_MACROS_H

#include "6507.h"

#define CYCLE_START switch (c->cycle_count) {

#define CYCLE_ADD(num, task)                                                   \
	case num:                                                              \
		task break;

#define CYCLE_END }

#define NEXT_CYCLE	  c->cycle_count++;
#define RESET_CYCLE	  c->cycle_count = 0;
#define GOTO_CYCLE(cycle) c->cycle_count = cycle

/* oops cycle */
#define CYCLE_OOPS 0xFF

#define CYCLE_ADDRMODE_IM                                                      \
	default:                                                               \
		addrmode_immediate(c);                                         \
		break;

#define CYCLE_ADDRMODE_REL CYCLE_ADDRMODE_IM

#define CYCLE_ADDRMODE_ZP                                                      \
	default:                                                               \
		addrmode_zero_page(c);                                         \
		break;

#define CYCLE_ADDRMODE_ZPX                                                     \
	default:                                                               \
		addrmode_zero_page_offset(c, c->regs.x);                       \
		break;

#define CYCLE_ADDRMODE_ZPY                                                     \
	default:                                                               \
		addrmode_zero_page_offset(c, c->regs.y);                       \
		break;

#define CYCLE_ADDRMODE_ABS                                                     \
	default:                                                               \
		addrmode_absolute(c);                                          \
		break;

#define CYCLE_ADDRMODE_ABX(force_oops)                                         \
	default:                                                               \
		addrmode_absolute_offset(c, c->regs.x, force_oops);            \
		break;

#define CYCLE_ADDRMODE_ABY(force_oops)                                         \
	default:                                                               \
		addrmode_absolute_offset(c, c->regs.y, force_oops);            \
		break;

#define CYCLE_ADDRMODE_IND                                                     \
	default:                                                               \
		addrmode_indirect(c);                                          \
		break;

#define CYCLE_ADDRMODE_INX                                                     \
	default:                                                               \
		addrmode_indirect_x(c);                                        \
		break;

#define CYCLE_ADDRMODE_INY(force_oops)                                         \
	default:                                                               \
		addrmode_indirect_y(c, force_oops);                            \
		break;

#endif
