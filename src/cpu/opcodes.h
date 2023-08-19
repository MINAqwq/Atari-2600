/* complete opcode table */

#ifndef ATARI_CPU_OPCODES
#define ATARI_CPU_OPCODES

#include "6507.h"

typedef void (*op_ptr)(C6507 *c);

/* zp asl */
void OP_06(C6507 *c);

/* accumulator asl */
void OP_0A(C6507 *c);

/* immediate and */
void OP_29(C6507 *c);

/* zp adc */
void OP_65(C6507 *c);

/* get opcode by its value */
op_ptr get_opcode(uint8_t op);

#endif
