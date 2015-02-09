/***************************************************************************
                          textmatrix.h  -  description
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

#ifndef TEXTMATRIX_H
#define TEXTMATRIX_H

#include "types.h"
#include <gfxcontrol.h>

// widget class provides console-like view

class TextMatrix
{
public:
    TextMatrix(unsigned x, unsigned y, unsigned wid, unsigned hei);
    virtual ~TextMatrix();

    virtual void update(unsigned) {};
    virtual unsigned keyPress(SDL_keysym*) {return 0;};
    void print(unsigned x, unsigned y, const char* string, BYTE attributes);

protected:
    void background(BYTE attribute);

private:
    static const DWORD palette[16];
    unsigned xpos, ypos;
    unsigned width, height;
};

#endif
