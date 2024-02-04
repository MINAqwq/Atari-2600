#include "bus/bus.h"
#include "cpu/6507.h"
#include "utils/debug.h"

/* fake rom:
 * ; Load 0x0090 to address 0x80
 * LDA #0x90	; load 0x90 into A
 * STA $80	; store A (0x90) to address 0x80
 * LDA #00	; load 0x00 into A
 * STA $81	; store A (0x00) to address 0x01
 *
 * ; Load 0xFE from address 0x92 after we stored it there
 * LDA #0xFE	; load 0xFE into A
 * LDY #02	; load 0x02 into Y
 * STA ($80),y	; read address 0x90 from addr 0x80 and add Y (0x02) to it
 * LDX $92	; read from address 0x92
 * PHA		; push A onto the stack
 * PLP		; pull whats on the stack an write it to P
 * AND #0xF0	; Bitwise and content in A with 0xF0 as mask
 */
static uint8_t rom[] = {0xA9, 0x90, 0x85, 0x80, 0xA9, 0x00, 0x85,
			0x81, 0xA9, 0xFE, 0xA0, 0x02, 0x91, 0x80,
			0xA6, 0x92, 0x48, 0x28, 0x29, 0xF0, 0x00};

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

	return 0;
}
