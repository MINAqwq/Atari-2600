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

/* ldy imc */
void OP_A0(C6507 *c);

/* lda in,x */
void OP_A1(C6507 *c);

/* ldx im */
void OP_A2(C6507 *c);

/* ldy zp */
void OP_A4(C6507 *c);

/* lda zp */
void OP_A5(C6507 *c);

/* ldx zp */
void OP_A6(C6507 *c);

/* lda im */
void OP_A9(C6507 *c);

/* ldy abs */
void OP_AC(C6507 *c);

/* lda abs */
void OP_AD(C6507 *c);

/* ldx abs */
void OP_AE(C6507 *c);

/* lda in,y */
void OP_B1(C6507 *c);

/* ldy zp,x */
void OP_B4(C6507 *c);

/* lda zp,x */
void OP_B5(C6507 *c);

/* ldx zp,y */
void OP_B6(C6507 *c);

/* lda abs,y */
void OP_B9(C6507 *c);

/* ldy abs,x */
void OP_BC(C6507 *c);

/* lda abs,x */
void OP_BD(C6507 *c);

/* ldx abs,y */
void OP_BE(C6507 *c);

/* get opcode by its value */
op_ptr get_opcode(uint8_t op);

#endif
