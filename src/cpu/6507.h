#ifndef ATARI_CPU_6507
#define ATARI_CPU_6507

#include "../bus/bus.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* macros for cool stuff */
#define DBIT(x)	    uint8_t x : 1
#define NDBIT(x, n) size_t x : n
#define TO_U8(x)    *(uint8_t *)&x

#define SET_FLAG(condition, flag) flag = (condition & 0x1);

#define CYCLE_TIME 1.19

/* constants */
static const uint16_t C6507_STACK_BASE = 0x100;

/* 6057 Register */
typedef struct {
	uint8_t a;  /* Accumulator  */
	uint8_t x;  /* Index Register */
	uint8_t y;  /* Index Register */
	uint8_t s;  /* Stack Pointer */
	uint8_t ir; /* instruction register */

	/* Status Register */
	struct __attribute__((packed)) {
		DBIT(carry); /* TODO: comment */
		DBIT(zero);
		DBIT(irq_disable);
		DBIT(decimal_mode);
		DBIT(pad0);
		DBIT(pad1);
		DBIT(overflow);
		DBIT(negative);
	} p;

	uint16_t pc; /* Programm Counter*/
} C6507_Register;

/* MOS 6057 Emulation */
typedef struct {
	C6507_Register regs;
	Bus	      *bus;
	uint8_t	       cycle_count;
	uint8_t	       addr_accumulator;
	uint16_t       tmp;
	uint16_t       tmp2;
} C6507;

/* reset the cpu.
 * this loads 0xFC into S and (read($FFFC) | (read($FFFD) << 8)) into the PC
 */
void c6507_reset(C6507 *c);

/* clock the cpu and execute a cycle (blocks until cycle is finished) */
void c6507_clock(C6507 *c);

/* execute the part of an instruction based on the cycle count */
void c6507_exec(C6507 *c);

/* helper function for pushing a byte onto the stack */
void c6507_push(uint8_t val, C6507 *c);

/* helper function for pop a byte onto the stack */
uint8_t c6507_pop(C6507 *c);

/* read the byte at pc, load it in tmp and increment pc */
void c6507_read_next_byte(C6507 *c);

/* init */
static void
c6507_init(Bus *b, C6507 *c)
{
	c->addr_accumulator = 0;

	/* connect to bus */
	c->bus = b;

	/* reset */
	c6507_reset(c);
}

#endif
