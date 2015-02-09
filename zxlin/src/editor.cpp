/***************************************************************************
                          editor.cpp  -  description
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

#include "editor.h"
#include <string.h>

Editor::Editor(TextMatrix* parent, unsigned x, unsigned y, char* data, unsigned maxlen)
{
    pParent = parent;
    xpos = x;
    ypos = y;
    string = data;
    if (maxlen)
    {
        memset(string, 0x20, maxlen);
        string[maxlen] = 0;
    }
    maxLen = maxlen;
    cursorPos = finalized = 0;
}

void Editor::endEdit()
{
    finalized = 1;
}

int Editor::keyPress(SDL_keysym* pKey)
{
    if (finalized) return 0;
    int key = translateSym(pKey->sym);
    if (! key) return 1;
    switch (key)
    {
        case SDLK_LEFT:
            moveLeft();
            break;

        case SDLK_RIGHT:
            moveRight();
            break;

        case SDLK_DELETE:
            cursorPos++;
        case SDLK_BACKSPACE:
            if (cursorPos)
            {
                cursorPos--;
                memcpy(string + cursorPos, string + cursorPos + 1, maxLen - cursorPos);
                string[maxLen - 1] = ' ';
            }
            break;

        case SDLK_RETURN:
            endEdit();

        case SDLK_ESCAPE:
            finalized = 1;
            break;

        default:
        {
            if (key >= ' ' && key <= 'z')
            {
                string[cursorPos] = key;
                moveRight();
            }
        }
            break;
    }
    _update();
    return !finalized;
}

int Editor::translateSym(SDLKey key)
{
    return key;
}

void Editor::moveLeft()
{
     if (cursorPos)
     {
          cursorPos--;
     }
}

void Editor::moveRight()
{
     if (cursorPos < maxLen - 1)
     {
          cursorPos++;
     }
}

void Editor::_update()
{
    char* tmp = new char[maxLen + 1];
    memset(tmp, 0, maxLen + 1);
    if (cursorPos)
    {
        memcpy(tmp, string, cursorPos);
        pParent->print(xpos, ypos, tmp, COLOR_EDIT);
    }
    *tmp = string[cursorPos];
    tmp[1] = 0;
    pParent->print(xpos + cursorPos, ypos, tmp, COLOR_CURSOR);
    if (cursorPos <= maxLen)
    {
        strcpy(tmp, string + cursorPos + 1);
        pParent->print(xpos + cursorPos + 1, ypos, tmp, COLOR_EDIT);
    }
    delete[] tmp;
}

