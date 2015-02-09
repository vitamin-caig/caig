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
#include "dma.h"
#include "computer.h"

//mode register
#define MR_MODE 3
#define MR_WRITE 0
#define MR_READ 2
#define MR_AUTOINIT 4
#define MR_DECREMENT 8
#define MR_TYPE 96
#define MR_ONDEMAND 0
#define MR_SINGLE 32
#define MR_BLOCK 64
#define MR_CASCADE 96

//command register
#define CR_MEMMEMENA 1
#define CR_FIXADRCH0 2
#define CR_BLOCKCTRL 4
#define CR_PACKTIME 8
#define CR_CYCPRIO 16
#define CR_EXTWRITE 32
#define CR_LOWDREQ 64
#define CR_LOWDACK 128

//status register
#define SR_CHAN0FIN 1
#define SR_CHAN1FIN 2
#define SR_CHAN2FIN 4
#define SR_CHAN3FIN 8
#define SR_CHAN0REQ 16
#define SR_CHAN1REQ 32
#define SR_CHAN2REQ 64
#define SR_CHAN3REQ 128

//mask register
#define MSKR_CHAN0BLK 1
#define MSKR_CHAN1BLK 2
#define MSKR_CHAN2BLK 4
#define MSKR_CHAN3BLK 8

//request register
#define RR_CHAN0REQ 1
#define RR_CHAN1REQ 2
#define RR_CHAN2REQ 4
#define RR_CHAN4REQ 8

//timer flags
#define TMC_BCDMASK 1
#define TMC_MODEMASK 14
#define TMC_LDMODE 48



DMA::DMA(Computer* pComp) : Device(pComp)
{
	pComputer->pIOManager->addDevice(this, FALSE);
	pComputer->pSndManager->addDevice(this);
	reset();
}


DMA::~DMA()
{
	pComputer->pSndManager->deleteDevice(this);
	pComputer->pIOManager->deleteDevice(this, FALSE);
}

void DMA::reset()
{
	memset(&banks, 0, (&RR - banks + 1) * sizeof(unsigned));
	MSKR = 15;	//block all channels
}

unsigned DMA::outByte(WORD port, BYTE data)
{
	if ((port & 0xff) == 0x77)
	{
		unsigned bus = port >> 8;
		switch (bus)
		{
			//volume
			case 0x3f:
				volume[0] = (data & 63);
				break;
			case 0x7f:
				volume[1] = (data & 63);
				break;
			case 0xbf:
				volume[2] = (data & 63);
				break;
			case 0xff:
				volume[3] = (data & 63);
				break;

			//timers
			case 0x3d:
			case 0x7d:
			case 0xbd:
			case 0xfd:
				timer[0].writeReg(bus >> 6, data);
				break;

			case 0x3e:
			case 0x7e:
			case 0xbe:
			case 0xfe:
				timer[1].writeReg(bus >> 6, data);
				break;

			//banks
			case 0x07:
			case 0x17:
			case 0x27:
			case 0x37:
				banks[bus >> 4] = data;
				break;

			//load CAR and BAR
			case 0x0c:
			case 0x2c:
			case 0x4c:
			case 0x6c:
				bus >>= 5;
				writeReg(BAR + bus, data);
				CAR[bus] = BAR[bus];
				//writeReg(CAR + bus, data);
				break;

			//load cwcr and bwcr
			case 0x1c:
			case 0x3c:
			case 0x5c:
			case 0x7c:
				bus >>= 5;
				writeReg(BWCR + bus, data);
				CWCR[bus] = BWCR[bus];
				//writeReg(CWCR + bus, data);
				break;

			//load cr
			case 0x8c:
				CR = data;
				break;

			//load rr
			case 0x9c:
				bus = 1 << (data & 3);
				if (data & 4)
					RR |= bus;
				else
					RR &= ~bus;
				break;

			//write mask bit
			case 0xac:
				bus = 1 << (data & 3);
				if (data & 4)
					MSKR |= bus;
				else
					MSKR &= ~bus;
				break;

			//write mode bit
			case 0xbc:
				MR[data & 3] = data >> 2;
				break;

			case 0xcc:
				lastfirst = FALSE;
				break;

			case 0xdc:
				reset();
				break;

			case 0xec:
				MSKR = 0;
				break;

			case 0xfc:
				MSKR = data;
				break;
		}
		return FALSE;
	}

	return TRUE;
}

