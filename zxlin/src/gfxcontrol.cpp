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

#include "gfxcontrol.h"
#include "types.h"
#include "font.h"
#include "configure.h"
//----------------------

GfxControl::GfxControl()
{
#ifdef _DEBUG_
    printf("GfxControl\n");
#endif

    scrdepth = 0;
    pSrcSurf = pDstSurf = pPhsSurf = pTmpSurf = NULL;
    initSubsys(Configure::VIDFullScreen);

    pSysBuf = new DWORD[W_WIDTH * W_HEIGHT];
    pPhsSurf = SDL_CreateRGBSurfaceFrom(pSysBuf, W_WIDTH, W_HEIGHT, 32, W_WIDTH * 4,
                                         0xff0000, 0x00ff00, 0x0000ff, 0x00);
    if (pPhsSurf == NULL)
    {
        printf("Cannot create user 32-bit surface!\n");
        exit(1);
    }
    if (scrdepth != 4)
    {
        pTmpSurf = SDL_DisplayFormat(pPhsSurf);
        if (pTmpSurf == NULL)
        {
            printf("Cannot create convert surface!\n");
            exit(1);
        }
    }

    if (Configure::VIDFullScreen || scrdepth != 4)
        pSrcSurf = pPhsSurf;
    else
        pSrcSurf = pDstSurf;

    pFilter = NULL;
    pBuffer = new DWORD[W_WIDTH * W_HEIGHT];

    //show video information:
    const SDL_VideoInfo* pInfo = SDL_GetVideoInfo();
    printf("Hardware surfaces:            %s\n"
           "Window manager:               %s\n"
           "Accelerated HW->HW blits:     %s\n"
           "Accelerated HWColorkey blits: %s\n"
           "Accelerated HWAlpha blits:    %s\n"
           "Accelerated SW->HW blits:     %s\n"
           "Accelerated SWColorkey blits: %s\n"
           "Accelerated SWAlpha blits:    %s\n"
           "Accelerated color fill:       %s\n"
           "Total video mem:              %i kB\n"
           "Current color depth:          %i bits\n\n",

            pInfo->hw_available ?   "Yes" : "No",
            pInfo->wm_available ?   "Yes" : "No",
            pInfo->blit_hw ?        "Yes" : "No",
            pInfo->blit_hw_CC ?     "Yes" : "No",
            pInfo->blit_hw_A ?      "Yes" : "No",
            pInfo->blit_sw ?        "Yes" : "No",
            pInfo->blit_sw_CC ?     "Yes" : "No",
            pInfo->blit_sw_A ?      "Yes" : "No",
            pInfo->blit_fill ?      "Yes" : "No",
            pInfo->video_mem, pInfo->vfmt->BitsPerPixel
            );
}

GfxControl::~GfxControl()
{
    delete[] pBuffer;
    if (scrdepth != 4)
    {
        SDL_FreeSurface(pTmpSurf);
    }
    SDL_FreeSurface(pPhsSurf);
    SDL_FreeSurface(pDstSurf);
    delete[] pSysBuf;
    delete pFilter;
#ifdef _DEBUG_
    printf("~GfxControl\n");
#endif
}

void GfxControl::putChar(unsigned x, unsigned y, TEXT sym, DWORD ink, DWORD paper)
{
DWORD* pTo = getSysBuffer() + y * W_WIDTH + x;

    putChar(pTo, sym, ink, paper);
}

void GfxControl::putChar(DWORD* pTo, TEXT sym, DWORD ink, DWORD paper)
{
const BYTE* pFnt = pFont + ((DWORD)(BYTE)sym << 4);

    for (int h = 0; h < 16; h++)
    {
        int mask = 128;
        for (int w = 0; w < 8; w++, mask >>= 1)
            *pTo++ = (*pFnt & mask) ? ink : paper;
        pTo += W_WIDTH - 8;
        pFnt++;
    }
}

void GfxControl::print(unsigned x, unsigned y, const TEXT* str, DWORD ink, DWORD paper)
{
DWORD* pTo = getSysBuffer() + y * W_WIDTH + x;
unsigned xst = x;

    while (*str)
    {
        if (*str == '\n')
        {
            pTo += 16 * W_WIDTH - (x - xst);
            x = xst;
        }
        else
        {
            putChar(pTo, *str, ink, paper);
            pTo += 8;
            x += 8;
        }
        str++;
    }
}

void GfxControl::putMaskChar(DWORD* pTo, TEXT sym, DWORD ink, DWORD mskc)
{
const BYTE* pFnt = pFont + ((DWORD)(BYTE)sym << 4);
unsigned mskup = 0;
unsigned mskth = *pFnt;
unsigned mskdw = pFnt[1];

    pTo--;
    for (int h = 0; h < 16; h++)
    {
        BYTE msk = mskup | mskth | mskdw;
        if (msk & 128) *pTo = mskc;
        pTo++;
        msk |= (msk << 1) | (msk >> 1);
        unsigned mask = 128;
        for (int w = 0; w < 8; w++, mask >>= 1)
        {
            if (msk & mask)
                *pTo = (*pFnt & mask) ? ink : mskc;
            pTo++;
        }
        pTo += W_WIDTH - 8 - 1;
        pFnt++;
        mskup = mskth;
        mskth = mskdw;
        mskdw = pFnt[1];
    }
}

