#include "instructions.h"
#include "../utils/debug.h"
#include "6507.h"

void
inst_adc(C6507 *c)
{
	uint16_t buf;

	buf = c->regs.a + c->value + c->regs.p.carry;

	SET_FLAG(buf >> 8, c->regs.p.carry)

	SET_FLAG(!c->regs.a, c->regs.p.zero)

	SET_FLAG(~(c->regs.a ^ (c->value)) & (c->regs.a ^ buf) & 0x80,
		 c->regs.p.overflow)

	SET_FLAG(buf & 0x80, c->regs.p.negative)

	c->regs.a = (uint8_t)buf;
}

void
inst_adc_bcd(C6507 *c)
{
	uint16_t l;
	uint16_t h;

	l = (c->regs.a & 0xF) + (c->value & 0x0F) + c->regs.p.carry;
	h = (c->regs.a & 0xF0) + (c->value & 0xF0);

	SET_FLAG(!((l + h) & 0xFF), c->regs.p.zero)

	if (l > 9) {
		h += 0x10;
		l += 0x06;
	}

	SET_FLAG(h >> 8, c->regs.p.carry)

	SET_FLAG(~(c->regs.a ^ ((uint8_t)c->value)) & (c->regs.a ^ h) & 0x80,
		 c->regs.p.overflow)

	SET_FLAG(h & 0x80, c->regs.p.negative)

	c->regs.a = (uint8_t)l | (uint8_t)h;
}

void
inst_and(C6507 *c)
{
	c->regs.a = c->regs.a & c->value;

	SET_FLAG(!c->regs.a, c->regs.p.zero)

	SET_FLAG(c->regs.a & 0x80, c->regs.p.negative)
}

void
inst_asl(C6507 *c)
{
	uint8_t old;
	uint8_t res;

	if (c->addr_accumulator) {
		old = c->regs.a;
		c->regs.a <<= 1;
		res = c->regs.a;
	} else {
		old = (uint8_t)c->value;
		c->value <<= 1;
		res = (uint8_t)c->value;
	}

	SET_FLAG(old >> 7, c->regs.p.carry)

	SET_FLAG(!c->regs.a, c->regs.p.zero)

	SET_FLAG(res >> 7, c->regs.p.negative)
}

void
inst_bcc(C6507 *c)
{
	/* only branch if carry is clear */
	if (c->regs.p.carry)
		return;

	c->regs.pc += (int8_t)(c->value);
}

void
inst_bcs(C6507 *c)
{
	/* only branch if carry is set */
	if (!c->regs.p.carry)
		return;

	c->regs.pc += (int8_t)(c->value);
}

void
inst_beq(C6507 *c)
{
	/* only brach if zero flag is set */
	if (!c->regs.p.zero)
		return;

	c->regs.pc += (int8_t)(c->value);
}

void
inst_bit(C6507 *c)
{
	uint8_t res;

	res = c->regs.a & (uint8_t)c->value;

	SET_FLAG(!res, c->regs.p.zero)

	SET_FLAG(((uint8_t)c->value) >> 6, c->regs.p.overflow)

	SET_FLAG(((uint8_t)c->value) >> 7, c->regs.p.negative)
}

void
inst_bmi(C6507 *c)
{
	/* only branch if negative is set */
	if (!c->regs.p.negative)
		return;

	c->regs.pc += (int8_t)(c->value);
}

void
inst_bne(C6507 *c)
{
	if (c->regs.p.zero) {
		return;
	}

	c->regs.pc += (int8_t)(c->value);
}

void
inst_bpl(C6507 *c)
{
	if (c->regs.p.negative) {
		return;
	}

	c->regs.pc += (int8_t)(c->value);
}

void
inst_brk(C6507 *c)
{
	debug_log("BRK: logic not implemented yet (sry)");
}

void
inst_bvc(C6507 *c)
{
	if (c->regs.p.overflow) {
		return;
	}

	c->regs.pc += (int8_t)(c->value);
}

void
inst_bvs(C6507 *c)
{
	if (!c->regs.p.overflow) {
		return;
	}

	c->regs.pc += (int8_t)(c->value);
}

void
inst_clc(C6507 *c)
{
	SET_FLAG(0, c->regs.p.carry)
}

void
inst_cld(C6507 *c)
{
	SET_FLAG(0, c->regs.p.decimal_mode)
}

void
inst_cli(C6507 *c)
{
	SET_FLAG(0, c->regs.p.irq_disable)
}

void
inst_clv(C6507 *c)
{
	SET_FLAG(0, c->regs.p.overflow)
}

void
inst_cmp(C6507 *c)
{
	/* should this instruction code cause a bug in this year, my girlfriend
	 * gets 10EUR */

	SET_FLAG(c->regs.a >= (uint8_t)c->value, c->regs.p.carry)

	SET_FLAG(c->regs.a == (uint8_t)c->value, c->regs.p.zero)

	SET_FLAG((c->regs.a - (uint8_t)c->value) >> 7, c->regs.p.negative)
}

