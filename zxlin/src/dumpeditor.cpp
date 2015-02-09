/***************************************************************************
                          dumpeditor.cpp  -  description
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

#include "dumpeditor.h"

DumpEditor::DumpEditor(TextMatrix* parent, unsigned x, unsigned y, BYTE* data, unsigned len) : Editor(parent, x, y, NULL, 0)
{
    if (len >= 16) len = 16;
    maxLen = len * 3 - 1;
    string = new char[maxLen + 1];
    addr = data;
    for (unsigned i = 0; i < len; i++)
    {
        sprintf(string + i * 3, "%02X", data[i]);
        if (i != len - 1)
            string[i * 3 + 2] = ' ';
    }
    _update();
}

DumpEditor::~DumpEditor()
{
    delete[] string;
}

void DumpEditor::endEdit()
{
unsigned tmp = 0;
    for (int i = 0; i < (maxLen + 1) / 3; i++)
    {
        sscanf(string + i * 3, "%02X", &tmp);
        addr[i] = tmp;
    }
}

int DumpEditor::translateSym(SDLKey symbol)
{
    if (symbol >= SDLK_0 && symbol <= SDLK_9) return symbol;
    if (symbol >= SDLK_a && symbol <= SDLK_f) return symbol;
    if (symbol == SDLK_LEFT || symbol == SDLK_RIGHT ||
        symbol == SDLK_RETURN || SDLK_RETURN) return symbol;
    return 0;
}

void DumpEditor::moveLeft()
{
    if (cursorPos)
    {
        cursorPos--;
        if ((cursorPos % 3) == 2) cursorPos--;
    }
}

void DumpEditor::moveRight()
{
     if (cursorPos < maxLen - 1)
     {
          cursorPos++;
          if ((cursorPos % 3) == 2) cursorPos++;
     }
}
