/***************************************************************************
                          cpu_funcs.cpp  -  description
                             -------------------
    begin                : ����27 2005
    copyright            : (C) 2005 by vitaly
    email                : vitamin_caig@mail.ru
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 * All code with some changes taken from UnrealSpeccy (C) SMT sources      *
 *                                                                         *
 ***************************************************************************/

#include "configure.h"
#include "cpu.h"

#include "zxlin.h"

extern Zxlin* ZXLin;

CPUFUNC const CPU::pOps[] = {
   _op_00, _op_01, _op_02, _op_03, _op_04, _op_05, _op_06, _op_07,
   _op_08, _op_09, _op_0A, _op_0B, _op_0C, _op_0D, _op_0E, _op_0F,
   _op_10, _op_11, _op_12, _op_13, _op_14, _op_15, _op_16, _op_17,
   _op_18, _op_19, _op_1A, _op_1B, _op_1C, _op_1D, _op_1E, _op_1F,
   _op_20, _op_21, _op_22, _op_23, _op_24, _op_25, _op_26, _op_27,
   _op_28, _op_29, _op_2A, _op_2B, _op_2C, _op_2D, _op_2E, _op_2F,
   _op_30, _op_31, _op_32, _op_33, _op_34, _op_35, _op_36, _op_37,
   _op_38, _op_39, _op_3A, _op_3B, _op_3C, _op_3D, _op_3E, _op_3F,

   _op_00, _op_41, _op_42, _op_43, _op_44, _op_45, _op_46, _op_47,
   _op_48, _op_00, _op_4A, _op_4B, _op_4C, _op_4D, _op_4E, _op_4F,
   _op_50, _op_51, _op_00, _op_53, _op_54, _op_55, _op_56, _op_57,
   _op_58, _op_59, _op_5A, _op_00, _op_5C, _op_5D, _op_5E, _op_5F,
   _op_60, _op_61, _op_62, _op_63, _op_00, _op_65, _op_66, _op_67,
   _op_68, _op_69, _op_6A, _op_6B, _op_6C, _op_00, _op_6E, _op_6F,
   _op_70, _op_71, _op_72, _op_73, _op_74, _op_75, _op_76, _op_77,
   _op_78, _op_79, _op_7A, _op_7B, _op_7C, _op_7D, _op_7E, _op_00,

   _op_80, _op_81, _op_82, _op_83, _op_84, _op_85, _op_86, _op_87,
   _op_88, _op_89, _op_8A, _op_8B, _op_8C, _op_8D, _op_8E, _op_8F,
   _op_90, _op_91, _op_92, _op_93, _op_94, _op_95, _op_96, _op_97,
   _op_98, _op_99, _op_9A, _op_9B, _op_9C, _op_9D, _op_9E, _op_9F,
   _op_A0, _op_A1, _op_A2, _op_A3, _op_A4, _op_A5, _op_A6, _op_A7,
   _op_A8, _op_A9, _op_AA, _op_AB, _op_AC, _op_AD, _op_AE, _op_AF,
   _op_B0, _op_B1, _op_B2, _op_B3, _op_B4, _op_B5, _op_B6, _op_B7,
   _op_B8, _op_B9, _op_BA, _op_BB, _op_BC, _op_BD, _op_BE, _op_BF,

   _op_C0, _op_C1, _op_C2, _op_C3, _op_C4, _op_C5, _op_C6, _op_C7,
   _op_C8, _op_C9, _op_CA, _op_CB, _op_CC, _op_CD, _op_CE, _op_CF,
   _op_D0, _op_D1, _op_D2, _op_D3, _op_D4, _op_D5, _op_D6, _op_D7,
   _op_D8, _op_D9, _op_DA, _op_DB, _op_DC, _op_DD, _op_DE, _op_DF,
   _op_E0, _op_E1, _op_E2, _op_E3, _op_E4, _op_E5, _op_E6, _op_E7,
   _op_E8, _op_E9, _op_EA, _op_EB, _op_EC, _op_ED, _op_EE, _op_EF,
   _op_F0, _op_F1, _op_F2, _op_F3, _op_F4, _op_F5, _op_F6, _op_F7,
   _op_F8, _op_F9, _op_FA, _op_FB, _op_FC, _op_FD, _op_FE, _op_FF,
};

void CPU::_op_00(CPU*)  // nop
{

}

void CPU::_op_01(CPU* cpu)  // ld bc,nnnn
{
   cpu->regB.C = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.B = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 6;
}

void CPU::_op_02(CPU* cpu) // ld (bc),a
{
   cpu->pMemory->write(cpu->regP.BC, cpu->regB.A);
   cpu->ticks += 3;
}


void CPU::_op_03(CPU* cpu) // inc bc
{
   cpu->regP.BC++;
   cpu->ticks += 2;
}

void CPU::_op_04(CPU* cpu) // inc b
{
   cpu->_inc8(cpu->regB.B);
}

void CPU::_op_05(CPU* cpu) // dec b
{
   cpu->_dec8(cpu->regB.B);
}


void CPU::_op_06(CPU* cpu) // ld b,nn
{
   cpu->regB.B = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 3;
}

void CPU::_op_07(CPU* cpu) // rlca
{
   cpu->regB.F = CPU::pRLCAF[cpu->regB.A] | (cpu->regB.F & (SF | ZF | PV));
   cpu->regB.A = CPU::pROLF[cpu->regB.A];
}

void CPU::_op_08(CPU* cpu) // ex af,af'
{
   cpu->regP.AF ^= cpu->AF_;
   cpu->AF_ ^= cpu->regP.AF;
   cpu->regP.AF ^= cpu->AF_;
}

void CPU::_op_09(CPU* cpu) // add hl,bc
{
   WORD tmp = cpu->regP.HL;
   cpu->regB.F = (cpu->regB.F & ~(NF | CF | F5 | F3 | HF));
   cpu->regB.F |= (((cpu->regP.HL & 0x0FFF) + (cpu->regP.BC & 0x0FFF)) >> 8) & 0x10; /* HF */
   cpu->regP.HL += cpu->regP.BC;
   if (cpu->regP.HL < tmp) cpu->regB.F |= CF;
   cpu->regB.F |= (cpu->regB.H & (F5 | F3));
   cpu->ticks += 7;
}

void CPU::_op_0A(CPU* cpu) // ld a,(bc)
{
   cpu->regB.A = cpu->pMemory->read(cpu->regP.BC);
   cpu->ticks += 3;
}

void CPU::_op_0B(CPU* cpu) // dec bc
{
   cpu->regP.BC--;
   cpu->ticks += 2;
}

void CPU::_op_0C(CPU* cpu) // inc c
{
   cpu->_inc8(cpu->regB.C);
}

void CPU::_op_0D(CPU* cpu) // dec c
{
   cpu->_dec8(cpu->regB.C);
}

void CPU::_op_0E(CPU* cpu) // ld c,nn
{
   cpu->regB.C = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 3;
}

void CPU::_op_0F(CPU* cpu) // rrca
{
   cpu->regB.F = pRRCAF[cpu->regB.A] | (cpu->regB.F & (SF | ZF | PV));
   cpu->regB.A = pRORF[cpu->regB.A];
}

void CPU::_op_10(CPU* cpu) // djnz rr
{
char off = (char)cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 4;

   if (--cpu->regB.B)
   {
        cpu->regP.PC += off;
        cpu->ticks += 5;
   }
}

void CPU::_op_11(CPU* cpu) // ld de,nnnn
{
   cpu->regB.E = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.D = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 6;
}

void CPU::_op_12(CPU* cpu) // ld (de),a
{
   cpu->pMemory->write(cpu->regP.DE, cpu->regB.A);
   cpu->ticks += 3;
}

void CPU::_op_13(CPU* cpu) // inc de
{
   cpu->regP.DE++;
   cpu->ticks += 2;
}

void CPU::_op_14(CPU* cpu) // inc d
{
   cpu->_inc8(cpu->regB.D);
}

void CPU::_op_15(CPU* cpu) // dec d
{
   cpu->_dec8(cpu->regB.D);
}

void CPU::_op_16(CPU* cpu) // ld d,nn
{
   cpu->regB.D = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 3;
}

void CPU::_op_17(CPU* cpu) // rla
{
   BYTE tmp = (cpu->regB.A << 1) + (cpu->regB.F & 1);
   cpu->regB.F = pRLCAF[cpu->regB.A] | (cpu->regB.F & (SF | ZF | PV)); // use same table with rlca
   cpu->regB.A = tmp;
}

void CPU::_op_18(CPU* cpu) // jr rr
{
   char off = (char)cpu->pMemory->read(cpu->regP.PC++);
   cpu->regP.PC += off;
   cpu->ticks += 8;
}

void CPU::_op_19(CPU* cpu) // add hl,de
{
   WORD tmp = cpu->regP.HL;
   cpu->regB.F = (cpu->regB.F & ~(NF | CF | F5 | F3 | HF));
   cpu->regB.F |= (((cpu->regP.HL & 0x0FFF) + (cpu->regP.DE & 0x0FFF)) >> 8) & 0x10; /* HF */
   cpu->regP.HL += cpu->regP.DE;
   if (cpu->regP.HL < tmp) cpu->regB.F |= CF;
   cpu->regB.F |= (cpu->regB.H & (F5 | F3));
   cpu->ticks += 7;
}

void CPU::_op_1A(CPU* cpu) // ld a,(de)
{
   cpu->regB.A = cpu->pMemory->read(cpu->regP.DE);
   cpu->ticks += 3;
}

void CPU::_op_1B(CPU* cpu) // dec de
{
   cpu->regP.DE--;
   cpu->ticks += 2;
}

void CPU::_op_1C(CPU* cpu) // inc e
{
   cpu->_inc8(cpu->regB.E);
}

void CPU::_op_1D(CPU* cpu) // dec e
{
   cpu->_dec8(cpu->regB.E);
}

void CPU::_op_1E(CPU* cpu) // ld e,nn
{
   cpu->regB.E = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 3;
}

void CPU::_op_1F(CPU* cpu) // rra
{
   BYTE tmp = (cpu->regB.A >> 1) + (cpu->regB.F << 7);
   cpu->regB.F = pRRCAF[cpu->regB.A] | (cpu->regB.F & (SF | ZF | PV)); // use same table with rrca
   cpu->regB.A = tmp;
}

void CPU::_op_20(CPU* cpu) // jr nz, rr
{
   if (! (cpu->regB.F & ZF))
      _op_18(cpu);      // jr
   else
   {
      cpu->regP.PC++;
      cpu->ticks += 3;
   }
}

void CPU::_op_21(CPU* cpu) // ld hl,nnnn
{
   cpu->regB.L = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.H = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 6;
}

void CPU::_op_22(CPU* cpu) // ld (nnnn),hl
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->pMemory->write(adr++, cpu->regB.L);
   cpu->pMemory->write(adr, cpu->regB.H);
   cpu->ticks += 12;
}

void CPU::_op_23(CPU* cpu) // inc hl
{
   cpu->regP.HL++;
   cpu->ticks += 2;
}

void CPU::_op_24(CPU* cpu) // inc h
{
   cpu->_inc8(cpu->regB.H);
}

void CPU::_op_25(CPU* cpu) // dec h
{
   cpu->_dec8(cpu->regB.H);
}

void CPU::_op_26(CPU* cpu) // ld h,nn
{
   cpu->regB.H = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 3;
}

void CPU::_op_27(CPU* cpu) // daa
{
   cpu->regP.AF = *(WORD*)
   (pDAAF + (cpu->regB.A + 0x100 * ((cpu->regB.F & 3) + ((cpu->regB.F >> 2) & 4))) * 2);
}

void CPU::_op_28(CPU* cpu) // jr z,rr
{
   if (cpu->regB.F & ZF)
      _op_18(cpu);
   else
   {
      cpu->regP.PC++;
      cpu->ticks += 3;
   }
}

void CPU::_op_29(CPU* cpu) // add hl,hl
{
   WORD tmp = cpu->regP.HL;
   cpu->regB.F = (cpu->regB.F & ~(NF | CF | F5 | F3 | HF));
   cpu->regB.F |= ((cpu->regB.H << 1) & 0x10); /* HF */
   cpu->regB.F |= ((cpu->regP.HL >> 7) & 0x10); /* HF */
   cpu->regP.HL += cpu->regP.HL;
   if (cpu->regP.HL < tmp) cpu->regB.F |= CF;
   cpu->regB.F |= (cpu->regB.H & (F5 | F3));
   cpu->ticks += 7;
}

void CPU::_op_2A(CPU* cpu) // ld hl,(nnnn)
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->regB.L = cpu->pMemory->read(adr++);
   cpu->regB.H = cpu->pMemory->read(adr);
   cpu->ticks += 12;
}

void CPU::_op_2B(CPU* cpu) // dec hl
{
   cpu->regP.HL--;
   cpu->ticks += 2;
}

void CPU::_op_2C(CPU* cpu) // inc l
{
   cpu->_inc8(cpu->regB.L);
}

void CPU::_op_2D(CPU* cpu) // dec l
{
   cpu->_dec8(cpu->regB.L);
}

void CPU::_op_2E(CPU* cpu) // ld l,nn
{
   cpu->regB.L = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 3;
}

void CPU::_op_2F(CPU* cpu) // cpl
{
   cpu->regB.A = cpu->regB.A ^ 0xff;
   cpu->regB.F = (cpu->regB.F & ~(F3 | F5)) | NF | HF | (cpu->regB.A & (F3 | F5));
}

void CPU::_op_30(CPU* cpu) // jr nc, rr
{
   if (! (cpu->regB.F & CF))
      _op_18(cpu);
   else
   {
      cpu->regP.PC++;
      cpu->ticks += 3;
   }
}

void CPU::_op_31(CPU* cpu) // ld sp,nnnn
{
   cpu->regB.SPl = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.SPh = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 6;
}

void CPU::_op_32(CPU* cpu) // ld (nnnn),a
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->pMemory->write(adr, cpu->regB.A);
   cpu->ticks += 9;
}

void CPU::_op_33(CPU* cpu) // inc sp
{
   cpu->regP.SP++;
   cpu->ticks += 2;
}

void CPU::_op_34(CPU* cpu) // inc (hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_inc8(tmp);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 7;
}

void CPU::_op_35(CPU* cpu) // dec (hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_dec8(tmp);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 7;
}

void CPU::_op_36(CPU* cpu) // ld (hl),nn
{
   cpu->pMemory->write(cpu->regP.HL, cpu->pMemory->read(cpu->regP.PC++));
   cpu->ticks += 6;
}

void CPU::_op_37(CPU* cpu) // scf
{
   cpu->regB.F = (cpu->regB.F & ~(F3|F5|HF|NF)) | (cpu->regB.A & (F3|F5)) | CF;
}

void CPU::_op_38(CPU* cpu) // jr c,rr
{
   if (cpu->regB.F & CF)
      _op_18(cpu);
   else
   {
      cpu->regP.PC++;
      cpu->ticks += 3;
   }
}

void CPU::_op_39(CPU* cpu) // add hl,sp
{
   WORD tmp = cpu->regP.HL;
   cpu->regB.F = (cpu->regB.F & ~(NF | CF | F5 | F3 | HF));
   cpu->regB.F |= (((cpu->regP.HL & 0x0FFF) + (cpu->regP.SP & 0x0FFF)) >> 8) & 0x10; /* HF */
   cpu->regP.HL += cpu->regP.SP;
   if (cpu->regP.HL < tmp) cpu->regB.F |= CF;
   cpu->regB.F |= (cpu->regB.H & (F5 | F3));
   cpu->ticks += 7;
}

void CPU::_op_3A(CPU* cpu) // ld a,(nnnn)
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->regB.A = cpu->pMemory->read(adr);
   cpu->ticks += 9;
}

void CPU::_op_3B(CPU* cpu) // dec sp
{
   cpu->regP.SP--;
   cpu->ticks += 2;
}

void CPU::_op_3C(CPU* cpu) // inc a
{
   cpu->_inc8(cpu->regB.A);
}

void CPU::_op_3D(CPU* cpu) // dec a
{
   cpu->_dec8(cpu->regB.A);
}

void CPU::_op_3E(CPU* cpu) // ld a,nn
{
   cpu->regB.A = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 3;
}

void CPU::_op_3F(CPU* cpu) // ccf
{
   cpu->regB.F = ((cpu->regB.F & ~(F3 | F5 | NF)) | (cpu->regB.A & (F3 | F5))) ^ CF;
}

void CPU::_op_41(CPU* cpu) // ld b,c
{
   cpu->regB.B = cpu->regB.C;
}

void CPU::_op_42(CPU* cpu) // ld b,d
{
   cpu->regB.B = cpu->regB.D;
}

void CPU::_op_43(CPU* cpu) // ld b,e
{
   cpu->regB.B = cpu->regB.E;
}

void CPU::_op_44(CPU* cpu) // ld b,h
{
   cpu->regB.B = cpu->regB.H;
}

void CPU::_op_45(CPU* cpu) // ld b,l
{
   cpu->regB.B = cpu->regB.L;
}

void CPU::_op_46(CPU* cpu) // ld b,(hl)
{
   cpu->regB.B = cpu->pMemory->read(cpu->regP.HL);
   cpu->ticks += 3;
}

void CPU::_op_47(CPU* cpu) // ld b,a
{
   cpu->regB.B = cpu->regB.A;
}

void CPU::_op_48(CPU* cpu) // ld c,b
{
   cpu->regB.C = cpu->regB.B;
}

void CPU::_op_4A(CPU* cpu) // ld c,d
{
   cpu->regB.C = cpu->regB.D;
}

void CPU::_op_4B(CPU* cpu) // ld c,e
{
   cpu->regB.C = cpu->regB.E;
}

void CPU::_op_4C(CPU* cpu) // ld c,h
{
   cpu->regB.C = cpu->regB.H;
}

void CPU::_op_4D(CPU* cpu) // ld c,l
{
   cpu->regB.C = cpu->regB.L;
}

void CPU::_op_4E(CPU* cpu) // ld c,(hl)
{
   cpu->regB.C = cpu->pMemory->read(cpu->regP.HL);
   cpu->ticks += 3;
}

void CPU::_op_4F(CPU* cpu) // ld c,a
{
   cpu->regB.C = cpu->regB.A;
}

void CPU::_op_50(CPU* cpu) // ld d,b
{
   cpu->regB.D = cpu->regB.B;
}

void CPU::_op_51(CPU* cpu) // ld d,c
{
   cpu->regB.D = cpu->regB.C;
}

void CPU::_op_53(CPU* cpu) // ld d,e
{
   cpu->regB.D = cpu->regB.E;
}

void CPU::_op_54(CPU* cpu) // ld d,h
{
   cpu->regB.D = cpu->regB.H;
}

void CPU::_op_55(CPU* cpu) // ld d,l
{
   cpu->regB.D = cpu->regB.L;
}

void CPU::_op_56(CPU* cpu) // ld d,(hl)
{
   cpu->regB.D = cpu->pMemory->read(cpu->regP.HL);
   cpu->ticks += 3;
}

void CPU::_op_57(CPU* cpu) // ld d,a
{
   cpu->regB.D = cpu->regB.A;
}

void CPU::_op_58(CPU* cpu) // ld e,b
{
   cpu->regB.E = cpu->regB.B;
}

void CPU::_op_59(CPU* cpu) // ld e,c
{
   cpu->regB.E = cpu->regB.C;
}

void CPU::_op_5A(CPU* cpu) // ld e,d
{
   cpu->regB.E = cpu->regB.D;
}

void CPU::_op_5C(CPU* cpu) // ld e,h
{
   cpu->regB.E = cpu->regB.H;
}

void CPU::_op_5D(CPU* cpu) // ld e,l
{
   cpu->regB.E = cpu->regB.L;
}

void CPU::_op_5E(CPU* cpu) // ld e,(hl)
{
   cpu->regB.E = cpu->pMemory->read(cpu->regP.HL);
   cpu->ticks += 3;
}

void CPU::_op_5F(CPU* cpu) // ld e,a
{
   cpu->regB.E = cpu->regB.A;
}

void CPU::_op_60(CPU* cpu) // ld h,b
{
   cpu->regB.H = cpu->regB.B;
}

