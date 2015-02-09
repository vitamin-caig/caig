/***************************************************************************
                          editor.h  -  description
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

#ifndef EDITOR_H
#define EDITOR_H

#include "textmatrix.h"

// simple string editor

class Editor
{
public:
    Editor(TextMatrix* parent, unsigned x, unsigned y, char* data, unsigned maxlen);
    virtual ~Editor() {};

    virtual void endEdit();
    virtual int keyPress(SDL_keysym* pKey);

    virtual int translateSym(SDLKey key);
    virtual void moveLeft();
    virtual void moveRight();

protected:
    virtual void _update();

protected:
    TextMatrix* pParent;
    int xpos;
    int ypos;
    char* string;
    int maxLen;
    int cursorPos;
    int finalized;
};

#endif