unsigned DMA::inByte(WORD port, BYTE* data)
{
	if ((port & 0xff) == 0x77)
	{
		unsigned bus = port >> 8;
		switch (bus)
		{
			//read CAR
			case 0x0c:
			case 0x2c:
			case 0x4c:
			case 0x6c:
				*data = readReg(CAR + (bus >> 5));
				return TRUE;

			//read CWCR
			case 0x1c:
			case 0x3c:
			case 0x5c:
			case 0x7c:
				*data = readReg(CWCR + (bus >> 5));
				return TRUE;

			//read SR
			case 0x8c:
				*data = SR;
				SR &= 0xf0;
				return TRUE;

			//read TR
			case 0xdc:
			case 0xfc:
				*data = TR;
				return TRUE;
		}
	}

	return FALSE;
}

void DMA::showState(GfxControl* pControl, unsigned full)
{
	/*
	if (full)
	{
		char tmp[400];
		sprintf(tmp, "Ch  BBBAR BWCR MR vol frq");
		pControl->printMask(640 - 30 * 8, 480 - 6 * 16, tmp, 0xffffff, 0);
		for (int i = 0; i < 4; i++)
		{
			sprintf(tmp, " %x %02x%04x %04x %02x %03i %i",
					i, banks[i], BAR[i], BWCR[i], MR[i], volume[i], 3500000 / ((unsigned(timer[i / 2].chans[i & 1].buffer) - 1) & 0xffff) + 1);
			pControl->printMask(640 - 30 * 8, 480 - 5 * 16 + i * 16, tmp, 0xffffff, 0);
		}
		sprintf(tmp, "SR:%02x CR:%02x MSKR:%01x RR:%01x", SR, CR, MSKR, RR);
		pControl->printMask(640 - 30 * 8, 480 - 16, tmp, 0xffffff, 0);
	}
	*/
}

void DMA::writeReg(unsigned* pReg, unsigned data)
{
	if (lastfirst)
		*pReg = (*pReg & 0xff) | (data << 8);
	else
		*pReg = (*pReg & 0xff00) | data;
	lastfirst = !lastfirst;
}

unsigned DMA::readReg(unsigned* pReg)
{

	return (lastfirst = !lastfirst) ? (*pReg & 0xff) : (*pReg >> 8);
}

void DMA::getLevel(int* left, int* right, unsigned)
{
static long long oldticks = 0;

	if (! (CR & CR_BLOCKCTRL) && (MSKR & 15) != 15)
	{
		//no block mode!!!
		unsigned ticks = pComputer->pCPU->timeticks - oldticks;
		while (ticks > 0)
		{
			unsigned rest = 0xfffff;
			unsigned t = 0;
			t = timer[0].chans[0].rest();
			if (t < rest) rest = t;
			t = timer[0].chans[1].rest();
			if (t < rest) rest = t;
			t = timer[1].chans[0].rest();
			if (t < rest) rest = t;
			t = timer[1].chans[1].rest();
			if (t < rest) rest = t;

			if (rest > ticks) rest = ticks;

			unsigned msk = timer[1].step(1, rest);
			msk <<= 1;
			msk |= timer[1].step(0, rest);
			msk <<= 1;
			msk |= timer[0].step(1, rest);
			msk <<= 1;
			msk |= timer[0].step(0, rest);
			msk <<= 4;
			SR |= msk;
			if (! (MSKR & 0x01) && (SR & 0x10))
				step(0);
			else if (! (MSKR & 0x02) && (SR & 0x20))
					step(1);
			else if (! (MSKR & 0x04) && (SR & 0x40))
					step(2);
			else if (! (MSKR & 0x08) && (SR & 0x80))
					step(3);

			ticks -= rest;
		}
	}
	*left = (volume[0] * values[0] + volume[1] * values[1]) - 32768;
	*right = (volume[2] * values[2] + volume[3] * values[3]) - 32768;
	oldticks = pComputer->pCPU->timeticks;
}


unsigned DMA::stepping()
{
unsigned res = FALSE;
	//no int generating
	if (CR & CR_BLOCKCTRL) return FALSE;//controller blocked

	return res;
}


void DMA::step(unsigned chan)
{
BYTE* ptr = pComputer->pMemory->getPage(4 * banks[chan]);

	RR &= ~(1 << chan);
	SR &= ~(0x10 << chan);
	CWCR[chan] = (--CWCR[chan]) & 0xffff;
	if (! CWCR[chan])
	{
		SR |= 1 << chan;
		if (MR[chan] & MR_AUTOINIT)
		{
			CAR[chan] = BAR[chan];
			CWCR[chan] = BWCR[chan];
		}
		else
		{
			MSKR |= 1 << chan;	//mask channel
			return;
		}
	}
	/*
	if ((CR & CR_MEMMEMENA) & !(chan & 2))
	{
		if (chan)
			ptr[CAR[1]] = TR;
		else
		{
			TR = ptr[CAR[0]];
			if (! (CR_FIXADRCH0))
			{
				if (MR[0] & MR_DECREMENT)
					CAR[0]--;
				else
					CAR[0]++;
			}
		}
	}
	else*/
	{
//		if ((MR[chan] & MR_MODE) == MR_WRITE)
		{
			values[chan] = ptr[CAR[chan]];
		}

		if (MR[chan] & MR_DECREMENT)
			CAR[chan]--;
		else
			CAR[chan]++;
	}
	CAR[chan] &= 0xffff;
	//continue?
	if ((MR[chan] & MR_CASCADE) == MR_BLOCK)
	{
		RR |= 1 << chan;
		SR |= 0x10 << chan;
	}
}