void CPU::_op_61(CPU* cpu) // ld h,c
{
   cpu->regB.H = cpu->regB.C;
}

void CPU::_op_62(CPU* cpu) // ld h,d
{
   cpu->regB.H = cpu->regB.D;
}

void CPU::_op_63(CPU* cpu) // ld h,e
{
   cpu->regB.H = cpu->regB.E;
}

void CPU::_op_65(CPU* cpu) // ld h,l
{
   cpu->regB.H = cpu->regB.L;
}

void CPU::_op_66(CPU* cpu) // ld h,(hl)
{
   cpu->regB.H = cpu->pMemory->read(cpu->regP.HL);
   cpu->ticks += 3;
}

void CPU::_op_67(CPU* cpu) // ld h,a
{
   cpu->regB.H = cpu->regB.A;
}

void CPU::_op_68(CPU* cpu) // ld l,b
{
   cpu->regB.L = cpu->regB.B;
}

void CPU::_op_69(CPU* cpu) // ld l,c
{
   cpu->regB.L = cpu->regB.C;
}

void CPU::_op_6A(CPU* cpu) // ld l,d
{
   cpu->regB.L = cpu->regB.D;
}

void CPU::_op_6B(CPU* cpu) // ld l,e
{
   cpu->regB.L = cpu->regB.E;
}

void CPU::_op_6C(CPU* cpu) // ld l,h
{
   cpu->regB.L = cpu->regB.H;
}

void CPU::_op_6E(CPU* cpu) // ld l,(hl)
{
   cpu->regB.L = cpu->pMemory->read(cpu->regP.HL);
   cpu->ticks += 3;
}

void CPU::_op_6F(CPU* cpu) // ld l,a
{
   cpu->regB.L = cpu->regB.A;
}

void CPU::_op_70(CPU* cpu) // ld (hl),b
{
   cpu->pMemory->write(cpu->regP.HL, cpu->regB.B);
   cpu->ticks += 3;
}

void CPU::_op_71(CPU* cpu) // ld (hl),c
{
   cpu->pMemory->write(cpu->regP.HL, cpu->regB.C);
   cpu->ticks += 3;
}

void CPU::_op_72(CPU* cpu) // ld (hl),d
{
   cpu->pMemory->write(cpu->regP.HL, cpu->regB.D);
   cpu->ticks += 3;
}

void CPU::_op_73(CPU* cpu) // ld (hl),e
{
   cpu->pMemory->write(cpu->regP.HL, cpu->regB.E);
   cpu->ticks += 3;
}

void CPU::_op_74(CPU* cpu) // ld (hl),h
{
   cpu->pMemory->write(cpu->regP.HL, cpu->regB.H);
   cpu->ticks += 3;
}

void CPU::_op_75(CPU* cpu) // ld (hl),l
{
   cpu->pMemory->write(cpu->regP.HL, cpu->regB.L);
   cpu->ticks += 3;
}

void CPU::_op_76(CPU* cpu) // halt
{
   cpu->halted = TRUE;
   cpu->haltpos = cpu->ticks;
}

void CPU::_op_77(CPU* cpu) // ld (hl),a
{
   cpu->pMemory->write(cpu->regP.HL, cpu->regB.A);
   cpu->ticks += 3;
}

void CPU::_op_78(CPU* cpu) // ld a,b
{
   cpu->regB.A = cpu->regB.B;
}

void CPU::_op_79(CPU* cpu) // ld a,c
{
   cpu->regB.A = cpu->regB.C;
}

void CPU::_op_7A(CPU* cpu) // ld a,d
{
   cpu->regB.A = cpu->regB.D;
}

void CPU::_op_7B(CPU* cpu) // ld a,e
{
   cpu->regB.A = cpu->regB.E;
}

void CPU::_op_7C(CPU* cpu) // ld a,h
{
   cpu->regB.A = cpu->regB.H;
}

void CPU::_op_7D(CPU* cpu) // ld a,l
{
   cpu->regB.A = cpu->regB.L;
}

void CPU::_op_7E(CPU* cpu) // ld a,(hl)
{
   cpu->regB.A = cpu->pMemory->read(cpu->regP.HL);
   cpu->ticks += 3;
}

void CPU::_op_80(CPU* cpu) // add a,b
{
   cpu->_add8(cpu->regB.B);
}

void CPU::_op_81(CPU* cpu) // add a,c
{
   cpu->_add8(cpu->regB.C);
}

void CPU::_op_82(CPU* cpu) // add a,d
{
   cpu->_add8(cpu->regB.D);
}

void CPU::_op_83(CPU* cpu) // add a,e
{
   cpu->_add8(cpu->regB.E);
}

void CPU::_op_84(CPU* cpu) // add a,h
{
   cpu->_add8(cpu->regB.H);
}

void CPU::_op_85(CPU* cpu) // add a,l
{
   cpu->_add8(cpu->regB.L);
}

void CPU::_op_86(CPU* cpu) // add a,(hl)
{
   cpu->_add8(cpu->pMemory->read(cpu->regP.HL));
   cpu->ticks += 3;
}

void CPU::_op_87(CPU* cpu) // add a,a
{
   cpu->_add8(cpu->regB.A);
}

void CPU::_op_88(CPU* cpu) // adc a,b
{
   cpu->_adc8(cpu->regB.B);
}

void CPU::_op_89(CPU* cpu) // adc a,c
{
   cpu->_adc8(cpu->regB.C);
}

void CPU::_op_8A(CPU* cpu) // adc a,d
{
   cpu->_adc8(cpu->regB.D);
}

void CPU::_op_8B(CPU* cpu) // adc a,e
{
   cpu->_adc8(cpu->regB.E);
}

void CPU::_op_8C(CPU* cpu) // adc a,h
{
   cpu->_adc8(cpu->regB.H);
}

void CPU::_op_8D(CPU* cpu) // adc a,l
{
   cpu->_adc8(cpu->regB.L);
}

void CPU::_op_8E(CPU* cpu) // adc a,(hl)
{
   cpu->_adc8(cpu->pMemory->read(cpu->regP.HL));
   cpu->ticks += 3;
}

void CPU::_op_8F(CPU* cpu) // adc a,a
{
   cpu->_adc8(cpu->regB.A);
}

void CPU::_op_90(CPU* cpu) // sub b
{
   cpu->_sub8(cpu->regB.B);
}

void CPU::_op_91(CPU* cpu) // sub c
{
   cpu->_sub8(cpu->regB.C);
}

void CPU::_op_92(CPU* cpu) // sub d
{
   cpu->_sub8(cpu->regB.D);
}

void CPU::_op_93(CPU* cpu) // sub e
{
   cpu->_sub8(cpu->regB.E);
}

void CPU::_op_94(CPU* cpu) // sub h
{
   cpu->_sub8(cpu->regB.H);
}

void CPU::_op_95(CPU* cpu) // sub l
{
   cpu->_sub8(cpu->regB.L);
}

void CPU::_op_96(CPU* cpu) // sub (hl)
{
   cpu->_sub8(cpu->pMemory->read(cpu->regP.HL));
   cpu->ticks += 3;
}

void CPU::_op_97(CPU* cpu) // sub a
{
   cpu->regP.AF = ZF | NF;
}

void CPU::_op_98(CPU* cpu) // sbc a,b
{
   cpu->_sbc8(cpu->regB.B);
}

void CPU::_op_99(CPU* cpu) // sbc a,c
{
   cpu->_sbc8(cpu->regB.C);
}

void CPU::_op_9A(CPU* cpu) // sbc a,d
{
   cpu->_sbc8(cpu->regB.D);
}

void CPU::_op_9B(CPU* cpu) // sbc a,e
{
   cpu->_sbc8(cpu->regB.E);
}

void CPU::_op_9C(CPU* cpu) // sbc a,h
{
   cpu->_sbc8(cpu->regB.H);
}

void CPU::_op_9D(CPU* cpu) // sbc a,l
{
   cpu->_sbc8(cpu->regB.L);
}

void CPU::_op_9E(CPU* cpu) // sbc a,(hl)
{
   cpu->_sbc8(cpu->pMemory->read(cpu->regP.HL));
   cpu->ticks += 3;
}

void CPU::_op_9F(CPU* cpu) // sbc a,a
{
   cpu->_sbc8(cpu->regB.A);
}

void CPU::_op_A0(CPU* cpu) // and b
{
   cpu->_and8(cpu->regB.B);
}

void CPU::_op_A1(CPU* cpu) // and c
{
   cpu->_and8(cpu->regB.C);
}

void CPU::_op_A2(CPU* cpu) // and d
{
   cpu->_and8(cpu->regB.D);
}

void CPU::_op_A3(CPU* cpu) // and e
{
   cpu->_and8(cpu->regB.E);
}

void CPU::_op_A4(CPU* cpu) // and h
{
   cpu->_and8(cpu->regB.H);
}

void CPU::_op_A5(CPU* cpu) // and l
{
   cpu->_and8(cpu->regB.L);
}

void CPU::_op_A6(CPU* cpu) // and (hl)
{
   cpu->_and8(cpu->pMemory->read(cpu->regP.HL));
   cpu->ticks += 3;
}

void CPU::_op_A7(CPU* cpu) // and a
{
   cpu->_and8(cpu->regB.A);
}

void CPU::_op_A8(CPU* cpu) // xor b
{
   cpu->_xor8(cpu->regB.B);
}

void CPU::_op_A9(CPU* cpu) // xor c
{
   cpu->_xor8(cpu->regB.C);
}

void CPU::_op_AA(CPU* cpu) // xor d
{
   cpu->_xor8(cpu->regB.D);
}

void CPU::_op_AB(CPU* cpu) // xor e
{
   cpu->_xor8(cpu->regB.E);
}

void CPU::_op_AC(CPU* cpu) // xor h
{
   cpu->_xor8(cpu->regB.H);
}

void CPU::_op_AD(CPU* cpu) // xor l
{
   cpu->_xor8(cpu->regB.L);
}

void CPU::_op_AE(CPU* cpu) // xor (hl)
{
   cpu->_xor8(cpu->pMemory->read(cpu->regP.HL));
   cpu->ticks += 3;
}

void CPU::_op_AF(CPU* cpu) // xor a
{
   cpu->regP.AF = ZF | PV;
}

void CPU::_op_B0(CPU* cpu) // or b
{
   cpu->_orl8(cpu->regB.B);
}

void CPU::_op_B1(CPU* cpu) // or c
{
   cpu->_orl8(cpu->regB.C);
}

void CPU::_op_B2(CPU* cpu) // or d
{
   cpu->_orl8(cpu->regB.D);
}

void CPU::_op_B3(CPU* cpu) // or e
{
   cpu->_orl8(cpu->regB.E);
}

void CPU::_op_B4(CPU* cpu) // or h
{
   cpu->_orl8(cpu->regB.H);
}

void CPU::_op_B5(CPU* cpu) // or l
{
   cpu->_orl8(cpu->regB.L);
}

void CPU::_op_B6(CPU* cpu) // or (hl)
{
   cpu->_orl8(cpu->pMemory->read(cpu->regP.HL));
   cpu->ticks += 3;
}

void CPU::_op_B7(CPU* cpu) // or a
{
   cpu->_orl8(cpu->regB.A);
}

void CPU::_op_B8(CPU* cpu)  // cp b
{
   cpu->_cpr8(cpu->regB.B);
}

void CPU::_op_B9(CPU* cpu) // cp c
{
   cpu->_cpr8(cpu->regB.C);
}

void CPU::_op_BA(CPU* cpu) // cp d
{
   cpu->_cpr8(cpu->regB.D);
}

void CPU::_op_BB(CPU* cpu) // cp e
{
   cpu->_cpr8(cpu->regB.E);
}

void CPU::_op_BC(CPU* cpu) // cp h
{
   cpu->_cpr8(cpu->regB.H);
}

void CPU::_op_BD(CPU* cpu) // cp l
{
   cpu->_cpr8(cpu->regB.L);
}

void CPU::_op_BE(CPU* cpu) // cp (hl)
{
   cpu->_cpr8(cpu->pMemory->read(cpu->regP.HL));
   cpu->ticks += 3;
}

void CPU::_op_BF(CPU* cpu) // cp a
{
   cpu->_cpr8(cpu->regB.A);
}

void CPU::_op_C0(CPU* cpu) // ret nz
{
   cpu->ticks++;
   if (! (cpu->regB.F & ZF))
      _op_C9(cpu);
}

void CPU::_op_C1(CPU* cpu) // pop bc
{
   cpu->_pop(cpu->regP.BC);
   cpu->ticks += 6;
}

void CPU::_op_C2(CPU* cpu) // jp nz,nnnn
{
   if (! (cpu->regB.F & ZF))
      _op_C3(cpu);
   else
   {
      cpu->regP.PC += 2;
      cpu->ticks += 6;
   }
}

void CPU::_op_C3(CPU* cpu) // jp nnnn
{
   cpu->regP.PC = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC) << 8);
   cpu->ticks += 6;
}

void CPU::_op_C4(CPU* cpu) // call nz,nnnn
{
   if (! (cpu->regB.F & ZF))
      _op_CD(cpu);
   else
   {
      cpu->ticks += 6;
      cpu->regP.PC += 2;
   }
}

void CPU::_op_C5(CPU* cpu) // push bc
{
   cpu->_push(cpu->regP.BC);
   cpu->ticks += 7;
}

void CPU::_op_C6(CPU* cpu) // add a,nn
{
   cpu->_add8(cpu->pMemory->read(cpu->regP.PC++));
   cpu->ticks += 3;
}

void CPU::_op_C7(CPU* cpu) // rst 00
{
   cpu->_push(cpu->regP.PC);
   cpu->regP.PC = 0;
   cpu->ticks += 7;
}

void CPU::_op_C8(CPU* cpu) // ret z
{
   if (cpu->regB.F & ZF)
   {
      cpu->_pop(cpu->regP.PC);
      cpu->ticks += 7;
   }
   else
      cpu->ticks++;
}

void CPU::_op_C9(CPU* cpu) // ret
{
   cpu->_pop(cpu->regP.PC);
   cpu->ticks += 6;
}

void CPU::_op_CA(CPU* cpu) // jp z,nnnn
{
   if (cpu->regB.F & ZF)
      _op_C3(cpu);
   else
   {
      cpu->ticks += 6;
      cpu->regP.PC += 2;
   }
}

void CPU::_op_CB(CPU* cpu)  // cb prefix
{
    BYTE opcode = cpu->cycle();
    (pOpsCB[opcode])(cpu);
}

void CPU::_op_CC(CPU* cpu) // call z,nnnn
{
   if (cpu->regB.F & ZF)
      _op_CD(cpu);
   else
   {
      cpu->regP.PC += 2;
      cpu->ticks += 6;
   }
}

void CPU::_op_CD(CPU* cpu) // call
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->_push(cpu->regP.PC);
   cpu->regP.PC = adr;
   cpu->ticks += 13;
}

void CPU::_op_CE(CPU* cpu) // adc a,nn
{
   cpu->_adc8(cpu->pMemory->read(cpu->regP.PC++));
   cpu->ticks += 3;
}

void CPU::_op_CF(CPU* cpu) // rst 08
{
   cpu->_push(cpu->regP.PC);
   cpu->regP.PC = 0x08;
   cpu->ticks += 7;
}

void CPU::_op_D0(CPU* cpu) // ret nc
{
   if (! (cpu->regB.F & CF))
   {
      cpu->_pop(cpu->regP.PC);
      cpu->ticks += 7;
   }
   else
      cpu->ticks++;
}

void CPU::_op_D1(CPU* cpu) // pop de
{
   cpu->_pop(cpu->regP.DE);
   cpu->ticks += 6;
}

void CPU::_op_D2(CPU* cpu) // jp nc,nnnn
{
   if (! (cpu->regB.F & CF))
      _op_C3(cpu);
   else
   {
      cpu->ticks += 6;
      cpu->regP.PC += 2;
   }
}

void CPU::_op_D3(CPU* cpu) // out (nn),a
{
   BYTE port = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 7;
   cpu->pManager->outByte(port + ((int)cpu->regB.A << 8), cpu->regB.A);
}

void CPU::_op_D4(CPU* cpu) // call nc,nnnn
{
   if (! (cpu->regB.F & CF))
      _op_CD(cpu);
   else
   {
      cpu->regP.PC += 2;
      cpu->ticks += 6;
   }
}

void CPU::_op_D5(CPU* cpu) // push de
{
   cpu->_push(cpu->regP.DE);
   cpu->ticks += 7;
}

void CPU::_op_D6(CPU* cpu) // sub nn
{
   cpu->_sub8(cpu->pMemory->read(cpu->regP.PC++));
   cpu->ticks += 3;
}

void CPU::_op_D7(CPU* cpu) // rst 10
{
   cpu->_push(cpu->regP.PC);
   cpu->regP.PC = 0x10;
   cpu->ticks += 7;
}

void CPU::_op_D8(CPU* cpu) // ret c
{
   if (cpu->regB.F & CF)
   {
      cpu->_pop(cpu->regP.PC);
      cpu->ticks += 7;
   }
   else
      cpu->ticks++;
}

void CPU::_op_D9(CPU* cpu) // exx
{
   cpu->regP.BC ^= cpu->BC_;
   cpu->BC_ ^= cpu->regP.BC;
   cpu->regP.BC ^= cpu->BC_;

   cpu->regP.DE ^= cpu->DE_;
   cpu->DE_ ^= cpu->regP.DE;
   cpu->regP.DE ^= cpu->DE_;

   cpu->regP.HL ^= cpu->HL_;
   cpu->HL_ ^= cpu->regP.HL;
   cpu->regP.HL ^= cpu->HL_;
}

void CPU::_op_DA(CPU* cpu) // jp c,nnnn
{
   if (cpu->regB.F & CF)
      _op_C3(cpu);
   else
   {
      cpu->ticks += 6;
      cpu->regP.PC += 2;
   }
}

void CPU::_op_DB(CPU* cpu) // in a,(nn)
{
   BYTE port = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 7;
   cpu->regB.A = cpu->pManager->inByte(port + ((int)cpu->regB.A << 8));
}

void CPU::_op_DC(CPU* cpu) // call c,nnnn
{
   if (cpu->regB.F & CF)
      _op_CD(cpu);
   else
   {
      cpu->regP.PC += 2;
      cpu->ticks += 6;
   }
}

void CPU::_op_DD(CPU* cpu)  // dd prefix
{
    _opDDFD(cpu, 0xDD);
}

void CPU::_op_DE(CPU* cpu) // sbc a,nn
{
   cpu->_sbc8(cpu->pMemory->read(cpu->regP.PC++));
   cpu->ticks += 3;
}

void CPU::_op_DF(CPU* cpu) // rst 18
{
   cpu->_push(cpu->regP.PC);
   cpu->regP.PC = 0x18;
   cpu->ticks += 7;
}

void CPU::_op_E0(CPU* cpu) // ret po
{
   if (! (cpu->regB.F & PV))
   {
      cpu->_pop(cpu->regP.PC);
      cpu->ticks += 7;
   }
   else
      cpu->ticks++;
}

void CPU::_op_E1(CPU* cpu) // pop hl
{
   cpu->_pop(cpu->regP.HL);
   cpu->ticks += 6;
}

void CPU::_op_E2(CPU* cpu) // jp po,nnnn
{
   if (! (cpu->regB.F & PV))
      _op_C3(cpu);
   else
   {
      cpu->ticks += 6;
      cpu->regP.PC += 2;
   }
}

void CPU::_op_E3(CPU* cpu) // ex (sp),hl
{
   WORD tmp = cpu->pMemory->read(cpu->regP.SP) + ((int)cpu->pMemory->read(cpu->regP.SP + 1) << 8);
   cpu->pMemory->write(cpu->regP.SP, cpu->regB.L);
   cpu->pMemory->write(cpu->regP.SP + 1, cpu->regB.H);
   cpu->regP.HL = tmp;
   cpu->ticks += 15;
}

void CPU::_op_E4(CPU* cpu) // call po,nnnn
{
   if (! (cpu->regB.F & PV))
      _op_CD(cpu);
   else
   {
      cpu->regP.PC += 2;
      cpu->ticks += 6;
   }
}

void CPU::_op_E5(CPU* cpu) // push hl
{
   cpu->_push(cpu->regP.HL);
   cpu->ticks += 7;
}

