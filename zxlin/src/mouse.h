/***************************************************************************
                          mouse.h  -  description
                             -------------------
    begin                : ??? ??? 16 2005
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

#ifndef MOUSE_H
#define MOUSE_H

#include <device.h>
#include <SDL/SDL.h>


/**
  *@author vitaly
  */

// emulated mouse device

class Mouse : public Device
{
public:
    Mouse(Computer* pComp);
    virtual ~Mouse();

    virtual unsigned inByte(WORD adr, BYTE* data);
    virtual unsigned outByte(WORD, BYTE) {return 1;};
    virtual void reset() {};
    virtual void showState(GfxControl* pControl, unsigned full);

    void setState(unsigned x, unsigned y, Uint8 state, Uint8* pState);

private:
    unsigned scaned;
    unsigned xpos;
    unsigned ypos;
    unsigned keys;
    unsigned joykeys;
};

#endif
