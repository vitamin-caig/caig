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

#include "configure.h"
#include "betadisk.h"
#include "memory.h"
#include "computer.h"
#include <sys/unistd.h>
#include <fcntl.h>
#include <qmessagebox.h>

#define Z80FRQ (Configure::ULATicksPerFrame * 50)
//3500000

BetaDisk::BetaDisk(Computer* pComp) : Device(pComp)
{
#ifdef _DEBUG_
    printf("BetaDisk\n");
#endif
	pComputer->pIOManager->addDevice(this, FALSE);
    memset(disk, 0, 4 * sizeof(DISK));
    memset(&trkcache, 0, sizeof(TRKCACHE));
    memset(fddTrack, 0, &wdTrDOS - fddTrack + 1);
    readState = writeState = formatState = 0;
}

BetaDisk::~BetaDisk()
{
    for (int i = 0; i < 4; i++) freeDisk(i);
	pComputer->pIOManager->deleteDevice(this, FALSE);
#ifdef _DEBUG_
    printf("~BetaDisk\n");
#endif
}

void BetaDisk::reset()
{
}

unsigned BetaDisk::inByte(WORD adr, BYTE* data)
{
    if (! ((Memory::status & MEMSTAT_DOSPORTS) && ((adr & 0x1f) == 0x1f))) return FALSE;

    adr &= 0xff;
    processWd();
    if (adr & 0x80)
        *data = wdRqs;
    else
        switch (adr)
        {
            case 0x1f:
                wdRqs &= ~INTRQ;
                *data = wdStatus;
                break;

            case 0x3f:
                *data = wdTrack;
                break;

            case 0x5f:
                *data = wdSector;
                break;

            case 0x7f:
                wdStatus &= ~WDS_DRQ;
                wdRqs &= ~DRQ;
                *data = wdData;
                break;

            default:
                *data = 0xff;
        }
    return TRUE;
}

unsigned BetaDisk::outByte(WORD adr, BYTE data)
{
    if (! ((Memory::status & MEMSTAT_DOSPORTS) && ((adr & 0x1f) == 0x1f))) return TRUE;
    processWd();

    adr &= 0xff;
    if (adr == 0x1f)    //cmd
    {
        wdRqs &= ~INTRQ;

        if ((data & 0xf0) == 0xd0)
        {
            wdState = WD_READY;
            wdStatus &= ~WDS_BUSY;
            return FALSE;
        }
        if (wdStatus & WDS_BUSY) return FALSE;
        wdCmd = data;
        wdNext = pComputer->timeStates + pComputer->pCPU->ticks;
        wdStatus = WDS_BUSY;
        wdRqs = 0;

        if ((data & 0xf0) == 0) //seek trk0
        {
            wdState2 = WD_SEEK0;
            wdStepDirection = -1;
            wdSeekop.wdSeek0cnt = 0x100;
            setupSeek(data);
            return FALSE;
        }
        if ((data & 0xf0) == 0x10)  //seek
        {
            wdState2 = WD_SEEK;
            if (wdTrack < wdData)
                wdStepDirection = +1;
            else if (wdTrack > wdData)
                    wdStepDirection = -1;
                 else
                    wdStepDirection = 0;
            setupSeek(data);
            return FALSE;
        }
        if ((data & 0xe0) == 0x20)  //step
        {
            wdState2 = WD_STEP;
            setupSeek(data);
            return FALSE;
        }
        if ((data & 0xc0) == 0x40)  //step-in, step-out
        {
            wdState2 = WD_STEP;
            wdStepDirection = (data & 0x20) ? -1 : 1;
            setupSeek(data);
            return FALSE;
        }

        if (! trkcache.trkd)    //other commands work with surface - abort if no track
        {
            wdState = WD_NOTFND;
            return FALSE;
        }

        //abort if disk is not spinning
        if (! fddMotor[wdDrive])
        {
            wdStatus = WDS_NOTRDY | WDS_NOTFOUND;
            wdState = WD_READY;
            return FALSE;
        }
        else
            fddMotor[wdDrive] = wdNext + 2 * Z80FRQ;

        if ((data & 0xe0) == 0x80)   //read sector
        {
            wdState = WD_READSECTORS;
            return FALSE;
        }

        if ((data & 0xf0) == 0xc0)  //read address
        {
            wdState2 = WD_STARTREAD;
            findMarker(0, 0);
            return FALSE;
        }

        if ((data & 0xe0) == 0xa0)  //write sector
        {
            if (Configure::BETAWriteProtect[wdDrive])
            {
                wdStatus |= WDS_WRITEP;
                return FALSE;
            }
            wdState = WD_WRITESECTORS;
            return FALSE;
        }

        if ((data & 0xf0) == 0xe0)  //read track
        {
            wdState2 = WD_STARTREAD;
            trkOp();
            return FALSE;
        }

        if ((data & 0xf0) == 0xf0)  //format track
        {
            if (Configure::BETAWriteProtect[wdDrive])
            {
                wdStatus |= WDS_WRITEP;
                return FALSE;
            }
            wdState2 = WD_FORMATTRACK;
            wdRqs |=DRQ;
            wdStatus |= WDS_DRQ;
            trkOp();
            return FALSE;
        }
    }


    //--------------
    if (adr == 0x3f)
    {
        wdTrack = data;
        return FALSE;
    }
    if (adr == 0x5f)
    {
        wdSector = data;
        return FALSE;
    }
    if (adr == 0x7f)
    {
        wdData = data;
        wdRqs &= ~DRQ;
        wdStatus &= ~WDS_DRQ;
        return FALSE;
    }

    if (adr & 0x80) //system
    {
        wdTrDOS = data;
        wdDrive = data & 3;
        wdSide = 1 & ~(data >> 4);
        if (! (data & 4))   //reset
        {
            wdStatus = 0x80;
            wdRqs = INTRQ;
            fddMotor[wdDrive] = 0;
            wdState = WD_READY;
        }
    }
    return FALSE;
}

