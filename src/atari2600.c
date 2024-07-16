#include "bus/bus.h"
#include "cpu/6507.h"
#include "utils/debug.h"

/* fake rom:
 * .org $1000
 * JSR routine
 * BRK
 *
 * routine:
 * LDA #0xFF
 * ADC #0x02
 * LDA #0x02
 * ADC #0x02
 * RTS
 * LDA #0x55
 * BRK
 */
static uint8_t rom[] = {0x20, 0x04, 0x10, 0x00, 0xA9, 0xFF, 0x69, 0x02,
			0xA9, 0x02, 0x69, 0x02, 0x60, 0xA9, 0x55, 0x00};

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
	memcpy(bus.memory + 0x1000, rom, sizeof(rom));

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

	return 0;
}
