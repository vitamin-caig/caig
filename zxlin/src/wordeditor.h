/***************************************************************************
                          wordeditor.h  -  description
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

#ifndef WORDEDITOR_H
#define WORDEDITOR_H

#include "editor.h"

// address editor for debug controls

class WordEditor : public Editor
{
public:
    WordEditor(TextMatrix* parent, unsigned x, unsigned y, WORD* data);
    virtual ~WordEditor();
    virtual void endEdit();
    virtual int translateSym(int symbol);
private:
    WORD* addr;
};

#endif
