/***************************************************************************
                          disasm.cpp  -  description
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

#include "disasm.h"

#include "wordeditor.h"
#include "dumpeditor.h"

#include "mnemotab.h"

Disasm::Disasm(Debugger* pPar, Computer* computer, unsigned x, unsigned y) : TextMatrix(x, y, 35, DISASM_LINES)
{
    pParent = pPar;
    pCPU = computer->pCPU;
    pMemory = computer->pMemory;
    pComp = computer;
    viewPos = pCPU->regP.PC;

    pEditor = NULL;
    column = 0;

    update(FALSE);
}

Disasm::~Disasm()
{

}

void Disasm::show()
{
    _reposit(pCPU->regP.PC);
}

void Disasm::_reposit(WORD addr)
{
    viewPos = addr;
    for (int i = 0; i < (DISASM_LINES >> 1); i++)
        viewPos = _up(viewPos);
    update(focus);
}

// processing input
unsigned Disasm::keyPress(SDL_keysym* pKey)
{
static WORD addr = 0;
static BYTE dump[4];
static char text[32];

    if (pEditor)
    {
        if (! pEditor->keyPress(pKey))
        {
            delete pEditor;
            pEditor = NULL;
            switch (column)
            {
                case 0:
                    viewPos = addr;
                    break;
                case 1:
                    for (int i = 0; i < 4; i++)
                        pMemory->write(addr + i, dump[i]);
                    update(TRUE);
                case 2:
                    break;
            }
            _reposit(addr);
        }
        return 1;
    }

    switch (pKey->sym)
    {
        case SDLK_UP:
            viewPos = _up(adrs[0]);
            update(TRUE);
            break;

        case SDLK_DOWN:
            viewPos = adrs[1];
            update(TRUE);
            break;

        case SDLK_LEFT:
            column = (column + 2) % 3;
            update(TRUE);
            break;

        case SDLK_RIGHT:
            column = (++column) % 3;
            update(TRUE);
            break;

        case SDLK_PAGEUP:
            viewPos = adrs[0];
            for (int i = 0; i < DISASM_LINES - 1; i++)
                viewPos = _up(viewPos);
            update(TRUE);
            break;

        case SDLK_PAGEDOWN:
            viewPos = adrs[DISASM_LINES - 1];
            update(TRUE);
            break;

        case SDLK_RETURN:
            addr = adrs[DISASM_LINES >> 1];
            switch (column)
            {
                case 0:
                    pEditor = new WordEditor(this, 0, DISASM_LINES >> 1, &addr);
                    break;
                case 1:
                    for (int i = 0; i < 4; i++)
                        dump[i] = pMemory->read(addr + i);
                    pEditor = new DumpEditor(this, 6, DISASM_LINES >> 1, dump, 4);
                    break;
                case 2:
                    pEditor = new Editor(this, 18, DISASM_LINES >> 1, text, 17);
                    break;
            }
            break;

        case SDLK_F4:
            pParent->setBreakPoint(adrs[DISASM_LINES >> 1]);
            pParent->hide();
            break;

        case SDLK_F9:
            pParent->toggleBreakPoint(adrs[DISASM_LINES >> 1]);
            update(TRUE);
            break;
//!!!!!!!!!!!!!!!!!!!!!!!!!
        case SDLK_F10:
            pParent->setBreakPoint(adrs[1 + (DISASM_LINES >> 1)]);
            pParent->hide();
            break;

        case SDLK_F11:
            pComp->frame(TRUE);
            viewPos = pCPU->regP.PC;
            for (int i = 0; i < (DISASM_LINES >> 1); i++)
                viewPos = _up(viewPos);
            pParent->update();
            break;

        default:
            return 0;
    }
    return 1;
}


// getting previous address to disasm
WORD Disasm::_up(WORD adr)
{
WORD tmpadr = (WORD)(adr - 16), prev = 0;
char tmp[48];

    do
    {
        prev = tmpadr;
        tmpadr = _getMnemo(tmpadr, tmp);
    }
    while (WORD(tmpadr + 0x8000) < WORD(adr + 0x8000));
    return prev;
}

void Disasm::update(unsigned focused)
{
WORD adr = 0;
char string[35];

    focus = focused;
    adr = viewPos;
    background(focused ? COLOR_FOCUSED : COLOR_MATRIX);
    BYTE colr = 0, color = 0;
    for (int i = 0; i < DISASM_LINES; i++)
    {
        colr = (i == (DISASM_LINES >> 1)) ? COLOR_SELECTED : COLOR_FOCUSED;
        adrs[i] = adr;
        _getAddr(adr, string);
        if (pCPU->regP.PC == adr) strcat(string, ">");

        color = column ? COLOR_FOCUSED : colr;
        if (! focused) color = COLOR_MATRIX;
        print(0, i, string, pParent->_isBreakPoint(adr) ? COLOR_BREAKPOINT : color);

        WORD adra = _getMnemo(adr, string);
        color = (column - 2) ? COLOR_FOCUSED : colr;
        if (! focused) color = COLOR_MATRIX;
        print(18, i, string, color);

        _getHex(adr, WORD(adra + 0x8000) - WORD(adr + 0x8000), string);
        color = (column - 1) ? COLOR_FOCUSED : colr;
        if (! focused) color = COLOR_MATRIX;
        print(6, i, string, color);
/*        if (colr == COLOR_SELECTED)
        {
            BYTE* mema = getBitmap() + 35 * 8 * 16 * (DISASM_LINES >> 1);
            for (int j = 0; j < 35 * 8; j += 2)
                mema[j] = mema[j + 15 * 35 *8] = COLOR_MATRIX >> 4;
        }
*/
        adr = adra;
    }
}