void BetaDisk::setupSeek(unsigned val)
{
static char steps[] = {6, 12, 20, 30};

    wdSeekop.wdStepTime = steps[val & 3] * (Z80FRQ / 1000);
    wdNext += Z80FRQ / 1000;    //1ms delay before command
    wdState = WD_WAIT;
    if (Configure::BETAWriteProtect[wdDrive]) wdStatus |= WDS_WRITEP;

    //disk spins 1.8 sec (9 turns) after command then stop
    fddMotor[wdDrive] = wdNext + 2 * Z80FRQ;
}

void BetaDisk::trkOp()
{
    wdAnyop.wdPtr = trkcache.trkd;
    wdAnyop.wdLen = trkcache.trklen;
    wdState = WD_WAIT;
    unsigned offset = (unsigned)(wdNext % (trkcache.trklen * trkcache.ts_byte));
    wdNext += (trkcache.trklen * trkcache.ts_byte - offset);    //wait index
}

void BetaDisk::showState(GfxControl* pControl, unsigned full)
{
static char szTmp[128];
const char cAnim[] = {'-', '\\', '|', '/'};
static unsigned aniPos = 0;

    if (full)
    {
        if (Configure::LEDBETA_X == (unsigned)-1) return;
        if (formatState)
        {
            sprintf(szTmp, "<%c> %c:%03i:%02i", cAnim[(aniPos & 24) >> 3], wdDrive + 'A', wdTrack * 2 + wdSide, wdSector);
            pControl->printMask(Configure::LEDBETA_X, Configure::LEDBETA_Y, szTmp, 0xff00ff, 0);
            formatState--;
            aniPos++;
            return;
        }
        if (writeState)
        {
            sprintf(szTmp, "->%c:%03i:%02i", wdDrive + 'A', wdTrack * 2 + wdSide, wdSector);
            pControl->printMask(Configure::LEDBETA_X, Configure::LEDBETA_Y, szTmp, 0xff0000, 0);
            writeState--;
            return;
        }
        if (readState)
        {
            sprintf(szTmp, "<-%c:%03i:%02i", wdDrive + 'A', wdTrack * 2 + wdSide, wdSector);
            pControl->printMask(Configure::LEDBETA_X, Configure::LEDBETA_Y, szTmp, 0xff, 0);
            readState--;
            return;
        }
    }
    else
    {
        pControl->clearWindow(BETA_X, BETA_Y, 64, 7 * 16, 0);
        sprintf(szTmp, "BETADISK\n"
                       "Stte: %02X\n"
                       "Cmd:  %02X\n"
                       "Data: %02X\n"
                       "Trk:  %02X\n"
                       "Sec:  %02X\n"
                       "Stts: %02X",
                       wdState, wdCmd, wdData, wdTrack, wdSector, wdStatus);
        pControl->print(BETA_X, BETA_Y, szTmp, 0xffffff, 0);
    }
}

void BetaDisk::betaTraps()
{
CPU* pCPU = pComputer->pCPU;

    if (pCPU->regP.PC == 0x3e01)
    {
        pCPU->regB.A = pCPU->regB.C = 1;
        return; // no delays
    }
    if (pCPU->regP.PC == 0x3fec &&
            (wdState == WD_READDATA ||
                (wdState2 == WD_READDATA && wdState == WD_WAIT)))
    {
        readState = STATE_TIME;
        if (wdRqs & DRQ)
        {
            //cpy byte from controller
            pComputer->pMemory->write(pCPU->regP.HL, wdData);
            pCPU->regP.HL++;
            pCPU->regB.B--;
            wdRqs &= ~DRQ;
            wdStatus &= ~WDS_DRQ;
        }
        while (wdAnyop.wdLen)    //move others
        {
            pComputer->pMemory->write(pCPU->regP.HL, *wdAnyop.wdPtr++);
            wdAnyop.wdLen--;
            pCPU->regP.HL++;
            pCPU->regB.B--;
        }
        pCPU->regP.PC += 2;//skip INI
        return;
    }
    if (pCPU->regP.PC == 0x3fd1 &&
            (wdRqs & DRQ) &&
            (wdAnyop.wdLen > 1) &&
            (wdState == WD_WRITEDATA ||
                (wdState2 == WD_WRITEDATA && wdState == WD_WAIT)))
    {
        writeState = STATE_TIME;
        while (wdAnyop.wdLen > 1)
        {
            *wdAnyop.wdPtr = pComputer->pMemory->read(pCPU->regP.HL);
            pCPU->regP.HL++;
            pCPU->regB.B--;
            trkcache.trki[(wdAnyop.wdPtr - trkcache.trkd) >> 3] &= ~(1 << ((wdAnyop.wdPtr - trkcache.trkd) & 7));
            wdAnyop.wdPtr++;
            wdAnyop.wdLen--;
        }
        pCPU->regP.PC += 2; //skip OUTI
        return;
    }
}



