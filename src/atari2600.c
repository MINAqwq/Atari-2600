#include "bus/bus.h"
#include "cpu/6507.h"

#include <stdio.h>
#include <stdlib.h>

int8_t
load_rom(char *path, Bus *bus)
{
	FILE *fp;

	fp = fopen(path, "rb");
	if (!fp) {
		return 1;
	}

	fread(bus->rom, 1, 0x1000, fp);

	fclose(fp);
	return 0;
}

int
main(int argc, char **argv)
{
	Bus  *bus;
	C6507 cpu;

	if (argc != 2) {
		fprintf(stderr, "%s [ROM.a26]\n", argv[0]);
		return 1;
	}

	bus = malloc(sizeof(*bus));

	if (load_rom(argv[1], bus)) {
		free(bus);
		return 1;
	}

	c6507_init(bus, &cpu);

	cpu.regs.a = 0x00;
	cpu.regs.pc = 0x1000;
	cpu.cycle_count = 0;

	while (1) {
		c6507_exec(&cpu);
	}

	/* Output after BRK should be
	------ CPU Status ------
	A:      05
	X:      00
	Y:      00
	SP:     FC
	CF:     0
	ZF:     0
	ID:     1
	DM:     1
	VF:     1
	NF:     1
	PC:     1004
	*/

	free(bus);

	return 0;
}
