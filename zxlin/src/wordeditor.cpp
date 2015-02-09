/***************************************************************************
                          wordeditor.cpp  -  description
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

#include "wordeditor.h"

WordEditor::WordEditor(TextMatrix* parent, unsigned x, unsigned y, WORD* data)
 : Editor(parent, x, y, new char[5], 4)
{
    addr = data;
    sprintf(string, "%04X", *data);
    _update();
}

WordEditor::~WordEditor()
{
    delete[] string;
}

void WordEditor::endEdit()
{
unsigned tmp = 0;
    sscanf(string, "%04X", &tmp);
    *addr = tmp;
}

int WordEditor::translateSym(int symbol)
{
    if (symbol >= SDLK_0 && symbol <= SDLK_9) return symbol;
    if (symbol >= SDLK_a && symbol <= SDLK_f) return symbol;
    if (symbol == SDLK_LEFT || symbol == SDLK_RIGHT ||
        symbol == SDLK_RETURN || symbol == SDLK_ESCAPE) return symbol;
    return 0;
}