//-- privates
// swap lower 2 bytes of data
unsigned BetaDisk::wordSwap(unsigned data)
{
union BYTEUINT
{
    BYTE bytes[4];
    unsigned uint;
};
    ((BYTEUINT*)&data)->bytes[3] = ((BYTEUINT*)&data)->bytes[0];
    ((BYTEUINT*)&data)->bytes[0] = ((BYTEUINT*)&data)->bytes[1];
    ((BYTEUINT*)&data)->bytes[1] = ((BYTEUINT*)&data)->bytes[3];
    data &= 0xffff;
    return data;
}

// calculating crc of a block
unsigned BetaDisk::wd93CRC(BYTE* ptr, unsigned size)
{
unsigned crc = 0xcdb4;

    while (size--)
    {
        crc ^= (*ptr++) << 8;
        for (int i = 8; i; i--)
            if ((crc <<= 1) & 0x10000) crc ^= 0x1021;   //x^12+x^5+1
    }
    return wordSwap(crc);
}


void BetaDisk::seekTrack(unsigned drv, unsigned cyl, unsigned side, unsigned fs)
{
//not in cache
    if (! ((drv - trkcache.drive) | (fs - trkcache.sf) | (cyl - trkcache.cyl) | (side - trkcache.side))) return;
//current disk structure
    DISK* dsk = disk + drv;
//copy parameters
    trkcache.cyls = dsk->cyls;
    trkcache.sides = dsk->sides;
    trkcache.sf = fs;
    trkcache.cyl = cyl;
    trkcache.side = side;
    trkcache.drive = drv;
// no more cylinders
    if (cyl >= dsk->cyls)
    {
        trkcache.trkd = NULL;
        return;
    }
    trkcache.trkd = dsk->trkd[cyl][side];
    trkcache.trki = dsk->trki[cyl][side];
    trkcache.trklen = dsk->trklen[cyl][side];
    if (! trkcache.trklen)
    {
        trkcache.trkd = NULL;
        return;
    }
    trkcache.ts_byte = Z80FRQ / (trkcache.trklen * FDD_RPS);
    if (!fs) return;
    //find sectors
    trkcache.s = 0;
    if (dsk->rawdata == NULL)
    {
        trkcache.trkd = NULL;
        return;
    }
    for (unsigned i = 0; i < trkcache.trklen; i++)
    {
        if (trkcache.trkd[i] == 0xa1 && trkcache.trkd[i + 1] == 0xfe && (trkcache.trki[i >> 3] & (1 << (i & 7))))
        {
            //oversec
            if (trkcache.s == MAX_SEC)
            {
                printf("BETA:Too many sectors in track\n");
                exit(2);
            }
            SECHDR* hdr = trkcache.hdr + trkcache.s++;
            hdr->id = trkcache.trkd + i + 2;
            *(unsigned*)hdr = *(unsigned*)hdr->id;
            hdr->crc = *(WORD*)(trkcache.trkd + i + 6);
            hdr->c1 = (wd93CRC(trkcache.trkd + i + 1, 5) == hdr->crc);
            hdr->data = NULL;
            hdr->datalen = 0;
            if (hdr->l > 5) continue;
            for (unsigned j = i + 8; j < trkcache.trklen; j++)
            {
                if (trkcache.trkd[j] == 0xa1 && (trkcache.trki[j >> 3] & (1 << (j & 7))) &&
                !(trkcache.trki[(j + 1) >> 3] & (1 << ((j + 1) & 7))))
                {
                    if (trkcache.trkd[j + 1] == 0xf8 || trkcache.trkd[j + 1] == 0xfb)
                    {
                        hdr->datalen = 128 << hdr->l;
                        hdr->data = trkcache.trkd + j + 2;
                        hdr->c2 = (wd93CRC(hdr->data - 1, hdr->datalen + 1) == *(WORD*)(hdr->data + hdr->datalen));
                    }
                    break;
                }
            }
        }
    }
}

