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
OP_01(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INX

	CYCLE_ADD(6, inst_ora(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_05(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_ora(c); RESET_CYCLE)

	CYCLE_END
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
OP_08(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)

	CYCLE_ADD(2, inst_php(c); NEXT_CYCLE)

	CYCLE_ADD(3, c->regs.s--; RESET_CYCLE)

	CYCLE_END
}

void
OP_09(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IM

	CYCLE_ADD(2, inst_ora(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_0A(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)

	CYCLE_ADD(2, ADDR_ACCUM(inst_asl, c); RESET_CYCLE)

	CYCLE_END
}

void
OP_0D(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_ora(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_11(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INY(0)

	CYCLE_ADD(5, inst_ora(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_15(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_ora(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_19(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABY(0)

	CYCLE_ADD(4, inst_ora(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_1D(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(0)

	CYCLE_ADD(4, inst_ora(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_21(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INX

	CYCLE_ADD(6, inst_and(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_24(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_bit(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_25(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_and(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_28(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)

	CYCLE_ADD(2, c->regs.s++; NEXT_CYCLE)

	CYCLE_ADD(3, inst_plp(c); NEXT_CYCLE)

	CYCLE_ADD(4, TO_U8(c->regs.p) = c->value; RESET_CYCLE)

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
OP_2C(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_bit(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_2D(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_and(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_31(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INY(0)

	CYCLE_ADD(5, inst_and(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_35(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_and(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_39(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABY(0)

	CYCLE_ADD(4, inst_and(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_3D(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(0)

	CYCLE_ADD(4, inst_and(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_41(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INX

	CYCLE_ADD(6, inst_eor(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_45(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_eor(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_48(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)

	CYCLE_ADD(2, inst_pha(c); NEXT_CYCLE)

	CYCLE_ADD(3, c->regs.s--; RESET_CYCLE)

	CYCLE_END
}

void
OP_49(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IM

	CYCLE_ADD(2, inst_eor(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_4D(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_eor(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_51(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INY(0)

	CYCLE_ADD(5, inst_eor(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_55(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_eor(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_59(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABY(0)

	CYCLE_ADD(4, inst_eor(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_5D(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(0)

	CYCLE_ADD(4, inst_eor(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_61(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INX

	CYCLE_ADD(6, c->regs.p.decimal_mode ? inst_adc_bcd(c) : inst_adc(c);
		  RESET_CYCLE)

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
OP_68(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)

	CYCLE_ADD(4, c->regs.s++; NEXT_CYCLE)

	CYCLE_ADD(2, inst_pla(c); NEXT_CYCLE)

	CYCLE_ADD(3, c->regs.a = c->value; RESET_CYCLE)

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
OP_6D(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, c->regs.p.decimal_mode ? inst_adc_bcd(c) : inst_adc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_71(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INY(0)

	CYCLE_ADD(5, c->regs.p.decimal_mode ? inst_adc_bcd(c) : inst_adc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_75(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, c->regs.p.decimal_mode ? inst_adc_bcd(c) : inst_adc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_79(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABY(0)

	CYCLE_ADD(4, c->regs.p.decimal_mode ? inst_adc_bcd(c) : inst_adc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_7D(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(0)

	CYCLE_ADD(4, c->regs.p.decimal_mode ? inst_adc_bcd(c) : inst_adc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_81(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INX

	CYCLE_ADD(6, inst_sta(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_84(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_sty(c); RESET_CYCLE)

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
OP_86(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_stx(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_8A(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)

	CYCLE_ADD(2, inst_txa(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_8C(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_sty(c); RESET_CYCLE)

	CYCLE_END
}

void
OD_8D(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_sta(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_8E(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_stx(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_91(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INY(1)

	CYCLE_ADD(5, inst_sta(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_94(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_sty(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_95(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_sta(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_96(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPY

	CYCLE_ADD(4, inst_stx(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_98(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)

	CYCLE_ADD(2, inst_tya(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_9D(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(1)

	CYCLE_ADD(4, inst_sta(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_99(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABY(1)

	CYCLE_ADD(4, inst_sta(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_9A(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)

	CYCLE_ADD(2, inst_txs(c); RESET_CYCLE)

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
OP_A6(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_ldx(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_A8(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)

	CYCLE_ADD(2, inst_tay(c); RESET_CYCLE)

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
OP_AA(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)

	CYCLE_ADD(2, inst_tax(c); RESET_CYCLE)

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
OP_BA(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)

	CYCLE_ADD(2, inst_tsx(c); RESET_CYCLE)

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

void
OP_C1(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INX

	CYCLE_ADD(6, inst_cmp(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_C5(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_cmp(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_C9(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IM

	CYCLE_ADD(2, inst_cmp(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_CD(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_cmp(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_D1(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INY(0)

	CYCLE_ADD(5, inst_cmp(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_D5(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_cmp(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_D9(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABY(0)

	CYCLE_ADD(4, inst_cmp(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_DD(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(0)

	CYCLE_ADD(4, inst_cmp(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_E1(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INX

	CYCLE_ADD(6, c->regs.p.decimal_mode ? inst_sbc_bcd(c) : inst_sbc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_E5(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, c->regs.p.decimal_mode ? inst_sbc_bcd(c) : inst_sbc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_E9(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IM

	CYCLE_ADD(2, c->regs.p.decimal_mode ? inst_sbc_bcd(c) : inst_sbc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_ED(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, c->regs.p.decimal_mode ? inst_sbc_bcd(c) : inst_sbc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_F1(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_INY(0)

	CYCLE_ADD(5, c->regs.p.decimal_mode ? inst_sbc_bcd(c) : inst_sbc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_F5(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, c->regs.p.decimal_mode ? inst_sbc_bcd(c) : inst_sbc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_F9(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABY(0)

	CYCLE_ADD(4, c->regs.p.decimal_mode ? inst_sbc_bcd(c) : inst_sbc(c);
		  RESET_CYCLE)

	CYCLE_END
}

void
OP_FD(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(0)

	CYCLE_ADD(4, c->regs.p.decimal_mode ? inst_sbc_bcd(c) : inst_sbc(c);
		  RESET_CYCLE)

	CYCLE_END
}

op_ptr
get_opcode(uint8_t op)
{
	switch (op) {
	case 0x00:
		return &OP_00;
	case 0x01:
		return &OP_01;
	case 0x05:
		return &OP_05;
	case 0x06:
		return &OP_06;
	case 0x08:
		return &OP_08;
	case 0x09:
		return &OP_09;
	case 0x0A:
		return &OP_0A;
	case 0x0D:
		return &OP_0D;
	case 0x11:
		return &OP_11;
	case 0x15:
		return &OP_15;
	case 0x19:
		return &OP_19;
	case 0x1D:
		return &OP_1D;
	case 0x21:
		return &OP_21;
	case 0x24:
		return &OP_24;
	case 0x25:
		return &OP_25;
	case 0x28:
		return &OP_28;
	case 0x29:
		return &OP_29;
	case 0x2C:
		return &OP_2C;
	case 0x2D:
		return &OP_2D;
	case 0x31:
		return &OP_31;
	case 0x35:
		return &OP_35;
	case 0x39:
		return &OP_39;
	case 0x3D:
		return &OP_3D;
	case 0x41:
		return &OP_41;
	case 0x45:
		return &OP_45;
	case 0x48:
		return &OP_48;
	case 0x49:
		return &OP_49;
	case 0x4D:
		return &OP_4D;
	case 0x51:
		return &OP_51;
	case 0x55:
		return &OP_55;
	case 0x59:
		return &OP_59;
	case 0x5D:
		return &OP_5D;
	case 0x61:
		return &OP_61;
	case 0x65:
		return &OP_65;
	case 0x68:
		return &OP_68;
	case 0x69:
		return &OP_69;
	case 0x6D:
		return &OP_6D;
	case 0x71:
		return &OP_71;
	case 0x75:
		return &OP_75;
	case 0x79:
		return &OP_79;
	case 0x7D:
		return &OP_7D;
	case 0x81:
		return &OP_81;
	case 0x84:
		return &OP_84;
	case 0x85:
		return &OP_85;
	case 0x86:
		return &OP_86;
	case 0x8A:
		return &OP_8A;
	case 0x8C:
		return &OP_8C;
	case 0x8E:
		return &OP_8E;
	case 0x91:
		return &OP_91;
	case 0x94:
		return &OP_94;
	case 0x95:
		return &OP_95;
	case 0x96:
		return &OP_96;
	case 0x98:
		return &OP_98;
	case 0x99:
		return &OP_99;
	case 0x9A:
		return &OP_9A;
	case 0x9D:
		return &OP_9D;
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
	case 0xA8:
		return &OP_A8;
	case 0xA9:
		return &OP_A9;
	case 0xAA:
		return &OP_AA;
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
	case 0xBA:
		return &OP_BA;
	case 0xBC:
		return &OP_BC;
	case 0xBD:
		return &OP_BD;
	case 0xBE:
		return &OP_BE;
	case 0xC1:
		return &OP_C1;
	case 0xC5:
		return &OP_C5;
	case 0xC9:
		return &OP_C9;
	case 0xCD:
		return &OP_CD;
	case 0xD1:
		return &OP_D1;
	case 0xD5:
		return &OP_D5;
	case 0xD9:
		return &OP_D9;
	case 0xDD:
		return &OP_DD;
	case 0xE1:
		return &OP_E1;
	case 0xE5:
		return &OP_E5;
	case 0xE9:
		return &OP_E9;
	case 0xED:
		return &OP_ED;
	case 0xF1:
		return &OP_F1;
	case 0xF5:
		return &OP_F5;
	case 0xF9:
		return &OP_F9;
	case 0xFD:
		return &OP_FD;
	}
	return NULL;
}
