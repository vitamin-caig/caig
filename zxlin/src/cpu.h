/***************************************************************************
                          cpu.h  -  description
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
 ***************************************************************************/

#ifndef CPU_H
#define CPU_H


/**
  *@author vitaly
  */

#include "types.h"
#include "iomanager.h"
#include "memory.h"

#define CF  1
#define NF  2
#define PV  4
#define F3  8
#define HF  16
#define F5  32
#define ZF  64
#define SF  128

class Zxlin;

class CPU;
typedef void (*CPUFUNC)(CPU*);
typedef BYTE (*LOGXFUNC)(CPU*, BYTE);

// cpu class

class CPU
{
public:
    CPU(Memory* pMem, IOManager* pIO);
    ~CPU();

    void reset();
    void NMI();

    void loop();
    void step();
    BYTE cycle();

    friend class Computer;
private:
// universal operations for groups of operations
    void _push(WORD val);
    void _pop(WORD& val);
    void _inc8(BYTE& reg);
    void _dec8(BYTE& reg);
    void _add8(BYTE reg);
    void _adc8(BYTE reg);
    void _sub8(BYTE reg);
    void _sbc8(BYTE reg);
    void _cpr8(BYTE reg);
    void _and8(BYTE reg);
    void _orl8(BYTE reg);
    void _xor8(BYTE reg);
    void _bit8(BYTE reg, BYTE bit);
    void _res8(BYTE& reg, BYTE bit);
    void _set8(BYTE& reg, BYTE bit);
    BYTE _rsb8(BYTE reg, BYTE bit);
    BYTE _stb8(BYTE reg, BYTE bit);
    void _rl8(BYTE& reg);
    void _rr8(BYTE& reg);
    #include "cpu_funcs.h"

private:
// calculating lookup-tables
    static const BYTE pMask[8];
    static const BYTE pINCF[256];   // inc flags
    static const BYTE pDECF[256];   // dec flags
    static const BYTE pDAAF[4096];  // daa flags
    static const BYTE pRLCF[256];   // rlc flags
    static const BYTE pRRCF[256];   // rrc flags
    static const BYTE pRL0[256];    // rl flags
    static const BYTE pRL1[256];    //
    static const BYTE pRR0[256];    // rr flags
    static const BYTE pRR1[256];    //
    static const BYTE pSRAF[256];   // sra flags

    static BYTE pADCF[0x20000];    // adc flags
    static BYTE pSBCF[0x20000];    // sbc flags
    static BYTE pCPF[0x10000];     // cp flags
    static BYTE pLogF[0x100];    // logic ops flags
    static BYTE pRLCAF[0x100];   // rlca flags
    static BYTE pRRCAF[0x100];   // rrca flags
    static BYTE pROLF[0x100];     // rol flags
    static BYTE pRORF[0x100];     // ror flags

// function tables
    static CPUFUNC const pOps[256];
    static CPUFUNC const pOpsCB[256];
    static CPUFUNC const pOpsED[256];
    static CPUFUNC const pOpsDD[0x100];
    static CPUFUNC const pOpsFD[0x100];
    static LOGXFUNC const pLogX[0x100];

private:
    Memory* pMemory;
    IOManager* pManager;

public:
    BYTE im;            // int mode
    bool iff1, iff2;    // iff flags
    bool halted;        // is cpu halted
    long long timeticks;// ticks from start
    DWORD ticks;        // ticks from int
    DWORD haltpos, eipos;// info
    WORD dummy;         // dummy for alignment
    BYTE R;             // regeneration
    BYTE I;             // interrupt vector

    ///ABBY: unnamed structs is disabled... so add nameing for them... search inherited changes
    union
    {
        struct              // regpairs
        {
            WORD PC;
            WORD SP;
            WORD IX;
            WORD IY;
            WORD AF;
            WORD BC;
            WORD DE;
            WORD HL;
        } regP;
        struct
        {
            BYTE PCl;       //registers
            BYTE PCh;
            BYTE SPl;
            BYTE SPh;
            BYTE LX;
            BYTE HX;
            BYTE LY;
            BYTE HY;
            BYTE F;
            BYTE A;
            BYTE C;
            BYTE B;
            BYTE E;
            BYTE D;
            BYTE L;
            BYTE H;
        } regB;
    };

    BYTE R_h;       // high bit of R
    BYTE tmp;       // one more dummy
// alternative registers set
    WORD AF_;
    WORD BC_;
    WORD DE_;
    WORD HL_;
};

#endif
