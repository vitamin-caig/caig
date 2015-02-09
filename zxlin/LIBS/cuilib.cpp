/***************************************************************************
 *   Copyright (C) 2006 by vitaly   *
 *   vitamin@vitamin   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "cuilib.h"
#include <string.h>

#define EDIT_OVER 1
#define EDIT_NUMBERS 2

CUIControl::CUIControl(GfxControl* pContr)
{
    pControl = pContr;
    editEditPos = editViewPos = editSize = editFlag = 0;
    editTmpBuf = NULL;
    pWindow = NULL;
}

CUIControl::~CUIControl()
{
}

void CUIControl::showWindow(CUIWindow* pWin)
{
    pWindow = pWin;
    if (pWin == NULL)
    {
        return;
    }
    while ((pWin->CurWidget->State & WSTATE_DISABLED) || (pWin->CurWidget->TypeID & WIDGET_TYPEMASK) == WIDGET_FRAME)
        pWin->CurWidget = pWin->CurWidget->Next;

    pControl->clearWindow(pWin->xPos << 3, pWin->yPos << 4,
                          pWin->xSize << 3, pWin->ySize << 4, pWin->bkgColor);
    frame(pWin->xPos, pWin->yPos, pWin->xSize,
          pWin->ySize, pWin->Title, pWin->txtColor, pWin->bkgColor, TRUE);
    updateWindow();
}

void CUIControl::updateWindow()
{
CUIWidget* pWidg = pWindow->CurWidget;

    if (pWidg == NULL) return;
    do
    {
        putWidget(pWidg);
        pWidg = pWidg->Next;
    }
    while (pWidg != pWindow->CurWidget);
//    pControl->lock();
    pControl->putBuffer();
}

unsigned CUIControl::processKeyPress(SDL_keysym* pKey)
{
    if (pWindow == NULL) return FALSE;

CUIWidget* pWid = pWindow->CurWidget;
unsigned tmp = TRUE;
char c = 0;

    if (editTmpBuf) //editorial
    {

        switch (pKey->sym)
        {
        case SDLK_RETURN:   //enter- proceed
            if (pWid->Param.EditBoxParam.FinishEdit)
                tmp = (*pWid->Param.EditBoxParam.FinishEdit)(pWindow, editTmpBuf);
            else
            {
                memcpy(pWid->Item, editTmpBuf, editSize);
                tmp = TRUE;
            }

        case SDLK_ESCAPE:  //cancel
            delete[] editTmpBuf;
            editTmpBuf = NULL;
            if (tmp)
                updateWindow();
            else
                showWindow(NULL);
            return tmp;


        case SDLK_HOME:
            editEditPos = editViewPos = 0;
            break;

        case SDLK_END:
            editEditPos = strlen(editTmpBuf);
			if (editEditPos >= (int)pWid->xSize)
                editViewPos = (editEditPos - pWid->xSize + 4) & 0xfffc;
            break;

        case SDLK_INSERT:
            editFlag ^= EDIT_OVER;
            return TRUE;

        case SDLK_DELETE:
            if (! editTmpBuf[editEditPos]) return TRUE;
            memcpy(editTmpBuf + editEditPos, editTmpBuf + editEditPos + 1, editSize - editEditPos);
            break;

        case SDLK_BACKSPACE:
            if (editEditPos)
                memcpy(editTmpBuf + editEditPos - 1, editTmpBuf + editEditPos, editSize - editEditPos + 1);
        case SDLK_LEFT:
            if (editEditPos)
            {
                editEditPos--;
                if (editEditPos < editViewPos)
                {
                    editViewPos -= 4;
                    if (editViewPos < 0) editViewPos = 0;
                }
            }
            break;

        case SDLK_RIGHT:
            if (editEditPos < editSize && editTmpBuf[editEditPos])
            {
                editEditPos++;
                if (editEditPos - editViewPos >= pWid->xSize)
                    editViewPos += 4;
            }
            break;

        default:
            if (pKey->sym < SDLK_SPACE || pKey->sym > SDLK_z) return TRUE;
            if ((editFlag & EDIT_NUMBERS) && (pKey->sym < SDLK_0 || pKey->sym > SDLK_9)) return TRUE;
            c = pKey->unicode;

            if (editFlag & EDIT_OVER)
                editTmpBuf[editEditPos] = c;
            else
            {
                if (strlen(editTmpBuf) == editSize - 1) return TRUE;
                unsigned i = editEditPos;
                do
                {
                    c ^= editTmpBuf[i];
                    editTmpBuf[i] ^= c;
                    c ^= editTmpBuf[i];
                    i++;
                }
                while (editTmpBuf[i - 1]);
            }
            if (editEditPos < editSize)
            {
                editEditPos++;
                if (editEditPos - editViewPos >= pWid->xSize)
                    editViewPos += 4;
            }
            break;
        }
        putWidget(pWid);
        pControl->putBuffer();
        return TRUE;
    }


    if (pKey->sym == SDLK_SPACE || pKey->sym == SDLK_RETURN)
    {
        switch (pWid->TypeID & WIDGET_TYPEMASK)
        {
        case WIDGET_BUTTON:
            if (pWid->Item)
                (*(BUTTONPROCFUNC)pWid->Item)(pWindow);
            break;
        case WIDGET_CHECK:
            *(unsigned*)pWid->Item = !(*(unsigned*)pWid->Item);
            break;
        case WIDGET_RADIO:
            *(unsigned*)pWid->Item = pWid->Param.RadioValue;
            break;
        case WIDGET_EDITBOX:
            editTmpBuf = new char[editSize = pWid->Param.EditBoxParam.StringLen];
            memcpy(editTmpBuf, (const char*)pWid->Item, editSize);
            editEditPos = editViewPos = 0;
            break;
        case WIDGET_NUMBER:
            editTmpBuf = new char[10];
            sprintf(editTmpBuf, "%ui", *(unsigned*)pWid->Item);
            editEditPos = editViewPos = 0;
            break;
        }
        if (pWid->State & WSTATE_AUTOHIDE)
        {
            showWindow(NULL);
            return FALSE;
        }
        updateWindow();
        return TRUE;
    }

    if (pKey->sym == SDLK_ESCAPE)
    {
        pWindow = NULL;
        return FALSE;
    }

int dir = 0;

    if (pKey->sym == SDLK_TAB)
        dir = (pKey->mod & KMOD_LSHIFT) ? -1 : 1;
    if (pKey->sym == SDLK_DOWN || pKey->sym == SDLK_RIGHT) dir = 1;
    if (pKey->sym == SDLK_UP || pKey->sym == SDLK_LEFT) dir = -1;
    if (dir)
    {
        do
        {
            pWindow->CurWidget = (dir == 1) ? pWindow->CurWidget->Next : pWindow->CurWidget->Prev;
        }
        while ((pWindow->CurWidget->State & WSTATE_DISABLED) || (pWindow->CurWidget->TypeID & WIDGET_TYPEMASK) == WIDGET_FRAME);
        updateWindow();
        return TRUE;
    }

//check hotkeys
    do
    {
        if (! ((pWid->State & WSTATE_DISABLED) || (pWid->TypeID & WIDGET_TYPEMASK) == WIDGET_FRAME))
        {
            int i = 0;
            while (pWid->Title[i])
            {
                if (pWid->Title[i] == '&' && ((pWid->Title[i + 1] & ~32) == (pKey->sym & ~32)))
                {
                    pWindow->CurWidget = pWid;
                    pKey->sym = SDLK_SPACE;
                    processKeyPress(pKey);
                    return TRUE;
                }
                i++;
            }
        }
        pWid = pWid->Next;
    }
    while (pWid != pWindow->CurWidget);
    return TRUE;
}


//-- privates ----
/***************************
218 194 191
195 197 180
192 193 217
196 179 -single-lined frame

201 203 187
204 206 185
200 202 188
205 186 -double-lined frame

****************************/
void CUIControl::frame(unsigned x, unsigned y, unsigned w, unsigned h, const char* header, DWORD txtColr, DWORD bgrColr, unsigned dbl)
{
char* tmpstr = new char[w + 1];
char sym;
unsigned i;

    x <<= 3;
    y <<= 4;
    for (i = 0; i < w; i++)
    {
        if (! i)
            sym = dbl ? 201 : 218;
        else
            if (i == w - 1)
                sym = dbl ? 187 : 191;
            else
                if (header && *header)
                    sym = *header++;
                else
                    sym = dbl ? 205 : 196;
        tmpstr[i] = sym;
    }
    tmpstr[i] = 0;
    pControl->print(x, y, tmpstr, txtColr, bgrColr);
    y += 16;
    if (h > 2)
    {
        for (i = 0; i < h - 2; i++)
        {
            pControl->putChar(x, y, dbl ? 186 : 179, txtColr, bgrColr);
            pControl->putChar(x + ((w - 1) << 3), y, dbl ? 186 : 179, txtColr, bgrColr);
            y += 16;
        }
    }
    memset(tmpstr, dbl ? 205 : 196, w);
    *tmpstr = dbl ? 200 : 192;
    tmpstr[w - 1] = dbl ? 188 : 217;
    pControl->print(x, y, tmpstr, txtColr, bgrColr);
}

