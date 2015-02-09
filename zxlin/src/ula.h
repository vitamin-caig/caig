/***************************************************************************
                          ula.h  -  description
                             -------------------
    begin                : ??? ??? 20 2005
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

#ifndef ULA_H
#define ULA_H


/**
  *@author vitaly
  */

#include "gfxcontrol.h"
#include "device.h"
#include <string.h>

class ULA : public Device, public TimetricDevice
{
public:
    ULA(Computer* pComp);
    virtual ~ULA();

// common functions
    void updateSettings();
    void setScreenSrc(BYTE** pSrc);
    void doFlash();

//---- render functions ---
    void draw(unsigned x, unsigned cntr);
    void saveShot(const char* filename);

//--- timetric device functions
    virtual void startFrame();
    virtual void renderUntil(unsigned cntr);
    virtual void retrace();

    void scaling(unsigned full);

//--- Device functions
    virtual unsigned outByte(WORD port, BYTE data);
    virtual void reset() {}
    virtual unsigned inByte(WORD, BYTE*) {return FALSE;}
    virtual void showState(GfxControl* pController, unsigned full);

private:
    void drawSingle(unsigned x, unsigned cntr);
    void drawDouble(unsigned x, unsigned cntr);

    friend class Computer;

private:
    BYTE pFE;
    BYTE flash;

    unsigned ticks;

    BYTE** pScreen;

// lookup-tables for faster rendering
    WORD pScrTab[192][256];
    WORD pAtrTab[192][256];
    DWORD pColTab[256];
    BYTE mask[256];
    unsigned leftTime[241];
    unsigned rightTime[241];
    unsigned line;
    unsigned fullscr;
};

#endif
