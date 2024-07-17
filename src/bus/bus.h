#ifndef ATARI_BUS_H
#define ATARI_BUS_H

#include <stdint.h>

/* Data Bus */
typedef struct {
	uint8_t dummy_riot[0x20];
	uint8_t dummy_tia[0x40];
	uint8_t ram[0x80];
	uint8_t rom[0x1000];
} Bus;

/* write val to addr */
void bus_write(uint16_t addr, uint8_t val, Bus *b);

/* read a byte from addr */
uint8_t bus_read(uint16_t addr, const Bus *b);

#endif
