/***************************************************************************
                          memory.cpp  -  description
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

#include "memory.h"
#include "configure.h"
#include "computer.h"

#define ROM_BASIC128 (pROM + ERBasic128 * 16384)
#define ROM_BASIC48 (pROM + ERBasic48 * 16384)
#define ROM_TRDOS (pROM + ERTrDOS * 16384)
#define ROM_SYSTEM (pROM + ERSystem * 16384)

unsigned Memory::status = 0;

//ctor
Memory::Memory(Computer* pComp) : Device(pComp)
{
#ifdef _DEBUG_
    printf("Memory\n");
#endif
	pComputer->pIOManager->addDevice(this, FALSE);
//memory allocation
    pMem = new BYTE[4096 * 1024];
    pROM = new BYTE[65536];
    pCache = new BYTE[16384];
    page = 0;
    pScreen = pMem + 5 * 16384;
    romPage = ERBasic128;
    page0 = pROM;
    page1 = pScreen;
    page2 = pMem + 2 * 16384;
    page3 = pMem;
    reset();
}

Memory::~Memory()
{
	pComputer->pIOManager->deleteDevice(this, FALSE);
    delete[] pCache;
    delete[] pROM;
    delete[] pMem;
#ifdef _DEBUG_
    printf("~Memory\n");
#endif
}

unsigned Memory::outByte(WORD port, BYTE data)
{
    if (! (port & 0x02))
    {
        if (! (port & 0x8000))
        {
            //scorpion
            if (port == 0x1ffd && (Configure::MEMMemType == MEM_SCORP256 || Configure::MEMMemType == MEM_SCORP1024))
            {
                state1ffd = data;
                updateState();
                return FALSE;
            }
            //pent128
            if (state7ffd & 0x20) return FALSE;
            state7ffd = data;
            updateState();
            return FALSE;
        }

        if (port == 0xdffd && Configure::MEMMemType == MEM_PROFI1024)
        {
            statedffd = data;
            updateState();
            return FALSE;
        }

        if (port == 0xfdfd && Configure::MEMMemType == MEM_ATM512)
        {
            statefdfd = data;
            updateState();
            return FALSE;
        }
    }
    return TRUE;
}

void Memory::updateState()
{
    page1 = pMem + 5 * 16384;
    page2 = pMem + 2 * 16384;

    if (status & MEMSTAT_TRDOS)
    {
        romPage = (state7ffd & 0x10) ? ERTrDOS : ERSystem;
        status |= MEMSTAT_LEAVEROM | MEMSTAT_DOSPORTS;
    }
    else
        romPage = (state7ffd & 0x10) ? ERBasic48 : ERBasic128;

    if (status & MEMSTAT_SYSTEMROM)
    {
        romPage = ERSystem;
        status |= MEMSTAT_LEAVEROM | MEMSTAT_DOSPORTS;
    }

    page0 = pROM + romPage * 16384;
    page = state7ffd & 7;
    switch (Configure::MEMMemType)
    {
    case MEM_PENT128:
        break;
    case MEM_PENT512:
        page += (state7ffd & 0xc0) >> 3;
        break;

    case MEM_SCORP256:
    case MEM_SCORP1024:
        page += (state1ffd & 0x10) >> 1;
        if (Configure::MEMMemType == MEM_SCORP1024)
            page += (state1ffd & 0xc0) >> 2;
        if (state1ffd & 2)
        {
            page0 = ROM_SYSTEM;
            romPage = ERSystem;
            status |= MEMSTAT_DOSPORTS;
        }
        if (state1ffd & 1) page0 = pMem, romPage = ERRam;
        break;

    case MEM_PROFI1024:
        page += (statedffd & 7) << 3;
        if (statedffd & 0x10) page0 = pMem, romPage = ERRam;
        if (statedffd & 0x20) status |= MEMSTAT_DOSPORTS;
        if (statedffd & 0x40) page2 = pMem + 6 * 16384;
        break;

    case MEM_ATM512:
        page += (statefdfd & 3) << 3;
    }

    page3 = pMem + page * 16384;

    if ((state7ffd & 0x10) && !(status & MEMSTAT_TRDOS))
        status |= MEMSTAT_SETDOSROM;
    else
        status &= ~MEMSTAT_SETDOSROM;
    pScreen = pMem + 16384 * ((state7ffd & 8) ? 7 : 5);
    if (status & MEMSTAT_CACHE)
        romPage = ERCache;
}

void Memory::reset()
{
    status = 0;
    state7ffd = state1ffd = statefdfd = statedffd = 0;
    switch (Configure::SYSResetTo)
    {
    case ERTrDOS:
        status = MEMSTAT_TRDOS;
    case ERBasic48:
        state7ffd = 0x10;
        break;
    case ERSystem:
        status = MEMSTAT_SYSTEMROM;
        break;
    case ERCache:
        status = MEMSTAT_CACHE;
    }
    updateState();
}

unsigned Memory::inByte(WORD port, BYTE* data)
{
    if (Configure::MEMCacheSize)
    {
        if ((BYTE)port == 0xfb)
        {
            status |= MEMSTAT_CACHE;
            *data = 0xff;
            return TRUE;
        }
        if ((BYTE)port == 0x7b)
        {
            status &= ~MEMSTAT_CACHE;
            *data = 0xff;
            return TRUE;
        }
    }
    return FALSE;
}

void Memory::showState(GfxControl* pControl, unsigned full)
{
static const char* pgnames[] = {"Basic128", "Basic48", "TR-DOS", "Cache", "SYSTEM"};
static char text[80];
int rompag = 0;

    if (state7ffd & 0x10) rompag++;
    if (status & MEMSTAT_TRDOS) rompag = 2;
    if (status & MEMSTAT_CACHE) rompag = 3;
    if (status & MEMSTAT_SYSTEMROM) rompag = 4;
    if (!full)
    {
        pControl->clearWindow(MEMORY_X, MEMORY_Y, 112, 64, 0);
        sprintf(text, "#0000 %s\n"
                      "#4000 Page5\n"
                      "#8000 Page2\n"
                      "#C000 Page%i", pgnames[rompag], page);
        pControl->print(MEMORY_X, MEMORY_Y, text, 0xffffff, 0);
    }
}



void Memory::write(WORD addr, BYTE data)
{
    switch (addr & 0xc000)
    {
        case 0: //ROM
            if ((status & MEMSTAT_CACHE) && addr < Configure::MEMCacheSize)
                pCache[addr] = data;
            else
                if (romPage == ERRam)
                    page0[addr] = data;
            break;

        case 0x4000: //page5
            page1[addr & 0x3fff] = data;
            break;

        case 0x8000: //page2
            page2[addr & 0x3fff] = data;
            break;

        case 0xc000: //last page
            page3[addr & 0x3fff] = data;
            break;
    }
}

BYTE Memory::read(WORD addr)
{
    switch (addr & 0xc000)
    {
        case 0:
            if ((status & MEMSTAT_CACHE) && addr < Configure::MEMCacheSize)
                return pCache[addr]; //cache
            return page0[addr];

        case 0x4000: //page5
            return page1[addr & 0x3fff];

        case 0x8000: //last page
            return page2[addr & 0x3fff];

        case 0xc000: //last page
            return page3[addr & 0x3fff];
    }
	return 0xff;
}


BYTE** Memory::getScreenSrc()
{
    return &pScreen;
}


BYTE* Memory::getROMPage(unsigned rompage)
{
    return (rompage < 4) ? pROM + (rompage << 14) : NULL;
}

unsigned Memory::getROMPage()
{
    return romPage;
}

BYTE* Memory::getPage(unsigned page)
{
    return (page < 256) ? pMem + (page << 14) : NULL;
}

void Memory::setROMPage(unsigned rompage)
{
    page0 = pROM + (rompage << 14);
}