void CPU::_op_E6(CPU* cpu) // and nn
{
   cpu->_and8(cpu->pMemory->read(cpu->regP.PC++));
   cpu->ticks += 3;
}

void CPU::_op_E7(CPU* cpu) // rst 20
{
   cpu->_push(cpu->regP.PC);
   cpu->regP.PC = 0x20;
   cpu->ticks += 7;
}

void CPU::_op_E8(CPU* cpu) // ret pe
{
   if (cpu->regB.F & PV)
   {
      cpu->_pop(cpu->regP.PC);
      cpu->ticks += 7;
   }
   else
      cpu->ticks++;
}

void CPU::_op_E9(CPU* cpu) // jp (hl)
{
   cpu->regP.PC = cpu->regP.HL;
}

void CPU::_op_EA(CPU* cpu) // jp pe,nnnn
{
   if (cpu->regB.F & PV)
      _op_C3(cpu);
   else
   {
      cpu->ticks += 6;
      cpu->regP.PC += 2;
   }
}

void CPU::_op_EB(CPU* cpu) // ex de,hl
{
   cpu->regP.DE ^= cpu->regP.HL;
   cpu->regP.HL ^= cpu->regP.DE;
   cpu->regP.DE ^= cpu->regP.HL;
}

void CPU::_op_EC(CPU* cpu) // call pe,nnnn
{
   if (cpu->regB.F & PV)
      _op_CD(cpu);
   else
   {
      cpu->regP.PC += 2;
      cpu->ticks += 6;
   }
}

void CPU::_op_ED(CPU* cpu)  // ed prefix
{
    BYTE opcode = cpu->cycle();
    (pOpsED[opcode])(cpu);
}

void CPU::_op_EE(CPU* cpu) // xor nn
{
   cpu->_xor8(cpu->pMemory->read(cpu->regP.PC++));
   cpu->ticks += 3;
}

void CPU::_op_EF(CPU* cpu) // rst 28
{
   cpu->_push(cpu->regP.PC);
   cpu->regP.PC = 0x28;
   cpu->ticks += 7;
}

void CPU::_op_F0(CPU* cpu) // ret p
{
   if (! (cpu->regB.F & SF))
   {
      cpu->_pop(cpu->regP.PC);
      cpu->ticks += 7;
   }
   else
      cpu->ticks++;
}

void CPU::_op_F1(CPU* cpu) // pop af
{
   cpu->_pop(cpu->regP.AF);
   cpu->ticks += 6;
}

void CPU::_op_F2(CPU* cpu) // jp p,nnnn
{
   if (! (cpu->regB.F & SF))
      _op_C3(cpu);
   else
   {
      cpu->ticks += 6;
      cpu->regP.PC += 2;
   }
}

void CPU::_op_F3(CPU* cpu) // di
{
   cpu->iff1 = cpu->iff2 = 0;
}

void CPU::_op_F4(CPU* cpu) // call p,nnnn
{
   if (! (cpu->regB.F & SF))
       _op_CD(cpu);
   else
   {
      cpu->regP.PC += 2;
      cpu->ticks += 6;
   }
}

void CPU::_op_F5(CPU* cpu) // push af
{
   cpu->_push(cpu->regP.AF);
   cpu->ticks += 7;
}

void CPU::_op_F6(CPU* cpu) // or nn
{
   cpu->_orl8(cpu->pMemory->read(cpu->regP.PC++));
   cpu->ticks += 3;
}

void CPU::_op_F7(CPU* cpu) // rst 30
{
   cpu->_push(cpu->regP.PC);
   cpu->regP.PC = 0x30;
   cpu->ticks += 7;
}

void CPU::_op_F8(CPU* cpu) // ret m
{
   if (cpu->regB.F & SF)
   {
      cpu->_pop(cpu->regP.PC);
      cpu->ticks += 7;
   }
   else
      cpu->ticks++;
}

void CPU::_op_F9(CPU* cpu) // ld sp,hl
{
   cpu->regP.SP = cpu->regP.HL;
   cpu->ticks += 2;
}

void CPU::_op_FA(CPU* cpu) // jp m,nnnn
{
   if (cpu->regB.F & SF)
      _op_C3(cpu);
   else
   {
      cpu->ticks += 6;
      cpu->regP.PC += 2;
   }
}

void CPU::_op_FB(CPU* cpu) // ei
{
   cpu->iff1 = cpu->iff2 = TRUE;
   cpu->eipos = cpu->ticks;
}

void CPU::_op_FC(CPU* cpu) // call m,nnnn
{
   if (cpu->regB.F & SF)
      _op_CD(cpu);
   else
   {
      cpu->regP.PC += 2;
      cpu->ticks += 6;
   }
}

void CPU::_op_FD(CPU* cpu)  // fd prefix
{
    _opDDFD(cpu, 0xFD);
}

void CPU::_op_FE(CPU* cpu) // cp nn
{
   cpu->_cpr8(cpu->pMemory->read(cpu->regP.PC++));
   cpu->ticks += 3;
}

void CPU::_op_FF(CPU* cpu) // rst 38
{
   cpu->_push(cpu->regP.PC);
   cpu->regP.PC = 0x38;
   cpu->ticks += 7;
}

//============================================

CPUFUNC const CPU::pOpsCB[] = {
   _opCB_00, _opCB_01, _opCB_02, _opCB_03, _opCB_04, _opCB_05, _opCB_06, _opCB_07,
   _opCB_08, _opCB_09, _opCB_0A, _opCB_0B, _opCB_0C, _opCB_0D, _opCB_0E, _opCB_0F,
   _opCB_10, _opCB_11, _opCB_12, _opCB_13, _opCB_14, _opCB_15, _opCB_16, _opCB_17,
   _opCB_18, _opCB_19, _opCB_1A, _opCB_1B, _opCB_1C, _opCB_1D, _opCB_1E, _opCB_1F,
   _opCB_20, _opCB_21, _opCB_22, _opCB_23, _opCB_24, _opCB_25, _opCB_26, _opCB_27,
   _opCB_28, _opCB_29, _opCB_2A, _opCB_2B, _opCB_2C, _opCB_2D, _opCB_2E, _opCB_2F,
   _opCB_30, _opCB_31, _opCB_32, _opCB_33, _opCB_34, _opCB_35, _opCB_36, _opCB_37,
   _opCB_38, _opCB_39, _opCB_3A, _opCB_3B, _opCB_3C, _opCB_3D, _opCB_3E, _opCB_3F,

   _opCB_40, _opCB_41, _opCB_42, _opCB_43, _opCB_44, _opCB_45, _opCB_46, _opCB_47,
   _opCB_48, _opCB_49, _opCB_4A, _opCB_4B, _opCB_4C, _opCB_4D, _opCB_4E, _opCB_4F,
   _opCB_50, _opCB_51, _opCB_52, _opCB_53, _opCB_54, _opCB_55, _opCB_56, _opCB_57,
   _opCB_58, _opCB_59, _opCB_5A, _opCB_5B, _opCB_5C, _opCB_5D, _opCB_5E, _opCB_5F,
   _opCB_60, _opCB_61, _opCB_62, _opCB_63, _opCB_64, _opCB_65, _opCB_66, _opCB_67,
   _opCB_68, _opCB_69, _opCB_6A, _opCB_6B, _opCB_6C, _opCB_6D, _opCB_6E, _opCB_6F,
   _opCB_70, _opCB_71, _opCB_72, _opCB_73, _opCB_74, _opCB_75, _opCB_76, _opCB_77,
   _opCB_78, _opCB_79, _opCB_7A, _opCB_7B, _opCB_7C, _opCB_7D, _opCB_7E, _opCB_7F,

   _opCB_80, _opCB_81, _opCB_82, _opCB_83, _opCB_84, _opCB_85, _opCB_86, _opCB_87,
   _opCB_88, _opCB_89, _opCB_8A, _opCB_8B, _opCB_8C, _opCB_8D, _opCB_8E, _opCB_8F,
   _opCB_90, _opCB_91, _opCB_92, _opCB_93, _opCB_94, _opCB_95, _opCB_96, _opCB_97,
   _opCB_98, _opCB_99, _opCB_9A, _opCB_9B, _opCB_9C, _opCB_9D, _opCB_9E, _opCB_9F,
   _opCB_A0, _opCB_A1, _opCB_A2, _opCB_A3, _opCB_A4, _opCB_A5, _opCB_A6, _opCB_A7,
   _opCB_A8, _opCB_A9, _opCB_AA, _opCB_AB, _opCB_AC, _opCB_AD, _opCB_AE, _opCB_AF,
   _opCB_B0, _opCB_B1, _opCB_B2, _opCB_B3, _opCB_B4, _opCB_B5, _opCB_B6, _opCB_B7,
   _opCB_B8, _opCB_B9, _opCB_BA, _opCB_BB, _opCB_BC, _opCB_BD, _opCB_BE, _opCB_BF,

   _opCB_C0, _opCB_C1, _opCB_C2, _opCB_C3, _opCB_C4, _opCB_C5, _opCB_C6, _opCB_C7,
   _opCB_C8, _opCB_C9, _opCB_CA, _opCB_CB, _opCB_CC, _opCB_CD, _opCB_CE, _opCB_CF,
   _opCB_D0, _opCB_D1, _opCB_D2, _opCB_D3, _opCB_D4, _opCB_D5, _opCB_D6, _opCB_D7,
   _opCB_D8, _opCB_D9, _opCB_DA, _opCB_DB, _opCB_DC, _opCB_DD, _opCB_DE, _opCB_DF,
   _opCB_E0, _opCB_E1, _opCB_E2, _opCB_E3, _opCB_E4, _opCB_E5, _opCB_E6, _opCB_E7,
   _opCB_E8, _opCB_E9, _opCB_EA, _opCB_EB, _opCB_EC, _opCB_ED, _opCB_EE, _opCB_EF,
   _opCB_F0, _opCB_F1, _opCB_F2, _opCB_F3, _opCB_F4, _opCB_F5, _opCB_F6, _opCB_F7,
   _opCB_F8, _opCB_F9, _opCB_FA, _opCB_FB, _opCB_FC, _opCB_FD, _opCB_FE, _opCB_FF,
};

void CPU::_opCB_00(CPU* cpu) // rlc b
{
   cpu->regB.F = pRLCF[cpu->regB.B];
   cpu->regB.B = pROLF[cpu->regB.B];
}

void CPU::_opCB_01(CPU* cpu) // rlc c
{
   cpu->regB.F = pRLCF[cpu->regB.C];
   cpu->regB.C = pROLF[cpu->regB.C];
}

void CPU::_opCB_02(CPU* cpu) // rlc d
{
   cpu->regB.F = pRLCF[cpu->regB.D];
   cpu->regB.D = pROLF[cpu->regB.D];
}

void CPU::_opCB_03(CPU* cpu) // rlc e
{
   cpu->regB.F = pRLCF[cpu->regB.E];
   cpu->regB.E = pROLF[cpu->regB.E];
}

void CPU::_opCB_04(CPU* cpu) // rlc h
{
   cpu->regB.F = pRLCF[cpu->regB.H];
   cpu->regB.H = pROLF[cpu->regB.H];
}

void CPU::_opCB_05(CPU* cpu) // rlc l
{
   cpu->regB.F = pRLCF[cpu->regB.L];
   cpu->regB.L = pROLF[cpu->regB.L];
}

void CPU::_opCB_06(CPU* cpu) // rlc (hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->regB.F = pRLCF[tmp];
   cpu->pMemory->write(cpu->regP.HL, pROLF[tmp]);
   cpu->ticks += 7;
}

void CPU::_opCB_07(CPU* cpu) // rlc a
{
   cpu->regB.F = pRLCF[cpu->regB.A];
   cpu->regB.A = pROLF[cpu->regB.A];
}

void CPU::_opCB_08(CPU* cpu) // rrc b
{
   cpu->regB.F = pRRCF[cpu->regB.B];
   cpu->regB.B = pRORF[cpu->regB.B];
}

void CPU::_opCB_09(CPU* cpu) // rrc c
{
   cpu->regB.F = pRRCF[cpu->regB.C];
   cpu->regB.C = pRORF[cpu->regB.C];
}

void CPU::_opCB_0A(CPU* cpu) // rrc d
{
   cpu->regB.F = pRRCF[cpu->regB.D];
   cpu->regB.D = pRORF[cpu->regB.D];
}

void CPU::_opCB_0B(CPU* cpu) // rrc e
{
   cpu->regB.F = pRRCF[cpu->regB.E];
   cpu->regB.E = pRORF[cpu->regB.E];
}

void CPU::_opCB_0C(CPU* cpu) // rrc h
{
   cpu->regB.F = pRRCF[cpu->regB.H];
   cpu->regB.H = pRORF[cpu->regB.H];
}

void CPU::_opCB_0D(CPU* cpu) // rrc l
{
   cpu->regB.F = pRRCF[cpu->regB.L];
   cpu->regB.L = pRORF[cpu->regB.L];
}

void CPU::_opCB_0E(CPU* cpu) // rrc (hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->regB.F = pRRCF[tmp];
   cpu->pMemory->write(cpu->regP.HL, pRORF[tmp]);
   cpu->ticks += 7;
}

void CPU::_opCB_0F(CPU* cpu) // rrc a
{
   cpu->regB.F = pRRCF[cpu->regB.A];
   cpu->regB.A = pRORF[cpu->regB.A];
}

void CPU::_opCB_10(CPU* cpu) // rl b
{
   cpu->_rl8(cpu->regB.B);
}

void CPU::_opCB_11(CPU* cpu) // rl c
{
    cpu->_rl8(cpu->regB.C);
}

void CPU::_opCB_12(CPU* cpu) // rl d
{
    cpu->_rl8(cpu->regB.D);
}

void CPU::_opCB_13(CPU* cpu) // rl e
{
    cpu->_rl8(cpu->regB.E);
}

void CPU::_opCB_14(CPU* cpu) // rl h
{
    cpu->_rl8(cpu->regB.H);
}

void CPU::_opCB_15(CPU* cpu) // rl l
{
    cpu->_rl8(cpu->regB.L);
}

void CPU::_opCB_16(CPU* cpu) // rl (hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_rl8(tmp);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 7;
}

void CPU::_opCB_17(CPU* cpu) // rl a
{
    cpu->_rl8(cpu->regB.A);
}

void CPU::_opCB_18(CPU* cpu) // rr b
{
    cpu->_rr8(cpu->regB.B);
}

void CPU::_opCB_19(CPU* cpu) // rr c
{
    cpu->_rr8(cpu->regB.C);
}

void CPU::_opCB_1A(CPU* cpu) // rr d
{
    cpu->_rr8(cpu->regB.D);
}

void CPU::_opCB_1B(CPU* cpu) // rr e
{
    cpu->_rr8(cpu->regB.E);
}

void CPU::_opCB_1C(CPU* cpu) // rr h
{
    cpu->_rr8(cpu->regB.H);
}

void CPU::_opCB_1D(CPU* cpu) // rr l
{
    cpu->_rr8(cpu->regB.L);
}

void CPU::_opCB_1E(CPU* cpu) // rr (hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_rr8(tmp);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 7;
}

void CPU::_opCB_1F(CPU* cpu) // rr a
{
    cpu->_rr8(cpu->regB.A);
}

void CPU::_opCB_20(CPU* cpu) // sla b
{
   cpu->regB.F = pRL0[cpu->regB.B];
   cpu->regB.B <<= 1;
}

void CPU::_opCB_21(CPU* cpu) // sla c
{
   cpu->regB.F = pRL0[cpu->regB.C];
   cpu->regB.C <<= 1;
}

void CPU::_opCB_22(CPU* cpu) // sla d
{
   cpu->regB.F = pRL0[cpu->regB.D];
   cpu->regB.D <<= 1;
}

void CPU::_opCB_23(CPU* cpu) // sla e
{
   cpu->regB.F = pRL0[cpu->regB.E];
   cpu->regB.E <<= 1;
}

void CPU::_opCB_24(CPU* cpu) // sla h
{
   cpu->regB.F = pRL0[cpu->regB.H];
   cpu->regB.H <<= 1;
}

void CPU::_opCB_25(CPU* cpu) // sla l
{
   cpu->regB.F = pRL0[cpu->regB.L];
   cpu->regB.L <<= 1;
}

void CPU::_opCB_26(CPU* cpu) // sla (hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->regB.F = pRL0[tmp];
   tmp <<= 1;
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 7;
}

void CPU::_opCB_27(CPU* cpu) // sla a
{
   cpu->regB.F = pRL0[cpu->regB.A];
   cpu->regB.A <<= 1;
}

void CPU::_opCB_28(CPU* cpu) // sra b
{
   cpu->regB.F = pSRAF[cpu->regB.B];
   cpu->regB.B = (cpu->regB.B >> 1) + (cpu->regB.B & 0x80);
}

void CPU::_opCB_29(CPU* cpu) // sra c
{
   cpu->regB.F = pSRAF[cpu->regB.C];
   cpu->regB.C = (cpu->regB.C >> 1) + (cpu->regB.C & 0x80);
}

void CPU::_opCB_2A(CPU* cpu) // sra d
{
   cpu->regB.F = pSRAF[cpu->regB.D];
   cpu->regB.D = (cpu->regB.D >> 1) + (cpu->regB.D & 0x80);
}

void CPU::_opCB_2B(CPU* cpu) // sra e
{
   cpu->regB.F = pSRAF[cpu->regB.E];
   cpu->regB.E = (cpu->regB.E >> 1) + (cpu->regB.E & 0x80);
}

void CPU::_opCB_2C(CPU* cpu) // sra h
{
   cpu->regB.F = pSRAF[cpu->regB.H];
   cpu->regB.H = (cpu->regB.H >> 1) + (cpu->regB.H & 0x80);
}

void CPU::_opCB_2D(CPU* cpu) // sra l
{
   cpu->regB.F = pSRAF[cpu->regB.L];
   cpu->regB.L = (cpu->regB.L >> 1) + (cpu->regB.L & 0x80);
}

void CPU::_opCB_2E(CPU* cpu) // sra (hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->regB.F = pSRAF[tmp];
   tmp = (tmp >> 1) + (tmp & 0x80);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 7;
}

void CPU::_opCB_2F(CPU* cpu) // sra a
{
   cpu->regB.F = pSRAF[cpu->regB.A];
   cpu->regB.A = (cpu->regB.A >> 1) + (cpu->regB.A & 0x80);
}

void CPU::_opCB_30(CPU* cpu) // sli b
{
   cpu->regB.F = pRL1[cpu->regB.B];
   cpu->regB.B = (cpu->regB.B << 1) + 1;
}

void CPU::_opCB_31(CPU* cpu) // sli c
{
   cpu->regB.F = pRL1[cpu->regB.C];
   cpu->regB.C = (cpu->regB.C << 1) + 1;
}

void CPU::_opCB_32(CPU* cpu) // sli d
{
   cpu->regB.F = pRL1[cpu->regB.D];
   cpu->regB.D = (cpu->regB.D << 1) + 1;
}

void CPU::_opCB_33(CPU* cpu) // sli e
{
   cpu->regB.F = pRL1[cpu->regB.E];
   cpu->regB.E = (cpu->regB.E << 1) + 1;
}

void CPU::_opCB_34(CPU* cpu) // sli h
{
   cpu->regB.F = pRL1[cpu->regB.H];
   cpu->regB.H = (cpu->regB.H << 1) + 1;
}

void CPU::_opCB_35(CPU* cpu) // sli l
{
   cpu->regB.F = pRL1[cpu->regB.L];
   cpu->regB.L = (cpu->regB.L << 1) + 1;
}

void CPU::_opCB_36(CPU* cpu) // sli (hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->regB.F = pRL1[tmp];
   tmp = (tmp << 1) + 1;
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 7;
}

void CPU::_opCB_37(CPU* cpu) // sli a
{
   cpu->regB.F = pRL1[cpu->regB.A];
   cpu->regB.A = (cpu->regB.A << 1) + 1;
}

void CPU::_opCB_38(CPU* cpu) // srl b
{
   cpu->regB.F = pRR0[cpu->regB.B];
   cpu->regB.B >>= 1;
}

