/***************************************************************************
                          dumpeditor.h  -  description
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

#ifndef DUMPEDITOR_H
#define DUMPEDITOR_H

#include "editor.h"

// editor-based class provides dump editing

class DumpEditor : public Editor
{
public:
    DumpEditor(TextMatrix* parent, unsigned x, unsigned y, BYTE* data, unsigned len);
    virtual ~DumpEditor();

    virtual void endEdit();
    virtual int translateSym(SDLKey key);
    virtual void moveLeft();
    virtual void moveRight();
private:
    BYTE* addr;
};

#endif
