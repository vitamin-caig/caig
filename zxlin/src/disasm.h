/***************************************************************************
                          disasm.h  -  description
                             -------------------
    begin                : ??? ??? 14 2005
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

#ifndef DISASM_H
#define DISASM_H

#include "debugger.h"
#include "computer.h"
#include "editor.h"

// textmatrix-based class provides disassembler in debugger

class Disasm : public TextMatrix
{
public:
    Disasm(Debugger* parent, Computer* computer, unsigned x, unsigned y);
    virtual ~Disasm();

    virtual void update(unsigned focused);
    virtual unsigned keyPress(SDL_keysym* pKey);

public:
    virtual void show();

private:
    static BYTE mnemotab[];
    WORD adrs[DISASM_LINES];
    WORD _up(WORD adr);
    void _reposit(WORD adr);

    WORD _getMnemo(WORD adr, char* string);
    void _getAddr(WORD adr, char* string);
    void _getHex(WORD adr, int count, char* string);

private:
    Debugger* pParent;
    Computer* pComp;
    CPU* pCPU;
    Memory* pMemory;
    WORD viewPos;
    unsigned column;
    Editor* pEditor;
    int focus;
};

#endif
