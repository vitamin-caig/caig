/***************************************************************************
                          ay.h  -  description
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

#ifndef AY_H
#define AY_H

#include <device.h>

/**
  *@author vitaly
  */

class AY : public Device, public SoundDevice
{
public:
    AY(Computer* pComp);
    virtual ~AY();
//-- Device virtuals
    virtual void reset();
    virtual unsigned inByte(WORD adr, BYTE* data);
    virtual unsigned outByte(WORD adr, BYTE data);
    virtual void showState(GfxControl* pControl, unsigned full);
//-- SoundDevice virtuals
    virtual void getLevel(int* left, int* right, unsigned time);

private:
    int vols[2][32];  //volumes table
    unsigned selreg;     //selected register

    BYTE reg[16];   //registers
    QWORD time;     //time

    unsigned bitA, bitB, bitC, bitN;            // signal flags
    BYTE vA, vB, vC, vE;                    // volume
    WORD timeA, timeB, timeC, timeN, timeE; // timers
    int decayEnvelope;                      // decay
    DWORD vNoise;                           // noise polynome
};

#endif