void CPU::_opCB_39(CPU* cpu) // srl c
{
   cpu->regB.F = pRR0[cpu->regB.C];
   cpu->regB.C >>= 1;
}

void CPU::_opCB_3A(CPU* cpu) // srl d
{
   cpu->regB.F = pRR0[cpu->regB.D];
   cpu->regB.D >>= 1;
}

void CPU::_opCB_3B(CPU* cpu) // srl e
{
   cpu->regB.F = pRR0[cpu->regB.E];
   cpu->regB.E >>= 1;
}

void CPU::_opCB_3C(CPU* cpu) // srl h
{
   cpu->regB.F = pRR0[cpu->regB.H];
   cpu->regB.H >>= 1;
}

void CPU::_opCB_3D(CPU* cpu) // srl l
{
   cpu->regB.F = pRR0[cpu->regB.L];
   cpu->regB.L >>= 1;
}

void CPU::_opCB_3E(CPU* cpu) // srl (hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->regB.F = pRR0[tmp];
   tmp >>= 1;
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 7;
}

void CPU::_opCB_3F(CPU* cpu) // srl a
{
   cpu->regB.F = pRR0[cpu->regB.A];
   cpu->regB.A >>= 1;
}

void CPU::_opCB_40(CPU* cpu) // bit 0,b
{
   cpu->_bit8(cpu->regB.B, 0);
}

void CPU::_opCB_41(CPU* cpu) // bit 0,c
{
   cpu->_bit8(cpu->regB.C, 0);
}

void CPU::_opCB_42(CPU* cpu) // bit 0,d
{
   cpu->_bit8(cpu->regB.D, 0);
}

void CPU::_opCB_43(CPU* cpu) // bit 0,e
{
   cpu->_bit8(cpu->regB.E, 0);
}

void CPU::_opCB_44(CPU* cpu) // bit 0,h
{
   cpu->_bit8(cpu->regB.H, 0);
}

void CPU::_opCB_45(CPU* cpu) // bit 0,l
{
   cpu->_bit8(cpu->regB.L, 0);
}

void CPU::_opCB_46(CPU* cpu) // bit 0,(hl)
{
   cpu->_bit8(cpu->pMemory->read(cpu->regP.HL), 0);
   cpu->ticks += 4;
}

void CPU::_opCB_47(CPU* cpu) // bit 0,a
{
   cpu->_bit8(cpu->regB.A, 0);
}

void CPU::_opCB_48(CPU* cpu) // bit 1,b
{
   cpu->_bit8(cpu->regB.B, 1);
}

void CPU::_opCB_49(CPU* cpu) // bit 1,c
{
   cpu->_bit8(cpu->regB.C, 1);
}

void CPU::_opCB_4A(CPU* cpu) // bit 1,d
{
   cpu->_bit8(cpu->regB.D, 1);
}

void CPU::_opCB_4B(CPU* cpu) // bit 1,e
{
   cpu->_bit8(cpu->regB.E, 1);
}

void CPU::_opCB_4C(CPU* cpu) // bit 1,h
{
   cpu->_bit8(cpu->regB.H, 1);
}

void CPU::_opCB_4D(CPU* cpu) // bit 1,l
{
   cpu->_bit8(cpu->regB.L, 1);
}

void CPU::_opCB_4E(CPU* cpu) // bit 1,(hl)
{
   cpu->_bit8(cpu->pMemory->read(cpu->regP.HL), 1);
   cpu->ticks += 4;
}

void CPU::_opCB_4F(CPU* cpu) // bit 1,a
{
   cpu->_bit8(cpu->regB.A, 1);
}

void CPU::_opCB_50(CPU* cpu) // bit 2,b
{
   cpu->_bit8(cpu->regB.B, 2);
}

void CPU::_opCB_51(CPU* cpu) // bit 2,c
{
   cpu->_bit8(cpu->regB.C, 2);
}

void CPU::_opCB_52(CPU* cpu) // bit 2,d
{
   cpu->_bit8(cpu->regB.D, 2);
}

void CPU::_opCB_53(CPU* cpu) // bit 2,e
{
   cpu->_bit8(cpu->regB.E, 2);
}

void CPU::_opCB_54(CPU* cpu) // bit 2,h
{
   cpu->_bit8(cpu->regB.H, 2);
}

void CPU::_opCB_55(CPU* cpu) // bit 2,l
{
   cpu->_bit8(cpu->regB.L, 2);
}

void CPU::_opCB_56(CPU* cpu) // bit 2,(hl)
{
   cpu->_bit8(cpu->pMemory->read(cpu->regP.HL), 2);
   cpu->ticks += 4;
}

void CPU::_opCB_57(CPU* cpu) // bit 2,a
{
   cpu->_bit8(cpu->regB.A, 2);
}

void CPU::_opCB_58(CPU* cpu) // bit 3,b
{
   cpu->_bit8(cpu->regB.B, 3);
}

void CPU::_opCB_59(CPU* cpu) // bit 3,c
{
   cpu->_bit8(cpu->regB.C, 3);
}

void CPU::_opCB_5A(CPU* cpu) // bit 3,d
{
   cpu->_bit8(cpu->regB.D, 3);
}

void CPU::_opCB_5B(CPU* cpu) // bit 3,e
{
   cpu->_bit8(cpu->regB.E, 3);
}

void CPU::_opCB_5C(CPU* cpu) // bit 3,h
{
   cpu->_bit8(cpu->regB.H, 3);
}

void CPU::_opCB_5D(CPU* cpu) // bit 3,l
{
   cpu->_bit8(cpu->regB.L, 3);
}

void CPU::_opCB_5E(CPU* cpu) // bit 3,(hl)
{
   cpu->_bit8(cpu->pMemory->read(cpu->regP.HL), 3);
   cpu->ticks += 4;
}

void CPU::_opCB_5F(CPU* cpu) // bit 3,a
{
   cpu->_bit8(cpu->regB.A, 3);
}

void CPU::_opCB_60(CPU* cpu) // bit 4,b
{
   cpu->_bit8(cpu->regB.B, 4);
}

void CPU::_opCB_61(CPU* cpu) // bit 4,c
{
   cpu->_bit8(cpu->regB.C, 4);
}

void CPU::_opCB_62(CPU* cpu) // bit 4,d
{
   cpu->_bit8(cpu->regB.D, 4);
}

void CPU::_opCB_63(CPU* cpu) // bit 4,e
{
   cpu->_bit8(cpu->regB.E, 4);
}

void CPU::_opCB_64(CPU* cpu) // bit 4,h
{
   cpu->_bit8(cpu->regB.H, 4);
}

void CPU::_opCB_65(CPU* cpu) // bit 4,l
{
   cpu->_bit8(cpu->regB.L, 4);
}

void CPU::_opCB_66(CPU* cpu) // bit 4,(hl)
{
   cpu->_bit8(cpu->pMemory->read(cpu->regP.HL), 4);
   cpu->ticks += 4;
}

void CPU::_opCB_67(CPU* cpu) // bit 4,a
{
   cpu->_bit8(cpu->regB.A, 4);
}

void CPU::_opCB_68(CPU* cpu) // bit 5,b
{
   cpu->_bit8(cpu->regB.B, 5);
}

void CPU::_opCB_69(CPU* cpu) // bit 5,c
{
   cpu->_bit8(cpu->regB.C, 5);
}

void CPU::_opCB_6A(CPU* cpu) // bit 5,d
{
   cpu->_bit8(cpu->regB.D, 5);
}

void CPU::_opCB_6B(CPU* cpu) // bit 5,e
{
   cpu->_bit8(cpu->regB.E, 5);
}

void CPU::_opCB_6C(CPU* cpu) // bit 5,h
{
   cpu->_bit8(cpu->regB.H, 5);
}

void CPU::_opCB_6D(CPU* cpu) // bit 5,l
{
   cpu->_bit8(cpu->regB.L, 5);
}

void CPU::_opCB_6E(CPU* cpu) // bit 5,(hl)
{
   cpu->_bit8(cpu->pMemory->read(cpu->regP.HL), 5);
   cpu->ticks += 4;
}

void CPU::_opCB_6F(CPU* cpu) // bit 5,a
{
   cpu->_bit8(cpu->regB.A, 5);
}

void CPU::_opCB_70(CPU* cpu) // bit 6,b
{
   cpu->_bit8(cpu->regB.B, 6);
}

void CPU::_opCB_71(CPU* cpu) // bit 6,c
{
   cpu->_bit8(cpu->regB.C, 6);
}

void CPU::_opCB_72(CPU* cpu) // bit 6,d
{
   cpu->_bit8(cpu->regB.D, 6);
}

void CPU::_opCB_73(CPU* cpu) // bit 6,e
{
   cpu->_bit8(cpu->regB.E, 6);
}

void CPU::_opCB_74(CPU* cpu) // bit 6,h
{
   cpu->_bit8(cpu->regB.H, 6);
}

void CPU::_opCB_75(CPU* cpu) // bit 6,l
{
   cpu->_bit8(cpu->regB.L, 6);
}

void CPU::_opCB_76(CPU* cpu) // bit 6,(hl)
{
   cpu->_bit8(cpu->pMemory->read(cpu->regP.HL), 6);
   cpu->ticks += 4;
}

void CPU::_opCB_77(CPU* cpu) // bit 6,a
{
   cpu->_bit8(cpu->regB.A, 6);
}

void CPU::_opCB_78(CPU* cpu) // bit 7,b
{
   cpu->_bit8(cpu->regB.B, 7);
}

void CPU::_opCB_79(CPU* cpu) // bit 7,c
{
   cpu->_bit8(cpu->regB.C, 7);
}

void CPU::_opCB_7A(CPU* cpu) // bit 7,d
{
   cpu->_bit8(cpu->regB.D, 7);
}

void CPU::_opCB_7B(CPU* cpu) // bit 7,e
{
   cpu->_bit8(cpu->regB.E, 7);
}

void CPU::_opCB_7C(CPU* cpu) // bit 7,h
{
   cpu->_bit8(cpu->regB.H, 7);
}

void CPU::_opCB_7D(CPU* cpu) // bit 7,l
{
   cpu->_bit8(cpu->regB.L, 7);
}

void CPU::_opCB_7E(CPU* cpu) // bit 7,(hl)
{
   cpu->_bit8(cpu->pMemory->read(cpu->regP.HL), 7);
   cpu->ticks += 4;
}

void CPU::_opCB_7F(CPU* cpu) // bit 7,a
{
   cpu->_bit8(cpu->regB.A, 7);
}

void CPU::_opCB_80(CPU* cpu) // res 0,b
{
   cpu->_res8(cpu->regB.B, 0);
}

void CPU::_opCB_81(CPU* cpu) // res 0,c
{
   cpu->_res8(cpu->regB.C, 0);
}

void CPU::_opCB_82(CPU* cpu) // res 0,d
{
   cpu->_res8(cpu->regB.D, 0);
}

void CPU::_opCB_83(CPU* cpu) // res 0,e
{
   cpu->_res8(cpu->regB.E, 0);
}

void CPU::_opCB_84(CPU* cpu) // res 0,h
{
   cpu->_res8(cpu->regB.H, 0);
}

void CPU::_opCB_85(CPU* cpu) // res 0,l
{
   cpu->_res8(cpu->regB.L, 0);
}

void CPU::_opCB_86(CPU* cpu) // res 0,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_res8(tmp, 0);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_87(CPU* cpu) // res 0,a
{
   cpu->_res8(cpu->regB.A, 0);
}

void CPU::_opCB_88(CPU* cpu) // res 1,b
{
   cpu->_res8(cpu->regB.B, 1);
}

void CPU::_opCB_89(CPU* cpu) // res 1,c
{
   cpu->_res8(cpu->regB.C, 1);
}

void CPU::_opCB_8A(CPU* cpu) // res 1,d
{
   cpu->_res8(cpu->regB.D, 1);
}

void CPU::_opCB_8B(CPU* cpu) // res 1,e
{
   cpu->_res8(cpu->regB.E, 1);
}

void CPU::_opCB_8C(CPU* cpu) // res 1,h
{
   cpu->_res8(cpu->regB.H, 1);
}

void CPU::_opCB_8D(CPU* cpu) // res 1,l
{
   cpu->_res8(cpu->regB.L, 1);
}

void CPU::_opCB_8E(CPU* cpu) // res 1,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_res8(tmp, 1);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_8F(CPU* cpu) // res 1,a
{
   cpu->_res8(cpu->regB.A, 1);
}

void CPU::_opCB_90(CPU* cpu) // res 2,b
{
   cpu->_res8(cpu->regB.B, 2);
}

void CPU::_opCB_91(CPU* cpu) // res 2,c
{
   cpu->_res8(cpu->regB.C, 2);
}

void CPU::_opCB_92(CPU* cpu) // res 2,d
{
   cpu->_res8(cpu->regB.D, 2);
}

void CPU::_opCB_93(CPU* cpu) // res 2,e
{
   cpu->_res8(cpu->regB.E, 2);
}

void CPU::_opCB_94(CPU* cpu) // res 2,h
{
   cpu->_res8(cpu->regB.H, 2);
}

void CPU::_opCB_95(CPU* cpu) // res 2,l
{
   cpu->_res8(cpu->regB.L, 2);
}

void CPU::_opCB_96(CPU* cpu) // res 2,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_res8(tmp, 2);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_97(CPU* cpu) // res 2,a
{
   cpu->_res8(cpu->regB.A, 2);
}

void CPU::_opCB_98(CPU* cpu) // res 3,b
{
   cpu->_res8(cpu->regB.B, 3);
}

void CPU::_opCB_99(CPU* cpu) // res 3,c
{
   cpu->_res8(cpu->regB.C, 3);
}

void CPU::_opCB_9A(CPU* cpu) // res 3,d
{
   cpu->_res8(cpu->regB.D, 3);
}

void CPU::_opCB_9B(CPU* cpu) // res 3,e
{
   cpu->_res8(cpu->regB.E, 3);
}

void CPU::_opCB_9C(CPU* cpu) // res 3,h
{
   cpu->_res8(cpu->regB.H, 3);
}

void CPU::_opCB_9D(CPU* cpu) // res 3,l
{
   cpu->_res8(cpu->regB.L, 3);
}

void CPU::_opCB_9E(CPU* cpu) // res 3,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_res8(tmp, 3);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_9F(CPU* cpu) // res 3,a
{
   cpu->_res8(cpu->regB.A, 3);
}

void CPU::_opCB_A0(CPU* cpu) // res 4,b
{
   cpu->_res8(cpu->regB.B, 4);
}

void CPU::_opCB_A1(CPU* cpu) // res 4,c
{
   cpu->_res8(cpu->regB.C, 4);
}

void CPU::_opCB_A2(CPU* cpu) // res 4,d
{
   cpu->_res8(cpu->regB.D, 4);
}

void CPU::_opCB_A3(CPU* cpu) // res 4,e
{
   cpu->_res8(cpu->regB.E, 4);
}

void CPU::_opCB_A4(CPU* cpu) // res 4,h
{
   cpu->_res8(cpu->regB.H, 4);
}

void CPU::_opCB_A5(CPU* cpu) // res 4,l
{
   cpu->_res8(cpu->regB.L, 4);
}

void CPU::_opCB_A6(CPU* cpu) // res 4,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_res8(tmp, 4);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_A7(CPU* cpu) // res 4,a
{
   cpu->_res8(cpu->regB.A, 4);
}

void CPU::_opCB_A8(CPU* cpu) // res 5,b
{
   cpu->_res8(cpu->regB.B, 5);
}

void CPU::_opCB_A9(CPU* cpu) // res 5,c
{
   cpu->_res8(cpu->regB.C, 5);
}

void CPU::_opCB_AA(CPU* cpu) // res 5,d
{
   cpu->_res8(cpu->regB.D, 5);
}

void CPU::_opCB_AB(CPU* cpu) // res 5,e
{
   cpu->_res8(cpu->regB.E, 5);
}

void CPU::_opCB_AC(CPU* cpu) // res 5,h
{
   cpu->_res8(cpu->regB.H, 5);
}

void CPU::_opCB_AD(CPU* cpu) // res 5,l
{
   cpu->_res8(cpu->regB.L, 5);
}

void CPU::_opCB_AE(CPU* cpu) // res 5,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_res8(tmp, 5);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_AF(CPU* cpu) // res 5,a
{
   cpu->_res8(cpu->regB.A, 5);
}

void CPU::_opCB_B0(CPU* cpu) // res 6,b
{
   cpu->_res8(cpu->regB.B, 6);
}

void CPU::_opCB_B1(CPU* cpu) // res 6,c
{
   cpu->_res8(cpu->regB.C, 6);
}

void CPU::_opCB_B2(CPU* cpu) // res 6,d
{
   cpu->_res8(cpu->regB.D, 6);
}

void CPU::_opCB_B3(CPU* cpu) // res 6,e
{
   cpu->_res8(cpu->regB.E, 6);
}

void CPU::_opCB_B4(CPU* cpu) // res 6,h
{
   cpu->_res8(cpu->regB.H, 6);
}

void CPU::_opCB_B5(CPU* cpu) // res 6,l
{
   cpu->_res8(cpu->regB.L, 6);
}

void CPU::_opCB_B6(CPU* cpu) // res 6,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_res8(tmp, 6);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_B7(CPU* cpu) // res 6,a
{
   cpu->_res8(cpu->regB.A, 6);
}

void CPU::_opCB_B8(CPU* cpu) // res 7,b
{
   cpu->_res8(cpu->regB.B, 7);
}

void CPU::_opCB_B9(CPU* cpu) // res 7,c
{
   cpu->_res8(cpu->regB.C, 7);
}

void CPU::_opCB_BA(CPU* cpu) // res 7,d
{
   cpu->_res8(cpu->regB.D, 7);
}

void CPU::_opCB_BB(CPU* cpu) // res 7,e
{
   cpu->_res8(cpu->regB.E, 7);
}

void CPU::_opCB_BC(CPU* cpu) // res 7,h
{
   cpu->_res8(cpu->regB.H, 7);
}

void CPU::_opCB_BD(CPU* cpu) // res 7,l
{
   cpu->_res8(cpu->regB.L, 7);
}

void CPU::_opCB_BE(CPU* cpu) // res 7,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_res8(tmp, 7);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_BF(CPU* cpu) // res 7,a
{
   cpu->_res8(cpu->regB.A, 7);
}

void CPU::_opCB_C0(CPU* cpu) // set 0,b
{
   cpu->_set8(cpu->regB.B, 0);
}

void CPU::_opCB_C1(CPU* cpu) // set 0,c
{
   cpu->_set8(cpu->regB.C, 0);
}

void CPU::_opCB_C2(CPU* cpu) // set 0,d
{
   cpu->_set8(cpu->regB.D, 0);
}

void CPU::_opCB_C3(CPU* cpu) // set 0,e
{
   cpu->_set8(cpu->regB.E, 0);
}

void CPU::_opCB_C4(CPU* cpu) // set 0,h
{
   cpu->_set8(cpu->regB.H, 0);
}

void CPU::_opCB_C5(CPU* cpu) // set 0,l
{
   cpu->_set8(cpu->regB.L, 0);
}

void CPU::_opCB_C6(CPU* cpu) // set 0,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_set8(tmp, 0);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_C7(CPU* cpu) // set 0,a
{
   cpu->_set8(cpu->regB.A, 0);
}

void CPU::_opCB_C8(CPU* cpu) // set 1,b
{
   cpu->_set8(cpu->regB.B, 1);
}

void CPU::_opCB_C9(CPU* cpu) // set 1,c
{
   cpu->_set8(cpu->regB.C, 1);
}

void CPU::_opCB_CA(CPU* cpu) // set 1,d
{
   cpu->_set8(cpu->regB.D, 1);
}

void CPU::_opCB_CB(CPU* cpu) // set 1,e
{
   cpu->_set8(cpu->regB.E, 1);
}

void CPU::_opCB_CC(CPU* cpu) // set 1,h
{
   cpu->_set8(cpu->regB.H, 1);
}

void CPU::_opCB_CD(CPU* cpu) // set 1,l
{
   cpu->_set8(cpu->regB.L, 1);
}

void CPU::_opCB_CE(CPU* cpu) // set 1,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_set8(tmp, 1);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_CF(CPU* cpu) // set 1,a
{
   cpu->_set8(cpu->regB.A, 1);
}