#define max(a, b) (a) >= (b) ? (a) : (b)
#define abs(x) ((x) >= 0) ? (x) : -(x)

// disassembling one string
WORD Disasm::_getMnemo(WORD adr, char* string)
{
static char r16_1[] = "bc\0de\0hl\0sp";
static char r16_2[] = "bc\0de\0ix\0sp";
static char r16_3[] = "bc\0de\0iy\0sp";
static char r8_1[] = "b\0\0\0\0c\0\0\0\0d\0\0\0\0e\0\0\0\0h\0\0\0\0l\0\0\0\0(hl)\0a";
static char r8_2[] = "b\0\0\0\0c\0\0\0\0d\0\0\0\0e\0\0\0\0hx\0\0\0lx\0\0\0(1x)\0a";
static char r8_3[] = "b\0\0\0\0c\0\0\0\0d\0\0\0\0e\0\0\0\0hy\0\0\0ly\0\0\0(1y)\0a";
static char cbtab[] = "rlc \0\0\0rrc \0\0\0rl \0\0\0\0rr \0\0\0\0sla \0\0\0sra \0\0\0sli \0\0\0srl \0\0\0"
                      "bit 0,\0bit 1,\0bit 2,\0bit 3,\0bit 4,\0bit 5,\0bit 6,\0bit 7,\0"
                      "res 0,\0res 1,\0res 2,\0res 3,\0res 4,\0res 5,\0res 6,\0res 7,\0"
                      "set 0,\0set 1,\0set 2,\0set 3,\0set 4,\0set 5,\0set 6,\0set 7,\0";
static char jr[] = "xxxxxx\0xxxxxx\0djnz \0\0jr \0\0\0\0jr nz,\0jr z,\0\0jr nc,\0jr c,\0";
static char logop[] = "add\0adc\0sub\0sbc\0and\0xor\0or\0\0cp";
static char flg[] = "nz\0z\0\0nc\0c\0\0po\0pe\0p\0\0m";

WORD st = adr;
BYTE p = 0, opcode = 0;
char *r16 = NULL, *r8 = NULL;

   r16 = r16_1;
   r8 = r8_1;
   for (;;)
   { // z80 prefixes
     opcode = pMemory->read(adr);
     if (opcode == 0xDD)
      {
          r16 = r16_2;
          r8 = r8_2;
          p = 0xDD;
      }
      else
       if (opcode == 0xFD)
       {
           r16 = r16_3;
           r8 = r8_3;
           p = 0xFD;
       }
       else
        break;
      adr++;
   }

   for (BYTE *ptr = mnemotab; *ptr; )
   {
      // cmd - start of command, c1 - mod/rm, cm - current pointer
      WORD radr = adr;
      if (opcode == 0xED) radr++;
      WORD cadr = radr + 1;
      int iMatch = 1;
      for (int j = 0; j < *ptr; j++) // match mask
         iMatch &= ((pMemory->read(adr + j) & ptr[j + *ptr + 1]) == ptr[j + 1]);
         if (iMatch)
         {
             *string = 0;
             BYTE *pt = NULL;
             for (pt = ptr + (2 * *ptr) + 1; *pt; pt++)
             { // scan all commands
             char ln[32];
             char* l1 = ln;
             *l1 = 0;

             BYTE rcmd = pMemory->read(radr);
             BYTE cm = pMemory->read(cadr);
             switch (*pt)
             {
                case _zr16: // in rcmd & 0x30
                   l1 = r16 + 3 * ((rcmd >> 4) & 3);
                   break;

                case _zr16a: // in rcmd & 0x30
                   if (((rcmd >> 4) & 3) == 3)
                    strcpy(l1, "af");
                   else
                    l1 = r16 + 3 * ((rcmd >> 4) & 3);
                   break;

                case _hl: // hl/ix/iy
                   l1 = r16 + 3 * 2;
                   break;

                case _zjr: // relative jumps
                   l1 = jr + 7 * ((rcmd >> 3) & 7);
                   break;

                case _zop: // z80 operations at rcmd & 0x38
                   l1 = logop + 4 * ((rcmd >> 3) & 7);
                   break;

                case _zf: // z80 flags at rcmd & 0x38
                   l1 = flg + 3 * ((rcmd >> 3) & 7);
                   break;

                case _cb: // all CB-opcodes
                {
                   if (!p)
                   {
                      sprintf(ln, "%s%s", cbtab + (cm >> 3) * 7,
                                          r8_1 + (cm & 7) * 5);
                      cadr++;
                   }
                   else
                   {
                      BYTE cm1 = pMemory->read(cadr + 1);
                      if ((cm1 & 7) != 6 && ((cm1 & 0xC0) != 0x40)) // operand is reg,(ix+nn)
                         sprintf(ln, "%s%s,(i%c%c%02X)", cbtab + (cm1 >> 3) * 7,
                                                         r8_1 + (cm1 & 7) * 5,
                                                         (p == 0xDD) ? 'x':'y',
                                                         (char)cm >= 0 ? '+' : '-', abs((char)cm));
                      else // only (ix+nn)
                         sprintf(ln, "%s(i%c%c%02X)", cbtab + (cm1 >> 3) * 7,
                                                      (p == 0xDD) ? 'x' : 'y',
                                                      (char)cm >= 0 ? '+' : '-', abs((char)cm));
                       cadr += 2;
                   }
                }
                break;

            case _zr8: // in rcmd & 0x38
              if (p && ((rcmd & 0x38) == 0x30))
              {
                  sprintf(ln, "(i%c%c%02X)", (p == 0xDD) ? 'x':'y',
                                             (char)cm >= 0 ? '+' : '-',
                                             abs((char)cm));
                  cadr++;
               }
               else
                 l1 = r8 + 5 * ((rcmd >> 3) & 7);
               break;

            case _zr8_: // in rcmd & 0x38, in ld r8,r8
               if (!p || (rcmd & 7) == 6)
               {
                   l1 = r8_1 + 5 * ((rcmd >> 3) & 7);
                   break;
               }
               if ((rcmd & 0x38) == 0x30)
               {
                  sprintf(ln, "(i%c%c%02X)", (p == 0xDD) ? 'x' : 'y',
                                             (char)cm >= 0 ? '+' : '-',
                                             abs((char)cm));
                  cadr++;
               }
               else
                 l1 = r8 + 5 * ((rcmd >> 3) & 7);
               break;

            case _zr81: // in rcmd & 7
               if (p && (rcmd & 7) == 6)
               {
                  sprintf(ln, "(i%c%c%02X)", (p == 0xDD) ? 'x' : 'y',
                                             (char)cm >= 0 ? '+' : '-',
                                             abs((char)cm));
                  cadr++;
               }
               else
                l1 = r8 + 5 * (rcmd & 7);
               break;

            case _zr81_: // in rcmd & 7, in ld r8,r8
               if (!p || ((rcmd & 0x38) == 0x30))
               {
                   l1 = r8_1 + 5 * (rcmd & 7);
                   break;
               }
               if ((rcmd & 7) == 6)
               {
                  sprintf(ln, "(i%c%c%02X)", (p == 0xDD) ? 'x' : 'y',
                                             (char)cm >= 0 ? '+' : '-',
                                             abs((char)cm));
                  cadr++;
               }
               else
                 l1 = r8 + 5 * (rcmd & 7);
               break;

            case _ld:
               strcpy(l1, "ld ");
               break;

            case _shrt: // short jump
               _getAddr(adr + cadr - st + (signed char)pMemory->read(cadr++) + 1, ln);
               break;

            case _ib: // immediate byte at cm
               sprintf(ln, "%02X", pMemory->read(cadr++));
               break;

            case _iw: // immediate word at cm
               _getAddr(pMemory->read(cadr) + (pMemory->read(cadr + 1) << 8), ln);
               cadr += 2;
               break;

            default:
               *(short*)ln = *pt;
         }  // switch
         strcat(string, l1);
      }

      // make tabulation between instruction and operands
      char b1[0x40];
      char* p = string, *q = b1;
      while (*p != ' ' && *p) *q++ = *p++;
      *q++ = *p;
      if (*p)
      {
         while (q < b1 + 4) *q++ = ' ';
         while (*++p) *q++ = *p;
      }
      *q = 0;
      strcpy(string, b1);
      return max(cadr, adr + *ptr);
      }
//nextcmd:
      ptr += (2 * *ptr) + 1;
      while (*ptr++); // skip mask,code and instruction
   }
   strcpy(string, "???");
   return adr + 1;
}


void Disasm::_getAddr(WORD adr, char* string)
{
    sprintf(string, "%04X", adr);
}

void Disasm::_getHex(WORD adr, int count, char* string)
{
    switch (count)
    {
        case 1:
            sprintf(string, "%02X", pMemory->read(adr));
            break;
        case 2:
            sprintf(string, "%02X %02X", pMemory->read(adr),
                                         pMemory->read(adr + 1));
            break;
        case 3:
            sprintf(string, "%02X %02X %02X", pMemory->read(adr),
                                              pMemory->read(adr + 1),
                                              pMemory->read(adr + 2));
            break;
        case 4:
            sprintf(string, "%02X %02X %02X %02X", pMemory->read(adr),
                                                    pMemory->read(adr + 1),
                                                    pMemory->read(adr + 2),
                                                    pMemory->read(adr + 3));
            break;
        default:
            sprintf(string, ".. %02X %02X %02X", pMemory->read(adr + count - 3),
                                                pMemory->read(adr + count - 2),
                                                pMemory->read(adr + count - 1));
            break;
        }
}

