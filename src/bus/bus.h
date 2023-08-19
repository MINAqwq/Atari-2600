#ifndef ATARI_BUS_H
#define ATARI_BUS_H

#include "memory_map.h"

#include <stdint.h>

static const uint16_t MAX_ADDR = (1 << 13);

/* Data Bus */
typedef struct {
	MemoryMap memory_map;
} Bus;

/* connect the rom to the bus */
void bus_connect_rom(uint8_t *rom, Bus *b);

/* write val to addr */
void bus_write(uint16_t addr, uint8_t val, Bus *b);

/* read a byte from addr */
uint8_t bus_read(uint16_t addr, Bus *b);

#endif