void CPU::_opCB_D0(CPU* cpu) // set 2,b
{
   cpu->_set8(cpu->regB.B, 2);
}

void CPU::_opCB_D1(CPU* cpu) // set 2,c
{
   cpu->_set8(cpu->regB.C, 2);
}

void CPU::_opCB_D2(CPU* cpu) // set 2,d
{
   cpu->_set8(cpu->regB.D, 2);
}

void CPU::_opCB_D3(CPU* cpu) // set 2,e
{
   cpu->_set8(cpu->regB.E, 2);
}

void CPU::_opCB_D4(CPU* cpu) // set 2,h
{
   cpu->_set8(cpu->regB.H, 2);
}

void CPU::_opCB_D5(CPU* cpu) // set 2,l
{
   cpu->_set8(cpu->regB.L, 2);
}

void CPU::_opCB_D6(CPU* cpu) // set 2,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_set8(tmp, 2);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_D7(CPU* cpu) // set 2,a
{
   cpu->_set8(cpu->regB.A, 2);
}

void CPU::_opCB_D8(CPU* cpu) // set 3,b
{
   cpu->_set8(cpu->regB.B, 3);
}

void CPU::_opCB_D9(CPU* cpu) // set 3,c
{
   cpu->_set8(cpu->regB.C, 3);
}

void CPU::_opCB_DA(CPU* cpu) // set 3,d
{
   cpu->_set8(cpu->regB.D, 3);
}

void CPU::_opCB_DB(CPU* cpu) // set 3,e
{
   cpu->_set8(cpu->regB.E, 3);
}

void CPU::_opCB_DC(CPU* cpu) // set 3,h
{
   cpu->_set8(cpu->regB.H, 3);
}

void CPU::_opCB_DD(CPU* cpu) // set 3,l
{
   cpu->_set8(cpu->regB.L, 3);
}

void CPU::_opCB_DE(CPU* cpu) // set 3,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_set8(tmp, 3);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_DF(CPU* cpu) // set 3,a
{
   cpu->_set8(cpu->regB.A, 3);
}

void CPU::_opCB_E0(CPU* cpu) // set 4,b
{
   cpu->_set8(cpu->regB.B, 4);
}

void CPU::_opCB_E1(CPU* cpu) // set 4,c
{
   cpu->_set8(cpu->regB.C, 4);
}

void CPU::_opCB_E2(CPU* cpu) // set 4,d
{
   cpu->_set8(cpu->regB.D, 4);
}

void CPU::_opCB_E3(CPU* cpu) // set 4,e
{
   cpu->_set8(cpu->regB.E, 4);
}

void CPU::_opCB_E4(CPU* cpu) // set 4,h
{
   cpu->_set8(cpu->regB.H, 4);
}

void CPU::_opCB_E5(CPU* cpu) // set 4,l
{
   cpu->_set8(cpu->regB.L, 4);
}

void CPU::_opCB_E6(CPU* cpu) // set 4,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_set8(tmp, 4);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_E7(CPU* cpu) // set 4,a
{
   cpu->_set8(cpu->regB.A, 4);
}

void CPU::_opCB_E8(CPU* cpu) // set 5,b
{
   cpu->_set8(cpu->regB.B, 5);
}

void CPU::_opCB_E9(CPU* cpu) // set 5,c
{
   cpu->_set8(cpu->regB.C, 5);
}

void CPU::_opCB_EA(CPU* cpu) // set 5,d
{
   cpu->_set8(cpu->regB.D, 5);
}

void CPU::_opCB_EB(CPU* cpu) // set 5,e
{
   cpu->_set8(cpu->regB.E, 5);
}

void CPU::_opCB_EC(CPU* cpu) // set 5,h
{
   cpu->_set8(cpu->regB.H, 5);
}

void CPU::_opCB_ED(CPU* cpu) // set 5,l
{
   cpu->_set8(cpu->regB.L, 5);
}

void CPU::_opCB_EE(CPU* cpu) // set 5,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_set8(tmp, 5);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_EF(CPU* cpu) // set 5,a
{
   cpu->_set8(cpu->regB.A, 5);
}

void CPU::_opCB_F0(CPU* cpu) // set 6,b
{
   cpu->_set8(cpu->regB.B, 6);
}

void CPU::_opCB_F1(CPU* cpu) // set 6,c
{
   cpu->_set8(cpu->regB.C, 6);
}

void CPU::_opCB_F2(CPU* cpu) // set 6,d
{
   cpu->_set8(cpu->regB.D, 6);
}

void CPU::_opCB_F3(CPU* cpu) // set 6,e
{
   cpu->_set8(cpu->regB.E, 6);
}

void CPU::_opCB_F4(CPU* cpu) // set 6,h
{
   cpu->_set8(cpu->regB.H, 6);
}

void CPU::_opCB_F5(CPU* cpu) // set 6,l
{
   cpu->_set8(cpu->regB.L, 6);
}

void CPU::_opCB_F6(CPU* cpu) // set 6,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_set8(tmp, 6);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_F7(CPU* cpu) // set 6,a
{
   cpu->_set8(cpu->regB.A, 6);
}

void CPU::_opCB_F8(CPU* cpu) // set 7,b
{
   cpu->_set8(cpu->regB.B, 7);
}

void CPU::_opCB_F9(CPU* cpu) // set 7,c
{
   cpu->_set8(cpu->regB.C, 7);
}

void CPU::_opCB_FA(CPU* cpu) // set 7,d
{
   cpu->_set8(cpu->regB.D, 7);
}

void CPU::_opCB_FB(CPU* cpu) // set 7,e
{
   cpu->_set8(cpu->regB.E, 7);
}

void CPU::_opCB_FC(CPU* cpu) // set 7,h
{
   cpu->_set8(cpu->regB.H, 7);
}

void CPU::_opCB_FD(CPU* cpu) // set 7,l
{
   cpu->_set8(cpu->regB.L, 7);
}

void CPU::_opCB_FE(CPU* cpu) // set 7,(hl)
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->_set8(tmp, 7);
   cpu->pMemory->write(cpu->regP.HL, tmp);
   cpu->ticks += 4;
}

void CPU::_opCB_FF(CPU* cpu) // set 7,a
{
   cpu->_set8(cpu->regB.A, 7);
}

CPUFUNC const CPU::pOpsED[0x100] = {
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,

   _opED_40, _opED_41, _opED_42, _opED_43, _opED_44, _opED_45, _opED_46, _opED_47,
   _opED_48, _opED_49, _opED_4A, _opED_4B, _opED_44, _opED_4D, _opED_56, _opED_4F,
   _opED_50, _opED_51, _opED_52, _opED_53, _opED_44, _opED_45, _opED_56, _opED_57,
   _opED_58, _opED_59, _opED_5A, _opED_5B, _opED_44, _opED_4D, _opED_5E, _opED_5F,
   _opED_60, _opED_61, _opED_62, _op_22, _opED_44, _opED_45, _opED_46, _opED_67,
   _opED_68, _opED_69, _opED_6A, _op_2A, _opED_44, _opED_4D, _opED_56, _opED_6F,
   _opED_70, _opED_71, _opED_72, _opED_73, _opED_44, _opED_45, _opED_76, _op_00,
   _opED_78, _opED_79, _opED_7A, _opED_7B, _opED_44, _opED_4D, _opED_5E, _op_00,

   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _opED_A0, _opED_A1, _opED_A2, _opED_A3, _op_00, _op_00, _op_00, _op_00,
   _opED_A8, _opED_A9, _opED_AA, _opED_AB, _op_00, _op_00, _op_00, _op_00,
   _opED_B0, _opED_B1, _opED_B2, _opED_B3, _op_00, _op_00, _op_00, _op_00,
   _opED_B8, _opED_B9, _opED_BA, _opED_BB, _op_00, _op_00, _op_00, _op_00,

   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00, _op_00,
   _op_00, _op_00, _op_00, _op_00, _opExtBreakpoint, _opExtCaps, _opExtIntTicks, _opExtTotalTicks
};

void CPU::_opED_40(CPU* cpu) // in b,(c)
{
   cpu->ticks += 4;
   cpu->regB.B = cpu->pManager->inByte(cpu->regP.BC);
   cpu->regB.F = pLogF[cpu->regB.B] | (cpu->regB.F & CF);
}

void CPU::_opED_41(CPU* cpu) // out (c),b
{
   cpu->ticks += 4;
   cpu->pManager->outByte(cpu->regP.BC, cpu->regB.B);
}

void CPU::_opED_42(CPU* cpu) // sbc hl,bc
{
   BYTE fl = NF;
   fl |= (((cpu->regP.HL & 0x0FFF) - (cpu->regP.BC & 0x0FFF) - (cpu->regP.AF & CF)) >> 8) & 0x10; /* HF */
   unsigned tmp = cpu->regP.HL - cpu->regP.BC - (cpu->regP.AF & CF);
   if (tmp & 0x10000) fl |= CF;
   if (!(tmp & 0xFFFF)) fl |= ZF;
   int ri = (int)(short)cpu->regP.HL - (int)(short)cpu->regP.BC - (int)(cpu->regP.AF & CF);
   if (ri < -0x8000 || ri >= 0x8000) fl |= PV;
   cpu->regP.HL = tmp;
   cpu->regB.F = fl | (cpu->regB.H & (F3 | F5 | SF));
   cpu->ticks += 7;
}

void CPU::_opED_43(CPU* cpu) // ld (nnnn),bc
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->pMemory->write(adr++, cpu->regB.C);
   cpu->pMemory->write(adr, cpu->regB.B);
   cpu->ticks += 12;
}

void CPU::_opED_44(CPU* cpu) // neg
{
   cpu->regB.F = pSBCF[cpu->regB.A];
   cpu->regB.A = -cpu->regB.A;
}

void CPU::_opED_45(CPU* cpu) // retn
{
   cpu->iff1 = cpu->iff2;
   cpu->_pop(cpu->regP.PC);
   cpu->ticks += 6;
}

void CPU::_opED_46(CPU* cpu) // im 0
{
   cpu->im = 0;
}

void CPU::_opED_47(CPU* cpu) // ld i,a
{
   cpu->I = cpu->regB.A;
   cpu->ticks++;
}

void CPU::_opED_48(CPU* cpu) // in c,(c)
{
   cpu->ticks += 4;
   cpu->regB.C = cpu->pManager->inByte(cpu->regP.BC);
   cpu->regB.F = pLogF[cpu->regB.C] | (cpu->regB.F & CF);
}

void CPU::_opED_49(CPU* cpu) // out (c),c
{
   cpu->ticks += 4;
   cpu->pManager->outByte(cpu->regP.BC, cpu->regB.C);
}

void CPU::_opED_4A(CPU* cpu) // adc hl,bc
{
   BYTE fl = (((cpu->regP.HL & 0x0FFF) + (cpu->regP.BC & 0x0FFF) + (cpu->regP.AF & CF)) >> 8) & 0x10; /* HF */
   unsigned tmp = cpu->regP.HL + cpu->regP.BC + (cpu->regP.AF & CF);
   if (tmp & 0x10000) fl |= CF;
   if (! (tmp & 0xFFFF)) fl |= ZF;
   int ri = (int)(short)cpu->regP.HL + (int)(short)cpu->regP.BC + (int)(cpu->regP.AF & CF);
   if (ri < -0x8000 || ri >= 0x8000) fl |= PV;
   cpu->regP.HL = tmp;
   cpu->regB.F = fl | (cpu->regB.H & (F3 | F5 | SF));
   cpu->ticks += 7;
}

void CPU::_opED_4B(CPU* cpu) // ld bc,(nnnn)
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->regB.C = cpu->pMemory->read(adr++);
   cpu->regB.B = cpu->pMemory->read(adr);
   cpu->ticks += 12;
}

void CPU::_opED_4D(CPU* cpu) // reti
{
   cpu->iff1 = cpu->iff2;
   cpu->_pop(cpu->regP.PC);
   cpu->ticks += 6;
}

void CPU::_opED_4F(CPU* cpu) // ld r,a
{
   cpu->R = cpu->regB.A;
   cpu->R_h = cpu->regB.A & 0x80;
   cpu->ticks++;
}

void CPU::_opED_50(CPU* cpu) // in d,(c)
{
   cpu->ticks += 4;
   cpu->regB.D = cpu->pManager->inByte(cpu->regP.BC);
   cpu->regB.F = pLogF[cpu->regB.D] | (cpu->regB.F & CF);
}

void CPU::_opED_51(CPU* cpu) // out (c),d
{
   cpu->ticks += 4;
   cpu->pManager->outByte(cpu->regP.BC, cpu->regB.D);
}

void CPU::_opED_52(CPU* cpu) // sbc hl,de
{
   BYTE fl = NF;
   fl |= (((cpu->regP.HL & 0x0FFF) - (cpu->regP.DE & 0x0FFF) - (cpu->regP.AF & CF)) >> 8) & 0x10; /* HF */
   unsigned tmp = cpu->regP.HL - cpu->regP.DE - (cpu->regP.AF & CF);
   if (tmp & 0x10000) fl |= CF;
   if (!(tmp & 0xFFFF)) fl |= ZF;
   int ri = (int)(short)cpu->regP.HL - (int)(short)cpu->regP.DE - (int)(cpu->regP.AF & CF);
   if (ri < -0x8000 || ri >= 0x8000) fl |= PV;
   cpu->regP.HL = tmp;
   cpu->regB.F = fl | (cpu->regB.H & (F3 | F5 | SF));
   cpu->ticks += 7;
}

void CPU::_opED_53(CPU* cpu) // ld (nnnn),de
{
   unsigned adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->pMemory->write(adr++, cpu->regB.E);
   cpu->pMemory->write(adr, cpu->regB.D);
   cpu->ticks += 12;
}

void CPU::_opED_56(CPU* cpu) // im 1
{
   cpu->im = 1;
}

void CPU::_opED_57(CPU* cpu) // ld a,i
{
   cpu->regB.A = cpu->I;
   cpu->regB.F = (pLogF[cpu->regB.A] | (cpu->regB.F & CF)) & ~PV;
   if (cpu->iff1 && (cpu->ticks + 10 < Configure::ULATicksPerFrame)) cpu->regB.F |= PV;
   cpu->ticks++;
}

void CPU::_opED_58(CPU* cpu) // in e,(c)
{
   cpu->ticks += 4;
   cpu->regB.E = cpu->pManager->inByte(cpu->regP.BC);
   cpu->regB.F = pLogF[cpu->regB.E] | (cpu->regB.F & CF);
}

void CPU::_opED_59(CPU* cpu) // out (c),e
{
   cpu->ticks += 4;
   cpu->pManager->outByte(cpu->regP.BC, cpu->regB.E);
}


void CPU::_opED_5A(CPU* cpu) // adc hl,de
{
   BYTE fl = (((cpu->regP.HL & 0x0FFF) + (cpu->regP.DE & 0x0FFF) + (cpu->regP.AF & CF)) >> 8) & 0x10; /* HF */
   unsigned tmp = cpu->regP.HL + cpu->regP.DE + (cpu->regP.AF & CF);
   if (tmp & 0x10000) fl |= CF;
   if (!(tmp & 0xFFFF)) fl |= ZF;
   int ri = (int)(short)cpu->regP.HL + (int)(short)cpu->regP.DE + (int)(cpu->regP.AF & CF);
   if (ri < -0x8000 || ri >= 0x8000) fl |= PV;
   cpu->regP.HL = tmp;
   cpu->regB.F = fl | (cpu->regB.H & (F3|F5|SF));
   cpu->ticks += 7;
}

void CPU::_opED_5B(CPU* cpu) // ld de,(nnnn)
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + (cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->regB.E = cpu->pMemory->read(adr++);
   cpu->regB.D = cpu->pMemory->read(adr);
   cpu->ticks += 12;
}

void CPU::_opED_5E(CPU* cpu) // im 2
{
   cpu->im = 2;
}

void CPU::_opED_5F(CPU* cpu) // ld a,r
{
   cpu->regB.A = (cpu->R & 0x7F) | cpu->R_h;
   cpu->regB.F = (pLogF[cpu->regB.A] | (cpu->regB.F & CF)) & ~PV;
   if (cpu->iff2 && ((cpu->ticks + 10 < Configure::ULATicksPerFrame) || cpu->eipos + 8 == cpu->ticks)) cpu->regB.F |= PV;
   cpu->ticks++;
}

void CPU::_opED_60(CPU* cpu) // in h,(c)
{
   cpu->ticks += 4;
   cpu->regB.H = cpu->pManager->inByte(cpu->regP.BC);
   cpu->regB.F = pLogF[cpu->regB.H] | (cpu->regB.F & CF);
}

void CPU::_opED_61(CPU* cpu) // out (c),h
{
   cpu->ticks += 4;
   cpu->pManager->outByte(cpu->regP.BC, cpu->regB.H);
}


void CPU::_opED_62(CPU* cpu) // sbc hl,hl
{
   BYTE fl = NF;
   fl |= (cpu->regB.F & CF) << 4; /* HF - copy from CF */
   unsigned tmp = 0 - (cpu->regP.AF & CF);
   if (tmp & 0x10000) fl |= CF;
   if (!(tmp & 0xFFFF)) fl |= ZF;
   // never set PV
   cpu->regP.HL = tmp;
   cpu->regB.F = fl | (cpu->regB.H & (F3 | F5 | SF));
   cpu->ticks += 7;
}

void CPU::_opED_67(CPU* cpu) // rrd
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->pMemory->write(cpu->regP.HL, (cpu->regB.A << 4) | (tmp >> 4));
   cpu->regB.A = (cpu->regB.A & 0xF0) | (tmp & 0x0F);
   cpu->regB.F = pLogF[cpu->regB.A] | (cpu->regB.F & CF);
   cpu->ticks += 10;
}

void CPU::_opED_68(CPU* cpu) // in l,(c)
{
   cpu->ticks += 4;
   cpu->regB.L = cpu->pManager->inByte(cpu->regP.BC);
   cpu->regB.F = pLogF[cpu->regB.L] | (cpu->regB.F & CF);
}

void CPU::_opED_69(CPU* cpu) // out (c),l
{
   cpu->ticks += 4;
   cpu->pManager->outByte(cpu->regP.BC, cpu->regB.L);
}

void CPU::_opED_6A(CPU* cpu) // adc hl,hl
{
   BYTE fl = ((cpu->regB.H << 1) & 0x10); /* HF */
   unsigned tmp = ((DWORD)cpu->regP.HL) * 2 + (cpu->regP.AF & CF);
   if (tmp & 0x10000) fl |= CF;
   if (!(tmp & 0xFFFF)) fl |= ZF;
   int ri = 2 * (int)(short)cpu->regP.HL + (int)(cpu->regP.AF & CF);
   if (ri < -0x8000 || ri >= 0x8000) fl |= PV;
   cpu->regP.HL = tmp;
   cpu->regB.F = fl | (cpu->regB.H & (F3 | F5 | SF));
   cpu->ticks += 7;
}

void CPU::_opED_6F(CPU* cpu) // rld
{
   BYTE tmp = cpu->pMemory->read(cpu->regP.HL);
   cpu->pMemory->write(cpu->regP.HL, (cpu->regB.A & 0x0F) | (tmp << 4));
   cpu->regB.A = (cpu->regB.A & 0xF0) | (tmp >> 4);
   cpu->regB.F = pLogF[cpu->regB.A] | (cpu->regB.F & CF);
   cpu->ticks += 10;
}

void CPU::_opED_70(CPU* cpu) // in (c)
{
   cpu->ticks += 4;
   cpu->regB.F = pLogF[cpu->pManager->inByte(cpu->regP.BC)] | (cpu->regB.F & CF);
}

void CPU::_opED_71(CPU* cpu) // out (c),0
{
   cpu->ticks += 4;
   cpu->pManager->outByte(cpu->regP.BC, 0);
}

