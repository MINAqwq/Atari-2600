#ifndef ATARI_CPU_INSTRUCTION_H
#define ATARI_CPU_INSTRUCTION_H

#include "6507.h"

#include <stdint.h>

/* 6507 Instruction */
typedef struct {
	char	name[7]; /* for disassembly */
	uint8_t opcode;
	/* opcode function returns 1 if oops cycle is needed */
	void (*fptr)(C6507 *c);
} Instruction;

/* add with carry */
void inst_adc(C6507 *c);

/* add with carry (binary-coded decimal addition) */
void inst_adc_bcd(C6507 *c);

/* bitwise and */
void inst_and(C6507 *c);

/* arithmetic shift left */
void inst_asl(C6507 *c);

/* branch carry clear */
void inst_bcc(C6507 *c);

/* branch carry set */
void inst_bcs(C6507 *c);

/* branch equal */
void inst_beq(C6507 *c);

/* bit test */
void inst_bit(C6507 *c);

/* branch minus */
void inst_bmi(C6507 *c);

/* branch not equal */
void inst_bne(C6507 *c);

/* branch plus */
void inst_bpl(C6507 *c);

/* break (interrupt/syscall) */
void inst_brk(C6507 *c);

/* branch overflow clear */
void inst_bvc(C6507 *c);

/* branch overflow set */
void inst_bvs(C6507 *c);

/* clear carry */
void inst_clc(C6507 *c);

/* clear decimal */
void inst_cld(C6507 *c);

/* clear interrupts disabled */
void inst_cli(C6507 *c);

/* clear overflow */
void inst_clv(C6507 *c);

/* compare */
void inst_cmp(C6507 *c);

/* compare x register */
void inst_cpx(C6507 *c);

/* compare y register */
void inst_cpy(C6507 *c);

/* decrement memory */
void inst_dec(C6507 *c);

/* decrement x register */
void inst_dex(C6507 *c);

/* decrement y register */
void inst_dey(C6507 *c);

/* exclusive or */
void inst_eor(C6507 *c);

/* increment memory */
void inst_inc(C6507 *c);

/* increment x register */
void inst_inx(C6507 *c);

/* increment y register */
void inst_iny(C6507 *c);

/* jump */
void inst_jmp(C6507 *c);

/* jump subroutine */
void inst_jsr(C6507 *c);

/* load accumulator */
void inst_lda(C6507 *c);

/* load x register */
void inst_ldx(C6507 *c);

/* load y register */
void inst_ldy(C6507 *c);

/* logical shift right  */
void inst_lsr(C6507 *c);

/* no operation */
void inst_nop(C6507 *c);

/* logical inclusive or */
void inst_ora(C6507 *c);

/* push accumulator */
void inst_pha(C6507 *c);

/* push processor status */
void inst_php(C6507 *c);

/* pull accumulator */
void inst_pla(C6507 *c);

/* pull processor status */
void inst_plp(C6507 *c);

/* rotate left */
void inst_rol(C6507 *c);

/* rotate right */
void inst_ror(C6507 *c);

/* return interrupt */
void inst_rti(C6507 *c);

/* return subroutine */
void inst_rts(C6507 *c);

/* subtract with carry */
void inst_sbc(C6507 *c);

/* subtract with carry (binary-coded decimal addition) */
void inst_sbc_bdc(C6507 *c);

/* set carry flag */
void inst_sec(C6507 *c);

/* set decimal flag */
void inst_sed(C6507 *c);

/* set interrupt disable */
void inst_sei(C6507 *c);

/* store accumulator */
void inst_sta(C6507 *c);

/* store x register */
void inst_stx(C6507 *c);

/* store y register */
void inst_sty(C6507 *c);

/* transfer accumulator to x */
void inst_tax(C6507 *c);

/* transfer accumulator to y */
void inst_tay(C6507 *c);

/* transfer sp to x */
void inst_tsx(C6507 *c);

/* transfer x to accumulator */
void inst_txa(C6507 *c);

/* transfer x to sp */
void inst_txs(C6507 *c);

/* transfer y to accumulator */
void inst_tya(C6507 *c);

#endif
