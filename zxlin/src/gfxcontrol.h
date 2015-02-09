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

#include <SDL/SDL.h>

#ifndef GFXCONTROL_H_INCLUDED
#define GFXCONTROL_H_INCLUDED

#include "types.h"

class VideoFilter
{
public:
	virtual ~VideoFilter() {}
    virtual void proceed(DWORD* src, DWORD* dst) = 0;
};

/************************************************
sysdrawers--------+---+-----> SDL_Surface::pixels
                  |   |             ^
uladrawers->filter+   32to16/24cnv--+
************************************************/
class GfxControl
{
public:
    GfxControl();
    virtual ~GfxControl();

    void putChar(unsigned x, unsigned y, TEXT sym, DWORD ink, DWORD paper);
    void putChar(DWORD* pTo, TEXT sym, DWORD ink, DWORD paper);
    void print(unsigned x, unsigned y, const TEXT* str, DWORD ink, DWORD paper);
    void putMaskChar(DWORD* pTo, TEXT sym, DWORD ink, DWORD mskc);
    void printMask(unsigned x, unsigned y, const TEXT* str, DWORD ink, DWORD mskc);
    void clearWindow(unsigned x, unsigned y, unsigned w, unsigned h, DWORD paper);

    void setFilter(VideoFilter* pFilter);
    DWORD* getBuffer();
    DWORD* getSysBuffer();

    void proceed();
    void putBuffer();

    void toFull();
    void toWin();
    void lock();
    void unlock();

private:
    void initSubsys(unsigned fullscr);

private:
    SDL_Surface* pDstSurf;  //video surface with current depth and size (physical)
    SDL_Surface* pSrcSurf;  //surface to draw (pointer to pDstSurf or other)
    SDL_Surface* pPhsSurf;  //always 32-bit W_WIDTHxW_HEIGHT surface
    VideoFilter* pFilter;
    unsigned scrdepth;
    unsigned scrwidth;
    unsigned scrheight;
    DWORD* pBuffer; //render to
    DWORD* pSysBuf; //last 32bit buffer
    static const BYTE pFont[4096];
    SDL_Surface* pTmpSurf;  //for non-32bit formats
};

#endif