void GfxControl::printMask(unsigned x, unsigned y, const TEXT* str, DWORD ink, DWORD mskc)
{
DWORD* pTo = getSysBuffer() + y * W_WIDTH + x;

    while (*str)
    {
        putMaskChar(pTo, *str++, ink, mskc);
        pTo += 8;
    }
}

void GfxControl::clearWindow(unsigned x, unsigned y, unsigned w, unsigned h, DWORD paper)
{
DWORD* pTo = getSysBuffer() + y * W_WIDTH + x;

    while (h--)
    {
        unsigned wtmp = w;
        while (w--) *pTo++ = paper;
        pTo += W_WIDTH - (w = wtmp);
    }
}

void GfxControl::setFilter(VideoFilter* pFilt)
{
    if (pFilter != NULL) delete pFilter;
    pFilter = pFilt;
}

DWORD* GfxControl::getBuffer()
{
    return (pFilter != NULL) ? pBuffer : getSysBuffer();
}

DWORD* GfxControl::getSysBuffer()
{
    return (scrdepth == 4) ? (DWORD*)pSrcSurf->pixels : pSysBuf;
}

void GfxControl::proceed()
{
    if (pFilter)
        pFilter->proceed(pBuffer, getSysBuffer());
}

void GfxControl::putBuffer()
{
    if (scrdepth != 4)
    {
        if (scrwidth == W_WIDTH)
            SDL_BlitSurface(pTmpSurf, NULL, pDstSurf, NULL);
        else
            SDL_SoftStretch(pTmpSurf, NULL, pDstSurf, NULL);
    }
    else
        if (scrwidth != W_WIDTH)
            SDL_SoftStretch(pSrcSurf, NULL, pDstSurf, NULL);
    SDL_Flip(pDstSurf);
}

void GfxControl::toFull()
{
    //in pPhsSurf always stores original frame!!!
    if (pSrcSurf != pPhsSurf)
        SDL_BlitSurface(pSrcSurf, NULL, pPhsSurf, NULL);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    initSubsys(TRUE);
}

void GfxControl::toWin()
{
    //in pPhsSurf always stores original frame!!!
    if (pSrcSurf != pPhsSurf)
        SDL_BlitSurface(pSrcSurf, NULL, pPhsSurf, NULL);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    initSubsys(FALSE);
}

void GfxControl::initSubsys(unsigned fullscr)
{
    unsigned flag = Configure::VIDHWSurface ? SDL_HWSURFACE : SDL_SWSURFACE;
    if (Configure::VIDAsyncBlit) flag |= SDL_ASYNCBLIT;
    if (Configure::VIDDoubleBuf) flag |= SDL_DOUBLEBUF;
    if (fullscr) flag |= SDL_NOFRAME;

    scrwidth = fullscr ? Configure::VIDFullWidth : W_WIDTH;
    scrheight = fullscr ? Configure::VIDFullHeight : W_HEIGHT;

    pDstSurf = SDL_SetVideoMode(scrwidth, scrheight, 32, flag);
    if (pDstSurf == NULL)
    {
        pDstSurf = SDL_SetVideoMode(scrwidth, scrheight, 24, flag);
        if (pDstSurf == NULL)
        {
            pDstSurf = SDL_SetVideoMode(scrwidth, scrheight, 16, flag);
            if (pDstSurf == NULL)
                pDstSurf = SDL_SetVideoMode(scrwidth, scrheight, 15, flag);
        }
        if (pDstSurf == NULL)
        {
            printf("%s\n", SDL_GetError());
            exit(-1);
        }
    }
    scrdepth = pDstSurf->format->BytesPerPixel;
    if (scrwidth != W_WIDTH || scrdepth != 4)
    {
        pSrcSurf = pPhsSurf;
        if (pPhsSurf) putBuffer();
    }
    else
    {
        pSrcSurf = pDstSurf;
        if (pPhsSurf) SDL_BlitSurface(pPhsSurf, NULL, pSrcSurf, NULL);
    }

    SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
    SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
    SDL_EventState(SDL_KEYUP, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);
    SDL_EventState(SDL_JOYAXISMOTION, SDL_IGNORE);
    SDL_EventState(SDL_JOYBALLMOTION, SDL_IGNORE);
    SDL_EventState(SDL_JOYHATMOTION, SDL_IGNORE);
    SDL_EventState(SDL_JOYBUTTONDOWN, SDL_IGNORE);
    SDL_EventState(SDL_JOYBUTTONUP, SDL_IGNORE);
    SDL_EventState(SDL_QUIT, SDL_ENABLE);
    SDL_EventState(SDL_SYSWMEVENT, SDL_IGNORE);
    SDL_EventState(SDL_VIDEORESIZE, SDL_IGNORE);
    SDL_EventState(SDL_VIDEOEXPOSE, SDL_IGNORE);
    SDL_EventState(SDL_USEREVENT, SDL_ENABLE);

    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    SDL_EnableUNICODE(1);

}

