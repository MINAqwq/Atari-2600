#ifndef ATARI_CPU_ADDRESSING_H
#define ATARI_CPU_ADDRESSING_H

#include "6507.h"

#define ADDR_ACCUM(inst, c)                                                    \
	c->addr_accumulator = 1;                                               \
	inst(c);                                                               \
	c->addr_accumulator = 0

/* https://www.nesdev.org/obelisk-6502-guide/addressing.html */

/* [1 cycle] takes the byte at pc and loads it into the temp register (pc gets
 * incremented)
 */
void addrmode_immediate(C6507 *c);

#define addrmode_relative(c) addrmode_immediate(c);

/* [2 cycles] takes the next byte at pc and uses it to read from the zero page
 */
void addrmode_zero_page(C6507 *c);

/* [3 cycles] zero page read with offset to the addr */
void addrmode_zero_page_offset(C6507 *c, uint8_t offset);

/* [3 Cycles] takes the next two bytes and makes a 16bit address out of them to
 * read a byte from that address */
void addrmode_absolute(C6507 *c);

/* [4 Cycles +] absolute with offset */
void addrmode_absolute_offset(C6507 *c, uint8_t offset, uint8_t force_oops);

/* [ 4 Cycles ] takes a word from an absolute address */
void addrmode_indirect(C6507 *c);

/* [5 Cycles] fetch a 16bit address from (zp + x) and read whats at the fetched
 * address */
void addrmode_indirect_x(C6507 *c);

/* [4 Cycles +] fetch a 16bit address from zp and read from (address + y) */
void addrmode_indirect_y(C6507 *c, uint8_t force_oops);

#endif
