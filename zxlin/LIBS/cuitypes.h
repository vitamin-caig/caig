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

#if !defined(CUITYPES_H_DEFINED)
#define CUITYPES_H_DEFINED

#include "types.h"


struct CUIWindow;
struct CUIWidget;
typedef void (*BUTTONPROCFUNC)(CUIWindow* pWin);
typedef unsigned (*TEXTPROCFUNC)(CUIWindow* pWin, const char* src);
struct CUIWindow
{
    const char* Title;
    CUIWidget* CurWidget;
    unsigned xPos, yPos;
    unsigned xSize, ySize;
    DWORD txtColor, disColor, bkgColor;
};


enum EWidgetType
{
    WIDGET_BUTTON = 0x100,
    WIDGET_CHECK = 0x200,
    WIDGET_RADIO = 0x300,
    WIDGET_EDITBOX = 0x400,
    WIDGET_FRAME = 0x500,
    WIDGET_NUMBER = 0x600,

    WIDGET_TYPEMASK = 0xff00,
    WIDGET_IDMASK = 0xff
};

enum EWidgetState
{
    WSTATE_DISABLED = 1,
    WSTATE_AUTOHIDE = 2,
};

union WIDGETPARAM
{
    struct
    {
    unsigned StringLen;
    TEXTPROCFUNC FinishEdit;
    } EditBoxParam;

    int RadioValue;
};

struct CUIWidget
{
    const char* Title;
    unsigned TypeID;
    unsigned State;
    void* Item;
    unsigned xPos, yPos;
    int xSize, ySize;
    CUIWidget* Prev;
    CUIWidget* Next;
    WIDGETPARAM Param;
};

#endif
