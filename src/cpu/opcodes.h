/* complete opcode table */

#ifndef ATARI_CPU_OPCODES
#define ATARI_CPU_OPCODES

#include "6507.h"

typedef void (*op_ptr)(C6507 *c);

/* asl zp */
void OP_06(C6507 *c);

/* asl a */
void OP_0A(C6507 *c);

/* and im */
void OP_29(C6507 *c);

/* adc zp */
void OP_65(C6507 *c);

/* sta zp */
void OP_85(C6507 *c);

/* lda in,x */
void OP_A1(C6507 *c);

/* lda zp */
void OP_A5(C6507 *c);

/* lda im */
void OP_A9(C6507 *c);

/* lda abs */
void OP_AD(C6507 *c);

/* lda in,y */
void OP_B1(C6507 *c);

/* lda zp,x */
void OP_B5(C6507 *c);

/* lda abs,y */
void OP_B9(C6507 *c);

/* lda abs,x */
void OP_BD(C6507 *c);

/* get opcode by its value */
op_ptr get_opcode(uint8_t op);

#endif
