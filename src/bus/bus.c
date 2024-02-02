#include "bus.h"
#include "../utils/debug.h"
#include "memory_map.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* print error message and terminate process */
void __attribute__((__noreturn__)) access_violation(unsigned int addr)
{
	fprintf(stderr, "access violation on addr $%02x\n", addr);
	exit(1);
}

void
bus_connect_rom(uint8_t *rom, Bus *b)
{
	debug_log("ROM: loading from %p", rom);
	b->memory_map.rom = rom;
}

void
bus_write(uint16_t addr, uint8_t val, Bus *b)
{
	uint8_t *ptr;

	debug_log("MEM: write #%d to $%04x", val, addr);

	if (addr > MAX_ADDR)
		access_violation(addr);

	ptr = memory_map_get(addr, &b->memory_map);
	if (!ptr)
		access_violation(addr);

	*ptr = val;
}

uint8_t
bus_read(uint16_t addr, Bus *b)
{
	const uint8_t *ptr;

	debug_log("MEM: read from %04x", addr);

	if (addr > MAX_ADDR)
		access_violation(addr);

	ptr = memory_map_get(addr, &b->memory_map);
	if (!ptr)
		access_violation(addr);

	return *ptr;
}
