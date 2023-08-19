#include "6507.h"
#include "../utils/debug.h"
#include "addressing.h"
#include "cycle_macros.h"
#include "opcodes.h"

#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>

/* https://pagetable.com/?p=410 */
void
c6507_reset(C6507 *c)
{
	/* TODO: Refactor with cycle macros */

	/* reset sequence (7 cycles) */
	// switch (c->cycle_count) {
	// case 0:
	c->regs.ir = 0;
	// return;
	// case 1:
	c->regs.s = 0xFF;
	// return;
	// case 2: /* FALLTHROUG */
	// case 3: /* FALLTHROUG */
	// case 4:
	c->regs.s--;
	c->regs.s--;
	c->regs.s--;
	// return;
	// case 5:
	// c->regs.pc &= bus_read(0xFFFC, c->bus);
	// 	return;
	// case 6:
	// c->regs.pc |= (bus_read(0xFFFD, c->bus) << 8);
	// 	return;
	// default:
	// TODO: Error
	// return;
	// }
}

void
c6507_clock(C6507 *c)
{
	op_ptr op;

	/* first cycle is always instruction fetching */
	if (c->cycle_count == 0) {
		c->regs.ir = addrmode_immediate(c);
		debug_log("ir = %02X", c->regs.ir);
		NEXT_CYCLE(c)
		return;
	}

	/* get current instruction */
	op = get_opcode(c->regs.ir);
	if (!op) {
		debug_log("op_ptr is null");
		/* TODO: error and exit */
		return;
	}

	/* execute instruction */
	debug_log("Execute #%d from $%02X", c->cycle_count, c->regs.ir);
	op(c);
}

void
c6507_exec(C6507 *c)
{
}

void
c6507_push(uint8_t val, C6507 *c)
{
	bus_write(c->regs.s + C6507_STACK_BASE, val, c->bus);
	c->regs.s--;
}

uint8_t
c6507_pop(C6507 *c)
{
	uint8_t tmp;

	tmp = bus_read(c->regs.s + C6507_STACK_BASE, c->bus);
	c->regs.s++;

	return tmp;
}