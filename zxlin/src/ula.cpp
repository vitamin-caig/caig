/***************************************************************************
                          ula.cpp  -  description
                             -------------------
    begin                : ??? ??? 20 2005
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

#include "ula.h"
#include "configure.h"
#include "string.h"
#include "zxlin.h"
#include <sys/unistd.h>
#include <fcntl.h>

ULA::ULA(Computer* pComp) : Device(pComp)
{
#ifdef _DEBUG_
    printf("ULA\n");
#endif
	pComputer->pIOManager->addDevice(this, FALSE);
    pScreen = (BYTE**)NULL;
    pFE = 0;
    ticks = 0;
    flash = 127;
    WORD off = 0;
    ///ABBY: New iso standart deprecate use of variable, defined in for, after his body
    unsigned y;
    for (y = 0; y < 192; y++)
        for (int x = 0; x < 256; x++)
        {
            pScrTab[y][x] =  off = ((y & 7) << 8) + ((y & 192) << 5) + ((y & 56) << 2) + (x >> 3);
            pAtrTab[y][x] =  (((off & 0x1800) >> 3) | (off & 255)) + 6144;
        }

    BYTE tmp = 128;
    for (y = 0; y < 256; y++)
    {
        mask[y] = tmp;
        tmp >>= 1;
        if (! tmp) tmp = 128;
    }
    updateSettings();
    fullscr = TRUE;
}

ULA::~ULA()
{
	pComputer->pIOManager->deleteDevice(this, FALSE);
#ifdef _DEBUG_
    printf("~ULA\n");
#endif
}

void ULA::updateSettings()
{
unsigned y;

    for (y = 0; y < 256; y++)
    {
        if (y < 128) //ink
            pColTab[y] = Configure::VIDPalette[((y & 64) >> 3) | (y & 7)];
        else //paper
            pColTab[y] = Configure::VIDPalette[(y & 120) >> 3];
    }

    unsigned start = Configure::ULATicksBeforePaper - 24 * Configure::ULATicksPerLine - 29;
    for (y = 0; y < 241; y++)
    {
        leftTime[y] = start;
        rightTime[y] = start + 128 + 32;
        start += Configure::ULATicksPerLine;
    }
}

void ULA::setScreenSrc(BYTE** pSrc)
{
    pScreen = pSrc;
}

void ULA::doFlash()
{
    flash ^= 128;
}

unsigned ULA::outByte(WORD port, BYTE data)
{
    if (! (port & 1))
        pFE = data;
    return 1;
}

#define ULA_X 254
#define ULA_Y 8
void ULA::showState(GfxControl*, unsigned)
{
}

void ULA::scaling(unsigned full)
{
DWORD* pSrc = ::ZXLin->pGfxControl->getBuffer();
DWORD* pDst = ::ZXLin->pGfxControl->getSysBuffer();
unsigned x, y;

    if (! full)
    {
        //reducing
        pSrc += W_WIDTH - 1;
        pDst += W_WIDTH - 1;
        for (y = 0; y < 240; y++)
        {
            for (x = 0; x < 320; x++)
            {
                *pDst-- = *pSrc--;
                pSrc--;
            }
            pSrc += 640 + W_WIDTH + W_WIDTH;
            pDst += 320 + W_WIDTH;
        }
    }
    else
    {
        //enlarging
        pSrc = pDst + W_WIDTH * 240 - 320;
        pDst = ::ZXLin->pGfxControl->getBuffer() + (W_HEIGHT - 1) * W_WIDTH;
        for (y = 0; y < 240; y++)
        {
            for (x = 0; x < 320; x++)
            {
                *pDst = pDst[-640] = pDst[1] = pDst[-639] = *pSrc++;
                pDst += 2;
            }
            pSrc -= 320 + 640;
            pDst -= 640 + W_WIDTH + W_WIDTH;
        }
    }
    fullscr = full;
}

void ULA::startFrame()
{
    line = 0;
}

void ULA::retrace()
{
    while (line < 240)
        renderUntil(rightTime[line]);
}

// main ULA rendering procedure
// renders 2 pixels per cpu tick
// screen area begins when counter exceeds ticksBeforePaper value
void ULA::renderUntil(unsigned cntr)
{
    if (line >= 240) return;
    if (cntr <= leftTime[line])
    {
        ticks = leftTime[line];
        return;
    }

    if (cntr >= rightTime[line] && cntr <= leftTime[line + 1] && ticks >= rightTime[line])
    {
        ticks = leftTime[++line];
        return;
    }

    unsigned x = (ticks - leftTime[line]) << 1;
    if (x >= 320)
    {
        return;
    }
    draw(x, cntr);
}

void ULA::saveShot(const char* filename)
{
char* pName = new char[strlen(filename) + 4];
//size = 1228854=12c036
const BYTE hdr[54] = {'B', 'M', //sign
                    0x36, 0xc0, 0x12, 0,    //size
                    0, 0, 0, 0,             //reserve
                    0x36, 0x00, 0x00, 0x00, //offset
                    0x28, 0x00, 0x00, 0x00, //desc size =40
                    0x80, 0x02, 0x00, 0x00, //width=640
                    0xe0, 0x01, 0x00, 0x00, //height=480
                    0x01, 0x00,             //planes
                    0x20, 0x00,             //bpp
                    0x00, 0x00, 0x00, 0x00, //compression
                    0x00, 0xc0, 0x12, 0x00, //size
                    0x00, 0x00, 0x00, 0x00, //resx
                    0x00, 0x00, 0x00, 0x00, //resy
                    0x00, 0x00, 0x00, 0x00, //cols
                    0x00, 0x00, 0x00, 0x00  //impcols
};

    strcpy(pName, filename);
    strcat(pName, ".bmp");
    int file = creat(pName, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
    if (file == -1) return;
    write(file, hdr, 54);
DWORD* src = ::ZXLin->pGfxControl->getBuffer();
    for (unsigned i = 0; i < 480; i++)
    {
        write(file, src + 640 * (479 - i), 640 * 4);
    }
    close(file);
	delete[] pName;
}

void ULA::draw(unsigned x, unsigned cntr)
{
    if (fullscr)
        drawDouble(x, cntr);
    else
        drawSingle(x, cntr);
}

void ULA::drawSingle(unsigned x, unsigned cntr)
{
DWORD* pLine = ::ZXLin->pGfxControl->getSysBuffer() + (W_WIDTH - 320) + W_WIDTH * line + x;

    if (cntr > rightTime[line]) cntr = rightTime[line];
    int yscr = line - 24;
    int xscr = x - 32;
    DWORD col = Configure::VIDPalette[pFE & 7];
    if (yscr >= 0 && yscr < 192)
    {
        while (ticks < cntr)
        {
            col = Configure::VIDPalette[pFE & 7];
            if (! (xscr & 256))
            {
                do
                {
                    BYTE clr = *(*pScreen + pAtrTab[yscr][xscr]) & flash;
                    if (*(*pScreen + pScrTab[yscr][xscr]) & mask[xscr])
                        col = pColTab[clr];
                    else
                        col = pColTab[clr ^ 128];
                    *pLine++ = col;
                    xscr++;
                }
                while (xscr & 1);
            }
            else
            {
                *pLine++ = col;
                *pLine=*(pLine-1);
                pLine++;
                xscr += 2;
            }
            ticks++;
        }
    }
    else
    {
        xscr = (cntr - ticks) << 3;
        *pLine = col;
        memcpy(pLine + 1, pLine, xscr - sizeof(DWORD));
        ticks = cntr;
    }
}

void ULA::drawDouble(unsigned x, unsigned cntr)
{
DWORD* pLine = ::ZXLin->pGfxControl->getBuffer() + W_WIDTH * 2 * line + x + x;

    if (cntr > rightTime[line]) cntr = rightTime[line];
    int yscr = line - 24;
    int xscr = x - 32;
    DWORD col = Configure::VIDPalette[pFE & 7];
    if (yscr >= 0 && yscr < 192)
    {
        while (ticks < cntr)
        {
            col = Configure::VIDPalette[pFE & 7];
            if (! (xscr & 256))
            {
                do
                {
                    BYTE clr = *(*pScreen + pAtrTab[yscr][xscr]) & flash;
                    if (*(*pScreen + pScrTab[yscr][xscr]) & mask[xscr])
                        col = pColTab[clr];
                    else
                        col = pColTab[clr ^ 128];
                    *pLine++ = col;
                    *pLine++ = col;
                    pLine[W_WIDTH - 2] = col;
                    pLine[W_WIDTH - 1] = col;

                    xscr++;
                }
                while (xscr & 1);
            }
            else
            {
                *pLine = col;
                memcpy(pLine + 1, pLine, 12);
                memcpy(pLine + W_WIDTH, pLine, 16);
                pLine += 4;
                xscr += 2;
            }
            ticks++;
        }
    }
    else
    {
        xscr = (cntr - ticks) << 3;
        *pLine = col;
        memcpy(pLine + 1, pLine, (xscr << 1) - sizeof(DWORD));
        memcpy(pLine + W_WIDTH, pLine, (xscr << 1));
        ticks = cntr;
    }
}
