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

#if !defined(CUILIB_H_DEFINED)
#define CUILIB_H_DEFINED

#include <gfxcontrol.h>
#include "cuitypes.h"
#include <SDL/SDL.h>

class CUIControl
{
public:
    CUIControl(GfxControl* pContr);
    ~CUIControl();

    void showWindow(CUIWindow* pWin);
    unsigned processKeyPress(SDL_keysym* pKey);

private:
    void updateWindow();
    void frame(unsigned x, unsigned y, unsigned w, unsigned h, const char* header, DWORD txtColr, DWORD bgrColr, unsigned dlb);
    void printText(unsigned x, unsigned y, const char* text, int count, DWORD txtColr, DWORD bgrColr);
    void putWidget(const CUIWidget* pWidget);

private:
    GfxControl* pControl;
    CUIWindow* pWindow;

    int editViewPos;
    int editEditPos;
    char* editTmpBuf;
    unsigned editSize;
    unsigned editFlag;
};
#endif
