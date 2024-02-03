#include "bus.h"
#include "../utils/debug.h"
#include "memory_map.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* print error message and terminate process */
void __attribute__((__noreturn__)) access_violation(unsigned int addr)
{
	fprintf(stderr, "access violation on addr $%04X\n", addr);
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

	if (addr > MAX_ADDR)
		access_violation(addr);

	ptr = memory_map_get(addr, &b->memory_map);
	if (!ptr)
		access_violation(addr);

	debug_log("MEM: write 0x%02X to $%04X", val, addr);

	*ptr = val;
}

uint8_t
bus_read(uint16_t addr, Bus *b)
{
	const uint8_t *ptr;

	if (addr > MAX_ADDR)
		access_violation(addr);

	ptr = memory_map_get(addr, &b->memory_map);
	if (!ptr)
		access_violation(addr);

	debug_log("MEM: read 0x%02X from $%04X", *ptr, addr);

	return *ptr;
}