void
inst_cpx(C6507 *c)
{
	SET_FLAG(c->regs.x >= (uint8_t)c->value, c->regs.p.carry)

	SET_FLAG(c->regs.x == (uint8_t)c->value, c->regs.p.zero)

	SET_FLAG((c->regs.x - (uint8_t)c->value) >> 7, c->regs.p.negative)
}

void
inst_cpy(C6507 *c)
{
	SET_FLAG(c->regs.y >= (uint8_t)c->value, c->regs.p.carry)

	SET_FLAG(c->regs.y == (uint8_t)c->value, c->regs.p.zero)

	SET_FLAG((c->regs.y - (uint8_t)c->value) >> 7, c->regs.p.negative)
}

void
inst_dec(C6507 *c)
{
	c->value--;

	SET_FLAG(!c->value, c->regs.p.zero)

	SET_FLAG(c->value >> 7, c->regs.p.negative)
}

void
inst_dex(C6507 *c)
{
	c->regs.x--;

	SET_FLAG(!c->regs.x, c->regs.p.zero)

	SET_FLAG(c->regs.x >> 7, c->regs.p.negative)
}

void
inst_dey(C6507 *c)
{
	c->regs.y--;

	SET_FLAG(!c->regs.y, c->regs.p.zero)

	SET_FLAG(c->regs.y >> 7, c->regs.p.negative)
}

void
inst_eor(C6507 *c)
{
	c->regs.a ^= (uint8_t)c->value;

	SET_FLAG(!c->regs.a, c->regs.p.zero)

	SET_FLAG(c->regs.a >> 7, c->regs.p.negative)
}

void
inst_inc(C6507 *c)
{
	c->value++;

	SET_FLAG(!c->value, c->regs.p.zero)

	SET_FLAG(c->value >> 7, c->regs.p.negative)
}

void
inst_inx(C6507 *c)
{
	c->regs.x++;

	SET_FLAG(!c->regs.x, c->regs.p.zero)

	SET_FLAG(c->regs.x >> 7, c->regs.p.negative)
}

void
inst_iny(C6507 *c)
{
	c->regs.y++;

	SET_FLAG(!c->regs.y, c->regs.p.zero)

	SET_FLAG(c->regs.y >> 7, c->regs.p.negative)
}

void
inst_jmp(C6507 *c)
{
	c->regs.pc = c->value;
}

void
inst_jsr(C6507 *c)
{
	c->regs.pc--;

	/* push return addr */
	c6507_push(c->regs.pc >> 8, c);
	c6507_push(c->regs.pc, c);

	/* jump to given addr */
	c->regs.pc = c->value;
}

void
inst_lda(C6507 *c)
{
	c->regs.a = (uint8_t)c->value;

	SET_FLAG(!c->regs.a, c->regs.p.zero)

	SET_FLAG(c->regs.a >> 7, c->regs.p.negative)
}

void
inst_ldx(C6507 *c)
{
	c->regs.x = (uint8_t)c->value;

	SET_FLAG(!c->regs.x, c->regs.p.zero)

	SET_FLAG(c->regs.x >> 7, c->regs.p.negative)
}

void
inst_ldy(C6507 *c)
{
	c->regs.y = (uint8_t)c->value;

	SET_FLAG(!c->regs.y, c->regs.p.zero)

	SET_FLAG(c->regs.y >> 7, c->regs.p.negative)
}

void
inst_lsr(C6507 *c)
{
	if (c->addr_accumulator) {
		SET_FLAG(c->regs.a & 1, c->regs.p.carry)

		c->regs.a >>= 1;

		SET_FLAG(!c->regs.a, c->regs.p.zero)
		return;
	}
	SET_FLAG((uint8_t)c->value & 1, c->regs.p.carry)

	c->value &= 0xFF;
	c->value >>= 1;

	SET_FLAG((uint8_t)c->value, c->regs.p.zero)
}

void
inst_nop(C6507 *c)
{
	(void)c;
	return;
}

void
inst_ora(C6507 *c)
{
	c->regs.a |= c->value;

	SET_FLAG(!c->regs.a, c->regs.p.zero)

	SET_FLAG(c->regs.a >> 7, c->regs.p.negative)
}

void
inst_pha(C6507 *c)
{
	c6507_push(c->regs.a, c);
}

void
inst_php(C6507 *c)
{
	c6507_push(TO_U8(c->regs.p), c);
}

void
inst_pla(C6507 *c)
{
	c->value = c6507_pop(c);

	SET_FLAG(!c->value, c->regs.p.zero)
	SET_FLAG(c->value >> 7, c->regs.p.negative)
}

void
inst_plp(C6507 *c)
{
	c->value = c6507_pop(c);
}

void
inst_rol(C6507 *c)
{
	uint8_t carry_buf;

	if (c->addr_accumulator) {
		carry_buf = c->regs.p.carry;

		SET_FLAG(c->regs.a >> 7, c->regs.p.carry)

		c->regs.a <<= 1;
		c->regs.a |= carry_buf;

		SET_FLAG(!c->regs.a, c->regs.p.zero)

		SET_FLAG(c->regs.a >> 7, c->regs.p.negative)
		return;
	}

	carry_buf = c->regs.p.carry;

	SET_FLAG(c->value >> 7, c->regs.p.carry)

	c->value <<= 1;
	c->value |= carry_buf << 7;

	SET_FLAG(!c->value, c->regs.p.zero)

	SET_FLAG(c->value >> 7, c->regs.p.negative)
}