void CUIControl::printText(unsigned x, unsigned y, const char* text, int count, DWORD txtColr, DWORD bgrColr)
{
unsigned txt = txtColr;

    x <<= 3;
    y <<= 4;
    while (count && *text)
    {
        if (*text == '&')
            txt = 0xff0000; //red txt
        else
        {
            pControl->putChar(x, y, *text, txt, bgrColr);
            x += 8;
            txt = txtColr;
            count--;
        }
        text++;
    }
}

void CUIControl::putWidget(const CUIWidget* pWidget)
{
static char tmpstr[128];
DWORD bgr = pWindow->bkgColor;
DWORD txt = (pWidget->State & WSTATE_DISABLED) ? pWindow->disColor : pWindow->txtColor;
const char* pSrc = NULL;
unsigned i = 0;
unsigned curr = FALSE;

    if (pWindow->CurWidget == pWidget)
    {
        bgr ^= txt;
        txt ^= bgr;
        bgr ^= txt;
        curr = TRUE;
    }
    switch (pWidget->TypeID & WIDGET_TYPEMASK)
    {
    case WIDGET_BUTTON:
        sprintf(tmpstr, "[%s]", pWidget->Title);
        break;

    case WIDGET_CHECK:
        sprintf(tmpstr, "[%c] %s", *(unsigned*)pWidget->Item ? 'x' : ' ', pWidget->Title);
        break;

    case WIDGET_RADIO:
        sprintf(tmpstr, "(%c) %s", (*(int*)pWidget->Item == pWidget->Param.RadioValue) ? '*' : ' ', pWidget->Title);
        break;

    case WIDGET_EDITBOX:
        memset(tmpstr, ' ', pWidget->xSize);
        tmpstr[pWidget->xSize] = 0;
        if (editTmpBuf && curr)
            pSrc = editTmpBuf;
        else
            pSrc = (const char*)pWidget->Item;
        i = strlen(pSrc) - editViewPos;
        if (i > pWidget->xSize) i = pWidget->xSize;
        memcpy(tmpstr, pSrc + editViewPos, i);
        printText(pWidget->xPos + pWindow->xPos, pWidget->yPos + pWindow->yPos, pWidget->Title, pWidget->xSize, pWindow->txtColor, pWindow->bkgColor);
        if (editTmpBuf && curr)   //cursor
        {
            pControl->print((pWidget->xPos  + pWindow->xPos) << 3, (pWidget->yPos  + pWindow->yPos+ 1) << 4, tmpstr, pWindow->txtColor, 0);
            pControl->putChar((pWidget->xPos + editEditPos - editViewPos + pWindow->xPos) << 3, (pWidget->yPos + 1 + pWindow->yPos) << 4, pSrc[editEditPos], 0, pWindow->txtColor);
        }
        else
            if (curr)
                pControl->print((pWidget->xPos  + pWindow->xPos) << 3, (pWidget->yPos  + pWindow->yPos+ 1) << 4, tmpstr, 0, pWindow->txtColor);
            else
                pControl->print((pWidget->xPos  + pWindow->xPos) << 3, (pWidget->yPos  + pWindow->yPos+ 1) << 4, tmpstr, pWindow->txtColor, 0);
        return;

    case WIDGET_FRAME:
        frame(pWidget->xPos + pWindow->xPos, pWidget->yPos + pWindow->yPos, pWidget->xSize, pWidget->ySize, pWidget->Title, txt, pWindow->bkgColor, FALSE);

    default:
        *tmpstr = 0;
    }
    printText(pWidget->xPos + pWindow->xPos, pWidget->yPos + pWindow->yPos, tmpstr, pWidget->xSize, txt, bgr);
}