void BetaDisk::formatTrack(unsigned drv, unsigned cyl, unsigned side, unsigned numsec, SECHDR* pHdr)
{
    trkcache.drive = (unsigned)-1;
    seekTrack(drv, cyl, side);
    memset(trkcache.trkd, 0, trkcache.trklen);
    memset(trkcache.trki, 0, (trkcache.trklen >> 3) + ((trkcache.trklen & 7) ? 1 : 0));

    BYTE* data = trkcache.trkd;
    unsigned i, off;
    for (i = 0; i < 80; i++) *data++ = 0x4e;   //first gap
    for (i = 0; i < 12; i++) *data++ = 0;
    for (i = 0; i < 3; i++)
    {
        off = data - trkcache.trkd;
        trkcache.trki[off >> 3] |= (1 << (off & 7));
        *data++ = 0xc2;
    }
    *data++ = 0xfc; //index
    for (unsigned sec = 0; sec < numsec; sec++, pHdr++)
    {
        for (i = 0; i < 50; i++) *data++ = 0x4e;
        for (i = 0; i < 12; i++) *data++ = 0;
        for (i = 0; i < 3; i++)
        {
            off = data - trkcache.trkd;
            trkcache.trki[off >> 3] |= (1 << (off & 7));
            *data++ = 0xa1;
        }
        *data++ = 0xfe; //marker
        *(DWORD*)data = *(DWORD*)pHdr;
        data += 4;
        unsigned crc = wd93CRC(data - 5, 5);
        if (pHdr->c1 == 1) crc = pHdr->crc;
        if (pHdr->c1 == 2) crc ^= 0xffff;
        *(DWORD*)data = crc;
        data += 2;
        if (pHdr->data)
        {
            for (i = 0; i < 22; i++) *data++ = 0x4e;
            for (i = 0; i < 12; i++) *data++ = 0;
            for (i = 0; i < 3; i++)
            {
                off = data - trkcache.trkd;
                trkcache.trki[off >> 3] |= (1 << (off & 7));
                *data++ = 0xa1;
            }
            *data++ = 0xfb; //sector
            if (pHdr->l > 5)
            {
                printf("BETA:Strange sector\n");
                exit(2);
            }
            unsigned len = 128 << pHdr->l;
            if (pHdr->data != (BYTE*)1)
                memcpy(data, pHdr->data, len);
            else
                memset(data, 0, len);
            crc = wd93CRC(data - 1, len + 1);
            if (pHdr->c2 == 1) crc = pHdr->crcd;
            if (pHdr->c2 == 2) crc ^= 0xffff;
            *(DWORD*)(data + len) = crc;
            data += len + 2;
        }
    }
    if (data > trkcache.trklen + trkcache.trkd)
    {
        printf("BETA:Track too long\n");
        exit(2);
    }
    while (data < trkcache.trkd + trkcache.trklen) *data++ = 0x4e;
}

//test==0 any ID
//test==1 correct crc&sec&trk
//test==2 correct side
void BetaDisk::findMarker(int test, int needdata)
{
    if (Configure::BETANoDelay)
    {
        fddTrack[wdDrive] = wdTrack;
        seekTrack(wdDrive, fddTrack[wdDrive], wdSide);
    }

    wdState = WD_WAIT;
    BYTE found = 0;
    unsigned t = MAX_TRACK_LEN;
    if (trkcache.trkd)
    {
        unsigned i = (unsigned)(wdNext % (trkcache.trklen * trkcache.ts_byte)) / trkcache.ts_byte;
        for (t = 0; t < trkcache.trklen; t++, i = (i + 1 >= trkcache.trklen) ? 0 : i + 1)
        {
            if (trkcache.trkd[i] != 0xa1 ||
                trkcache.trkd[i + 1] != 0xfe ||
                !(trkcache.trki[i >> 3] & (1 << (i & 7)))) continue;
            wdAnyop.wdPtr = trkcache.trkd + i + 2;
            wdAnyop.wdLen = 6; // nearest marker
            if (! test)
            {
                found = 1;
                break;
            }
            if (trkcache.trkd[i + 2] != wdTrack || trkcache.trkd[i + 4] != wdSector) continue;
            if (test > 1 && trkcache.trkd[i + 3] != (BYTE)wdSide) continue;
            if (wd93CRC(trkcache.trkd + i + 1, 5) != *(WORD*)(trkcache.trkd + i + 6)) continue;
            if (! needdata)
            {
                found = 1;
                break;
            }
            for (unsigned j = i + 8; j < trkcache.trklen - 4; j++)
                if (trkcache.trkd[j] == 0xa1 && (trkcache.trki[j >> 3] & (1 << (j & 7))) &&
                  !(trkcache.trki[(j + 1) >> 3] & (1 << ((j + 1) & 7))))
                {
                    if (trkcache.trkd[j + 1] == 0xf8 || trkcache.trkd[j + 1] == 0xfb)
                    {
                        wdAnyop.wdPtr = trkcache.trkd + j + 2;
                        wdAnyop.wdLen = 0x80 << trkcache.trkd[i + 5];
                        found = 1;
                        break;
                    }
                    break;
                }
                break;
        }
        if (found && (wdAnyop.wdPtr - trkcache.trkd + wdAnyop.wdLen > trkcache.trklen))
            wdAnyop.wdLen = trkcache.trklen - (wdAnyop.wdPtr - trkcache.trkd);
    }
    else    //no disk/track
        wdNext += 20 * Z80FRQ;

    if (! found)
    {
        wdAnyop.wdPtr = NULL;
        wdState2 = WD_NOTFND;
        t = 4 * MAX_TRACK_LEN;
    }
    wdAnyop.wdPtr0 = wdAnyop.wdPtr;
    wdAnyop.wdLen0 = wdAnyop.wdLen;
    wdNext += ((long long)t) * trkcache.ts_byte;
}

void BetaDisk::seekStep()
{
    fddTrack[wdDrive] += wdStepDirection;
    if (fddTrack[wdDrive] == (BYTE)-1) fddTrack[wdDrive] = 0;
    if (fddTrack[wdDrive] >= MAX_PHYS_CYLS) fddTrack[wdDrive] = MAX_PHYS_CYLS;
    seekTrack(wdDrive, fddTrack[wdDrive], wdSide);
    if (wdCmd & 0x10) wdTrack += wdStepDirection;
    wdNext += wdSeekop.wdStepTime;
    wdState2 = wdState;
    wdState = WD_WAIT;
}