void CPU::_opED_72(CPU* cpu) // sbc hl,sp
{
   BYTE fl = NF;
   fl |= (((cpu->regP.HL & 0x0FFF) - (cpu->regP.SP & 0x0FFF) - (cpu->regP.AF & CF)) >> 8) & 0x10; /* HF */
   unsigned tmp = cpu->regP.HL - cpu->regP.SP - (cpu->regP.AF & CF);
   if (tmp & 0x10000) fl |= CF;
   if (!(tmp & 0xFFFF)) fl |= ZF;
   int ri = (int)(short)cpu->regP.HL - (int)(short)cpu->regP.SP - (int)(cpu->regP.AF & CF);
   if (ri < -0x8000 || ri >= 0x8000) fl |= PV;
   cpu->regP.HL = tmp;
   cpu->regB.F = fl | (cpu->regB.H & (F3|F5|SF));
   cpu->ticks += 7;
}

void CPU::_opED_73(CPU* cpu) // ld (nnnn),sp
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->pMemory->write(adr++, cpu->regB.SPl);
   cpu->pMemory->write(adr, cpu->regB.SPh);
   cpu->ticks += 12;
}

void CPU::_opED_76(CPU* cpu) // im 1
{
   cpu->im = 1;
}

void CPU::_opED_78(CPU* cpu) // in a,(c)
{
   cpu->ticks += 4;
   cpu->regB.A = cpu->pManager->inByte(cpu->regP.BC);
   cpu->regB.F = pLogF[cpu->regB.A] | (cpu->regB.F & CF);
}

void CPU::_opED_79(CPU* cpu) // out (c),a
{
   cpu->ticks += 4;
   cpu->pManager->outByte(cpu->regP.BC, cpu->regB.A);
}

void CPU::_opED_7A(CPU* cpu) // adc hl,sp
{
   BYTE fl = (((cpu->regP.HL & 0x0FFF) + (cpu->regP.SP & 0x0FFF) + (cpu->regP.AF & CF)) >> 8) & 0x10; /* HF */
   unsigned tmp = cpu->regP.HL + cpu->regP.SP + (cpu->regP.AF & CF);
   if (tmp & 0x10000) fl |= CF;
   if (!(unsigned short)tmp) fl |= ZF;
   int ri = (int)(short)cpu->regP.HL + (int)(short)cpu->regP.SP + (int)(cpu->regP.AF & CF);
   if (ri < -0x8000 || ri >= 0x8000) fl |= PV;
   cpu->regP.HL = tmp;
   cpu->regB.F = fl | (cpu->regB.H & (F3|F5|SF));
   cpu->ticks += 7;
}

void CPU::_opED_7B(CPU* cpu) // ld sp,(nnnn)
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->regB.SPl = cpu->pMemory->read(adr++);
   cpu->regB.SPh = cpu->pMemory->read(adr);
   cpu->ticks += 12;
}

void CPU::_opED_A0(CPU* cpu) // ldi
{
   cpu->ticks += 8;
   cpu->pMemory->write(cpu->regP.DE++, cpu->pMemory->read(cpu->regP.HL++));
   cpu->regB.F &= ~(NF|HF|PV);
   if (--cpu->regP.BC) cpu->regB.F |= PV;
}

void CPU::_opED_A1(CPU* cpu) // cpi
{
   cpu->ticks += 8;
   BYTE cf = cpu->regB.F & CF;
   cpu->_cpr8(cpu->pMemory->read(cpu->regP.HL++));
   cpu->regB.F = (cpu->regB.F & ~(CF|PV)) | cf;
   if (--cpu->regP.BC) cpu->regB.F |= PV;
}

void CPU::_opED_A2(CPU* cpu) // ini
{
   cpu->ticks += 8;
   cpu->pMemory->write(cpu->regP.HL++, cpu->pManager->inByte(cpu->regP.BC));
   cpu->_dec8(cpu->regB.B);
}

void CPU::_opED_A3(CPU* cpu) // outi
{
   cpu->ticks += 8;
   cpu->_dec8(cpu->regB.B);
   cpu->pManager->outByte(cpu->regP.BC, cpu->pMemory->read(cpu->regP.HL++));
   cpu->regB.F &= ~CF;
   if (! cpu->regB.L) cpu->regB.F |= CF;
}

void CPU::_opED_A8(CPU* cpu) // ldd
{
   cpu->ticks += 8;
   cpu->pMemory->write(cpu->regP.DE--, cpu->pMemory->read(cpu->regP.HL--));
   cpu->regB.F &= ~(NF|HF|PV);
   if (--cpu->regP.BC) cpu->regB.F |= PV;
}

void CPU::_opED_A9(CPU* cpu) // cpd
{
   cpu->ticks += 8;
   BYTE cf = cpu->regB.F & CF;
   cpu->_cpr8(cpu->pMemory->read(cpu->regP.HL--));
   cpu->regB.F = (cpu->regB.F & ~(CF|PV)) | cf;
   if (--cpu->regP.BC) cpu->regB.F |= PV;
}

void CPU::_opED_AA(CPU* cpu) // ind
{
   cpu->ticks += 8;
   cpu->pMemory->write(cpu->regP.HL--, cpu->pManager->inByte(cpu->regP.BC));
   cpu->_dec8(cpu->regB.B);
}

void CPU::_opED_AB(CPU* cpu) // outd
{
   cpu->ticks += 8;
   cpu->_dec8(cpu->regB.B);
   cpu->pManager->outByte(cpu->regP.BC, cpu->pMemory->read(cpu->regP.HL--));
   cpu->regB.F &= ~CF;
   if (cpu->regB.L == 0xFF) cpu->regB.F |= CF;
}

void CPU::_opED_B0(CPU* cpu) // ldir
{
   cpu->ticks += 8;
   cpu->pMemory->write(cpu->regP.DE++, cpu->pMemory->read(cpu->regP.HL++));
   cpu->regB.F &= ~(NF|HF|PV);
   if (--cpu->regP.BC)
   {
       cpu->regB.F |= PV;
       cpu->regP.PC -= 2;
       cpu->ticks += 5;
   }
}

void CPU::_opED_B1(CPU* cpu) // cpir
{
   cpu->ticks += 8;
   BYTE cf = cpu->regB.F & CF;
   cpu->_cpr8(cpu->pMemory->read(cpu->regP.HL++));
   cpu->regB.F = (cpu->regB.F & ~(CF|PV)) | cf;
   if (--cpu->regP.BC)
   {
      cpu->regB.F |= PV;
      if (! (cpu->regB.F & ZF))
      {
          cpu->regP.PC -= 2;
          cpu->ticks += 5;
      }
   }
}

void CPU::_opED_B2(CPU* cpu) // inir
{
   cpu->ticks += 8;
   cpu->pMemory->write(cpu->regP.HL++, cpu->pManager->inByte(cpu->regP.BC));
   cpu->_dec8(cpu->regB.B);
   if (cpu->regB.B)
   {
       cpu->regB.F |= PV;
       cpu->regP.PC -= 2;
       cpu->ticks += 5;
   }
   else
       cpu->regB.F &= ~PV;
}

void CPU::_opED_B3(CPU* cpu) // otir
{
   cpu->ticks += 8;
   cpu->_dec8(cpu->regB.B);
   cpu->pManager->outByte(cpu->regP.BC, cpu->pMemory->read(cpu->regP.HL++));
   if (cpu->regB.B)
   {
       cpu->regB.F |= PV;
       cpu->regP.PC -= 2;
       cpu->ticks += 5;
   }
   else
       cpu->regB.F &= ~PV;
   cpu->regB.F &= ~CF;
   if (! cpu->regB.L) cpu->regB.F |= CF;
}

void CPU::_opED_B8(CPU* cpu) // lddr
{
   cpu->ticks += 8;
   cpu->pMemory->write(cpu->regP.DE--, cpu->pMemory->read(cpu->regP.HL--));
   cpu->regB.F &= ~(NF|HF|PV);
   if (--cpu->regP.BC)
   {
       cpu->regB.F |= PV;
       cpu->regP.PC -= 2;
       cpu->ticks += 5;
   }
   else
       cpu->regB.F &= ~PV;
}

void CPU::_opED_B9(CPU* cpu) // cpdr
{
   cpu->ticks += 8;
   BYTE cf = cpu->regB.F & CF;
   cpu->_cpr8(cpu->pMemory->read(cpu->regP.HL--));
   cpu->regB.F = (cpu->regB.F & ~(CF|PV)) | cf;
   if (--cpu->regP.BC)
   {
      cpu->regB.F |= PV;
      if (! (cpu->regB.F & ZF))
      {
          cpu->regP.PC -= 2;
          cpu->ticks += 5;
      }
   }
}

void CPU::_opED_BA(CPU* cpu) // indr
{
   cpu->ticks += 8;
   cpu->pMemory->write(cpu->regP.HL--, cpu->pManager->inByte(cpu->regP.BC));
   cpu->_dec8(cpu->regB.B);
   if (cpu->regB.B)
   {
       cpu->regB.F |= PV;
       cpu->regP.PC -= 2;
       cpu->ticks += 5;
   }
   else
       cpu->regB.F &= ~PV;
}

void CPU::_opED_BB(CPU* cpu) // otdr
{
   cpu->ticks += 8;
   cpu->_dec8(cpu->regB.B);
   cpu->pManager->outByte(cpu->regP.BC, cpu->pMemory->read(cpu->regP.HL--));
   if (cpu->regB.B)
   {
       cpu->regB.F |= PV;
       cpu->regP.PC -= 2;
       cpu->ticks += 5;
   }
   else
       cpu->regB.F &= ~PV;
   cpu->regB.F &= ~CF;
   if (cpu->regB.L == 0xFF) cpu->regB.F |= CF;
}

CPUFUNC const CPU::pOpsDD[0x100] = {
   _op_00, _op_01,   _op_02,   _op_03,   _op_04,   _op_05,   _op_06,   _op_07,
   _op_08, _opDD_09, _op_0A,   _op_0B,   _op_0C,   _op_0D,   _op_0E,   _op_0F,
   _op_10, _op_11,   _op_12,   _op_13,   _op_14,   _op_15,   _op_16,   _op_17,
   _op_18, _opDD_19, _op_1A,   _op_1B,   _op_1C,   _op_1D,   _op_1E,   _op_1F,
   _op_20, _opDD_21, _opDD_22, _opDD_23, _opDD_24, _opDD_25, _opDD_26, _op_27,
   _op_28, _opDD_29, _opDD_2A, _opDD_2B, _opDD_2C, _opDD_2D, _opDD_2E, _op_2F,
   _op_30, _op_31,   _op_32,   _op_33,   _opDD_34, _opDD_35, _opDD_36, _op_37,
   _op_38, _opDD_39, _op_3A,   _op_3B,   _op_3C,   _op_3D,   _op_3E,   _op_3F,

   _op_00, _op_41, _op_42, _op_43, _opDD_44, _opDD_45, _opDD_46, _op_47,
   _op_48, _op_00, _op_4A, _op_4B, _opDD_4C, _opDD_4D, _opDD_4E, _op_4F,
   _op_50, _op_51, _op_00, _op_53, _opDD_54, _opDD_55, _opDD_56, _op_57,
   _op_58, _op_59, _op_5A, _op_00, _opDD_5C, _opDD_5D, _opDD_5E, _op_5F,
   _opDD_60, _opDD_61, _opDD_62, _opDD_63, _op_00,   _opDD_65, _opDD_66, _opDD_67,
   _opDD_68, _opDD_69, _opDD_6A, _opDD_6B, _opDD_6C, _op_00,   _opDD_6E, _opDD_6F,
   _opDD_70, _opDD_71, _opDD_72, _opDD_73, _opDD_74, _opDD_75, _op_76,   _opDD_77,
   _op_78,   _op_79,   _op_7A,   _op_7B,   _opDD_7C, _opDD_7D, _opDD_7E, _op_00,

   _op_80, _op_81, _op_82, _op_83, _opDD_84, _opDD_85, _opDD_86, _op_87,
   _op_88, _op_89, _op_8A, _op_8B, _opDD_8C, _opDD_8D, _opDD_8E, _op_8F,
   _op_90, _op_91, _op_92, _op_93, _opDD_94, _opDD_95, _opDD_96, _op_97,
   _op_98, _op_99, _op_9A, _op_9B, _opDD_9C, _opDD_9D, _opDD_9E, _op_9F,
   _op_A0, _op_A1, _op_A2, _op_A3, _opDD_A4, _opDD_A5, _opDD_A6, _op_A7,
   _op_A8, _op_A9, _op_AA, _op_AB, _opDD_AC, _opDD_AD, _opDD_AE, _op_AF,
   _op_B0, _op_B1, _op_B2, _op_B3, _opDD_B4, _opDD_B5, _opDD_B6, _op_B7,
   _op_B8, _op_B9, _op_BA, _op_BB, _opDD_BC, _opDD_BD, _opDD_BE, _op_BF,

   _op_C0, _op_C1, _op_C2, _op_C3, _op_C4, _op_C5, _op_C6, _op_C7,
   _op_C8, _op_C9, _op_CA, _op_CB, _op_CC, _op_CD, _op_CE, _op_CF,
   _op_D0, _op_D1, _op_D2, _op_D3, _op_D4, _op_D5, _op_D6, _op_D7,
   _op_D8, _op_D9, _op_DA, _op_DB, _op_DC, _op_DD, _op_DE, _op_DF,
   _op_E0, _opDD_E1, _op_E2, _opDD_E3, _op_E4, _opDD_E5, _op_E6, _op_E7,
   _op_E8, _opDD_E9, _op_EA, _op_EB,   _op_EC, _op_ED,   _op_EE, _op_EF,
   _op_F0, _op_F1,   _op_F2, _op_F3,   _op_F4, _op_F5,   _op_F6, _op_F7,
   _op_F8, _opDD_F9, _op_FA, _op_FB,   _op_FC, _op_FD,   _op_FE, _op_FF,
};

void CPU::_opDD_09(CPU* cpu) // add ix,bc
{
   WORD tmp = cpu->regP.IX;
   cpu->regB.F = (cpu->regB.F & ~(NF | CF | F5 | F3 | HF));
   cpu->regB.F |= (((cpu->regP.IX & 0x0FFF) + (cpu->regP.BC & 0x0FFF)) >> 8) & 0x10; /* HF */
   cpu->regP.IX += cpu->regP.BC;
   if (cpu->regP.IX < tmp) cpu->regB.F |= CF;
   cpu->regB.F |= (cpu->regB.HX & (F5 | F3));
   cpu->ticks += 7;
}

void CPU::_opDD_19(CPU* cpu) // add ix,de
{
   WORD tmp = cpu->regP.IX;
   cpu->regB.F = (cpu->regB.F & ~(NF | CF | F5 | F3 | HF));
   cpu->regB.F |= (((cpu->regP.IX & 0x0FFF) + (cpu->regP.DE & 0x0FFF)) >> 8) & 0x10; /* HF */
   cpu->regP.IX += cpu->regP.DE;
   if (cpu->regP.IX < tmp) cpu->regB.F |= CF;
   cpu->regB.F |= (cpu->regB.HX & (F5 | F3));
   cpu->ticks += 7;
}

void CPU::_opDD_21(CPU* cpu) // ld ix,nnnn
{
   cpu->regB.LX = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.HX = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 6;
}

void CPU::_opDD_22(CPU* cpu) // ld (nnnn),ix
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->pMemory->write(adr++, cpu->regB.LX);
   cpu->pMemory->write(adr, cpu->regB.HX);
   cpu->ticks += 12;
}

void CPU::_opDD_23(CPU* cpu) // inc ix
{
   cpu->regP.IX++;
   cpu->ticks += 2;
}

void CPU::_opDD_24(CPU* cpu) // inc xh
{
   cpu->_inc8(cpu->regB.HX);
}

void CPU::_opDD_25(CPU* cpu) // dec xh
{
   cpu->_dec8(cpu->regB.HX);
}

void CPU::_opDD_26(CPU* cpu) // ld xh,nn
{
   cpu->regB.HX = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 3;
}

void CPU::_opDD_29(CPU* cpu) // add ix,ix
{
   WORD tmp = cpu->regP.IX;
   cpu->regB.F = (cpu->regB.F & ~(NF | CF | F5 | F3 | HF));
   cpu->regB.F |= ((cpu->regB.HX <<= 1) & 0x10); /* HF */
   if (cpu->regP.IX < tmp) cpu->regB.F |= CF;
   cpu->regB.F |= (cpu->regB.HX & (F5 | F3));
   cpu->ticks += 7;
}

void CPU::_opDD_2A(CPU* cpu) // ld ix,(nnnn)
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->regB.LX = cpu->pMemory->read(adr++);
   cpu->regB.HX = cpu->pMemory->read(adr);
   cpu->ticks += 12;
}

void CPU::_opDD_2B(CPU* cpu) // dec ix
{
   cpu->regP.IX--;
   cpu->ticks += 2;
}

void CPU::_opDD_2C(CPU* cpu) // inc xl
{
   cpu->_inc8(cpu->regB.LX);
}

void CPU::_opDD_2D(CPU* cpu) // dec xl
{
   cpu->_dec8(cpu->regB.LX);
}

void CPU::_opDD_2E(CPU* cpu) // ld xl,nn
{
   cpu->regB.LX = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 3;
}

void CPU::_opDD_34(CPU* cpu) // inc (ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   BYTE tmp = cpu->pMemory->read(cpu->regP.IX + ofs);
   cpu->_inc8(tmp);
   cpu->pMemory->write(cpu->regP.IX + ofs, tmp);
   cpu->ticks += 15;
}

void CPU::_opDD_35(CPU* cpu) // dec (ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   BYTE tmp = cpu->pMemory->read(cpu->regP.IX + ofs);
   cpu->_dec8(tmp);
   cpu->pMemory->write(cpu->regP.IX + ofs, tmp);
   cpu->ticks += 15;
}

void CPU::_opDD_36(CPU* cpu) // ld (ix+nn),nn
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IX + ofs, cpu->pMemory->read(cpu->regP.PC++));
   cpu->ticks += 11;
}

void CPU::_opDD_39(CPU* cpu) // add ix,sp
{
   WORD tmp = cpu->regP.IX;
   cpu->regB.F = (cpu->regB.F & ~(NF | CF | F5 | F3 | HF));
   cpu->regB.F |= (((cpu->regP.IX & 0x0FFF) + (cpu->regP.SP & 0x0FFF)) >> 8) & 0x10; /* HF */
   cpu->regP.IX += cpu->regP.SP;
   if (cpu->regP.IX < tmp) cpu->regB.F |= CF;
   cpu->regB.F |= (cpu->regB.LX & (F5 | F3));
   cpu->ticks += 7;
}

void CPU::_opDD_44(CPU* cpu) // ld b,xh
{
   cpu->regB.B = cpu->regB.HX;
}

void CPU::_opDD_45(CPU* cpu) // ld b,xl
{
   cpu->regB.B = cpu->regB.LX;
}

void CPU::_opDD_46(CPU* cpu) // ld b,(ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.B = cpu->pMemory->read(cpu->regP.IX + ofs);
   cpu->ticks += 11;
}

void CPU::_opDD_4C(CPU* cpu) // ld c,xh
{
   cpu->regB.C = cpu->regB.HX;
}

void CPU::_opDD_4D(CPU* cpu) // ld c,xl
{
   cpu->regB.C = cpu->regB.LX;
}

void CPU::_opDD_4E(CPU* cpu) // ld c,(ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.C = cpu->pMemory->read(cpu->regP.IX + ofs);
   cpu->ticks += 11;
}

void CPU::_opDD_54(CPU* cpu) // ld d,xh
{
   cpu->regB.D = cpu->regB.HX;
}

void CPU::_opDD_55(CPU* cpu) // ld d,xl
{
   cpu->regB.D = cpu->regB.LX;
}

void CPU::_opDD_56(CPU* cpu) // ld d,(ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.D = cpu->pMemory->read(cpu->regP.IX + ofs);
   cpu->ticks += 11;
}

void CPU::_opDD_5C(CPU* cpu) // ld e,xh
{
   cpu->regB.E = cpu->regB.HX;
}

void CPU::_opDD_5D(CPU* cpu) // ld e,xl
{
   cpu->regB.E = cpu->regB.LX;
}

void CPU::_opDD_5E(CPU* cpu) // ld e,(ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.E = cpu->pMemory->read(cpu->regP.IX + ofs);
   cpu->ticks += 11;
}

void CPU::_opDD_60(CPU* cpu) // ld xh,b
{
   cpu->regB.HX = cpu->regB.B;
}

