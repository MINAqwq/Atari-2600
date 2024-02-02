#include "bus/bus.h"
#include "cpu/6507.h"
#include "utils/debug.h"

/* fake rom:
 * LDX #00
 * LDY #55
 *
 * LDA #05
 * STA $10
 *
 * loop:
 * STY $11,X
 * INX
 * CPX $10
 * BNE loop
 */
static uint8_t rom[] = {0xA2, 0x00, 0xA0, 0x37, 0xA9, 0x05, 0x06, 0x85,
                        0x10, 0x94, 0x11, 0xE8, 0xE4, 0x10, 0xD0, 0xF9};

int
main()
{
	Bus bus;
	C6507 cpu;

	c6507_init(&bus, &cpu);

	cpu.regs.a = 5;
	cpu.regs.pc = 0x1000;
	cpu.cycle_count = 0;

	/* load fake rom */
	bus.memory_map.rom = &rom[0];

	c6507_clock(&cpu);

	c6507_clock(&cpu);
	c6507_clock(&cpu);
	c6507_clock(&cpu);

	debug_print_cpu_status(&cpu);

	return bus_read(0x5, &bus);
}
