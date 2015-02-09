/***************************************************************************
                          iomanager.cpp  -  description
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

#include "iomanager.h"
#include "zxlin.h"
#include <stdio.h>

IOManager::IOManager()
{
#ifdef _DEBUG_
    printf("IOManager\n");
#endif
}

IOManager::~IOManager()
{
#ifdef _DEBUG_
    printf("~IOManager\n");
#endif
}

void IOManager::reset()
{
Device* pDev = NULL;
QPtrListIterator<Device> iDev(unbuff);

	while ((pDev = iDev.current()) != NULL)
    {
        ++iDev;
        pDev->reset();
    }
	iDev = QPtrListIterator<Device>(buff);
	while ((pDev = iDev.current()) != NULL)
	{
		++iDev;
		pDev->reset();
	}
}

unsigned IOManager::inByte(WORD addr)
{
BYTE temp = 0xff;
Device* pDev = NULL;
QPtrListIterator<Device> iDev(unbuff);

    while ((pDev = iDev.current()) != NULL)
    {
        ++iDev;
        if (pDev->inByte(addr, &temp)) return temp;
    }
	iDev = QPtrListIterator<Device>(buff);
	while ((pDev = iDev.current()) != NULL)
	{
		++iDev;
		if (pDev->inByte(addr, &temp)) return temp;
	}
    return 0xff;
}

void IOManager::outByte(WORD addr, BYTE data)
{
Device* pDev = NULL;
QPtrListIterator<Device> iDev(unbuff);

    while ((pDev = iDev.current()) != NULL)
    {
        ++iDev;
        if (! pDev->outByte(addr, data)) return;
    }
	iDev = QPtrListIterator<Device>(buff);
	while ((pDev = iDev.current()) != NULL)
	{
		++iDev;
		if (! pDev->outByte(addr, data)) return;
	}
}

void IOManager::showState(unsigned full)
{
Device* pDev = NULL;
QPtrListIterator<Device> iDev(unbuff);

    while ((pDev = iDev.current()) != NULL)
    {
        ++iDev;
        pDev->showState(::ZXLin->pGfxControl, full);
    }
	iDev = QPtrListIterator<Device>(buff);
	while ((pDev = iDev.current()) != NULL)
	{
		++iDev;
		pDev->showState(::ZXLin->pGfxControl, full);
	}
}

void IOManager::addDevice(Device* pDevice, unsigned buffered)
{
	if (buffered)
    	buff.append(pDevice);
	else
		unbuff.append(pDevice);
}

unsigned IOManager::deleteDevice(Device* pDevice, unsigned buffered)
{
	if (buffered)
		return buff.removeRef(pDevice);
	else
		return unbuff.removeRef(pDevice);
}
