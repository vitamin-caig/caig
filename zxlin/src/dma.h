/***************************************************************************
 *   Copyright (C) 2006 by vitaly   *
 *   vitamin@vitamin   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef DMA_H
#define DMA_H

#include "device.h"

/**
	@author vitaly <vitamin@vitamin>
*/
class DMA : public Device, public SoundDevice
{
public:
    DMA(Computer* pComp);
    virtual ~DMA();

//--- Device functions
	virtual unsigned outByte(WORD port, BYTE data);
	virtual void reset();
	virtual unsigned inByte(WORD port, BYTE* data);
	virtual void showState(GfxControl* pController, unsigned full);

//-- SoundDevice virtuals
	virtual void getLevel(int* left, int* right, unsigned time);

//--DMA-specific function
	unsigned stepping();
protected:
	void writeReg(unsigned* pReg, unsigned data);
	unsigned readReg(unsigned* pReg);

	void step(unsigned chan);
protected:

struct Timer
{
	struct tmr_chan
	{
		unsigned counter;
		unsigned buffer;
		unsigned lohi;
		unsigned mode;

		unsigned dec();
		unsigned rest();
		unsigned skip(unsigned skp);
	};
	tmr_chan chans[3];
	void writeReg(unsigned reg, unsigned data);
	unsigned readReg(unsigned chan);
	unsigned step(unsigned chan);
	unsigned step(unsigned chan, unsigned skp);
};
	unsigned banks[4];	//bank registers (hardware)
	unsigned volume[4];	//volume 6
	unsigned values[4];	//out values 8
	Timer timer[2];

	unsigned lastfirst;	//flip-flop
	unsigned BAR[4];	//base address register	16
	unsigned BWCR[4];	//base word count register 16
	unsigned CAR[4];	//current address register 16
	unsigned CWCR[4];	//current word count register 16
	unsigned TAR;		//temporary address register 16
	unsigned TWCR;		//temporary word count register 16
	unsigned SR;		//status register 8
	unsigned CR;		//command register 8
	unsigned MR[4];		//mode register 6
	unsigned TR;		//temporary register 8
	unsigned MSKR;		//mask register 4
	unsigned RR;		//request register 4
};

#endif
