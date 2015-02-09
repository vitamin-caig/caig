/***************************************************************************
                          keyboard.h  -  description
                             -------------------
    begin                : ??? ??? 29 2005
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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "iomanager.h"
#include <SDL/SDL.h>

/**
  *@author vitaly
  */

// keyboard input class

class Keyboard : public Device
{
public:
    Keyboard(Computer* pComp);
    virtual ~Keyboard();

    virtual void reset() {}
    virtual unsigned inByte(WORD port, BYTE* data);
	virtual unsigned outByte(WORD port, BYTE data);
    virtual void showState(GfxControl* pControl, unsigned full);
    void setState(unsigned x, unsigned y, Uint8 state, Uint8* pState);

private:
    unsigned keypolling;
    BYTE keydatas[8];
};

#endif
