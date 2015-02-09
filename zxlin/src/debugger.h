/***************************************************************************
                          debugger.h  -  description
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

#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <qvaluelist.h>

#include "computer.h"
#include "textmatrix.h"

// debugging providing widget

class Debugger
{
public:
    Debugger(Computer* computer);
    virtual ~Debugger();

    void toggleBreakPoint(WORD adr);    // set or reset breakpoint
    bool isBreakPoint(WORD adr);        // is there are a breakpoint
    bool _isBreakPoint(WORD adr);       // same with different
    void setBreakPoint(DWORD adr);      // set operational BP
    void update();                      // redraw

public:
    virtual void show();
    virtual void hide();

    virtual void keyPressEvent(SDL_keysym* pKey);

private:
    enum                    //panes enum
    {
        ContextPane = 0,
        DisasmPane = 1,
        DumpPane = 2,
        LastPane = 3,
        PanesTotal = LastPane
    };
    unsigned focusedPane;
    Computer* pComp;
    TextMatrix* pPane[PanesTotal];  // panes
    DWORD breakpoint;               // operational BP
    QValueList<WORD> breakPoints;   // usual BPs
};

#endif
