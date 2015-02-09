/***************************************************************************
                          computer.h  -  description
                             -------------------
    begin                : ??? ??? 20 2005
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

#ifndef COMPUTER_H
#define COMPUTER_H


/**
  *@author vitaly
  */

#include <SDL/SDL.h>
#include "configure.h"
#include "cpu.h"
#include "memory.h"
#include "iomanager.h"
#include "soundmanager.h"
#include "betadisk.h"
#include "ula.h"
#include "keyboard.h"
#include "mouse.h"
#include "dac.h"
#include "ay.h"
#include "dma.h"

class Debugger;

#pragma pack(1)
struct hdrSNA128
{
    BYTE i;
    WORD hl_, de_, bc_, af_;
    WORD hl, de, bc, iy, ix;
    BYTE iff1;  //00/ff
    BYTE r;
    WORD af, sp;
    BYTE im, pFE;
    BYTE page5[16384];
    BYTE page2[16384];
    BYTE actpage[16384];
    /*128k ext*/
    WORD pc;
    BYTE p7FFD, trdos;
};

struct hdrZ80
{
    BYTE a, f;
    WORD bc, hl, pc, sp;
    BYTE i, r, flags;
    WORD de, bc_, de_, hl_;
    BYTE a_, f_;
    WORD iy, ix;
    BYTE iff1, iff2, im;
    /* 2.01 ext */
    WORD len, newpc;
    BYTE model, p7FFD;
    BYTE r1, r2, p7FFD_1;
    BYTE AY[16];
};
#pragma pack()


class Computer
{
public:
    Computer();
    virtual ~Computer();

    void reset();
    unsigned frame(unsigned stepping = FALSE, unsigned rendering = TRUE);
    void tracing(unsigned tracing);
    unsigned isTracing() {return trace;}

    void visualize(unsigned fps);

    unsigned loadSna(const char* filename);
    unsigned saveSna(const char* filename);
/*
    unsigned loadZ80(const char* filename);
    unsigned saveZ80(const char* filename);
*/
private:
    void loadROM(const char* filename, unsigned rompage);

public:
    unsigned trace;
    QWORD timeStates;
    Debugger* pDebugger;        // debugger
    CPU* pCPU;                  // main part
    Memory* pMemory;            // universal device
    IOManager* pIOManager;      // universal device
    SoundManager* pSndManager;  // universal device
    BetaDisk* pBetaDisk;        // beta-disk interface
    ULA* pULA;                  // window-depending device
    Keyboard* pKbd;             // event-depending device
    Mouse* pMouse;              // event-depending device
    BYTE* pROMPage;
    unsigned maxSpeed;

    DAC* pDAC;
    AY* pAY;

	DMA* pDMA;
};

#endif
