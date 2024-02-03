#include "bus/bus.h"
#include "cpu/6507.h"
#include "utils/debug.h"

/* fake rom:
 * LDA #0x90
 * STA $80
 * LDA #00
 * STA $81
 *
 * LDA #0xFE
 * LDY #02
 * STA ($80),y
 * LDX $92
 */
static uint8_t rom[] = {0xA9, 0x90, 0x85, 0x80, 0xA9, 0x00, 0x85, 0x81, 0xA9,
			0xFE, 0xA0, 0x02, 0x91, 0x80, 0xA6, 0x92, 0x00};

int
main()
{
	Bus   bus;
	C6507 cpu;

	c6507_init(&bus, &cpu);

	cpu.regs.a = 0x00;
	cpu.regs.pc = 0x1000;
	cpu.cycle_count = 0;

	bus.memory_map.riot = NULL;
	bus.memory_map.tia = NULL;

	/* load fake rom */
	bus.memory_map.rom = &rom[0];

	while (1) {
		c6507_clock(&cpu);
	}

	return 0;
}