void CPU::_opDD_61(CPU* cpu) // ld xh,c
{
   cpu->regB.HX = cpu->regB.C;
}

void CPU::_opDD_62(CPU* cpu) // ld xh,d
{
   cpu->regB.HX = cpu->regB.D;
}

void CPU::_opDD_63(CPU* cpu) // ld xh,e
{
   cpu->regB.HX = cpu->regB.E;
}

void CPU::_opDD_65(CPU* cpu) // ld xh,xl
{
   cpu->regB.HX = cpu->regB.LX;
}

void CPU::_opDD_66(CPU* cpu) // ld h,(ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.H = cpu->pMemory->read(cpu->regP.IX + ofs);
   cpu->ticks += 11;
}

void CPU::_opDD_67(CPU* cpu) // ld xh,a
{
   cpu->regB.HX = cpu->regB.A;
}

void CPU::_opDD_68(CPU* cpu) // ld xl,b
{
   cpu->regB.LX = cpu->regB.B;
}

void CPU::_opDD_69(CPU* cpu) // ld xl,c
{
   cpu->regB.LX = cpu->regB.C;
}

void CPU::_opDD_6A(CPU* cpu) // ld xl,d
{
   cpu->regB.LX = cpu->regB.D;
}

void CPU::_opDD_6B(CPU* cpu) // ld xl,e
{
   cpu->regB.LX = cpu->regB.E;
}

void CPU::_opDD_6C(CPU* cpu) // ld xl,xh
{
   cpu->regB.LX = cpu->regB.HX;
}

void CPU::_opDD_6E(CPU* cpu) // ld l,(ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.L = cpu->pMemory->read(cpu->regP.IX + ofs);
   cpu->ticks += 11;
}

void CPU::_opDD_6F(CPU* cpu) // ld xl,a
{
   cpu->regB.LX = cpu->regB.A;
}

void CPU::_opDD_70(CPU* cpu) // ld (ix+nn),b
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IX + ofs, cpu->regB.B);
   cpu->ticks += 11;
}

void CPU::_opDD_71(CPU* cpu) // ld (ix+nn),c
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IX + ofs, cpu->regB.C);
   cpu->ticks += 11;
}

void CPU::_opDD_72(CPU* cpu) // ld (ix+nn),d
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IX + ofs, cpu->regB.D);
   cpu->ticks += 11;
}

void CPU::_opDD_73(CPU* cpu) // ld (ix+nn),e
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IX + ofs, cpu->regB.E);
   cpu->ticks += 11;
}

void CPU::_opDD_74(CPU* cpu) // ld (ix+nn),h
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IX + ofs, cpu->regB.H);
   cpu->ticks += 11;
}

void CPU::_opDD_75(CPU* cpu) // ld (ix+nn),l
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IX + ofs, cpu->regB.L);
   cpu->ticks += 11;
}

void CPU::_opDD_77(CPU* cpu) // ld (ix+nn),a
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IX + ofs, cpu->regB.A);
   cpu->ticks += 11;
}

void CPU::_opDD_7C(CPU* cpu) // ld a,xh
{
   cpu->regB.A = cpu->regB.HX;
}

void CPU::_opDD_7D(CPU* cpu) // ld a,xl
{
   cpu->regB.A = cpu->regB.LX;
}

void CPU::_opDD_7E(CPU* cpu) // ld a,(ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.A = cpu->pMemory->read(cpu->regP.IX + ofs);
   cpu->ticks += 11;
}

void CPU::_opDD_84(CPU* cpu) // add a,xh
{
   cpu->_add8(cpu->regB.HX);
}

void CPU::_opDD_85(CPU* cpu) // add a,xl
{
   cpu->_add8(cpu->regB.LX);
}

void CPU::_opDD_86(CPU* cpu) // add a,(ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_add8(cpu->pMemory->read(cpu->regP.IX + ofs));
   cpu->ticks += 11;
}

void CPU::_opDD_8C(CPU* cpu) // adc a,xh
{
   cpu->_adc8(cpu->regB.HX);
}

void CPU::_opDD_8D(CPU* cpu) // adc a,xl
{
   cpu->_adc8(cpu->regB.LX);
}


void CPU::_opDD_8E(CPU* cpu) // adc a,(ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_adc8(cpu->pMemory->read(cpu->regP.IX + ofs));
   cpu->ticks += 11;
}

void CPU::_opDD_94(CPU* cpu) // sub xh
{
   cpu->_sub8(cpu->regB.HX);
}

void CPU::_opDD_95(CPU* cpu) // sub xl
{
   cpu->_sub8(cpu->regB.LX);
}

void CPU::_opDD_96(CPU* cpu) // sub (ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_sub8(cpu->pMemory->read(cpu->regP.IX + ofs));
   cpu->ticks += 11;
}

void CPU::_opDD_9C(CPU* cpu) // sbc a,xh
{
   cpu->_sbc8(cpu->regB.HX);
}

void CPU::_opDD_9D(CPU* cpu) // sbc a,xl
{
   cpu->_sbc8(cpu->regB.LX);
}

void CPU::_opDD_9E(CPU* cpu) // sbc a,(ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_sbc8(cpu->pMemory->read(cpu->regP.IX + ofs));
   cpu->ticks += 11;
}

void CPU::_opDD_A4(CPU* cpu) // and xh
{
   cpu->_and8(cpu->regB.HX);
}

void CPU::_opDD_A5(CPU* cpu) // and xl
{
   cpu->_and8(cpu->regB.LX);
}

void CPU::_opDD_A6(CPU* cpu) // and (ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_and8(cpu->pMemory->read(cpu->regP.IX + ofs));
   cpu->ticks += 11;
}

void CPU::_opDD_AC(CPU* cpu) // xor xh
{
   cpu->_xor8(cpu->regB.HX);
}

void CPU::_opDD_AD(CPU* cpu) // xor xl
{
   cpu->_xor8(cpu->regB.LX);
}

void CPU::_opDD_AE(CPU* cpu) // xor (ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_xor8(cpu->pMemory->read(cpu->regP.IX + ofs));
   cpu->ticks += 11;
}

void CPU::_opDD_B4(CPU* cpu) // or xh
{
   cpu->_orl8(cpu->regB.HX);
}

void CPU::_opDD_B5(CPU* cpu) // or xl
{
   cpu->_orl8(cpu->regB.LX);
}

void CPU::_opDD_B6(CPU* cpu) // or (ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_orl8(cpu->pMemory->read(cpu->regP.IX + ofs));
   cpu->ticks += 11;
}

void CPU::_opDD_BC(CPU* cpu) // cp xh
{
   cpu->_cpr8(cpu->regB.HX);
}
void CPU::_opDD_BD(CPU* cpu) // cp xl
{
   cpu->_cpr8(cpu->regB.LX);
}

void CPU::_opDD_BE(CPU* cpu) // cp (ix+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_cpr8(cpu->pMemory->read(cpu->regP.IX + ofs));
   cpu->ticks += 11;
}

void CPU::_opDD_E1(CPU* cpu) // pop ix
{
   cpu->_pop(cpu->regP.IX);
   cpu->ticks += 6;
}

void CPU::_opDD_E3(CPU* cpu) // ex (sp),ix
{
   WORD tmp = cpu->pMemory->read(cpu->regP.SP) + ((int)cpu->pMemory->read(cpu->regP.SP + 1) << 8);
   cpu->pMemory->write(cpu->regP.SP, cpu->regB.LX);
   cpu->pMemory->write(cpu->regP.SP + 1, cpu->regB.HX);
   cpu->regP.IX = tmp;
   cpu->ticks += 15;
}

void CPU::_opDD_E5(CPU* cpu) // push ix
{
   cpu->_push(cpu->regP.IX);
   cpu->ticks += 7;
}

void CPU::_opDD_E9(CPU* cpu) // jp (ix)
{
   cpu->regP.PC = cpu->regP.IX;
}

void CPU::_opDD_F9(CPU* cpu) // ld sp,ix
{
   cpu->regP.SP = cpu->regP.IX;
   cpu->ticks += 2;
}


CPUFUNC const CPU::pOpsFD[0x100] = {
   _op_00, _op_01,   _op_02,   _op_03,   _op_04,   _op_05,   _op_06,   _op_07,
   _op_08, _opFD_09, _op_0A,   _op_0B,   _op_0C,   _op_0D,   _op_0E,   _op_0F,
   _op_10, _op_11,   _op_12,   _op_13,   _op_14,   _op_15,   _op_16,   _op_17,
   _op_18, _opFD_19, _op_1A,   _op_1B,   _op_1C,   _op_1D,   _op_1E,   _op_1F,
   _op_20, _opFD_21, _opFD_22, _opFD_23, _opFD_24, _opFD_25, _opFD_26, _op_27,
   _op_28, _opFD_29, _opFD_2A, _opFD_2B, _opFD_2C, _opFD_2D, _opFD_2E, _op_2F,
   _op_30, _op_31,   _op_32,   _op_33,   _opFD_34, _opFD_35, _opFD_36, _op_37,
   _op_38, _opFD_39, _op_3A,   _op_3B,   _op_3C,   _op_3D,   _op_3E,   _op_3F,

   _op_00, _op_41, _op_42, _op_43, _opFD_44, _opFD_45, _opFD_46, _op_47,
   _op_48, _op_00, _op_4A, _op_4B, _opFD_4C, _opFD_4D, _opFD_4E, _op_4F,
   _op_50, _op_51, _op_00, _op_53, _opFD_54, _opFD_55, _opFD_56, _op_57,
   _op_58, _op_59, _op_5A, _op_00, _opFD_5C, _opFD_5D, _opFD_5E, _op_5F,
   _opFD_60, _opFD_61, _opFD_62, _opFD_63, _op_00,   _opFD_65, _opFD_66, _opFD_67,
   _opFD_68, _opFD_69, _opFD_6A, _opFD_6B, _opFD_6C, _op_00,   _opFD_6E, _opFD_6F,
   _opFD_70, _opFD_71, _opFD_72, _opFD_73, _opFD_74, _opFD_75, _op_76,   _opFD_77,
   _op_78,   _op_79,   _op_7A,   _op_7B,   _opFD_7C, _opFD_7D, _opFD_7E, _op_00,

   _op_80, _op_81, _op_82, _op_83, _opFD_84, _opFD_85, _opFD_86, _op_87,
   _op_88, _op_89, _op_8A, _op_8B, _opFD_8C, _opFD_8D, _opFD_8E, _op_8F,
   _op_90, _op_91, _op_92, _op_93, _opFD_94, _opFD_95, _opFD_96, _op_97,
   _op_98, _op_99, _op_9A, _op_9B, _opFD_9C, _opFD_9D, _opFD_9E, _op_9F,
   _op_A0, _op_A1, _op_A2, _op_A3, _opFD_A4, _opFD_A5, _opFD_A6, _op_A7,
   _op_A8, _op_A9, _op_AA, _op_AB, _opFD_AC, _opFD_AD, _opFD_AE, _op_AF,
   _op_B0, _op_B1, _op_B2, _op_B3, _opFD_B4, _opFD_B5, _opFD_B6, _op_B7,
   _op_B8, _op_B9, _op_BA, _op_BB, _opFD_BC, _opFD_BD, _opFD_BE, _op_BF,

   _op_C0, _op_C1, _op_C2, _op_C3, _op_C4, _op_C5, _op_C6, _op_C7,
   _op_C8, _op_C9, _op_CA, _op_CB, _op_CC, _op_CD, _op_CE, _op_CF,
   _op_D0, _op_D1, _op_D2, _op_D3, _op_D4, _op_D5, _op_D6, _op_D7,
   _op_D8, _op_D9, _op_DA, _op_DB, _op_DC, _op_FD, _op_DE, _op_DF,
   _op_E0, _opFD_E1, _op_E2, _opFD_E3, _op_E4, _opFD_E5, _op_E6, _op_E7,
   _op_E8, _opFD_E9, _op_EA, _op_EB,   _op_EC, _op_ED,   _op_EE, _op_EF,
   _op_F0, _op_F1,   _op_F2, _op_F3,   _op_F4, _op_F5,   _op_F6, _op_F7,
   _op_F8, _opFD_F9, _op_FA, _op_FB,   _op_FC, _op_FD,   _op_FE, _op_FF,
};

void CPU::_opFD_09(CPU* cpu) // add iy,bc
{
   WORD tmp = cpu->regP.IY;
   cpu->regB.F = (cpu->regB.F & ~(NF | CF | F5 | F3 | HF));
   cpu->regB.F |= (((cpu->regP.IY & 0x0FFF) + (cpu->regP.BC & 0x0FFF)) >> 8) & 0x10; /* HF */
   cpu->regP.IY += cpu->regP.BC;
   if (cpu->regP.IY < tmp) cpu->regB.F |= CF;
   cpu->regB.F |= (cpu->regB.HY & (F5 | F3));
   cpu->ticks += 7;
}

void CPU::_opFD_19(CPU* cpu) // add iy,de
{
   WORD tmp = cpu->regP.IY;
   cpu->regB.F = (cpu->regB.F & ~(NF | CF | F5 | F3 | HF));
   cpu->regB.F |= (((cpu->regP.IY & 0x0FFF) + (cpu->regP.DE & 0x0FFF)) >> 8) & 0x10; /* HF */
   cpu->regP.IY += cpu->regP.DE;
   if (cpu->regP.IY < tmp) cpu->regB.F |= CF;
   cpu->regB.F |= (cpu->regB.HY & (F5 | F3));
   cpu->ticks += 7;
}

void CPU::_opFD_21(CPU* cpu) // ld iy,nnnn
{
   cpu->regB.LY = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.HY = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 6;
}

void CPU::_opFD_22(CPU* cpu) // ld (nnnn),iy
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->pMemory->write(adr++, cpu->regB.LY);
   cpu->pMemory->write(adr, cpu->regB.HY);
   cpu->ticks += 12;
}

void CPU::_opFD_23(CPU* cpu) // inc iy
{
   cpu->regP.IY++;
   cpu->ticks += 2;
}

void CPU::_opFD_24(CPU* cpu) // inc yh
{
   cpu->_inc8(cpu->regB.HY);
}

void CPU::_opFD_25(CPU* cpu) // dec yh
{
   cpu->_dec8(cpu->regB.HY);
}

void CPU::_opFD_26(CPU* cpu) // ld yh,nn
{
   cpu->regB.HY = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 3;
}

void CPU::_opFD_29(CPU* cpu) // add iy,iy
{
   WORD tmp = cpu->regP.IY;
   cpu->regB.F = (cpu->regB.F & ~(NF | CF | F5 | F3 | HF));
   cpu->regB.F |= ((cpu->regB.HY <<= 1) & 0x10); /* HF */
   if (cpu->regP.IY < tmp) cpu->regB.F |= CF;
   cpu->regB.F |= (cpu->regB.HY & (F5 | F3));
   cpu->ticks += 7;
}

void CPU::_opFD_2A(CPU* cpu) // ld iy,(nnnn)
{
   WORD adr = cpu->pMemory->read(cpu->regP.PC++) + ((int)cpu->pMemory->read(cpu->regP.PC++) << 8);
   cpu->regB.LY = cpu->pMemory->read(adr++);
   cpu->regB.HY = cpu->pMemory->read(adr);
   cpu->ticks += 12;
}

void CPU::_opFD_2B(CPU* cpu) // dec iy
{
   cpu->regP.IY--;
   cpu->ticks += 2;
}

void CPU::_opFD_2C(CPU* cpu) // inc yl
{
   cpu->_inc8(cpu->regB.LY);
}

void CPU::_opFD_2D(CPU* cpu) // dec yl
{
   cpu->_dec8(cpu->regB.LY);
}

void CPU::_opFD_2E(CPU* cpu) // ld yl,nn
{
   cpu->regB.LY = cpu->pMemory->read(cpu->regP.PC++);
   cpu->ticks += 3;
}

void CPU::_opFD_34(CPU* cpu) // inc (iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   BYTE tmp = cpu->pMemory->read(cpu->regP.IY + ofs);
   cpu->_inc8(tmp);
   cpu->pMemory->write(cpu->regP.IY + ofs, tmp);
   cpu->ticks += 15;
}

void CPU::_opFD_35(CPU* cpu) // dec (iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   BYTE tmp = cpu->pMemory->read(cpu->regP.IY + ofs);
   cpu->_dec8(tmp);
   cpu->pMemory->write(cpu->regP.IY + ofs, tmp);
   cpu->ticks += 15;
}

void CPU::_opFD_36(CPU* cpu) // ld (iy+nn),nn
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IY + ofs, cpu->pMemory->read(cpu->regP.PC++));
   cpu->ticks += 11;
}

void CPU::_opFD_39(CPU* cpu) // add iy,sp
{
   WORD tmp = cpu->regP.IY;
   cpu->regB.F = (cpu->regB.F & ~(NF | CF | F5 | F3 | HF));
   cpu->regB.F |= (((cpu->regP.IY & 0x0FFF) + (cpu->regP.SP & 0x0FFF)) >> 8) & 0x10; /* HF */
   cpu->regP.IY += cpu->regP.SP;
   if (cpu->regP.IY < tmp) cpu->regB.F |= CF;
   cpu->regB.F |= (cpu->regB.LY & (F5 | F3));
   cpu->ticks += 7;
}

void CPU::_opFD_44(CPU* cpu) // ld b,yh
{
   cpu->regB.B = cpu->regB.HY;
}

void CPU::_opFD_45(CPU* cpu) // ld b,yl
{
   cpu->regB.B = cpu->regB.LY;
}

void CPU::_opFD_46(CPU* cpu) // ld b,(iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.B = cpu->pMemory->read(cpu->regP.IY + ofs);
   cpu->ticks += 11;
}

void CPU::_opFD_4C(CPU* cpu) // ld c,yh
{
   cpu->regB.C = cpu->regB.HY;
}

void CPU::_opFD_4D(CPU* cpu) // ld c,yl
{
   cpu->regB.C = cpu->regB.LY;
}

void CPU::_opFD_4E(CPU* cpu) // ld c,(iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.C = cpu->pMemory->read(cpu->regP.IY + ofs);
   cpu->ticks += 11;
}

void CPU::_opFD_54(CPU* cpu) // ld d,yh
{
   cpu->regB.D = cpu->regB.HY;
}

void CPU::_opFD_55(CPU* cpu) // ld d,yl
{
   cpu->regB.D = cpu->regB.LY;
}

void CPU::_opFD_56(CPU* cpu) // ld d,(iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.D = cpu->pMemory->read(cpu->regP.IY + ofs);
   cpu->ticks += 11;
}

void CPU::_opFD_5C(CPU* cpu) // ld e,yh
{
   cpu->regB.E = cpu->regB.HY;
}

void CPU::_opFD_5D(CPU* cpu) // ld e,yl
{
   cpu->regB.E = cpu->regB.LY;
}

void CPU::_opFD_5E(CPU* cpu) // ld e,(iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.E = cpu->pMemory->read(cpu->regP.IY + ofs);
   cpu->ticks += 11;
}

void CPU::_opFD_60(CPU* cpu) // ld yh,b
{
   cpu->regB.HY = cpu->regB.B;
}

void CPU::_opFD_61(CPU* cpu) // ld yh,c
{
   cpu->regB.HY = cpu->regB.C;
}

void CPU::_opFD_62(CPU* cpu) // ld yh,d
{
   cpu->regB.HY = cpu->regB.D;
}

void CPU::_opFD_63(CPU* cpu) // ld yh,e
{
   cpu->regB.HY = cpu->regB.E;
}

void CPU::_opFD_65(CPU* cpu) // ld yh,yl
{
   cpu->regB.HY = cpu->regB.LY;
}

void CPU::_opFD_66(CPU* cpu) // ld h,(iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.H = cpu->pMemory->read(cpu->regP.IY + ofs);
   cpu->ticks += 11;
}

void CPU::_opFD_67(CPU* cpu) // ld yh,a
{
   cpu->regB.HY = cpu->regB.A;
}

void CPU::_opFD_68(CPU* cpu) // ld yl,b
{
   cpu->regB.LY = cpu->regB.B;
}

void CPU::_opFD_69(CPU* cpu) // ld yl,c
{
   cpu->regB.LY = cpu->regB.C;
}

void CPU::_opFD_6A(CPU* cpu) // ld yl,d
{
   cpu->regB.LY = cpu->regB.D;
}

