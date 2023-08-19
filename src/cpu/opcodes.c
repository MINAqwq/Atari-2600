#include "opcodes.h"
#include "addressing.h"
#include "cycle_macros.h"
#include "instructions.h"

void
OP_06(C6507 *c)
{
	CYCLE_START(c)

	CYCLE_ADD(1, c->tmp2 = addrmode_immediate(c); NEXT_CYCLE(c))
	CYCLE_ADD(2, c->tmp = addrmode_zero_page(c->tmp2, c); NEXT_CYCLE(c))
	CYCLE_ADD(3, inst_asl(c); NEXT_CYCLE(c))
	CYCLE_ADD(4, bus_write(c->tmp2, c->tmp, c->bus); RESET_CYCLE(c))

	CYCLE_END
}

void
OP_0A(C6507 *c)
{
	CYCLE_START(c)

	CYCLE_ADD(1, addrmode_immediate(c);)
	CYCLE_ADD(2, ADDR_ACCUM(inst_asl, c) RESET_CYCLE(c))

	CYCLE_END
}

void
OP_29(C6507 *c)
{
	CYCLE_START(c)

	CYCLE_ADD(1, c->tmp = addrmode_immediate(c); NEXT_CYCLE(c))
	CYCLE_ADD(2, inst_and(c); RESET_CYCLE(c))

	CYCLE_END
}

void
OP_65(C6507 *c)
{
	CYCLE_START(c)

	CYCLE_ADD(1, c->tmp = addrmode_immediate(c); NEXT_CYCLE(c))
	CYCLE_ADD(2, c->tmp = addrmode_zero_page(c->tmp, c); NEXT_CYCLE(c))
	CYCLE_ADD(3, c->regs.p.decimal_mode ? inst_adc_bcd(c) : inst_adc(c);
	          RESET_CYCLE(c))

	CYCLE_END
}

op_ptr
get_opcode(uint8_t op)
{
	if (op == 0x29)
		return &OP_29;

	if (op == 0x65)
		return &OP_65;

	return NULL;
}