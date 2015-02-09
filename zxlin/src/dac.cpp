/***************************************************************************
                          dac.cpp  -  description
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

#include "dac.h"
#include "string.h"
#include "configure.h"
#include "computer.h"

unsigned DAC::Beeper::outByte(WORD adr, BYTE data)
{
	if (! (adr & 1))
		level = (data & 16) ? 0xff : 0x00;
	return TRUE;
}

void DAC::Beeper::getLevel(int* left, int* right, unsigned)
{
	*left = *right = 64 * level * Configure::SNDVolBeepr / 100;
}

DAC::DAC(Computer* pComp) : Device(pComp)
{
#ifdef _DEBUG_
    printf("DAC\n");
#endif
	pBeeper = new Beeper;
	pComputer->pIOManager->addDevice(pBeeper, FALSE);
	pComputer->pSndManager->addDevice(pBeeper);
	pComputer->pIOManager->addDevice(this);
	pComputer->pSndManager->addDevice(this);
    reset();
}

DAC::~DAC()
{
	pComputer->pSndManager->deleteDevice(this);
	pComputer->pIOManager->deleteDevice(this);
	pComputer->pSndManager->deleteDevice(pBeeper);
	pComputer->pIOManager->deleteDevice(pBeeper);
	delete pBeeper;
#ifdef _DEBUG_
    printf("~DAC\n");
#endif
}

void DAC::reset()
{
    covFBLevel = covDDLevel = 0;
    memset(sdLevels, 0, 4 * sizeof(unsigned));
}

// dispatch
unsigned DAC::outByte(WORD adr, BYTE data)
{
    if ((adr & 0xaf)== 0x0f)
    {
        switch (adr & 0xff)
        {
            case 0x0f:
                sdLevels[0] = data;
                break;
            case 0x1f:
                sdLevels[1] = data;
                break;
            case 0x4f:
                sdLevels[2] = data;
                break;
            case 0x5f:
                sdLevels[3] = data;
        }
        return FALSE;
    }
    if (! (adr & 4))            //0xfb
    {
        covFBLevel = data;
        return FALSE;
    }
    if ((adr & 0xff) == 0xdd)    //0xdd
    {
        covDDLevel = data;
        return FALSE;
    }
	return TRUE;
}

// time-independent device, just return level
void DAC::getLevel(int* left, int* right, unsigned)
{
	*left = *right = covFBLevel * Configure::SNDVolCovFB + covDDLevel * Configure::SNDVolCovDD;
	*left += Configure::SNDVolSoundrv * (sdLevels[0] + sdLevels[1]);
	*right += Configure::SNDVolSoundrv * (sdLevels[2] + sdLevels[3]);
	*left = (*left * 128 / 400 - 32768);
	*right = (*right * 128 / 400 - 32768);
}
