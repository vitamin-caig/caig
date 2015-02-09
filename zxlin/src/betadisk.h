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

// info taken from UnrealSpeccy sources. Thx 2 SMT!!!
#ifndef BETADISK_H
#define BETADISK_H

#include <device.h>
class Computer;

class BetaDisk : public Device
{
public:
    BetaDisk(Computer* pComp);
    ~BetaDisk();

    unsigned openSCL(const char* filename, unsigned drv);
    unsigned openTRD(const char* filename, unsigned drv);
    unsigned saveTRD(const char* filename, unsigned drv);
    unsigned openFDI(const char* filename, unsigned drv);
    unsigned saveFDI(const char* filename, unsigned drv);
    unsigned freeDisk(unsigned drv);

//-- Device virtuals
    virtual void reset();
    virtual unsigned inByte(WORD adr, BYTE* data);
    virtual unsigned outByte(WORD adr, BYTE data);
    virtual void showState(GfxControl* pControl, unsigned full);

    void betaTraps();
//structures
private:
    enum
    {
        MAX_TRACK_LEN = 6912,
        MAX_CYLS = 86,
        MAX_PHYS_CYLS = 86,
        MAX_SEC = 256,

        FDD_RPS = 5,
        STATE_TIME = 20,
    };

    struct SECHDR
    {
        BYTE c, s, n, l;    //cylinder, side, drive, len
        WORD crc;           //crc
        BYTE c1, c2;        //crc is correct in data and idx
        BYTE* data;         //sector data
        BYTE* id;           //index data
        unsigned datalen;   //len of data area
        unsigned crcd;      //crc of data
    };

    struct DISK
    {
        BYTE* rawdata;                  //disk rawdata
        unsigned rawsize;               //size of rawdata
        unsigned cyls, sides;           //disk parameters
        unsigned optype;                //operational
        unsigned trklen[MAX_CYLS][2];   //len of tracks
        BYTE* trkd[MAX_CYLS][2];        //data of tracks
        BYTE* trki[MAX_CYLS][2];        //index of tracks
    };

    struct TRKCACHE
    {
        unsigned drive, cyl, side;      //cache info
        unsigned cyls, sides, trklen;   //disk parameters
        BYTE* trkd;                     //track data
        BYTE* trki;                     //track index
        unsigned ts_byte, s, sf;        //
        SECHDR hdr[MAX_SEC];            //sectors headers
    };

    DISK disk[4];
    TRKCACHE trkcache;

// contoller
    enum WDSTATE
    {
        WD_READY = 0,
        WD_WAIT,
        WD_SEEK0,
        WD_SEEK,
        WD_STEP,
        WD_SEEKDONE,
        WD_STARTREAD,
        WD_READSECTORS,
        WD_READDATA,
        WD_NOTFND,
        WD_WRITESECTORS,
        WD_STARTWRITE,
        WD_STARTWRITE2,
        WD_WRITEDATA,
        WD_FORMATTRACK,
        WD_FORMAT,
        WD_RESET
    };

    enum
    {
        INTRQ = 0x80,
        DRQ = 0x40
    };

    enum
    {
        WDS_BUSY        = 0x01,
        WDS_INDEX       = 0x02,
        WDS_DRQ         = 0x02,
        WDS_TRK00       = 0x04,
        WDS_LOST        = 0x04,
        WDS_CRCERR      = 0x08,
        WDS_NOTFOUND    = 0x10,
        WDS_RECORDT     = 0x20,
        WDS_HEADL       = 0x20,
        WDS_WRFAULT     = 0x20,
        WDS_WRITEP      = 0x40,
        WDS_NOTRDY      = 0x80
    };

    BYTE fddTrack[4];
    QWORD fddMotor[4];

    QWORD wdNext;
    BYTE wdState;
    BYTE wdCmd;
    BYTE wdData;
    BYTE wdTrack;
    BYTE wdSector;
    BYTE wdRqs;
    BYTE wdStatus;
    BYTE wdState2;
    unsigned wdDrive;
    unsigned wdSide;
    union
    {
        struct
        {
            unsigned wdStepTime;
            unsigned wdSeek0cnt;
        } wdSeekop;
        struct
        {
            BYTE* wdPtr;
            unsigned wdLen;
            BYTE* wdPtr0;
            unsigned wdLen0;
        } wdAnyop;
    };
    signed char wdStepDirection;
    BYTE wdTrDOS;

private:
    unsigned readState;
    unsigned writeState;
    unsigned formatState;

//functions
private:
    unsigned wordSwap(unsigned data);
    unsigned wd93CRC(BYTE* ptr, unsigned size);
    void seekTrack(unsigned drv, unsigned cyl, unsigned side, unsigned fs = 0);
    unsigned newDisk(unsigned drv, unsigned cyls, unsigned sides);
    void formatTrack(unsigned drv, unsigned cyl, unsigned side, unsigned numsec, SECHDR* pHdr);
    void findMarker(int test, int needdata);
    void seekStep();
    void setupSeek(unsigned val);
    void trkOp();
    void processWd();

    int writeSector(unsigned drv, unsigned cyl, unsigned side, unsigned sec, BYTE* data, unsigned crc = -1);
    SECHDR* getSector(unsigned drv, unsigned cyl, unsigned side, unsigned sec);
    BYTE* loadFile(const char* filename);
    unsigned formatTRD(unsigned drv, unsigned cyls);
    unsigned emptyDisk(unsigned drv);
    unsigned addFile(unsigned drv, BYTE* hdr, BYTE* data);
};

#endif