void BetaDisk::processWd()
{
    seekTrack(wdDrive, fddTrack[wdDrive], wdSide);

    QWORD time = pComputer->timeStates + pComputer->pCPU->ticks;
    for (unsigned drv = 0; drv < 4; drv++)
        if (time > fddMotor[drv] && (wdTrDOS & 8)) fddMotor[drv] = 0;
    if (! fddMotor[wdDrive]) wdStatus |= WDS_NOTRDY;
    if (! (wdCmd & 0x80))   //seek/step commands
    {
        wdStatus &= ~(WDS_TRK00 | WDS_INDEX);
        if (fddMotor[wdDrive] && (wdTrDOS & 8))
            wdStatus |= WDS_HEADL;
        if (! fddTrack[wdDrive]) wdStatus |= WDS_TRK00;
        //TODO test spinning
        if (disk[wdDrive].rawdata &&
            fddMotor[wdDrive] &&
            (time % (Z80FRQ / FDD_RPS) < (Z80FRQ * 4 / 1000)))
                wdStatus |= WDS_INDEX;  //index every turn, len = 4ms (if disk present)
    }
    for (;;)
    {
        switch (wdState)
        {
        case WD_READY:
            wdStatus &= ~WDS_BUSY;
            wdRqs |= INTRQ;
            return;

        case WD_WAIT:
            if (Configure::BETANoDelay && time < wdNext) return;
            wdState = wdState2;
            break;

        case WD_NOTFND:
            wdStatus |= WDS_NOTFOUND;
            wdState = WD_READY;
            break;

        case WD_SEEK0:
            if (! fddTrack[wdDrive] || !wdSeekop.wdSeek0cnt)
            {
                wdTrack = 0;
                wdState = WD_SEEKDONE;
                break;
            }
            if (wdSeekop.wdSeek0cnt == 0x100)
                wdTrack = 0;
            else
                wdTrack--;
            wdSeekop.wdSeek0cnt--;
            seekStep();
            break;

        case WD_SEEK:
            if (wdTrack == wdData)
                wdState = WD_SEEKDONE;
            else
                seekStep();
            break;

        case WD_STEP:
            wdState = WD_READY;
            seekStep();
            break;

        case WD_SEEKDONE:
            if (wdCmd & 4)  //read track number
            {
                wdState2 = WD_READY;
                findMarker(0, 0);
                if (! wdAnyop.wdPtr || *wdAnyop.wdPtr != wdTrack)
                    wdState2 = WD_NOTFND;
            }
            else
            {
                wdState = WD_READY;
                wdRqs = INTRQ;
            }
            break;

        case WD_RESET:  //seek to trk0 but no busy
            if (! fddTrack[wdDrive])
                wdState = WD_READY;
            else
            {
                fddTrack[wdDrive]--;
                seekTrack(wdDrive, fddTrack[wdDrive], wdSide);
            }
            wdNext += wdSeekop.wdStepTime;
            break;

        case WD_READDATA:
            if (Configure::BETANoDelay && (wdRqs & DRQ) && wdNext > time) return;
            if (wdAnyop.wdLen)
            {
                readState = STATE_TIME;
                if (wdRqs & DRQ) wdStatus |= WDS_LOST;
                wdData = *wdAnyop.wdPtr++;
                wdAnyop.wdLen--;
                wdRqs = DRQ;
                wdStatus |= WDS_DRQ;
                wdNext += trkcache.ts_byte;
                wdState = WD_WAIT;
                wdState2 = WD_READDATA;
            }
            else
            {
                wdState = WD_READY;
                if ((wdCmd & 0xe0) == 0x80) //read sector
                {
                    if (wdAnyop.wdPtr0[-1] == 0xf8) wdStatus |= WDS_RECORDT;
                    if (*(WORD*)(wdAnyop.wdPtr0 + wdAnyop.wdLen0) != wd93CRC(wdAnyop.wdPtr0 - 1, wdAnyop.wdLen0 + 1))
                        wdStatus |= WDS_CRCERR;
                    if (wdCmd & 0x10)
                    {
                        wdState = WD_READSECTORS;
                        wdSector++;
                    }
                }
                if ((wdCmd & 0xf0) == 0xc0) //read address
                {
                    if (*(WORD*)(wdAnyop.wdPtr0 + 4) != wd93CRC(wdAnyop.wdPtr0 - 1, 5))
                        wdStatus |= WDS_CRCERR;
                }
            }
            break;

            case WD_READSECTORS:
                wdState2 = WD_STARTREAD;
                findMarker((wdCmd & 2) ? 2 : 1, 1);
                break;

            case WD_STARTREAD:
                wdState2 = WD_READDATA;
                wdState = WD_WAIT;
                wdNext += trkcache.ts_byte;
                wdRqs = DRQ;
                wdStatus |= WDS_DRQ;
                wdData = *wdAnyop.wdPtr++;
                wdAnyop.wdLen--;
                break;

            case WD_WRITESECTORS:
                wdState2 = WD_STARTWRITE;
                findMarker((wdCmd & 2) ? 2 : 1, 1);
                break;

            case WD_STARTWRITE: //set drq and wait 22 bytes
                wdState = WD_WAIT;
                wdState2 = WD_STARTWRITE2;
                wdRqs |= DRQ;
                wdStatus |= WDS_DRQ;
                wdNext += 22 * trkcache.ts_byte;
                break;

            case WD_STARTWRITE2:
                if (wdRqs & DRQ)
                {
                    if (Configure::BETANoDelay && wdNext > time) return;
                    wdState = WD_READY;
                    wdStatus |= WDS_LOST;
                }
                else
                {
                    disk[wdDrive].optype |= 1;
                    wdAnyop.wdPtr[-1] = (wdCmd & 1) ? 0xf8 : 0xfb;
                    *wdAnyop.wdPtr = wdData;
                    trkcache.trki[(wdAnyop.wdPtr - trkcache.trkd) >> 3] &= ~(1 << ((wdAnyop.wdPtr - trkcache.trkd) & 7));
                    wdAnyop.wdPtr++;
                    wdAnyop.wdLen--;
                    wdState = WD_WAIT;
                    wdState2 = WD_WRITEDATA;
                    wdStatus |= WDS_DRQ;
                    wdRqs |= DRQ;
                    wdNext += 12 * trkcache.ts_byte;
                }
                break;

            case WD_WRITEDATA:
                if (Configure::BETANoDelay && (wdRqs & DRQ) && wdNext > time) return;
                if (wdRqs & DRQ)
                {
                    wdStatus |= WDS_LOST;
                    wdData = 0;
                }
                writeState = STATE_TIME;
                *wdAnyop.wdPtr = wdData;
                trkcache.trki[(wdAnyop.wdPtr - trkcache.trkd) >> 3] &= ~(1 << ((wdAnyop.wdPtr - trkcache.trkd) & 7));
                wdAnyop.wdPtr++;
                if (--wdAnyop.wdLen)
                {
                    wdNext += trkcache.ts_byte;
                    wdState = WD_WAIT;
                    wdState2 = WD_WRITEDATA;
                    wdRqs = DRQ;
                    wdStatus |= WDS_DRQ;
                }
                else
                {
                    wdState = WD_READY;
                    if ((wdCmd & 0xe0) == 0xa0) //write sector
                    {
                        *(WORD*)(wdAnyop.wdPtr0 + wdAnyop.wdLen0) = wd93CRC(wdAnyop.wdPtr0 - 1, wdAnyop.wdLen0 + 1);
                        trkcache.trki[(wdAnyop.wdPtr0 + wdAnyop.wdLen0 - trkcache.trkd) >> 3] &= ~(1 << ((wdAnyop.wdPtr0 + wdAnyop.wdLen0 - trkcache.trkd) & 7));
                        trkcache.trki[(wdAnyop.wdPtr0 + wdAnyop.wdLen0 + 1 - trkcache.trkd) >> 3] &= ~(1 << ((wdAnyop.wdPtr0 + wdAnyop.wdLen0 + 1 - trkcache.trkd) & 7));
                        if (wdCmd & 0x10)
                        {
                            wdState = WD_WRITESECTORS;
                            wdSector++;
                        }
                    }
                }
                break;

            case  WD_FORMATTRACK:
                if (wdRqs & DRQ)
                {
                    if (Configure::BETANoDelay && wdNext > time) return;
                    wdState = WD_READY;
                    wdStatus |= WDS_LOST;
                    break;
                }
                disk[wdDrive].optype |= 2;
                *wdAnyop.wdPtr = wdData;
                trkcache.trki[(wdAnyop.wdPtr - trkcache.trkd) >> 3] &= ~(1 << ((wdAnyop.wdPtr - trkcache.trkd) & 7));
                wdAnyop.wdPtr++;
                wdAnyop.wdLen--;
                wdState = WD_WAIT;
                wdState2 = WD_FORMAT;
                wdStatus |= WDS_DRQ;
                wdRqs |= DRQ;
                wdNext += trkcache.ts_byte;
                wdAnyop.wdPtr0 = wdAnyop.wdPtr;
                break;

            case WD_FORMAT:
            {
                if (Configure::BETANoDelay && (wdRqs & DRQ) && wdNext > time) return;
                formatState = STATE_TIME;
                if (wdRqs & DRQ)
                {
                    wdStatus |= WDS_LOST;
                    wdData = 0;
                }
                BYTE marker = 0, data = wdData;
                unsigned crc;
                if (data == 0xf5)
                {
                    data = 0xa1;
                    marker = 1;
                    wdAnyop.wdPtr0 = wdAnyop.wdPtr + 1;
                }
                if (data == 0xf6)
                {
                    data = 0xc2;
                    marker = 1;
                }
                if (data == 0xf7)
                {
                    crc = wd93CRC(wdAnyop.wdPtr0, wdAnyop.wdPtr - wdAnyop.wdPtr0);
                    data = crc & 0xff;
                }
                *wdAnyop.wdPtr = data;
                if (marker)
                    trkcache.trki[(wdAnyop.wdPtr - trkcache.trkd) >> 3] |= (1 << ((wdAnyop.wdPtr - trkcache.trkd) & 7));
                else
                    trkcache.trki[(wdAnyop.wdPtr - trkcache.trkd) >> 3] &= ~(1 << ((wdAnyop.wdPtr - trkcache.trkd) & 7));
                wdAnyop.wdPtr++;
                wdAnyop.wdLen--;
                if (wdData == 0xf7) //second byte of crc16
                {
                    *wdAnyop.wdPtr = crc >> 8;
                    trkcache.trki[(wdAnyop.wdPtr - trkcache.trkd) >> 3] &= ~(1 << ((wdAnyop.wdPtr - trkcache.trkd) & 7));
                    wdAnyop.wdPtr++;
                    wdAnyop.wdLen--;
                }
                if ((int)wdAnyop.wdLen > 0)
                {
                    wdNext += trkcache.ts_byte;
                    wdState = WD_WAIT;
                    wdState2 = WD_FORMAT;
                    wdRqs = DRQ;
                    wdStatus |= WDS_DRQ;
                }
                else
                    wdState = WD_READY;
            }
            break;

            default:
                printf("BETA:WD1793 in wrong state!!!\n");
                exit(2);
        }
    }
}