////--- timer ---------

void DMA::Timer::writeReg(unsigned reg, unsigned data)
{
tmr_chan* pC = NULL;
//gate is always hi
	if (reg == 3)	//control word
	{
		pC = chans + (data >> 6);
		if ((data & 192) == 192) return;
		if (! (data & TMC_LDMODE))	//lock
		{
			pC->lohi = pC->counter;
			if (pC->mode & 16) pC->lohi |= 0x0010000;
			if (pC->mode & 32) pC->lohi |= 0x1000000;
		}
		else
			pC->mode = data & 63;
	}
	else
	{
		//load counter
		pC = chans + reg;
		//ld lo ld hi
		if (pC->lohi & 0x10000)	//lock word
			pC->lohi = ! (pC->mode & 16);//0 for lo and lohi
		pC->buffer = pC->lohi ? ((pC->buffer & 0xff) | (data << 8)) : ((pC->buffer & 0xff00) | data);
		if ((pC->mode & TMC_LDMODE) == TMC_LDMODE)
			pC->lohi = !pC->lohi;
	}
}



unsigned DMA::Timer::readReg(unsigned chan)
{
	if (chan == 3) return 0xff;
	tmr_chan* pC = chans + chan;
	unsigned result = 0;
	if (! (pC->lohi & 0x10000))
		pC->lohi = pC->counter;

	switch (pC->mode & TMC_LDMODE)
	{
		case 0:	//lock??
			return 0xff;
			break;
		case 0x20://hi
			pC->lohi >>= 8;
			break;
	}

	result = pC->lohi & 0xff;
	pC->lohi >>= 8;
	return result;
}

unsigned DMA::Timer::tmr_chan::rest()
{
unsigned res = 0;
/*
	if (mode & TMC_BCDMASK)
	{
		res = (counter & 15) + ((counter & 0xf0) >> 4) * 10 + ((counter & 0xf00) >> 10) * 100 + ((counter & 0xf000) >> 12) * 1000;
		if (! res) res = 9999;
	}
	else*/
	{
		res = counter;
		if (! res) res = 0x10000;
	}
	return res;
}

unsigned DMA::Timer::tmr_chan::skip(unsigned skp)
{
	/*
	if (mode & TMC_BCDMASK)
	{
		return FALSE;
	}
	else
	*/
	{
		counter -= skp;
		counter &= 0xffff;
		return (counter + skp) >= 0x10000;
	}
}

unsigned DMA::Timer::tmr_chan::dec()
{
	counter--;
	counter &= 0xffff;
	/*
	if (mode & TMC_BCDMASK)
	{
		if ((counter & 0x0f) == 0x0f)
		{
			counter = (counter & 0xfff0) | 0x09;
			counter -= 0x10;
			if ((counter & 0xf0) == 0xf0)
			{
				counter = (counter & 0xff0f) | 0x90;
				counter -= 0x100;
				if ((counter & 0xf00) == 0xf00)
				{
					counter = (counter & 0xf0ff) | 0x900;
					counter -= 0x1000;
					if ((counter & 0xf000) == 0xf000)
						counter = (counter & 0xfff) | 0x9000;
				}
			}
		}
	}
	*/
	return !counter;
}

unsigned DMA::Timer::step(unsigned chan)
{
tmr_chan* pC = chans + chan;


	if ((pC->mode & TMC_MODEMASK) == (2 << 1) ||
			(pC->mode & TMC_MODEMASK) == (6 << 1))
	{
		if (pC->dec())
		{
			pC->counter = (pC->counter + pC->buffer) & 0xffff;
			return TRUE;
		}
	}
	return FALSE;
}

unsigned DMA::Timer::step(unsigned chan, unsigned skp)
{
	tmr_chan* pC = chans + chan;

	//only mode2
	if ((pC->mode & TMC_MODEMASK) == (2 << 1) ||
			(pC->mode & TMC_MODEMASK) == (6 << 1))
	{
		if (pC->skip(skp))
		{
			pC->counter = (pC->counter + pC->buffer) & 0xffff;
			return TRUE;
		}
	}
	return FALSE;
}
