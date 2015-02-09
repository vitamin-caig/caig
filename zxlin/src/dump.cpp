/***************************************************************************
                          dump.cpp  -  description
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

#include "dump.h"
#include "dumpeditor.h"
#include "wordeditor.h"
#include "debugger.h"

Dump::Dump(Debugger* pPar, Computer* computer, unsigned x, unsigned y) : TextMatrix(x, y, 69, 9)
{
    pParent = pPar;
    viewPos = 0;
    column = string = 0;
    pMemory = computer->pMemory;
    pEditor = NULL;
    update(FALSE);
}

Dump::~Dump()
{

}

unsigned Dump::keyPress(SDL_keysym* pKey)
{
static WORD addr = 0;
static BYTE dump[16];

    if (pEditor)
    {
        if (! pEditor->keyPress(pKey))
        {
            delete pEditor;
            pEditor = NULL;
            if (column)
            {
               for (int i = 0; i < 16; i++)
                    pMemory->write(addr + i, dump[i]);
               pParent->update();
            }
            else
            {
               addr &= 0xfff0;
               viewPos = addr - (string << 4);
            }
            update(TRUE);
        }
        return 1;
    }

    switch (pKey->sym)
    {
        case SDLK_RETURN:
            addr = viewPos + (string << 4);
            if (column)
            {
                for (int i = 0; i < 16; i++)
                    dump[i] = pMemory->read(addr + i);
                pEditor = new DumpEditor(this, 5, string + 1, dump, 16);
            }
            else
                pEditor = new WordEditor(this, 0, string + 1, &addr);
            break;

        case SDLK_UP:
            if (string)
                string--;
            else
                viewPos -= 16;
            update(TRUE);
            break;

        case SDLK_DOWN:
            if (string == 7)
                viewPos += 16;
            else
                string++;
            update(TRUE);
            break;

        case SDLK_LEFT:
        case SDLK_RIGHT:
            column ^= 1;
            update(TRUE);
            break;

        case SDLK_PAGEUP:
            viewPos -= 128;
            update(TRUE);
            break;

        case SDLK_PAGEDOWN:
            viewPos += 128;
            update(TRUE);
            break;

        default:
            return 0;
    }
    return 1;
}

void Dump::update(unsigned focused)
{
char str[65];

    BYTE colr = 0, color = focused ? COLOR_FOCUSED : COLOR_MATRIX;
    background(color);

    print(0, 0, "addr +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F 0123456789ABCDEF", (color & 240) + 10);

    for (unsigned i = 0; i < 8; i++)
    {
        color = (i == string) ? COLOR_SELECTED : COLOR_FOCUSED;

        colr = column ? COLOR_FOCUSED : color;
        if (! focused) colr = COLOR_MATRIX;
        sprintf(str, "%04X", WORD(viewPos + (i << 4)));
        print(0, i + 1, str, colr);
        for (unsigned j = 0; j < 16; j++)
        {
            BYTE c = pMemory->read(viewPos + (i << 4) + j);
            sprintf(str + j * 3, "%02X", c);
            str[j * 3 + 2] = ' ';
            if (c == '\n' || c == '\0') c = '.';
            str[j + 48] = c;
        }
        str[64] = 0;
        colr = column ? color : COLOR_FOCUSED;
        if (! focused) colr = COLOR_MATRIX;
        print(5, i + 1, str, colr);
    }
}
