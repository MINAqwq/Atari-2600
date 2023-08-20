#include "addressing.h"

uint8_t
addrmode_immediate(C6507 *c)
{
	uint8_t val;

	val = bus_read(c->regs.pc, c->bus);
	c->regs.pc++;
	return val;
}

uint8_t
addrmode_zero_page(uint8_t addr, C6507 *c)
{
	return bus_read(addr, c->bus);
}

uint16_t
addrmode_absolute(uint8_t pre, C6507 *c)
{
	uint8_t b;

	b = bus_read(c->regs.pc, c->bus);
	c->regs.pc++;
	return (uint8_t)((b << 8) | pre);
}
