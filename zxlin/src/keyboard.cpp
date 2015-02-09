/***************************************************************************
                          keyboard.cpp  -  description
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

#include "keyboard.h"
#include "configure.h"
#include "computer.h"

Keyboard::Keyboard(Computer* pComp) : Device(pComp)
{
#ifdef _DEBUG_
    printf("Keyboard\n");
#endif
	pComputer->pIOManager->addDevice(this, FALSE);
    memset(keydatas, 0xff, 8);
    keypolling = 0;
}

Keyboard::~Keyboard()
{
	pComputer->pIOManager->deleteDevice(this, FALSE);
#ifdef _DEBUG_
    printf("~Keyboard\n");
#endif
}

void Keyboard::setState(unsigned, unsigned, Uint8, Uint8* pState)
{
Keymap* map = Configure::INKbdMap;

    memset(keydatas, 0xff, 8);
    while (map->pckey != -1)
    {
        if (pState[map->pckey] == 1)
        {
            if (map->zxkey1 < 0x100)
                keydatas[map->zxkey1 >> 5] &= ~(map->zxkey1 & 31);

            if (map->zxkey2 && map->zxkey2 < 0x100)
                 keydatas[map->zxkey2 >> 5] &= ~(map->zxkey2 & 31);
//            break;
        }
        map++;
    }

}

unsigned Keyboard::inByte(WORD port, BYTE* data)
{
const BYTE pollings[] = {64, 16, 4, 1, 2, 8, 32, 128};

    if (! (port & 1))
    {
        *data = 0xff;
        for (int i = 0; i < 8; i++, port >>= 1)
            if (! (port & 0x100))
            {
                keypolling |= pollings[i];
                *data &= keydatas[i];
            }
        return TRUE;
    }
    return FALSE;
}

unsigned Keyboard::outByte(WORD, BYTE)
{
	return TRUE;
}

void Keyboard::showState(GfxControl* pControl, unsigned full)
{
    if (full && Configure::LEDKBD_X != (unsigned)-1)
    {
        for (int i = 0; i < 8; i++)
        {
            pControl->clearWindow(Configure::LEDKBD_X + 16 * (i & 1), Configure::LEDKBD_Y + 4 * (i >> 1), 12, 2, (keypolling & 1) ? 0xffff00 : 0xff);
            keypolling >>= 1;
        }
    }
}
