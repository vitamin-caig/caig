/***************************************************************************
                          context.cpp  -  description
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

#include "context.h"
#include "debugger.h"

///ABBY: Inherited changes from CPU, (unnamed structs->regB, regP)
const unsigned Context::map[4][4] = {
  { 2,  3,  0,  0},
  { 6,  7,  8,  9},
  {11, 12, 13, 14},
  { 4,  5,  1,  0}
};

Context::Context(CPU* cpu, unsigned x, unsigned y) : TextMatrix(x, y, 32, 5)
{
    row = column = 0;
    pCPU = cpu;
    update(FALSE);
    pEditor = NULL;
}

Context::~Context()
{

}

void Context::update(unsigned focused)
{
static char context[256];
BYTE flag = pCPU->regB.F;

    sprintf(context, "PC %04X SP %04X Time %06lu    \n"
                     "AF %04X BC %04X DE %04X HL %04X\n"
                     "AF'%04X BC'%04X DE'%04X HL'%04X\n"
                     "IX %04X IY %04X IR %04X im %02X\n"
                     "Flag %c%c%c%c%c%c%c%c iff1 %i iff2 %i"
      ,
            pCPU->regP.PC, pCPU->regP.SP, pCPU->ticks,
            pCPU->regP.AF, pCPU->regP.BC, pCPU->regP.DE, pCPU->regP.HL,
            pCPU->AF_, pCPU->BC_, pCPU->DE_, pCPU->HL_,
            pCPU->regP.IX, pCPU->regP.IY, (pCPU->I << 8) + pCPU->R, pCPU->im,
            flag & 128 ? 'S' : '-',
            flag & 64  ? 'Z' : '-',
            flag & 32  ? '1' : '0',
            flag & 16  ? 'H' : '-',
            flag & 8   ? '1' : '0',
            flag & 4   ? 'P' : 'O',
            flag & 2   ? 'N' : '-',
            flag & 1   ? 'C' : '-',
            pCPU->iff1, pCPU->iff2
            );

    background(focused ? COLOR_FOCUSED : COLOR_MATRIX);
    print(0, 0, context, focused ? COLOR_FOCUSED : COLOR_MATRIX);
    if (focused)
    {
        memcpy(context, context + 32 * row + 8 * column + 3, 4);
        context[4] = 0;
        print(column * 8 + 3, row, context, COLOR_SELECTED);
    }
}

unsigned Context::keyPress(SDL_keysym* pKey)
{
static WORD reg = 0;

    if (pEditor)
    {
        if (! pEditor->keyPress(pKey))
        {
            delete pEditor;
            pEditor = NULL;
            *(&pCPU->dummy + map[row][column]) = reg;
            update(TRUE);
        }
        return 1;
    }

    switch(pKey->sym)
    {
        case SDLK_DOWN:
            do
            {
                row = (row + 1) & 3;
            }
            while (! map[row][column]);
            update(TRUE);
            break;

        case SDLK_UP:
            do
            {
                row = (row - 1) & 3;
            }
            while (! map[row][column]);
            update(TRUE);
            break;

        case SDLK_LEFT:
            do
            {
                column = (column - 1) & 3;
            }
            while (! map[row][column]);
            update(TRUE);
            break;

        case SDLK_RIGHT:
            do
            {
                column = (column + 1) & 3;
            }
            while (! map[row][column]);
            update(TRUE);
            break;

        case SDLK_RETURN:
            reg = *(&pCPU->dummy + map[row][column]);
            pEditor = new WordEditor(this, column * 8 + 3, row, &reg);
            break;

        default:
            return 0;
        }
    return 1;
}
