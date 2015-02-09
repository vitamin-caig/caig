/***************************************************************************
                          memory.h  -  description
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

#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

/**
  *@author vitaly
  */

#include "device.h"

// memory interface
enum EMemState
{
// service ROM is active
    MEMSTAT_SYSTEMROM = 1,
// trdos ROM is active
    MEMSTAT_TRDOS = 2,
// trdos ports are accessible
    MEMSTAT_DOSPORTS = 4,
// trdos will become active at 0x3dxx
    MEMSTAT_SETDOSROM = 8,
// rom will be closed if pc >= 0x4000
    MEMSTAT_LEAVEROM = 16,
// active cache
    MEMSTAT_CACHE = 32,
};

class Memory : public Device
{
public:
    Memory(Computer* pComp);
    virtual ~Memory();

    virtual unsigned outByte(WORD port, BYTE data);
    virtual void reset();
    virtual unsigned inByte(WORD port, BYTE* data);
    virtual void showState(GfxControl* pControl, unsigned full);

    void write(WORD addr, BYTE data);
    BYTE read(WORD addr);

    BYTE** getScreenSrc();

    unsigned getROMPage();
    BYTE* getROMPage(unsigned rompage);
    BYTE* getPage(unsigned page);
    void setROMPage(unsigned rompage);

    void updateState();
    static unsigned status;

    friend class Computer;

private:
    BYTE* pMem;
    BYTE* pROM;    //basic128, basic48, trdos, systemrom
    BYTE* pCache;
    BYTE* pScreen;

    unsigned romPage;
    BYTE* page0;
    BYTE* page1;
    BYTE* page2;
    BYTE* page3;
    unsigned page;

    unsigned state7ffd;
    unsigned state1ffd;
    unsigned statedffd;
    unsigned statefdfd;
};

#endif
