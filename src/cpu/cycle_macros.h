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

#define CYCLE_ADDRMODE_IM CYCLE_ADD(1, addrmode_immediate(c);)

#define CYCLE_ADDRMODE_REL CYCLE_ADDRMODE_IM

#define CYCLE_ADDRMODE_ZP                                                      \
	CYCLE_ADD(1, addrmode_zero_page(c);)                                   \
	CYCLE_ADD(2, addrmode_zero_page(c);)

#define CYCLE_ADDRMODE_ZPX                                                     \
	CYCLE_ADD(1, addrmode_zero_page_offset(c, 0);)                         \
	CYCLE_ADD(2, addrmode_zero_page_offset(c, c->regs.x);)                 \
	CYCLE_ADD(3, addrmode_zero_page_offset(c, 0);)

#define CYCLE_ADDRMODE_ZPY                                                     \
	CYCLE_ADD(1, addrmode_zero_page_offset(c, 0);)                         \
	CYCLE_ADD(2, addrmode_zero_page_offset(c, c->regs.y);)                 \
	CYCLE_ADD(3, addrmode_zero_page_offset(c, 0);)

#define CYCLE_ADDRMODE_ABS                                                     \
	CYCLE_ADD(1, addrmode_absolute(c);)                                    \
	CYCLE_ADD(2, addrmode_absolute(c);)                                    \
	CYCLE_ADD(3, addrmode_absolute(c);)

#define CYCLE_ADDRMODE_ABX(force_oops)                                         \
	CYCLE_ADD(1, addrmode_absolute_offset(c, 0, 0);)                       \
	CYCLE_ADD(2, addrmode_absolute_offset(c, 0, 0);)                       \
	CYCLE_ADD(3, addrmode_absolute_offset(c, c->regs.x, force_oops);)      \
	CYCLE_ADD(CYCLE_OOPS, addrmode_absolute_offset(c, 0, 0);)

#define CYCLE_ADDRMODE_ABY(force_oops)                                         \
	CYCLE_ADD(1, addrmode_absolute_offset(c, 0, 0);)                       \
	CYCLE_ADD(2, addrmode_absolute_offset(c, 0, 0);)                       \
	CYCLE_ADD(3, addrmode_absolute_offset(c, c->regs.y, force_oops);)      \
	CYCLE_ADD(CYCLE_OOPS, addrmode_absolute_offset(c, 0, 0);)

#define CYCLE_ADDRMODE_IND                                                     \
	CYCLE_ADD(1, addrmode_indirect(c);)                                    \
	CYCLE_ADD(2, addrmode_indirect(c);)                                    \
	CYCLE_ADD(3, addrmode_indirect(c);)                                    \
	CYCLE_ADD(4, addrmode_indirect(c);)

#define CYCLE_ADDRMODE_INX                                                     \
	CYCLE_ADD(1, addrmode_indirect_x(c);)                                  \
	CYCLE_ADD(2, addrmode_indirect_x(c);)                                  \
	CYCLE_ADD(3, addrmode_indirect_x(c);)                                  \
	CYCLE_ADD(4, addrmode_indirect_x(c);)                                  \
	CYCLE_ADD(5, addrmode_indirect_x(c);)

#define CYCLE_ADDRMODE_INY(force_oops)                                         \
	CYCLE_ADD(1, addrmode_indirect_y(c, 0);)                               \
	CYCLE_ADD(2, addrmode_indirect_y(c, 0);)                               \
	CYCLE_ADD(3, addrmode_indirect_y(c, 0);)                               \
	CYCLE_ADD(4, addrmode_indirect_y(c, force_oops);)                      \
	CYCLE_ADD(CYCLE_OOPS, addrmode_indirect_y(c, 0);)

#endif