// open files....
unsigned BetaDisk::newDisk(unsigned drv, unsigned cyls, unsigned sides)
{
DISK* dsk = disk + drv;

    if (freeDisk(drv)) return TRUE;
    unsigned trklen = MAX_TRACK_LEN;
    unsigned trklen2 = trklen + (trklen >> 3) + ((trklen & 7) ? 1 : 0);
    dsk->rawsize = cyls * sides * trklen2;
    dsk->rawdata = new BYTE[dsk->rawsize];
    memset(dsk->rawdata, 0, dsk->rawsize);
    dsk->cyls = cyls;
    dsk->sides = sides;
    for (unsigned i = 0; i < cyls; i++)
        for (unsigned j = 0; j < sides; j++)
        {
            dsk->trklen[i][j] = trklen;
            dsk->trkd[i][j] = dsk->rawdata + trklen2 * (i * sides + j);
            dsk->trki[i][j] = dsk->trkd[i][j] + trklen;
        }
    trkcache.drive = (unsigned)-1;
    seekTrack(drv, 0, 0);
    return FALSE;
}

unsigned BetaDisk::freeDisk(unsigned drv)
{
DISK* dsk = disk + drv;
    if (dsk->optype)
    {
        QString str = QString("Drive %1 changed. Save?").arg(QChar(drv + 'A'), 1);
        int res = QMessageBox::question(NULL, "Warning!", str, QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel | QMessageBox::Escape);
        if (res == 2) return TRUE;//cancel
        if (res == 0)    //ok
        {
            str = QFileDialog::getSaveFileName(".", "Betadisk images (*.trd, *.TRD)", NULL, NULL, "Save changed file");
            if (! str.isEmpty())
            {
                //save trd file
                if (saveTRD(str, drv))
                {
                    QMessageBox::warning(NULL, "Error", QString("Cannot save %1").arg(str), QMessageBox::Ok, 0);
                    return TRUE; //do not remove!!!
                }
            }
        }
    }
    if (dsk->rawdata) delete[] dsk->rawdata;
    memset(dsk, 0, sizeof(DISK));
    *Configure::BETAImages[drv] = 0;

    trkcache.drive = (unsigned)-1;
    seekTrack(drv, 0, 0);
    return FALSE;
}

