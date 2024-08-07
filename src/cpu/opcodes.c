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
	CYCLE_ADD(4, NEXT_CYCLE)
	CYCLE_ADD(5, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

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
OP_10(C6507 *c)
{
	CYCLE_BRANCH(inst_bpl, c)
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
OP_0E(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_asl(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE)
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

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
OP_16(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_asl(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE)
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_18(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, inst_clc(c); NEXT_CYCLE)
	CYCLE_ADD(2, RESET_CYCLE)

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
OP_1E(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(1)

	CYCLE_ADD(4, inst_asl(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE)
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_20(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	/* jsr pushes the current pc - 1 to onto the stack before jumping */
	CYCLE_ADD(4, c6507_push((--c->regs.pc) >> 8, c); NEXT_CYCLE)
	CYCLE_ADD(5, c6507_push(c->regs.pc, c); NEXT_CYCLE)
	CYCLE_ADD(6, inst_jmp(c); RESET_CYCLE)

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
OP_26(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_rol(c); NEXT_CYCLE)
	CYCLE_ADD(4, NEXT_CYCLE)
	CYCLE_ADD(5, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

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
OP_2A(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, ADDR_ACCUM(inst_rol, c); NEXT_CYCLE)
	CYCLE_ADD(2, RESET_CYCLE)

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
OP_2E(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_rol(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE)
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_30(C6507 *c)
{
	CYCLE_BRANCH(inst_bmi, c)
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
OP_36(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_rol(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE)
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_38(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, inst_sec(c); NEXT_CYCLE)
	CYCLE_ADD(2, RESET_CYCLE)

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
OP_3E(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(1)

	CYCLE_ADD(4, inst_rol(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE)
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

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
OP_46(C6507 *c)
{

	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_lsr(c); NEXT_CYCLE)
	CYCLE_ADD(4, NEXT_CYCLE)
	CYCLE_ADD(5, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

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
OP_4A(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)
	CYCLE_ADD(2, ADDR_ACCUM(inst_lsr, c); RESET_CYCLE)

	CYCLE_END
}

void
OP_4C(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(3, inst_jmp(c); RESET_CYCLE)

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
OP_4E(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_lsr(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE)
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_50(C6507 *c)
{
	CYCLE_BRANCH(inst_bvc, c)
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
OP_56(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_lsr(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE)
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_58(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, inst_cli(c); NEXT_CYCLE)
	CYCLE_ADD(2, RESET_CYCLE)

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
OP_5E(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(1)

	CYCLE_ADD(4, inst_lsr(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE)
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_60(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, c->addr = c6507_pop(c); NEXT_CYCLE)
	CYCLE_ADD(2, NEXT_CYCLE)
	CYCLE_ADD(3, c->addr |= ((c6507_pop(c) << 8) & 0xFF00); NEXT_CYCLE)
	CYCLE_ADD(4, NEXT_CYCLE)
	CYCLE_ADD(5, c->addr++; NEXT_CYCLE)
	CYCLE_ADD(6, inst_rts(c); RESET_CYCLE)

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
OP_66(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_ror(c); NEXT_CYCLE)
	CYCLE_ADD(4, NEXT_CYCLE)
	CYCLE_ADD(5, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

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
OP_6A(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, ADDR_ACCUM(inst_ror, c); NEXT_CYCLE)
	CYCLE_ADD(2, RESET_CYCLE)

	CYCLE_END
}

void
OP_6C(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IND

	CYCLE_ADD(5, inst_jmp(c); RESET_CYCLE)

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
OP_6E(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_ror(c); NEXT_CYCLE);
	CYCLE_ADD(5, NEXT_CYCLE)
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_70(C6507 *c)
{
	CYCLE_BRANCH(inst_bvs, c)
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
OP_76(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_ror(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE)
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_78(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, inst_sei(c); NEXT_CYCLE)
	CYCLE_ADD(2, RESET_CYCLE)

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
OP_7E(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(1)

	CYCLE_ADD(4, inst_ror(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE)
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

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
OP_88(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)
	CYCLE_ADD(2, inst_dey(c); RESET_CYCLE)

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
OP_8D(C6507 *c)
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
OP_90(C6507 *c)
{
	CYCLE_BRANCH(inst_bcc, c)
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
OP_B0(C6507 *c)
{
	CYCLE_BRANCH(inst_bcs, c)
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
OP_B8(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, inst_clv(c); NEXT_CYCLE)
	CYCLE_ADD(2, RESET_CYCLE)

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
OP_C0(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IM

	CYCLE_ADD(2, inst_cpy(c); RESET_CYCLE)

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
OP_C4(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_cpy(c); RESET_CYCLE)

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
OP_C6(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_dec(c); NEXT_CYCLE)
	CYCLE_ADD(4, NEXT_CYCLE) /* TODO: why does dec take 2 more cycle? */
	CYCLE_ADD(5, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_C8(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)
	CYCLE_ADD(2, inst_iny(c); RESET_CYCLE)

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
OP_CA(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)
	CYCLE_ADD(2, inst_dex(c); RESET_CYCLE)

	CYCLE_END
}

void
OP_CC(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_cpy(c); RESET_CYCLE)

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
OP_CE(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_dec(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE) /* TODO: why does dec take 2 more cycle? */
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_D0(C6507 *c)
{
	CYCLE_BRANCH(inst_bne, c)
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
OP_D6(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_dec(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE) /* TODO: why does dec take 2 more cycle? */
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_D8(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, inst_cld(c); NEXT_CYCLE)
	CYCLE_ADD(2, RESET_CYCLE)

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
OP_DE(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(1)

	CYCLE_ADD(4, inst_dec(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE) /* TODO: why does dec take 2 more cycle? */
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_E0(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_IM

	CYCLE_ADD(2, inst_cpx(c); RESET_CYCLE)

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
OP_E4(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_cpx(c); RESET_CYCLE)

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
OP_E6(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZP

	CYCLE_ADD(3, inst_inc(c); NEXT_CYCLE)
	CYCLE_ADD(4, NEXT_CYCLE) /* TODO: why does inc take 2 more cycle? */
	CYCLE_ADD(5, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_E8(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE)
	CYCLE_ADD(2, inst_inx(c); RESET_CYCLE)

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
OP_EA(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, NEXT_CYCLE);
	CYCLE_ADD(2, RESET_CYCLE);

	CYCLE_END
}

void
OP_EC(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_cpx(c); RESET_CYCLE)

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
OP_EE(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABS

	CYCLE_ADD(4, inst_inc(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE) /* TODO: why does inc take 2 more cycle? */
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_F0(C6507 *c)
{
	CYCLE_BRANCH(inst_beq, c)
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
OP_F6(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ZPX

	CYCLE_ADD(4, inst_inc(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE) /* TODO: why does inc take 2 more cycle? */
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

	CYCLE_END
}

void
OP_F8(C6507 *c)
{
	CYCLE_START

	CYCLE_ADD(1, inst_sed(c); NEXT_CYCLE)
	CYCLE_ADD(2, RESET_CYCLE)

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

void
OP_FE(C6507 *c)
{
	CYCLE_START

	CYCLE_ADDRMODE_ABX(1)

	CYCLE_ADD(4, inst_inc(c); NEXT_CYCLE)
	CYCLE_ADD(5, NEXT_CYCLE) /* TODO: why does inc take 2 more cycle? */
	CYCLE_ADD(6, bus_write(c->addr, c->value, c->bus); RESET_CYCLE)

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
	case 0x0E:
		return &OP_0E;
	case 0x10:
		return &OP_10;
	case 0x11:
		return &OP_11;
	case 0x15:
		return &OP_15;
	case 0x16:
		return &OP_16;
	case 0x18:
		return &OP_18;
	case 0x19:
		return &OP_19;
	case 0x20:
		return &OP_20;
	case 0x1D:
		return &OP_1D;
	case 0x1E:
		return &OP_1E;
	case 0x21:
		return &OP_21;
	case 0x24:
		return &OP_24;
	case 0x25:
		return &OP_25;
	case 0x26:
		return &OP_26;
	case 0x28:
		return &OP_28;
	case 0x29:
		return &OP_29;
	case 0x2A:
		return &OP_2A;
	case 0x2C:
		return &OP_2C;
	case 0x2D:
		return &OP_2D;
	case 0x2E:
		return &OP_2E;
	case 0x30:
		return &OP_30;
	case 0x31:
		return &OP_31;
	case 0x35:
		return &OP_35;
	case 0x36:
		return &OP_36;
	case 0x38:
		return &OP_38;
	case 0x39:
		return &OP_39;
	case 0x3D:
		return &OP_3D;
	case 0x3E:
		return &OP_3E;
	case 0x41:
		return &OP_41;
	case 0x45:
		return &OP_45;
	case 0x46:
		return &OP_46;
	case 0x48:
		return &OP_48;
	case 0x49:
		return &OP_49;
	case 0x4A:
		return &OP_4A;
	case 0x4C:
		return &OP_4C;
	case 0x4D:
		return &OP_4D;
	case 0x4E:
		return &OP_4E;
	case 0x50:
		return &OP_50;
	case 0x51:
		return &OP_51;
	case 0x55:
		return &OP_55;
	case 0x56:
		return &OP_56;
	case 0x58:
		return &OP_58;
	case 0x59:
		return &OP_59;
	case 0x5D:
		return &OP_5D;
	case 0x5E:
		return &OP_5E;
	case 0x60:
		return &OP_60;
	case 0x61:
		return &OP_61;
	case 0x65:
		return &OP_65;
	case 0x66:
		return &OP_66;
	case 0x68:
		return &OP_68;
	case 0x69:
		return &OP_69;
	case 0x6A:
		return &OP_6A;
	case 0x6C:
		return &OP_6C;
	case 0x6D:
		return &OP_6D;
	case 0x6E:
		return &OP_6E;
	case 0x70:
		return &OP_70;
	case 0x71:
		return &OP_71;
	case 0x75:
		return &OP_75;
	case 0x76:
		return &OP_76;
	case 0x78:
		return &OP_78;
	case 0x79:
		return &OP_79;
	case 0x7D:
		return &OP_7D;
	case 0x7E:
		return &OP_7E;
	case 0x81:
		return &OP_81;
	case 0x84:
		return &OP_84;
	case 0x85:
		return &OP_85;
	case 0x86:
		return &OP_86;
	case 0x88:
		return &OP_88;
	case 0x8A:
		return &OP_8A;
	case 0x8C:
		return &OP_8C;
	case 0x8D:
		return &OP_8D;
	case 0x8E:
		return &OP_8E;
	case 0x90:
		return &OP_90;
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
	case 0xB0:
		return &OP_B0;
	case 0xB1:
		return &OP_B1;
	case 0xB4:
		return &OP_B4;
	case 0xB5:
		return &OP_B5;
	case 0xB6:
		return &OP_B6;
	case 0xB8:
		return &OP_B8;
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
	case 0xC0:
		return &OP_C0;
	case 0xC1:
		return &OP_C1;
	case 0xC4:
		return &OP_C4;
	case 0xC5:
		return &OP_C5;
	case 0xC6:
		return &OP_C6;
	case 0xC8:
		return &OP_C8;
	case 0xC9:
		return &OP_C9;
	case 0xCA:
		return &OP_CA;
	case 0xCC:
		return &OP_CC;
	case 0xCD:
		return &OP_CD;
	case 0xCE:
		return &OP_CE;
	case 0xD0:
		return &OP_D0;
	case 0xD1:
		return &OP_D1;
	case 0xD5:
		return &OP_D5;
	case 0xD6:
		return &OP_D6;
	case 0xD8:
		return &OP_D8;
	case 0xD9:
		return &OP_D9;
	case 0xDD:
		return &OP_DD;
	case 0xDE:
		return &OP_DE;
	case 0xE0:
		return &OP_E0;
	case 0xE1:
		return &OP_E1;
	case 0xE4:
		return &OP_E4;
	case 0xE5:
		return &OP_E5;
	case 0xE6:
		return &OP_E6;
	case 0xE8:
		return &OP_E8;
	case 0xE9:
		return &OP_E9;
	case 0xEA:
		return &OP_EA;
	case 0xEC:
		return &OP_EC;
	case 0xED:
		return &OP_ED;
	case 0xEE:
		return &OP_EE;
	case 0xF0:
		return &OP_F0;
	case 0xF1:
		return &OP_F1;
	case 0xF5:
		return &OP_F5;
	case 0xF6:
		return &OP_F6;
	case 0xF8:
		return &OP_F8;
	case 0xF9:
		return &OP_F9;
	case 0xFD:
		return &OP_FD;
	case 0xFE:
		return &OP_FE;
	}
	return NULL;
}
