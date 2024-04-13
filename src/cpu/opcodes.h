/* complete opcode table */

#ifndef ATARI_CPU_OPCODES
#define ATARI_CPU_OPCODES

#include "6507.h"

typedef void (*op_ptr)(C6507 *c);

/* brk */
void OP_00(C6507 *c);

/* in,x */
void OP_01(C6507 *c);

/* ora zp */
void OP_05(C6507 *c);

/* asl zp */
void OP_06(C6507 *c);

/* php */
void OP_08(C6507 *c);

/* ora im */
void OP_09(C6507 *c);

/* asl a */
void OP_0A(C6507 *c);

/* ora abs */
void OP_0D(C6507 *c);

/* ora in,y*/
void OP_11(C6507 *c);

/* ora zp,x */
void OP_15(C6507 *c);

/* ora abs,y */
void OP_19(C6507 *c);

/* ora abs,x */
void OP_1D(C6507 *c);

/* and in,x */
void OP_21(C6507 *c);

/* bit zp */
void OP_24(C6507 *c);

/* and zp */
void OP_25(C6507 *c);

/* plp */
void OP_28(C6507 *c);

/* and im */
void OP_29(C6507 *c);

/* bit abs */
void OP_2C(C6507 *c);

/* and abs */
void OP_2D(C6507 *c);

/* and iny */
void OP_31(C6507 *c);

/* and zp,x */
void OP_35(C6507 *c);

/* and abs,y */
void OP_39(C6507 *c);

/* and abs,x */
void OP_3D(C6507 *c);

/* eor in,x */
void OP_41(C6507 *c);

/* eor zp */
void OP_45(C6507 *c);

/* pha */
void OP_48(C6507 *c);

/* eor im */
void OP_49(C6507 *c);

/* eor abs */
void OP_4D(C6507 *c);

/* eor in,y */
void OP_51(C6507 *c);

/* eor zp,x */
void OP_55(C6507 *c);

/* eor abs,y */
void OP_59(C6507 *c);

/* eor abs,x */
void OP_5D(C6507 *c);

/* adc in,x */
void OP_61(C6507 *c);

/* adc zp */
void OP_65(C6507 *c);

/* pla */
void OP_68(C6507 *c);

/* adc im */
void OP_69(C6507 *c);

/* adc abs */
void OP_6D(C6507 *c);

/* adc in,y */
void OP_71(C6507 *c);

/* adc zp,x */
void OP_75(C6507 *c);

/* adc abs,y */
void OP_79(C6507 *c);

/* adc abs,x */
void OP_7D(C6507 *c);

/* sta in,x */
void OP_81(C6507 *c);

/* sty zp */
void OP_84(C6507 *c);

/* sta zp */
void OP_85(C6507 *c);

/* stx zp */
void OP_86(C6507 *c);

/* dey im */
void OP_88(C6507 *c);

/* txa */
void OP_8A(C6507 *c);

/* sty abs */
void OP_8C(C6507 *c);

/* sta abs */
void OD_8D(C6507 *c);

/* stx abs */
void OP_8E(C6507 *c);

/* sta in,y */
void OP_91(C6507 *c);

/* sty zp,x */
void OP_94(C6507 *c);

/* sta zp,x */
void OP_95(C6507 *c);

/* stx zp,y */
void OP_96(C6507 *c);

/* tya */
void OP_98(C6507 *c);

/* sta abs,y */
void OP_99(C6507 *c);

/* txs */
void OP_9A(C6507 *c);

/* sta abs,x */
void OP_9D(C6507 *c);

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

/* tay */
void OP_A8(C6507 *c);

/* lda im */
void OP_A9(C6507 *c);

/* tax */
void OP_AA(C6507 *c);

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

/* tsx */
void OP_BA(C6507 *c);

/* ldy abs,x */
void OP_BC(C6507 *c);

/* lda abs,x */
void OP_BD(C6507 *c);

/* ldx abs,y */
void OP_BE(C6507 *c);

/* cpy im */
void OP_C0(C6507 *c);

/* cmp in,x */
void OP_C1(C6507 *c);

/* cpy im */
void OP_C4(C6507 *c);

/* cmp zp */
void OP_C5(C6507 *c);

/* dec zp */
void OP_C6(C6507 *c);

/* iny im */
void OP_C8(C6507 *c);

/* cmp im */
void OP_C9(C6507 *c);

/* dex im */
void OP_CA(C6507 *c);

/* cpy abs */
void OP_CC(C6507 *c);

/* cmp abs */
void OP_CD(C6507 *c);

/* dec abs */
void OP_CE(C6507 *c);

/* cmp in,y */
void OP_D1(C6507 *c);

/* cmp zp,x */
void OP_D5(C6507 *c);

/* dec zp,x */
void OP_D6(C6507 *c);

/* cmp abs,y */
void OP_D9(C6507 *c);

/* cmp abs,x */
void OP_DD(C6507 *c);

/* dec abs,x */
void OP_DE(C6507 *c);

/* cpx im */
void OP_E0(C6507 *c);

/* sbc in,x */
void OP_E1(C6507 *c);

/* cpx zp */
void OP_E4(C6507 *c);

/* sbc zp */
void OP_E5(C6507 *c);

/* inc zp */
void OP_E6(C6507 *c);

/* inx im */
void OP_E8(C6507 *c);

/* sbc im */
void OP_E9(C6507 *c);

/* cpx zp */
void OP_EC(C6507 *c);

/* sbc abs */
void OP_ED(C6507 *c);

/* inc abs */
void OP_EE(C6507 *c);

/* sbc in,y */
void OP_F1(C6507 *c);

/* sbc zp,x */
void OP_F5(C6507 *c);

/* inc zp,x */
void OP_F6(C6507 *c);

/* sbc abs,y */
void OP_F9(C6507 *c);

/* sbc abs,x */
void OP_FD(C6507 *c);

/* inc abs,x */
void OP_FE(C6507 *c);

/* get opcode by its value */
op_ptr get_opcode(uint8_t op);

#endif
