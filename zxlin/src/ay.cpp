/***************************************************************************
                          ay.cpp  -  description
                             -------------------
    begin                : ??? ??? 19 2005
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

#include "ay.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "configure.h"
#include "computer.h"

// defines for registers values
#define AYFRQA ((WORD)reg[0] + ((WORD)reg[1] << 8))
#define AYFRQB ((WORD)reg[2] + ((WORD)reg[3] << 8))
#define AYFRQC ((WORD)reg[4] + ((WORD)reg[5] << 8))
#define AYFRQN reg[6]
#define AYMIXER reg[7]
#define AYVOLA reg[8]
#define AYVOLB reg[9]
#define AYVOLC reg[10]
#define AYFRQE ((WORD)reg[11] + ((WORD)reg[12] << 8))
#define AYENVE reg[13]

#define AYEXPRANGE 4

//ctor
AY::AY(Computer* pComp) : Device(pComp)
{
#ifdef _DEBUG_
    printf("AY\n");
#endif
	pComputer->pIOManager->addDevice(this);
	pComputer->pSndManager->addDevice(this);

	// creating volume table
    for (int i = 0; i < 32; i++)
	{
		vols[0][i] = (unsigned short)((16384 / AYEXPRANGE) * (exp(log(AYEXPRANGE + 1) * (i & 30) / 30) - 1)); //AY
		vols[1][i] = i * 528;	//YM
	}
    vols[1][1] = 0;
    reset();
}

//dtor
AY::~AY()
{
	pComputer->pSndManager->deleteDevice(this);
	pComputer->pIOManager->deleteDevice(this);
#ifdef _DEBUG_
    printf("~AY\n");
#endif
}

//reset. clear all registers and counters
void AY::reset()
{
    memset(reg, 0, 16);
    AYMIXER = 0xff;
    selreg = 0;
    time = 0;
    bitA = bitB = bitC = bitN = 0;
    vA = vB = vC = vE = 0;
    timeA = timeB = timeC = timeN = timeE = 0;
    decayEnvelope = 0;
}

// reading selected register
unsigned AY::inByte(WORD adr, BYTE* data)
{
    if ((adr & 0xc0ff) == 0xc0fd && selreg < 0x10)
    {
        *data = reg[selreg];
        return TRUE;
    }
    return FALSE;
}

// writing: selecting or writing register
unsigned AY::outByte(WORD adr, BYTE data)
{
    if (adr & 2) return TRUE;
// 0xfffd - selecting the register
    if ((adr & 0xc0ff) == 0xc0fd)
        selreg = Configure::SNDAYYM ? data : (data & 0x0f);   //differs in models
    else
    // 0xbffd - writing data to register
        if ((adr & 0xc000) == 0x8000)
        {
            if (selreg >= 0x10) return 1;
            if ((1 << selreg) & 0x202a) data &= 0x0f;
            if ((1 << selreg) & 0x0740) data &= 0x1f;
            reg[selreg] = data;
            if (selreg == 13)
            {
                timeE = 0;
                if (data & 4)
                {
                    vE = 0;
                    decayEnvelope = 1;
                }
                else
                {
                    vE = 31;
                    decayEnvelope = -1;
                }
            }
        }
    return FALSE;
}

void AY::showState(GfxControl* pControl, unsigned full)
{
static char szTmp[128];
    if (full)   // show volume bars
    {
        if (Configure::LEDAY_X == (unsigned)-1) return;
        pControl->clearWindow(Configure::LEDAY_X, Configure::LEDAY_Y, (AYMIXER & 1) ? 0 : ((AYVOLA & 0x0f) << 1), 3, (AYVOLA & 16) ? 0xff : 0xffffff);
        pControl->clearWindow(Configure::LEDAY_X, Configure::LEDAY_Y + 4, (AYMIXER & 2) ? 0 : ((AYVOLB & 0x0f) << 1), 3, (AYVOLB & 16) ? 0xff : 0xffffff);
        pControl->clearWindow(Configure::LEDAY_X, Configure::LEDAY_Y + 8, (AYMIXER & 4) ? 0 : ((AYVOLC & 0x0f) << 1), 3, (AYVOLC & 16) ? 0xff : 0xffffff);
		pControl->clearWindow(Configure::LEDAY_X, Configure::LEDAY_Y + 12, ((AYMIXER & 56) == 56 && ((AYVOLA | AYVOLB | AYVOLC) & 15)) ? 0 : AYFRQN, 3, 0xc040);
    }
    else
    {   //show context info
        pControl->clearWindow(AY_X, AY_Y, 40, 15 * 16, 0);
        sprintf(szTmp, "AY/YM\n"
                       "0:%02X\n1:%02X\n2:%02X\n3:%02X\n4:%02X\n"
                       "5:%02X\n6:%02X\n7:%02X\n8:%02X\n9:%02X\n"
                       "A:%02X\nB:%02X\nC:%02X\nD:%02X",
                       reg[0], reg[1], reg[2], reg[3], reg[4],
                       reg[5], reg[6], reg[7], reg[8], reg[9],
                       reg[10], reg[11], reg[12], reg[13]);
        pControl->print(AY_X, AY_Y, szTmp, 0xffffff, 0);
    }
}

// calculate volume after ticks elapsed
void AY::getLevel(int* left, int* right, unsigned ticks)
{
//envelopes
unsigned ea = (AYVOLA & 0x10) ? -1 : 0;
unsigned eb = (AYVOLB & 0x10) ? -1 : 0;
unsigned ec = (AYVOLC & 0x10) ? -1 : 0;

//volumes
    vA = (((AYVOLA & 0x0f) << 1) + 1) & ~ea;
    vB = (((AYVOLB & 0x0f) << 1) + 1) & ~eb;
    vC = (((AYVOLC & 0x0f) << 1) + 1) & ~ec;

    //rendering values
    while (ticks--)
    {
        time++;
        if (Configure::SNDAY35)
        {
            if (time & 0x07) continue;  //divide by 8
        }
        else
            if (time & 0x0f) continue;  //divide by 16
        if (++timeA >= AYFRQA)  //tmrA overflow
        {
            timeA = 0;
            bitA ^= -1;
        }
        if (++timeB >= AYFRQB)  //..B
        {
            timeB = 0;
            bitB ^= -1;
        }
        if (++timeC >= AYFRQC)  //..C
        {
            timeC = 0;
            bitC ^= -1;
        }
        if (++timeN >= AYFRQN * 2)  //..N
        {
            timeN = 0;
            vNoise = (vNoise * 2 + 1) ^ (((vNoise >> 16) ^ (vNoise >> 13)) & 1);
            bitN = (vNoise & 0x10000) ? -1 : 0;
        }
        if (++timeE >= AYFRQE)  //.E
        {
            timeE = 0;
            vE += decayEnvelope;
            if (vE & ~31)
            {
                unsigned mask = 1 << AYENVE;
                if (mask & ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) |
                    (1 << 6) | (1 << 7) | (1 << 9) | (1 << 15)))
                    vE = decayEnvelope = 0;
                else
                    if (mask & ((1 << 8) | (1 << 12)))
                        vE &= 31;
                    else
                        if (mask & ((1 << 10) | (1 << 14)))
                        {
                            decayEnvelope = -decayEnvelope;
                            vE += decayEnvelope;
                        }
                        else
                        {
                            vE = 31;
                            decayEnvelope = 0;  //11,13
                        }
            }
        }   // envelope timer overload
    }   // ticks waiting

    // creating level
	WORD en = vols[Configure::SNDAYYM][((ea & vE) | vA) & (((AYMIXER & 1) ? 0xff : bitA) & ((AYMIXER & 8) ? 0xff : bitN))];
    DWORD lft = en * Configure::SNDVolAL;
    DWORD rgt = en * Configure::SNDVolAR;
	en = vols[Configure::SNDAYYM][((eb & vE) | vB) & (((AYMIXER & 2) ? 0xff : bitB) & ((AYMIXER & 16) ? 0xff : bitN))];
    lft += en * Configure::SNDVolBL;
    rgt += en * Configure::SNDVolBR;
	en = vols[Configure::SNDAYYM][((ec & vE) | vC) & (((AYMIXER & 4) ? 0xff : bitC) & ((AYMIXER & 32) ? 0xff : bitN))];
    lft += en * Configure::SNDVolCL;
    rgt += en * Configure::SNDVolCR;
    *left = lft / 300;
    *right = rgt / 300;
}
