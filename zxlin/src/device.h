/***************************************************************************
                          device.h  -  description
                             -------------------
    begin                : ����12 2005
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
#ifndef DEVICE_H
#define DEVICE_H

#include "types.h"
#include "gfxcontrol.h"
#include <string.h>
//#include "computer.h"

class Computer;

// device interface.
// provides three functions:
// -reset (calls when computer is resetted)
// -inByte (calls when cpu reads from port). return TRUE if sets databus
// -outByte (calls when cpu writes to port). return FALSE if use databus
// -getState (calls when need to put info).
//  full = 0 (for lcd mode)- pStat = ULA*
//  full != 0 (for debug mode)- pStat = string buffer
class Device    // describes device interface
{
public:
	Device(Computer* pComp) : pComputer(pComp) {}
	virtual ~Device() {}
    virtual void reset() = 0;
    virtual unsigned inByte(WORD port, BYTE* data) = 0;
    virtual unsigned outByte(WORD port, BYTE data) = 0;
    virtual void showState(GfxControl* pController, unsigned full) = 0;
protected:
	Computer* pComputer;
};

// time-dependent device interface
// provides the next functions:
// -startFrame (calls every frame start)
// -renderUntil (calls after every command executing)
// -retrace (calls on halt to render till the end of frame)
class TimetricDevice
{
public:
	virtual ~TimetricDevice() {}
    virtual void startFrame() = 0;
    virtual void renderUntil(unsigned ticks) = 0;
    virtual void retrace() = 0;
};

// sound device interface
// provides function to return sound level after ticks
class SoundDevice
{
public:
	virtual ~SoundDevice() {}
    virtual void getLevel(int* left, int* right, unsigned ticks) = 0;
};
#endif
