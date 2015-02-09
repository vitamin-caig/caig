/***************************************************************************
                          mouse.cpp  -  description
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

#include "mouse.h"
#include "configure.h"
#include "computer.h"

Mouse::Mouse(Computer* pComp) : Device(pComp)
{
#ifdef _DEBUG_
    printf("Mouse\n");
#endif
	pComputer->pIOManager->addDevice(this);
    keys = 255;
    xpos = rand() % 255;
    ypos = rand() % 255;
    joykeys = 0;
}

Mouse::~Mouse()
{
	pComputer->pIOManager->deleteDevice(this);
#ifdef _DEBUG_
    printf("~Mouse\n");
#endif
}

// remapping moving and pressing to port outs
unsigned Mouse::inByte(WORD port, BYTE* data)
{
    if (! (port & 0x20))
    {
        port |= 0xfa00;
        if (port == 0xfadf)
        {
            *data = keys;
            return scaned = TRUE;
        }

        if (port == 0xfbdf)
        {
            *data = xpos;
            return scaned = TRUE;
        }

        if (port == 0xffdf)
        {
            *data = ypos;
            return scaned = TRUE;
        }
        *data = joykeys;
        return TRUE;
    }
    return FALSE;
}

void Mouse::showState(GfxControl* pControl, unsigned full)
{
    if (full && scaned && Configure::LEDMOUS_X != (unsigned)-1)
    {
        pControl->printMask(Configure::LEDMOUS_X, Configure::LEDMOUS_Y, "mouse", 0xff, 0x00);
        scaned = FALSE;
    }
}

void Mouse::setState(unsigned x, unsigned y, Uint8 state, Uint8* pState)
{
    xpos = x & 255;
    ypos = (~y) & 255;
    if (state & SDL_BUTTON_LMASK) keys &= ~1;
    if (state & SDL_BUTTON_MMASK) keys &= ~4;
    if (state & SDL_BUTTON_RMASK) keys &= ~2;
    if (! (state & (SDL_BUTTON_LMASK | SDL_BUTTON_MMASK | SDL_BUTTON_RMASK))) keys = 0xff;
    joykeys = 0;
Keymap* pMap = Configure::INKbdMap;
    while (pMap->pckey != -1)
    {
        if (pState[pMap->pckey] ==1)
        {
            if (pMap->zxkey1 >= 0x100)
                joykeys |= 1 << (pMap->zxkey1 & 0x7);
            if (pMap->zxkey2 >= 0x100)
                joykeys |= 1 << (pMap->zxkey2 & 0x7);
        }
        pMap++;
    }
}
