#include "6507.h"
#include "../utils/debug.h"
#include "addressing.h"
#include "cycle_macros.h"
#include "opcodes.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* https://pagetable.com/?p=410 */
void
c6507_reset(C6507 *c)
{
	/* TODO: Refactor with cycle macros */

	c->regs.ir = 0;

	c->regs.s = 0xFF;

	c->regs.s--;
	c->regs.s--;
	c->regs.s--;
}

void
c6507_clock(C6507 *c)
{
	op_ptr op;

	/* first cycle is always instruction fetching */
	if (c->cycle_count == 0) {
		c->regs.ir = bus_read(c->regs.pc, c->bus);
		c->regs.pc++;
		debug_log("ir = %02X", c->regs.ir);
		NEXT_CYCLE
		return;
	}

	/* get current instruction */
	op = get_opcode(c->regs.ir);
	if (!op) {
		debug_log(
		    "%02X not implemented! holy jesus wtf are you doing??\n",
		    c->regs.ir);
		exit(1);
		return;
	}

	/* execute instruction */
	debug_log("Execute #%d from $%02X", c->cycle_count, c->regs.ir);
	op(c);
}

void
c6507_exec(C6507 *c)
{
	/* sanity check (could be removed if cpu emulation works fine) */
	if (c->cycle_count != 0) {
		debug_log("exec starts not at cycle 0\n");
		exit(2);
	}

	/* fetch instruction */
	c6507_clock(c);

	/* execute instruction */
	while (c->cycle_count != 0) {
		c6507_clock(c);
	}
}

void
c6507_push(uint8_t val, C6507 *c)
{
	/* stack grows downwards */
	c->regs.s--;
	bus_write(c->regs.s + C6507_STACK_BASE, val, c->bus);
}

uint8_t
c6507_pop(C6507 *c)
{
	uint8_t val;

	val = bus_read(c->regs.s + C6507_STACK_BASE, c->bus);
	c->regs.s++;
	return val;
}
