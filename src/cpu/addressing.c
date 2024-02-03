#include "addressing.h"
#include "../utils/memory_page.h"
#include "6507.h"
#include "cycle_macros.h"

void
addrmode_immediate(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, {
		c->tmp = bus_read(c->regs.pc, c->bus);
		c->regs.pc++;
	} NEXT_CYCLE)

	CYCLE_END
}

void
addrmode_zero_page(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, c->tmp2 = bus_read(c->regs.pc, c->bus); c->regs.pc++;
		  NEXT_CYCLE)

	CYCLE_ADD(2, c->tmp = bus_read(c->tmp2, c->bus); NEXT_CYCLE)

	CYCLE_END
}

void
addrmode_zero_page_offset(C6507 *c, uint8_t offset)
{
	CYCLE_START

	CYCLE_ADD(1, c->tmp2 = bus_read(c->regs.pc, c->bus); c->regs.pc++;
		  NEXT_CYCLE)

	CYCLE_ADD(2, c->tmp2 += offset; c->tmp2 &= 0xFF; NEXT_CYCLE)

	CYCLE_ADD(3, c->tmp = bus_read(c->tmp2, c->bus); NEXT_CYCLE)

	CYCLE_END
}

void
addrmode_absolute(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, c->tmp2 = bus_read(c->regs.pc, c->bus); c->tmp2 &= 0xFF;
		  c->regs.pc++; NEXT_CYCLE)

	CYCLE_ADD(2, c->tmp2 = (uint16_t)((bus_read(c->regs.pc, c->bus) << 8) |
					  c->tmp2);
		  c->regs.pc++; NEXT_CYCLE)

	CYCLE_ADD(3, c->tmp = bus_read(c->tmp2, c->bus); NEXT_CYCLE)

	CYCLE_END
}

void
addrmode_absolute_offset(C6507 *c, uint8_t offset, uint8_t force_oops)
{
	uint16_t old_page;

	CYCLE_START

	CYCLE_ADD(1, c->tmp2 = bus_read(c->regs.pc, c->bus); c->regs.pc++;
		  NEXT_CYCLE)

	CYCLE_ADD(2, c->tmp2 = (uint16_t)((bus_read(c->regs.pc, c->bus) << 8) |
					  c->tmp2);
		  c->regs.pc++; NEXT_CYCLE)

	CYCLE_ADD(3, old_page = c->tmp2; c->tmp2 += offset;
		  (force_oops || (page(old_page) != page(c->tmp2)))
		      ? GOTO_CYCLE(CYCLE_OOPS)
		      : NEXT_CYCLE;
		  c->tmp = bus_read(c->tmp2, c->bus);)

	CYCLE_ADD(CYCLE_OOPS, GOTO_CYCLE(4);)

	CYCLE_END
}

void
addrmode_indirect(C6507 *c)
{
	CYCLE_START

	/* fetch pointer lo */
	CYCLE_ADD(1, c->tmp2 = bus_read(c->regs.pc, c->bus); c->regs.pc++;
		  NEXT_CYCLE)

	/* fetch pointer hi */
	CYCLE_ADD(2, c->tmp2 |= (uint16_t)((bus_read(c->regs.pc, c->bus) << 8));
		  c->regs.pc++; NEXT_CYCLE)

	/* fetch value lo */
	CYCLE_ADD(3, c->tmp = bus_read(c->tmp2, c->bus); NEXT_CYCLE)

	/* fetch value hi */
	CYCLE_ADD(4, c->tmp |= (bus_read(c->tmp2 + 1, c->bus) << 8); NEXT_CYCLE)

	CYCLE_END
}

void
addrmode_indirect_x(C6507 *c)
{
	CYCLE_START

	/* fetch pointer */
	CYCLE_ADD(1, c->tmp2 = bus_read(c->regs.pc, c->bus); c->regs.pc++;
		  NEXT_CYCLE)

	/* add x to address */
	CYCLE_ADD(2, c->tmp2 += c->regs.x; c->tmp2 &= 0xFF; NEXT_CYCLE)

	/* fetch addr lo */
	CYCLE_ADD(3, c->tmp = bus_read(c->tmp2, c->bus); NEXT_CYCLE)

	/* fetch addr hi */
	CYCLE_ADD(4, c->tmp |= (uint16_t)((bus_read(c->tmp2 + 1, c->bus) << 8));
		  NEXT_CYCLE)

	/* fetch value from address */
	CYCLE_ADD(5, c->tmp = bus_read(c->tmp, c->bus); NEXT_CYCLE)

	CYCLE_END
}

void
addrmode_indirect_y(C6507 *c, uint8_t force_oops)
{
	uint16_t old_page;

	CYCLE_START

	/* fetch pointer */
	CYCLE_ADD(1, c->tmp2 = bus_read(c->regs.pc, c->bus); c->regs.pc++;
		  NEXT_CYCLE)

	/* fetch addr lo */
	CYCLE_ADD(2, c->tmp = bus_read(c->tmp2, c->bus); NEXT_CYCLE)

	/* fetch addr hi */
	CYCLE_ADD(3, c->tmp |= (uint16_t)((bus_read(c->tmp2 + 1, c->bus) << 8));
		  NEXT_CYCLE)

	/* add y to address, deref it and and check page cross */
	CYCLE_ADD(4, old_page = c->tmp; c->tmp += c->regs.y;
		  (force_oops || (page(old_page) != page(c->tmp)))
		      ? GOTO_CYCLE(CYCLE_OOPS)
		      : NEXT_CYCLE;
		  c->tmp = bus_read(c->tmp, c->bus);)

	/* oops cycle on page cross */
	CYCLE_ADD(CYCLE_OOPS, GOTO_CYCLE(5);)

	CYCLE_END
}