unsigned BetaDisk::emptyDisk(unsigned drv)
{
    if (formatTRD(drv, MAX_CYLS)) return TRUE;
    SECHDR* s8 = getSector(drv, 0, 0, 9);
    if (s8 == NULL) return TRUE;
    s8->data[0xe2] = 1;                 //first free track
    s8->data[0xe3] = 0x16;              //80t,ds
    *(WORD*)(s8->data + 0xe5) = 2544;   //free sectors
    s8->data[0xe7] = 0x10;              //trdos
    writeSector(drv, 0, 0, 9, s8->data);//upd crc
    return FALSE;
}

unsigned BetaDisk::addFile(unsigned drv, BYTE* hdr, BYTE* data)
{
SECHDR* s8 = getSector(drv, 0, 0, 9);

    if (s8 == NULL) return TRUE;
    BYTE* dat = s8->data;
    unsigned len = hdr[13];
    unsigned pos = dat[0xe4] << 4;
    SECHDR* dir = getSector(drv, 0, 0, 1 + (pos >> 8));
    if (dir == NULL) return TRUE;
    if (*(WORD*)(dat + 0xe5) < len) return TRUE;   //disk full
    memcpy(dir->data + (pos & 0xff), hdr, 14);
    *(WORD*)(dir->data + (pos & 0xff) + 14) = *(WORD*)(dat + 0xe1);
    writeSector(drv, 0, 0, 1 + (pos >> 8), dir->data);

    pos = dat[0xe1] + (dat[0xe2] << 4);

    for (unsigned i = 0; i < len; i++, pos++)
        writeSector(drv, pos >> 5, (pos >> 4) & 1, (pos & 15) + 1, data + (i << 8));

    dat[0xe1] = pos & 15;
    dat[0xe2] = pos >> 4;
    dat[0xe4]++;
    *(WORD*)(dat + 0xe5) -= len;
    writeSector(drv, 0, 0, 9, dat);
    return FALSE;
}

