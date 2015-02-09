/***************************************************************************
                          debugger.cpp  -  description
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

#include "debugger.h"
#include "context.h"
#include "disasm.h"
#include "dump.h"
#include "zxlin.h"

Debugger::Debugger(Computer* computer)
{
#ifdef _DEBUG_
    printf("Debugger\n");
#endif
    pComp = computer;
    focusedPane = ContextPane;
    breakpoint = 0x10000;

    pPane[ContextPane] = new Context(computer->pCPU, CONTEXT_X, CONTEXT_Y);
    pPane[ContextPane]->update(TRUE);

    pPane[DisasmPane] = new Disasm(this, computer, DISASM_X, DISASM_Y);

    pPane[DumpPane] = new Dump(this, computer, DUMP_X, DUMP_Y);

//    pPane[3] = new Mempager(computer, 36 * 8, 88);
}

Debugger::~Debugger()
{
    for (int i = 0; i < PanesTotal; i++)
        delete pPane[i];
#ifdef _DEBUG_
    printf("~Debugger\n");
#endif
}

void Debugger::show()
{
    pComp->tracing(TRUE);
    pComp->pULA->scaling(FALSE);
    pComp->pIOManager->showState(FALSE);
    ::ZXLin->pGfxControl->clearWindow(0, 0, W_WIDTH - 320, W_HEIGHT, 0x3030);
    ::ZXLin->pGfxControl->clearWindow(W_WIDTH - 320, 240, 320, W_HEIGHT - 240, 0x3030);
    ((Disasm*)pPane[DisasmPane])->show();
    update();
}

void Debugger::hide()
{
    pComp->pULA->scaling(TRUE);
    pComp->tracing(FALSE);
}

void Debugger::keyPressEvent(SDL_keysym* pKey)
{
    if (! pPane[focusedPane]->keyPress(pKey))
    {
        if (pKey->sym == SDLK_ESCAPE)
            hide();

        if (pKey->sym == SDLK_TAB)
        {
            focusedPane = (++focusedPane) % LastPane;
            update();
        }
    }
    ::ZXLin->pGfxControl->putBuffer();
}

void Debugger::update()
{
    for (unsigned i = 0; i < PanesTotal; i++)
        pPane[i]->update(focusedPane == i);
    pComp->pIOManager->showState(FALSE);
    ::ZXLin->pGfxControl->putBuffer();
}

void Debugger::toggleBreakPoint(WORD addr)
{
    for (QValueList<WORD>::iterator p = breakPoints.begin(); p != breakPoints.end(); ++p)
        if (*p == addr)
        {
            breakPoints.remove(p);
            return;
        }
    breakPoints.append(addr);
}

void Debugger::setBreakPoint(DWORD adr)
{
    breakpoint = adr;
}

bool Debugger::_isBreakPoint(WORD addr)
{
    return (breakPoints.findIndex(addr) != -1);
}

bool Debugger::isBreakPoint(WORD addr)
{
    if (_isBreakPoint(addr)) return TRUE;
    if (breakpoint == DWORD(addr))
    {
        breakpoint = 0x10000;
        return TRUE;
    }
    return FALSE;
}
