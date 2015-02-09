/***************************************************************************
                          textmatrix.cpp  -  description
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

#include "textmatrix.h"
#include "configure.h"
#include "zxlin.h"

const DWORD TextMatrix::palette[16] = {0x000000, 0x000080, 0x800000, 0x800080,
                                       0x008000, 0x008080, 0x808000, 0x808080,
                                       0x000000, 0x0000ff, 0xff0000, 0xff00ff,
                                       0x00ff00, 0x00ffff, 0xffff00, 0xffffff};

TextMatrix::TextMatrix(unsigned x, unsigned y, unsigned wid, unsigned hei)
{
    xpos = x;
    ypos = y;
    width = wid << 3;
    height = hei << 4;
}

TextMatrix::~TextMatrix()
{
}

//x and y in syms
void TextMatrix::print(unsigned x, unsigned y, const char* string, BYTE attributes)
{
    ::ZXLin->pGfxControl->print((x << 3) + xpos, (y << 4) + ypos, string, palette[attributes & 15], palette[attributes >> 4]);
}

void TextMatrix::background(BYTE attribute)
{
    ::ZXLin->pGfxControl->clearWindow(xpos, ypos, width, height, palette[attribute >> 4]);
}

