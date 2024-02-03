#include "bus/bus.h"
#include "cpu/6507.h"
#include "utils/debug.h"

/* fake rom:
 * LDA #5
 * STA $81
 * ADC $81
 */
static uint8_t rom[] = {0xA9, 0x05, 0x85, 0x81, 0x65, 0x81};

int
main()
{
	Bus   bus;
	C6507 cpu;

	c6507_init(&bus, &cpu);

	cpu.regs.a = 0x00;
	cpu.regs.pc = 0x1000;
	cpu.cycle_count = 0;

	/* load fake rom */
	bus.memory_map.rom = &rom[0];

	c6507_clock(&cpu);

	c6507_clock(&cpu);

	c6507_clock(&cpu);

	c6507_clock(&cpu);

	c6507_clock(&cpu);
	c6507_clock(&cpu);

	c6507_clock(&cpu);

	c6507_clock(&cpu);

	c6507_clock(&cpu);
	c6507_clock(&cpu);

	c6507_clock(&cpu);

	debug_print_cpu_status(&cpu);

	return 0;
}
