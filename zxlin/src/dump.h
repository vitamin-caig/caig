/***************************************************************************
                          dump.h  -  description
                             -------------------
    begin                : ����2 2005
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

#ifndef DUMP_H
#define DUMP_H

#include "debugger.h"
#include "textmatrix.h"
#include "computer.h"
#include "editor.h"

// textmatrix-based class provides dump view

class Dump : public TextMatrix
{
public:
    Dump(Debugger* pPar, Computer* computer, unsigned x, unsigned y);
    virtual ~Dump();

    virtual void update(unsigned focused);
    virtual unsigned keyPress(SDL_keysym* pKey);

private:
    Debugger* pParent;
    Memory* pMemory;
    unsigned column;
    unsigned string;
    WORD viewPos;
    Editor* pEditor;
};

#endif
