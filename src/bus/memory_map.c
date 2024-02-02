#include "memory_map.h"
#include "bus.h"

#include <stddef.h>

uint8_t *
memory_map_get(uint16_t addr, MemoryMap *mm)
{

	/* TIA Registers */
	if (addr < 0x80)
		return mm->tia;

	/* RAM */
	if (addr < 0x100)
		return mm->ram + addr - 0x80;

	/* RIOT */
	if (addr < 0x300)
		return mm->riot + addr - 0x280;

	/* nothing */
	if (addr < 0x1000)
		return NULL;

	/* ROM */
	return mm->rom + addr - 0x1000;
}
