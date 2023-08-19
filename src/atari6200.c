#include "bus/bus.h"
#include "cpu/6507.h"
#include "utils/debug.h"

int
main()
{
	Bus bus;
	C6507 cpu;

	c6507_init(&bus, &cpu);

	/* fake rom */
	bus_write(0x05, 0x03, &bus);
	bus_write(0x06, 0x05, &bus);
	bus_write(0x80, 0x65, &bus);
	bus_write(0x81, 0x06, &bus);

	cpu.regs.a = 5;
	cpu.regs.pc = 0x80;
	cpu.cycle_count = 0;

	c6507_clock(&cpu);

	c6507_clock(&cpu);
	c6507_clock(&cpu);
	c6507_clock(&cpu);

	debug_print_cpu_status(&cpu);

	return bus_read(0x5, &bus);
}