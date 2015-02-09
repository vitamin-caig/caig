/***************************************************************************
                          dac.h  -  description
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

#ifndef DAC_H
#define DAC_H

#include <device.h>

/**
  *@author vitaly
  */

// DAC class. provides 0xfb&0xdd covox and 0x0f,0x1f,0x4f,0x5f soundrive

class DAC : public SoundDevice, public Device
{
private:
	class Beeper : public SoundDevice, public Device
	{
	public:
		Beeper() : Device(NULL) {level = 0;}
		virtual ~Beeper() {};
		virtual void reset() {}
		virtual unsigned inByte(WORD, BYTE*) {return FALSE;}
		virtual unsigned outByte(WORD adr, BYTE data);
		virtual void showState(GfxControl*, unsigned) {}
		virtual void getLevel(int* left, int* right, unsigned ticks);
	private:
		unsigned level;
	} *pBeeper;

public:
    DAC(Computer* pComp);
    virtual ~DAC();

    virtual void reset();
    virtual unsigned inByte(WORD, BYTE*) {return FALSE;}
    virtual unsigned outByte(WORD adr, BYTE data);
    virtual void showState(GfxControl*, unsigned) {}

    virtual void getLevel(int* left, int* right, unsigned ticks);

private:
    unsigned covFBLevel;
    unsigned covDDLevel;
    unsigned sdLevels[4];
};

#endif
