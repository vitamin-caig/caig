/***************************************************************************
                          zxlin.h  -  description
                             -------------------
    begin                : ����12 21:05:58 MSK 2005
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

#ifndef ZXLIN_H
#define ZXLIN_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "types.h"

#include "debugger.h"

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include "configure.h"
#include "cuilib.h"

/** Zxlin is the base class of the project */
class Zxlin
{
public:
    Zxlin();
    virtual ~Zxlin();

    void run();
    void draw();

    unsigned openFile(const char* filename);

public:
    virtual void keyPressEvent(SDL_keysym* pKey);
    virtual void threadEvent();

public:
    Computer* pComputer;
    Configure* pConfigure;
    CUIControl* pCUIControl;
    GfxControl* pGfxControl;

private:
    SDL_Thread* pThread;
    unsigned paused;
    unsigned fullScr;
    unsigned inputLock;
    unsigned watchdog;
};
#endif