void
inst_ror(C6507 *c)
{
	uint8_t carry_buf;

	if (c->addr_accumulator) {
		carry_buf = c->regs.p.carry;

		SET_FLAG(c->regs.a & 1, c->regs.p.carry)

		c->regs.a >>= 1;
		c->regs.a |= (carry_buf << 7);

		SET_FLAG(!c->regs.a, c->regs.p.zero)

		SET_FLAG(c->regs.a >> 7, c->regs.p.negative)
		return;
	}

	carry_buf = c->regs.p.carry;

	SET_FLAG(c->value & 1, c->regs.p.carry)

	c->value >>= 1;
	c->value |= (carry_buf << 7);

	SET_FLAG(!c->value, c->regs.p.zero)

	SET_FLAG(c->value >> 7, c->regs.p.negative)
}

void
inst_rti(C6507 *c)
{
	c->regs.pc = c->addr;

	SET_FLAG(c->value >> 0 & 1, c->regs.p.carry)
	SET_FLAG(c->value >> 1 & 1, c->regs.p.zero)
	SET_FLAG(c->value >> 2 & 1, c->regs.p.irq_disable)
	SET_FLAG(c->value >> 3 & 1, c->regs.p.decimal_mode)
	SET_FLAG(c->value >> 6 & 1, c->regs.p.overflow)
	SET_FLAG(c->value >> 7 & 1, c->regs.p.negative)
}

void
inst_rts(C6507 *c)
{
	c->regs.pc = c->value;
}

void
inst_sbc(C6507 *c)
{
	uint16_t buf;

	buf = c->regs.a - (c->value + !c->regs.p.carry);

	SET_FLAG((uint8_t)(buf >> 8), c->regs.p.carry)

	SET_FLAG(!c->regs.a, c->regs.p.zero)

	SET_FLAG((c->regs.a ^ (c->value)) & (c->regs.a ^ buf) & 0x80,
		 c->regs.p.overflow)

	SET_FLAG(buf & 0x80, c->regs.p.negative)

	c->regs.a = (uint8_t)buf;
}

void
inst_sbc_bcd(C6507 *c)
{
	uint16_t l;
	uint16_t h;

	l = (c->regs.a & 0xF) - (c->value & 0x0F) - c->regs.p.carry;
	h = (c->regs.a & 0xF0) - (c->value & 0xF0);

	if (l & 0x10) {
		h -= 0x01;
		l -= 0x06;
	}

	uint16_t res = l + h;

	SET_FLAG(!(res << 8), c->regs.p.zero)

	SET_FLAG(!(res >> 8), c->regs.p.carry)

	SET_FLAG((c->regs.a ^ res) & (c->regs.a ^ res) & 0x80,
		 c->regs.p.overflow)

	SET_FLAG(h & 0x80, c->regs.p.negative)

	if (h & 0x100)
		h -= 0x60;

	c->regs.a = (uint8_t)l | (uint8_t)h;
}

void
inst_sec(C6507 *c)
{
	SET_FLAG(1, c->regs.p.carry)
}

void
inst_sed(C6507 *c)
{
	SET_FLAG(1, c->regs.p.decimal_mode)
}

void
inst_sei(C6507 *c)
{
	SET_FLAG(1, c->regs.p.irq_disable)
}

void
inst_sta(C6507 *c)
{
	bus_write(c->addr, c->regs.a, c->bus);
}

void
inst_stx(C6507 *c)
{
	bus_write(c->addr, c->regs.x, c->bus);
}

void
inst_sty(C6507 *c)
{
	bus_write(c->addr, c->regs.y, c->bus);
}

void
inst_tax(C6507 *c)
{
	c->regs.x = c->regs.a;

	SET_FLAG(!c->regs.x, c->regs.p.zero)

	SET_FLAG(c->regs.x & 0x80, c->regs.p.negative)
}

void
inst_tay(C6507 *c)
{
	c->regs.y = c->regs.a;

	SET_FLAG(!c->regs.y, c->regs.p.zero)

	SET_FLAG(c->regs.y & 0x80, c->regs.p.negative)
}

void
inst_tsx(C6507 *c)
{
	c->regs.x = c->regs.s;

	SET_FLAG(!c->regs.x, c->regs.p.zero)

	SET_FLAG(c->regs.x & 0x80, c->regs.p.negative)
}

void
inst_txa(C6507 *c)
{
	c->regs.a = c->regs.x;

	SET_FLAG(!c->regs.a, c->regs.p.zero)

	SET_FLAG(c->regs.a & 0x80, c->regs.p.negative)
}

void
inst_txs(C6507 *c)
{
	c->regs.s = c->regs.x;
}

void
inst_tya(C6507 *c)
{
	c->regs.a = c->regs.y;

	SET_FLAG(!c->regs.a, c->regs.p.zero)

	SET_FLAG(c->regs.a & 0x80, c->regs.p.negative)
}
