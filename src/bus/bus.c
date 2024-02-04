#include "bus.h"
#include "../utils/debug.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void
bus_connect_rom(uint8_t *rom, Bus *b)
{
	debug_log("ROM: loading from %p (not implemented)", rom);
	exit(1);
}

void
bus_write(uint16_t addr, uint8_t val, Bus *b)
{

	debug_log("MEM: write 0x%02X to $%04X", val, addr);

	b->memory[addr] = val;
}

uint8_t
bus_read(uint16_t addr, const Bus *b)
{
	uint8_t tmp;

	tmp = b->memory[addr];

	debug_log("MEM: read 0x%02X from $%04X", tmp, addr);

	return tmp;
}
