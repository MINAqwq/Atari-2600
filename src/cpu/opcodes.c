#include "opcodes.h"
#include "../utils/debug.h"
#include "6507.h"
#include "addressing.h"
#include "cycle_macros.h"
#include "instructions.h"

#include <stdlib.h>

void
OP_00(C6507 *c)
{
	inst_brk(c);
	debug_print_cpu_status(c);
	exit(1);
}

void
OP_06(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_asl(c); NEXT_CYCLE)
	CYCLE_ADD(4, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_0A(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IM

	CYCLE_ADD(2, ADDR_ACCUM(inst_asl, c); RESET_CYCLE)

	CYCLE_END
}

void
OP_29(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IM

	CYCLE_ADD(2, inst_and(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_65(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, c->regs.p.decimal_mode ? inst_adc_bcd(c) : inst_adc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_69(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IM

	CYCLE_ADD(2, c->regs.p.decimal_mode ? inst_adc_bcd(c) : inst_adc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_85(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_sta(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_A0(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IM

	CYCLE_ADD(2, inst_ldy(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_A1(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INX

	CYCLE_ADD(6, inst_lda(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_A6(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_ldx(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_A2(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IM

	CYCLE_ADD(2, inst_ldx(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_A4(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_ldy(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_A5(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_lda(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_A9(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IM

	CYCLE_ADD(2, inst_lda(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_AC(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_ldy(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_AD(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_lda(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_AE(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_ldx(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_B1(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INY(0)

	CYCLE_ADD(5, inst_lda(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_B4(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_ldy(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_B5(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_lda(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_B6(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_ldx(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_B9(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABY(0)

	CYCLE_ADD(4, inst_lda(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_BC(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(0)

	CYCLE_ADD(4, inst_ldy(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_BD(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(0)

	CYCLE_ADD(4, inst_lda(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_BE(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABY(0)

	CYCLE_ADD(4, inst_ldx(c); RESET_CYCLE)

	CYCLE_END
}

op_ptr
get_opcode(uint8_t op)
{
	switch (op) {
	case 0x00:
		return &OP_00;
	case 0x06:
		return &OP_06;
	case 0x0A:
		return &OP_0A;
	case 0x29:
		return &OP_29;
	case 0x65:
		return &OP_65;
	case 0x85:
		return &OP_85;
	case 0xA0:
		return &OP_A0;
	case 0xA1:
		return &OP_A1;
	case 0xA2:
		return &OP_A2;
	case 0xA4:
		return &OP_A4;
	case 0xA5:
		return &OP_A5;
	case 0xA6:
		return &OP_A6;
	case 0xA9:
		return &OP_A9;
	case 0xAC:
		return &OP_AC;
	case 0xAD:
		return &OP_AD;
	case 0xAE:
		return &OP_AE;
	case 0xB1:
		return &OP_B1;
	case 0xB4:
		return &OP_B4;
	case 0xB5:
		return &OP_B5;
	case 0xB6:
		return &OP_B6;
	case 0xB9:
		return &OP_B9;
	case 0xBC:
		return &OP_BC;
	case 0xBD:
		return &OP_BD;
	case 0xBE:
		return &OP_BE;
	}
	return NULL;
}
