/***************************************************************************
                          cpu.cpp  -  description
                             -------------------
    begin                : ??? ??? 12 2005
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
 * A big number of ideas and code was taken from UnrealSpeccy emulator     *
 * sources.                                                                *
 * Author: SMT                                                             *
 *                                                                         *
 *                                                                         *
 ***************************************************************************/

#include "cpu.h"
#include "string.h"
#include "stdio.h"
#include "cpu_tabs.h"
#include "configure.h"

/*
#ifdef DEBUG
default: printf("Error in _op_sjmp\n"); break;
#else
*/

CPU::CPU(Memory* pMem, IOManager* pIO)
{
#ifdef _DEBUG_
    printf("CPU\n");
#endif
    pMemory = pMem;
    pManager = pIO;
    reset();

int c = 0, x = 0, y = 0, i = 0, r = 0;
unsigned res = 0;
int res1 = 0;
BYTE fl = 0;

// adc flags table generating
    for (c = 0; c < 2; c++)
        for (x = 0; x < 0x100; x++)
            for (y = 0; y < 0x100; y++)
            {
                res = x + y + c;
                fl = 0;
                if (! (res & 0xFF)) fl |= ZF;
                fl |= (res & (F3 | F5 | SF));
                if (res >= 0x100) fl |= CF;
                if (((x & 0x0F) + (y & 0x0F) + c) & 0x10) fl |= HF;
                r = (signed char)x + (signed char)y + c;
                if (r >= 0x80 || r <= -0x81) fl |= PV;

                pADCF[(c << 16) + (x << 8) + y] = fl;
            }

    // sbc and cp flags generating
    for (c = 0; c < 2; c++)
        for (x = 0; x < 0x100; x++)
            for (y = 0; y < 0x100; y++)
            {
                res1 = x - y - c;
                fl = res1 & (F3 | F5 | SF);
                if (!(res1 & 0xFF)) fl |= ZF;
                if (res1 & 0x10000) fl |= CF;
                r = (signed char)x - (signed char)y - c;
                if (r >= 0x80 || r < -0x80) fl |= PV;
                if (((x & 0x0F) - (res1 & 0x0F) - c) & 0x10) fl |= HF;
                fl |= NF;
                pSBCF[(c << 16) + (x << 8) + y] = fl;
            }

   for (i = 0; i < 0x10000; i++)
      pCPF[i] = (pSBCF[i] & ~(F3|F5)) | (i & (F3|F5));

   // logic ops flags generating
   for (x = 0; x < 0x100; x++)
   {
      fl = x & (F3|F5|SF);
      BYTE p = PV;
      for (i = 0x80; i; i >>= 1)
         if (x & i) p ^= PV;
      pLogF[x] = fl | p;
   }
   *pLogF |= ZF;

   // rotation flags generating
   for (i = 0; i < 0x100; i++)
   {
      pRLCAF[i] = pRLCF[i] & 0x3B;        // rra,rla uses same tables
      pRRCAF[i] = pRRCF[i] & 0x3B;
      pROLF[i] = (i << 1) + (i >> 7);
      pRORF[i] = (i >> 1) + (i << 7);
   }
   timeticks = 0;
   reset();
}

CPU::~CPU()
{
#ifdef _DEBUG_
    printf("~CPU\n");
#endif
}


void CPU::reset()
{
    pManager->reset();
    iff1 = iff2 = halted = FALSE;
    R = I = im = 0;
    regP.PC = 0;
    ticks = haltpos = eipos = 0;
}

void CPU::NMI()
{
    _push(regP.PC);
    iff1 = halted = FALSE;
    regP.PC = 0x66;
}

//-------------------------

void CPU::_push(WORD val)
{
    pMemory->write(--regP.SP, val >> 8);
    pMemory->write(--regP.SP, val & 0xff);
}

void CPU::_pop(WORD& val)
{
    val = pMemory->read(regP.SP++) + (pMemory->read(regP.SP++) << 8);
}

// arithmetic
void CPU::_inc8(BYTE& reg)
{
   regB.F = pINCF[reg] | (regB.F & CF);
   reg++;
}

void CPU::_dec8(BYTE& reg)
{
   regB.F = pDECF[reg] | (regB.F & CF);
   reg--;
}

void CPU::_add8(BYTE reg)
{
//   BYTE carry = (regB.F & CF);
   regB.F = pADCF[regB.A + (reg << 8)];
   regB.A += reg;
}

void CPU::_adc8(BYTE reg)
{
   BYTE carry = (regB.F & CF);
   regB.F = pADCF[regB.A + (reg << 8) + (carry << 16)];
   regB.A += reg + carry;
}

void CPU::_sub8(BYTE reg)
{
   regB.F = pSBCF[(regB.A << 8) + reg];
   regB.A -= reg;
}

void CPU::_sbc8(BYTE reg)
{
   BYTE carry = (regB.F & CF);
   regB.F = pSBCF[(regB.A << 8) + reg + (carry << 16)];
   regB.A -= reg + carry;
}

void CPU::_cpr8(BYTE reg)
{
   regB.F = pCPF[(regB.A << 8) + reg];
}

// logic
void CPU::_and8(BYTE reg)
{
   regB.A &= reg;
   regB.F = pLogF[regB.A] | HF;
}

void CPU::_orl8(BYTE reg)
{
   regB.A |= reg;
   regB.F = pLogF[regB.A];
}

void CPU::_xor8(BYTE reg)
{
   regB.A ^= reg;
   regB.F = pLogF[regB.A];
}

// bit
void CPU::_bit8(BYTE reg, BYTE bit)
{
   regB.F = pLogF[reg & pMask[bit]] | HF | (regB.F & CF);
}

void CPU::_res8(BYTE& reg, BYTE bit)
{
    reg &= ~pMask[bit];
}

void CPU::_set8(BYTE& reg, BYTE bit)
{
    reg |= pMask[bit];
}

BYTE CPU::_rsb8(BYTE reg, BYTE bit)
{
    return reg & ~pMask[bit];
}

BYTE CPU::_stb8(BYTE reg, BYTE bit)
{
    return reg | pMask[bit];
}

void CPU::_rl8(BYTE& val)
{
   if (regB.F & CF)
   {
      regB.F = pRL1[val];
      val = (val << 1) + 1;
   }
   else
   {
      regB.F = pRL0[val];
      val <<= 1;
   }
}

void CPU::_rr8(BYTE& val)
{
   if (regB.F & CF)
   {
        regB.F = pRR1[val];
        val = (val >> 1) + 0x80;
   }
   else
   {
        regB.F = pRR0[val];
        val >>= 1;
    }
}

//////////////////////////////////////////////

BYTE CPU::cycle()
{
    R++;
    ticks += 4;
    return pMemory->read(regP.PC++);
}

void CPU::step()
{
    DWORD oldticks = ticks;
    if (regB.PCh && Configure::ULAEvenM1) ticks += (ticks & 1);
    BYTE opcode = cycle();
    (pOps[opcode])(this);
    timeticks += ticks - oldticks;
}
