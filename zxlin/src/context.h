/***************************************************************************
                          context.h  -  description
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

#ifndef CONTEXT_H
#define CONTEXT_H

#include "textmatrix.h"
#include "cpu.h"
#include "wordeditor.h"

// texmatrix-based class for displaying CPU context

class Context : public TextMatrix
{
public:
    Context(CPU* cpu, unsigned x, unsigned y);
    virtual ~Context();

    virtual void update(unsigned focused);
    virtual unsigned keyPress(SDL_keysym* pKey);
private:
    static const unsigned map[4][4];
    unsigned column;
    unsigned row;
    CPU* pCPU;
    Editor* pEditor;
};

#endif
