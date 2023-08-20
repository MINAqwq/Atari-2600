#ifndef ATARI_CPU_ADDRESSING_H
#define ATARI_CPU_ADDRESSING_H

#include "6507.h"
#include <bits/stdint-uintn.h>

#define ADDR_ACCUM(inst, c)                                                    \
	c->addr_accumulator = 1;                                               \
	inst(c);                                                               \
	c->addr_accumulator = 0;

/* https://www.nesdev.org/obelisk-6502-guide/addressing.html */

/*
 * Every function is exactly 1 cycle
 */

/* returns (pc + 1) */
uint8_t addrmode_immediate(C6507 *c);

/* returns [[pc + 1 + i]]*/
uint8_t addrmode_zero_page(uint8_t i, C6507 *c);

/* returns [pc + 1] interpreted as signed byte */
#define addrmode_relative(c) (int8_t) addrmode_immediate(c);

/* returns [pc + 1] the low byte for absolute */
#define addmode_absolut_pre(c) addrmode_immediate(c);

/* returns ((pc + 1) << 8 | pre) !! -> NEEDS A CALL TO ABSOLUT PRE BEFORE
 */
uint16_t addrmode_absolute(uint8_t pre, C6507 *c);

#endif