BYTE* BetaDisk::loadFile(const char* filename)
{
    printf("Loading %s : ", filename);
int file = open(filename, O_RDONLY)    ;

    if (file == -1)
    {
        printf("failed to open!\n");
        return NULL;
    }
    unsigned size = lseek(file, 0, SEEK_END);
    lseek(file, SEEK_SET, 0);

BYTE* buff = new BYTE[size];

    if (read(file, buff, size) == -1)
    {
        close(file);
        delete[] buff;
        printf("failed to read!\n");
        return NULL;
    }
    close(file);
    return buff;
}

unsigned BetaDisk::formatTRD(unsigned drv, unsigned cyls)
{
    if (newDisk(drv, cyls, 2)) return TRUE;

SECHDR hdr[16];
static BYTE lv[3][16] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
                         {1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 8, 16},
                         {1, 12, 7, 2, 13, 8, 3, 14, 9, 4, 15, 10, 5, 16, 11, 6}};

    for (unsigned c = 0; c < trkcache.cyls; c++)
        for (unsigned side = 0; side < 2; side++)
        {
            for (unsigned sec = 0; sec < 16; sec++)
            {
            unsigned s = lv[Configure::BETAInterleave][sec];
                hdr[sec].n = s;
                hdr[sec].l = 1;
                hdr[sec].c = c;
                hdr[sec].s = 0;
                hdr[sec].c1 = hdr[sec].c2 = 0;
                hdr[sec].data = (BYTE*)1;
            }
            formatTrack(drv, c, side, 16, hdr);
        }

    return FALSE;
}

unsigned BetaDisk::openSCL(const char* filename, unsigned drv)
{
    drv &= 3;
    if (emptyDisk(drv))
        return TRUE;

BYTE* buff = loadFile(filename);
    if (buff == NULL) return TRUE;

    unsigned size, i;
    for (i = size = 0; i < buff[8]; i++) size += buff[9 + 14 * i + 13];
    if (size > 2544)
    {
        SECHDR* s8 = getSector(drv, 0, 0, 9);
        if (s8 != NULL)
        {
            *(WORD*)(s8->data + 0xe5) = size;
            writeSector(drv, 0, 0, 9, s8->data);
        }
    }
    BYTE* data = buff + 9 + 14 * buff[8];
    for (i = 0; i < buff[8]; i++)
    {
        if (addFile(drv, buff + 9 + 14 * i, data))
        {
            printf("cannot add file!\n");
            delete[] buff;
            return TRUE;
        }
        data += buff[9 + 14 * i + 13] << 8;
    }
    delete[] buff;
    strcpy(Configure::BETAImages[drv], filename);
    printf("Ok!\n");
    return FALSE;
}

unsigned BetaDisk::openTRD(const char* filename, unsigned drv)
{
    drv &= 3;
    if (formatTRD(drv, MAX_CYLS))
        return TRUE;

BYTE* buff = loadFile(filename);
    if (buff == NULL) return TRUE;

   for (unsigned i = 0; i < 655360; i += 256)
        writeSector(drv, i >> 13, (i >> 12) & 1, ((i >> 8) & 0x0f) + 1, buff + i);
   delete[] buff;

   strcpy(Configure::BETAImages[drv], filename);
   printf("Ok!\n");
   return FALSE;
}

unsigned BetaDisk::saveTRD(const char* filename, unsigned drv)
{
	drv &= 3;
    printf("Saving %s:", filename);

int file = creat(filename, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
    if (file == -1)
    {
        printf("failed to open!\n");
        return 1;
    }
BYTE* buff = new BYTE[256]; //empty sector

    memset(buff, 0, 256);
    for (unsigned i = 0; i < 2560; i++)
    {
        SECHDR* pHd = getSector(drv, i >> 5, (i >> 4) & 1, (i & 0x0f) + 1);
        BYTE* data = buff;
        if (pHd) data = pHd->data;
        if (! data) data = buff;
        if (write(file, data, 256) == -1)
        {
            printf("failed to write!\n");
            close(file);
            return 1;
        }
    }
    close(file);
	disk[drv].optype = 0;	//no changed
    printf("Ok!\n");
    return 0;
}

int BetaDisk::writeSector(unsigned drv, unsigned cyl, unsigned side, unsigned sec, BYTE* data, unsigned crc)
{
unsigned i;
    seekTrack(drv, cyl, side, 1);
    for (i = 0; i < trkcache.s; i++)
        if (trkcache.hdr[i].n == sec) break;

    if (i == trkcache.s) return 0;
    if (trkcache.hdr[i].c != cyl || trkcache.hdr[i].l != 1) return 0;
    memcpy(trkcache.hdr[i].data, data, 256);
    if (crc == (unsigned)-1) crc = wd93CRC(trkcache.hdr[i].data - 1, 257);
    *(WORD*)(trkcache.hdr[i].data + 256) = (WORD)crc;
    return 1;
}

BetaDisk::SECHDR* BetaDisk::getSector(unsigned drv, unsigned cyl, unsigned side, unsigned sec)
{
unsigned i;
    seekTrack(drv, cyl, side, 1);
    for (i = 0; i < trkcache.s; i++)
        if (trkcache.hdr[i].n == sec) break;
    if (i == trkcache.s) return NULL;
    if (trkcache.hdr[i].l != 1 || trkcache.hdr[i].c != cyl) return NULL;
    return trkcache.hdr + i;
}
