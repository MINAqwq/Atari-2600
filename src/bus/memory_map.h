#ifndef ATARI_MEMORY_MAP_H
#define ATARI_MEMORY_MAP_H

#include <stdint.h>

/* memory map containing mapped memory locations */
typedef struct {
	uint8_t *tia;     /*  128 Byte TIA */
	uint8_t ram[128]; /*  128 Byte RAM */
	uint8_t *riot;    /*  128 Byte RIOT */
	uint8_t *rom;     /* 4096 Byte ROM */
} MemoryMap;

/* returns a pointer to addr or NULL on access violation */
uint8_t *memory_map_get(uint16_t addr, MemoryMap *mm);

#endif