void CPU::_opFD_6B(CPU* cpu) // ld yl,e
{
   cpu->regB.LY = cpu->regB.E;
}

void CPU::_opFD_6C(CPU* cpu) // ld yl,yh
{
   cpu->regB.LY = cpu->regB.HY;
}

void CPU::_opFD_6E(CPU* cpu) // ld l,(iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.L = cpu->pMemory->read(cpu->regP.IY + ofs);
   cpu->ticks += 11;
}

void CPU::_opFD_6F(CPU* cpu) // ld yl,a
{
   cpu->regB.LY = cpu->regB.A;
}

void CPU::_opFD_70(CPU* cpu) // ld (iy+nn),b
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IY + ofs, cpu->regB.B);
   cpu->ticks += 11;
}

void CPU::_opFD_71(CPU* cpu) // ld (iy+nn),c
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IY + ofs, cpu->regB.C);
   cpu->ticks += 11;
}

void CPU::_opFD_72(CPU* cpu) // ld (iy+nn),d
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IY + ofs, cpu->regB.D);
   cpu->ticks += 11;
}

void CPU::_opFD_73(CPU* cpu) // ld (iy+nn),e
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IY + ofs, cpu->regB.E);
   cpu->ticks += 11;
}

void CPU::_opFD_74(CPU* cpu) // ld (iy+nn),h
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IY + ofs, cpu->regB.H);
   cpu->ticks += 11;
}

void CPU::_opFD_75(CPU* cpu) // ld (iy+nn),l
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IY + ofs, cpu->regB.L);
   cpu->ticks += 11;
}

void CPU::_opFD_77(CPU* cpu) // ld (iy+nn),a
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->pMemory->write(cpu->regP.IY + ofs, cpu->regB.A);
   cpu->ticks += 11;
}

void CPU::_opFD_7C(CPU* cpu) // ld a,yh
{
   cpu->regB.A = cpu->regB.HY;
}

void CPU::_opFD_7D(CPU* cpu) // ld a,yl
{
   cpu->regB.A = cpu->regB.LY;
}

void CPU::_opFD_7E(CPU* cpu) // ld a,(iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->regB.A = cpu->pMemory->read(cpu->regP.IY + ofs);
   cpu->ticks += 11;
}

void CPU::_opFD_84(CPU* cpu) // add a,yh
{
   cpu->_add8(cpu->regB.HY);
}

void CPU::_opFD_85(CPU* cpu) // add a,yl
{
   cpu->_add8(cpu->regB.LY);
}

void CPU::_opFD_86(CPU* cpu) // add a,(iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_add8(cpu->pMemory->read(cpu->regP.IY + ofs));
   cpu->ticks += 11;
}

void CPU::_opFD_8C(CPU* cpu) // adc a,yh
{
   cpu->_adc8(cpu->regB.HY);
}

void CPU::_opFD_8D(CPU* cpu) // adc a,yl
{
   cpu->_adc8(cpu->regB.LY);
}


void CPU::_opFD_8E(CPU* cpu) // adc a,(iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_adc8(cpu->pMemory->read(cpu->regP.IY + ofs));
   cpu->ticks += 11;
}

void CPU::_opFD_94(CPU* cpu) // sub yh
{
   cpu->_sub8(cpu->regB.HY);
}

void CPU::_opFD_95(CPU* cpu) // sub yl
{
   cpu->_sub8(cpu->regB.LY);
}

void CPU::_opFD_96(CPU* cpu) // sub (iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_sub8(cpu->pMemory->read(cpu->regP.IY + ofs));
   cpu->ticks += 11;
}

void CPU::_opFD_9C(CPU* cpu) // sbc a,yh
{
   cpu->_sbc8(cpu->regB.HY);
}

void CPU::_opFD_9D(CPU* cpu) // sbc a,yl
{
   cpu->_sbc8(cpu->regB.LY);
}

void CPU::_opFD_9E(CPU* cpu) // sbc a,(iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_sbc8(cpu->pMemory->read(cpu->regP.IY + ofs));
   cpu->ticks += 11;
}

void CPU::_opFD_A4(CPU* cpu) // and yh
{
   cpu->_and8(cpu->regB.HY);
}

void CPU::_opFD_A5(CPU* cpu) // and yl
{
   cpu->_and8(cpu->regB.LY);
}

void CPU::_opFD_A6(CPU* cpu) // and (iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_and8(cpu->pMemory->read(cpu->regP.IY + ofs));
   cpu->ticks += 11;
}

void CPU::_opFD_AC(CPU* cpu) // xor yh
{
   cpu->_xor8(cpu->regB.HY);
}

void CPU::_opFD_AD(CPU* cpu) // xor yl
{
   cpu->_xor8(cpu->regB.LY);
}

void CPU::_opFD_AE(CPU* cpu) // xor (iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_xor8(cpu->pMemory->read(cpu->regP.IY + ofs));
   cpu->ticks += 11;
}

void CPU::_opFD_B4(CPU* cpu) // or yh
{
   cpu->_orl8(cpu->regB.HY);
}

void CPU::_opFD_B5(CPU* cpu) // or yl
{
   cpu->_orl8(cpu->regB.LY);
}

void CPU::_opFD_B6(CPU* cpu) // or (iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_orl8(cpu->pMemory->read(cpu->regP.IY + ofs));
   cpu->ticks += 11;
}

void CPU::_opFD_BC(CPU* cpu) // cp yh
{
   cpu->_cpr8(cpu->regB.HY);
}
void CPU::_opFD_BD(CPU* cpu) // cp yl
{
   cpu->_cpr8(cpu->regB.LY);
}

void CPU::_opFD_BE(CPU* cpu) // cp (iy+nn)
{
   char ofs = cpu->pMemory->read(cpu->regP.PC++);
   cpu->_cpr8(cpu->pMemory->read(cpu->regP.IY + ofs));
   cpu->ticks += 11;
}

void CPU::_opFD_E1(CPU* cpu) // pop iy
{
   cpu->_pop(cpu->regP.IY);
   cpu->ticks += 6;
}

void CPU::_opFD_E3(CPU* cpu) // ex (sp),iy
{
   WORD tmp = cpu->pMemory->read(cpu->regP.SP) + ((int)cpu->pMemory->read(cpu->regP.SP + 1) << 8);
   cpu->pMemory->write(cpu->regP.SP, cpu->regB.LY);
   cpu->pMemory->write(cpu->regP.SP + 1, cpu->regB.HY);
   cpu->regP.IY = tmp;
   cpu->ticks += 15;
}

void CPU::_opFD_E5(CPU* cpu) // push iy
{
   cpu->_push(cpu->regP.IY);
   cpu->ticks += 7;
}

void CPU::_opFD_E9(CPU* cpu) // jp (iy)
{
   cpu->regP.PC = cpu->regP.IY;
}

void CPU::_opFD_F9(CPU* cpu) // ld sp,iy
{
   cpu->regP.SP = cpu->regP.IY;
   cpu->ticks += 2;
}

LOGXFUNC const CPU::pLogX[0x100] = {
   _oplx_00, _oplx_00, _oplx_00, _oplx_00, _oplx_00, _oplx_00, _oplx_00, _oplx_00,
   _oplx_08, _oplx_08, _oplx_08, _oplx_08, _oplx_08, _oplx_08, _oplx_08, _oplx_08,
   _oplx_10, _oplx_10, _oplx_10, _oplx_10, _oplx_10, _oplx_10, _oplx_10, _oplx_10,
   _oplx_18, _oplx_18, _oplx_18, _oplx_18, _oplx_18, _oplx_18, _oplx_18, _oplx_18,
   _oplx_20, _oplx_20, _oplx_20, _oplx_20, _oplx_20, _oplx_20, _oplx_20, _oplx_20,
   _oplx_28, _oplx_28, _oplx_28, _oplx_28, _oplx_28, _oplx_28, _oplx_28, _oplx_28,
   _oplx_30, _oplx_30, _oplx_30, _oplx_30, _oplx_30, _oplx_30, _oplx_30, _oplx_30,
   _oplx_38, _oplx_38, _oplx_38, _oplx_38, _oplx_38, _oplx_38, _oplx_38, _oplx_38,

   _oplx_40, _oplx_40, _oplx_40, _oplx_40, _oplx_40, _oplx_40, _oplx_40, _oplx_40,
   _oplx_48, _oplx_48, _oplx_48, _oplx_48, _oplx_48, _oplx_48, _oplx_48, _oplx_48,
   _oplx_50, _oplx_50, _oplx_50, _oplx_50, _oplx_50, _oplx_50, _oplx_50, _oplx_50,
   _oplx_58, _oplx_58, _oplx_58, _oplx_58, _oplx_58, _oplx_58, _oplx_58, _oplx_58,
   _oplx_60, _oplx_60, _oplx_60, _oplx_60, _oplx_60, _oplx_60, _oplx_60, _oplx_60,
   _oplx_68, _oplx_68, _oplx_68, _oplx_68, _oplx_68, _oplx_68, _oplx_68, _oplx_68,
   _oplx_70, _oplx_70, _oplx_70, _oplx_70, _oplx_70, _oplx_70, _oplx_70, _oplx_70,
   _oplx_78, _oplx_78, _oplx_78, _oplx_78, _oplx_78, _oplx_78, _oplx_78, _oplx_78,

   _oplx_80, _oplx_80, _oplx_80, _oplx_80, _oplx_80, _oplx_80, _oplx_80, _oplx_80,
   _oplx_88, _oplx_88, _oplx_88, _oplx_88, _oplx_88, _oplx_88, _oplx_88, _oplx_88,
   _oplx_90, _oplx_90, _oplx_90, _oplx_90, _oplx_90, _oplx_90, _oplx_90, _oplx_90,
   _oplx_98, _oplx_98, _oplx_98, _oplx_98, _oplx_98, _oplx_98, _oplx_98, _oplx_98,
   _oplx_A0, _oplx_A0, _oplx_A0, _oplx_A0, _oplx_A0, _oplx_A0, _oplx_A0, _oplx_A0,
   _oplx_A8, _oplx_A8, _oplx_A8, _oplx_A8, _oplx_A8, _oplx_A8, _oplx_A8, _oplx_A8,
   _oplx_B0, _oplx_B0, _oplx_B0, _oplx_B0, _oplx_B0, _oplx_B0, _oplx_B0, _oplx_B0,
   _oplx_B8, _oplx_B8, _oplx_B8, _oplx_B8, _oplx_B8, _oplx_B8, _oplx_B8, _oplx_B8,

   _oplx_C0, _oplx_C0, _oplx_C0, _oplx_C0, _oplx_C0, _oplx_C0, _oplx_C0, _oplx_C0,
   _oplx_C8, _oplx_C8, _oplx_C8, _oplx_C8, _oplx_C8, _oplx_C8, _oplx_C8, _oplx_C8,
   _oplx_D0, _oplx_D0, _oplx_D0, _oplx_D0, _oplx_D0, _oplx_D0, _oplx_D0, _oplx_D0,
   _oplx_D8, _oplx_D8, _oplx_D8, _oplx_D8, _oplx_D8, _oplx_D8, _oplx_D8, _oplx_D8,
   _oplx_E0, _oplx_E0, _oplx_E0, _oplx_E0, _oplx_E0, _oplx_E0, _oplx_E0, _oplx_E0,
   _oplx_E8, _oplx_E8, _oplx_E8, _oplx_E8, _oplx_E8, _oplx_E8, _oplx_E8, _oplx_E8,
   _oplx_F0, _oplx_F0, _oplx_F0, _oplx_F0, _oplx_F0, _oplx_F0, _oplx_F0, _oplx_F0,
   _oplx_F8, _oplx_F8, _oplx_F8, _oplx_F8, _oplx_F8, _oplx_F8, _oplx_F8, _oplx_F8
};


BYTE CPU::_oplx_00(CPU* cpu, BYTE byte) // rlc (ix+nn)
{
   cpu->regB.F = pRLCF[byte];
   return pROLF[byte];
}

BYTE CPU::_oplx_08(CPU* cpu, BYTE byte) // rrc (ix+nn)
{
   cpu->regB.F = pRRCF[byte];
   return pRORF[byte];
}

BYTE CPU::_oplx_10(CPU* cpu, BYTE byte) // rl (ix+nn)
{
   if (cpu->regB.F & CF)
   {
      cpu->regB.F = pRL1[byte];
      return (byte << 1) + 1;
   }
   else
   {
      cpu->regB.F = pRL0[byte];
      return (byte << 1);
   }
}

BYTE CPU::_oplx_18(CPU* cpu, BYTE byte) // rr (ix+nn)
{
   if (cpu->regB.F & CF)
   {
      cpu->regB.F = pRR1[byte];
      return (byte >> 1) + 0x80;
   }
   else
   {
      cpu->regB.F = pRR0[byte];
      return (byte >> 1);
   }
}

BYTE CPU::_oplx_20(CPU* cpu, BYTE byte) // sla (ix+nn)
{
   cpu->regB.F = pRL0[byte];
   return (byte << 1);
}

BYTE CPU::_oplx_28(CPU* cpu, BYTE byte) // sra (ix+nn)
{
   cpu->regB.F = pSRAF[byte];
   return (byte >> 1) + (byte & 0x80);
}

BYTE CPU::_oplx_30(CPU* cpu, BYTE byte) // sli (ix+nn)
{
   cpu->regB.F = pRL1[byte];
   return (byte << 1) + 1;
}

BYTE CPU::_oplx_38(CPU* cpu, BYTE byte) // srl (ix+nn)
{
   cpu->regB.F = pRR0[byte];
   return (byte >> 1);
}

BYTE CPU::_oplx_40(CPU* cpu, BYTE byte) // bit 0,(ix+nn)
{
   cpu->_bit8(byte, 0);
   return byte;
}

BYTE CPU::_oplx_48(CPU* cpu, BYTE byte) // bit 1,(ix+nn)
{
   cpu->_bit8(byte, 1);
   return byte;
}

BYTE CPU::_oplx_50(CPU* cpu, BYTE byte) // bit 2,(ix+nn)
{
   cpu->_bit8(byte, 2);
   return byte;
}

BYTE CPU::_oplx_58(CPU* cpu, BYTE byte) // bit 3,(ix+nn)
{
   cpu->_bit8(byte, 3);
   return byte;
}

BYTE CPU::_oplx_60(CPU* cpu, BYTE byte) // bit 4,(ix+nn)
{
   cpu->_bit8(byte, 4);
   return byte;
}

BYTE CPU::_oplx_68(CPU* cpu, BYTE byte) // bit 5,(ix+nn)
{
   cpu->_bit8(byte, 5);
   return byte;
}

BYTE CPU::_oplx_70(CPU* cpu, BYTE byte) // bit 6,(ix+nn)
{
   cpu->_bit8(byte, 6);
   return byte;
}

BYTE CPU::_oplx_78(CPU* cpu, BYTE byte) // bit 7,(ix+nn)
{
   cpu->_bit8(byte, 7);
   return byte;
}

BYTE CPU::_oplx_80(CPU* cpu, BYTE byte) // res 0,(ix+nn)
{
   return cpu->_rsb8(byte, 0);
}

BYTE CPU::_oplx_88(CPU* cpu, BYTE byte) // res 1,(ix+nn)
{
   return cpu->_rsb8(byte, 1);
}

BYTE CPU::_oplx_90(CPU* cpu, BYTE byte) // res 2,(ix+nn)
{
   return cpu->_rsb8(byte, 2);
}

BYTE CPU::_oplx_98(CPU* cpu, BYTE byte) // res 3,(ix+nn)
{
   return cpu->_rsb8(byte, 3);
}

BYTE CPU::_oplx_A0(CPU* cpu, BYTE byte) // res 4,(ix+nn)
{
   return cpu->_rsb8(byte, 4);
}

BYTE CPU::_oplx_A8(CPU* cpu, BYTE byte) // res 5,(ix+nn)
{
   return cpu->_rsb8(byte, 5);
}

BYTE CPU::_oplx_B0(CPU* cpu, BYTE byte) // res 6,(ix+nn)
{
   return cpu->_rsb8(byte, 6);
}

BYTE CPU::_oplx_B8(CPU* cpu, BYTE byte) // res 7,(ix+nn)
{
   return cpu->_rsb8(byte, 7);
}

BYTE CPU::_oplx_C0(CPU* cpu, BYTE byte) // set 0,(ix+nn)
{
   return cpu->_stb8(byte, 0);
}

BYTE CPU::_oplx_C8(CPU* cpu, BYTE byte) // set 1,(ix+nn)
{
   return cpu->_stb8(byte, 1);
}

BYTE CPU::_oplx_D0(CPU* cpu, BYTE byte) // set 2,(ix+nn)
{
   return cpu->_stb8(byte, 2);
}

BYTE CPU::_oplx_D8(CPU* cpu, BYTE byte) // set 3,(ix+nn)
{
   return cpu->_stb8(byte, 3);
}

BYTE CPU::_oplx_E0(CPU* cpu, BYTE byte) // set 4,(ix+nn)
{
   return cpu->_stb8(byte, 4);
}

BYTE CPU::_oplx_E8(CPU* cpu, BYTE byte) // set 5,(ix+nn)
{
   return cpu->_stb8(byte, 5);
}

BYTE CPU::_oplx_F0(CPU* cpu, BYTE byte) // set 6,(ix+nn)
{
   return cpu->_stb8(byte, 6);
}

BYTE CPU::_oplx_F8(CPU* cpu, BYTE byte) // set 7,(ix+nn)
{
   return cpu->_stb8(byte, 7);
}


////////////////////////////////

void CPU::_opDDFD(CPU* cpu, BYTE opcode)
{
// offsets to b,c,d,e,h,l,<unused>,a  from CPU::A
static unsigned reg_offset[] = { 2,1, 4,3, 6,5, 7,0 };

   BYTE op1 = 0; // last DD/FD prefix
   do
   {
      op1 = opcode;
      opcode = cpu->cycle();
   }
   while ((opcode | 0x20) == 0xFD); // opcode == DD/FD

   if (opcode == 0xCB)
   {
      WORD ptr = ((op1 == 0xDD) ? cpu->regP.IX : cpu->regP.IY) + (signed char)cpu->pMemory->read(cpu->regP.PC++);
      // DDCBnnXX,FDCBnnXX increment R by 2, not 3!
      opcode = cpu->cycle();
      cpu->R--;
      BYTE byte = (pLogX[opcode])(cpu, cpu->pMemory->read(ptr));
      if ((opcode & 0xC0) == 0x40)
      {
          cpu->ticks += 8;
          return;
      } // bit n,rm

      // select destination register for shift/res/set
      *(&cpu->regB.A + reg_offset[opcode & 7]) = byte;
      cpu->pMemory->write(ptr, byte);
      cpu->ticks += 11;
      return;
   }

   if (opcode == 0xED)
   {
      opcode = cpu->cycle();
      (pOpsED[opcode])(cpu);
      return;
   }

   // one prefix: DD/FD
   ((op1 == 0xDD) ? pOpsDD[opcode] : pOpsFD[opcode])(cpu);
}

//extended commands

void CPU::_opExtBreakpoint(CPU* pCPU)
{
	if (Configure::SYSExtCommands)
	{
		ZXLin->pComputer->pDebugger->setBreakPoint(pCPU->regP.PC);
	}
}

void CPU::_opExtCaps(CPU* pCPU)
{
	if (Configure::SYSExtCommands)
	{
		pCPU->regB.A = 1;	//support ext commands
	}
}

//HLDE = ticks from int
void CPU::_opExtIntTicks(CPU* pCPU)
{
	if (Configure::SYSExtCommands)
	{
		pCPU->regP.DE = pCPU->ticks >> 16;
		pCPU->regP.HL = pCPU->ticks & 0xffff;
	}
}

//DE'HL'DEHL = timeticks
void CPU::_opExtTotalTicks(CPU* pCPU)
{
	if (Configure::SYSExtCommands)
	{
		pCPU->DE_ = pCPU->timeticks >> 48;
		pCPU->HL_ = (pCPU->timeticks >> 32) & 0xffff;
		pCPU->regP.DE = (pCPU->timeticks >> 16) & 0xffff;
		pCPU->regP.HL = pCPU->timeticks & 0xffff;
	}
}
