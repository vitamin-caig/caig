/***************************************************************************
                          computer.cpp  -  description
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
#include <sys/unistd.h>
#include <fcntl.h>

#include "zxlin.h"
#include "computer.h"
#include "debugger.h"

///ABBY: Inherited changes from CPU, (unnamed structs->regB, regP)
//ctor. create all necessary objects and devices
Computer::Computer()
{
#ifdef _DEBUG_
    printf("Computer\n");
#endif
    trace = FALSE;

    pIOManager = new IOManager;
	pSndManager = new SoundManager;

	pULA = new ULA(this);
    pBetaDisk = new BetaDisk(this);
    pMemory = new Memory(this);
    pCPU = new CPU(pMemory, pIOManager);

    pDebugger = new Debugger(this);

	pKbd = new Keyboard(this);
    pMouse = new Mouse(this);

	pDAC = new DAC(this);
	pAY = new AY(this);

	pDMA = new DMA(this);

    pROMPage = new BYTE[49152];
    pULA->setScreenSrc(pMemory->getScreenSrc());
    timeStates = 0;
    maxSpeed = FALSE;

    //processing autostarts
    if (*Configure::VARBasic128ROM)
        loadROM(Configure::VARBasic128ROM, ERBasic128);
    if (*Configure::VARBasic48ROM)
        loadROM(Configure::VARBasic48ROM, ERBasic48);
    if (*Configure::VARTRDosROM)
        loadROM(Configure::VARTRDosROM, ERTrDOS);
    if (*Configure::VARSystemROM)
        loadROM(Configure::VARSystemROM, ERSystem);
    if (*Configure::VARAutoLoad)
        ::ZXLin->openFile(Configure::VARAutoLoad);
}


Computer::~Computer()
{
	delete pDMA;

    delete pROMPage;
    delete pAY;
    delete pDAC;
    delete pMouse;
    delete pKbd;
    delete pDebugger;
    delete pCPU;
    delete pMemory;
    delete pBetaDisk;
    delete pSndManager;
    delete pIOManager;
    delete pULA;
#ifdef _DEBUG_
    printf("~Computer\n");
#endif
}

void Computer::reset()
{
    pCPU->reset();
    pIOManager->reset();
}

// loads an a ROM to specified ROMpage
void Computer::loadROM(const char* filename, unsigned rompage)
{
char pTmp[MAX_PATH_LEN];
int var1 = 0;

    strcpy(pTmp, filename);

char* pExt = strrchr(pTmp, ':');

    if (pExt != NULL)
    {
        var1 = atoi(pExt + 1);
        *pExt = 0;
    }

int file = open(pTmp, O_RDONLY);

    printf("Loading ROM %s : ", filename);
    if (file == -1)
    {
        printf("Failed!\n");
        return;
    }
    if (var1)
        lseek(file, var1 << 14, SEEK_SET);
    if (rompage < 3)
        read(file, pMemory->getROMPage(rompage), 16384);
    close(file);
    printf("Ok!\n");
}

// loads *.sna file
unsigned Computer::loadSna(const char* filename)
{
hdrSNA128 header;

    printf("Loading %s: ", filename);

int file = open(filename, O_RDONLY);

    if (file == -1)
    {
        printf("failed!\n");
        return TRUE;
    }
    int len = lseek(file, 0, SEEK_END);
    lseek(file, 0, SEEK_SET);
    if (len != 131103 && len != 147487 && len != 49179)
    {
        printf("Wrong file!\n");
        close(file);
        return TRUE;
    }
    if (len == 131103 || len == 147487)
        len = 1;    //128k
    else
        len = 0;
    read(file, &header, sizeof(hdrSNA128) - (len ? 0 : 4));

    Configure::MEMMemType = MEM_PENT128;
//    unsigned tmpres = Configure::SYSResetTo;
    Configure::SYSResetTo = len ? (header.trdos ? ERTrDOS : ERBasic128) : ERBasic48;
    reset();

    pCPU->I = header.i;
    pCPU->HL_ = header.hl_;
    pCPU->DE_ = header.de_;
    pCPU->BC_ = header.bc_;
    pCPU->AF_ = header.af_;
    pCPU->regP.HL = header.hl;
    pCPU->regP.DE = header.de;
    pCPU->regP.BC = header.bc;
    pCPU->regP.IY = header.iy;
    pCPU->regP.IX = header.ix;
    pCPU->iff1 = header.iff1 ? 1 : 0;

    pCPU->R = header.r;
    pCPU->R_h = header.r & 128;
    pCPU->regP.AF = header.af;
    pCPU->regP.SP = header.sp;
    pCPU->im = header.im;
    pULA->outByte(0xfe, header.pFE);
    memcpy(pMemory->getPage(5), header.page5, 16384);
    memcpy(pMemory->getPage(2), header.page2, 16384);
    memcpy(pMemory->getPage(len ? (header.p7FFD & 7) : 0), header.actpage, 16384);
    if (len)
        pCPU->regP.PC = header.pc;
    else
        pCPU->regP.PC = pMemory->read(pCPU->regP.SP++) + (pMemory->read(pCPU->regP.SP++) << 8);

    if (len)
        for (unsigned i = 0; i < 8; i++)
        {
            if (i == 2 || i == 5 || i == (header.p7FFD & 7)) continue;
            read(file, pMemory->getPage(i), 16384);
        }

    pIOManager->outByte(0x7ffd, len ? header.p7FFD : 0x30);
    close(file);
    printf("Ok!\n");
    pCPU->ticks = 0;
    pULA->startFrame();
    pSndManager->startFrame();
	return FALSE;
}

unsigned Computer::saveSna(const char* filename)
{
hdrSNA128 header;

    printf("Saving %s : ", filename);
int file = creat(filename, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
    if (file == -1)
    {
        printf("Failed!\n");
        return TRUE;
    }
    header.trdos = (pMemory->status & MEMSTAT_TRDOS) ? 1 : 0;
    header.af_ = pCPU->AF_;
    header.bc_ = pCPU->BC_;
    header.de_ = pCPU->DE_;
    header.hl_ = pCPU->HL_;
    header.af = pCPU->regP.AF;
    header.bc = pCPU->regP.BC;
    header.de = pCPU->regP.DE;
    header.hl = pCPU->regP.HL;
    header.ix = pCPU->regP.IX;
    header.iy = pCPU->regP.IY;
    header.sp = pCPU->regP.SP;
    header.pc = pCPU->regP.PC;
    header.i = pCPU->I;
    header.r = (pCPU->R & 0x7f) + pCPU->R_h;
    header.im = pCPU->im;
    header.iff1 = pCPU->iff1 ? 0xff : 0;
    header.pFE = pULA->pFE;
    header.p7FFD = pMemory->state7ffd;
    unsigned size = sizeof(hdrSNA128);
    if (header.p7FFD == 0x30) //save 48k
    {
        size = 0xc01b;
        header.sp -= 2;
        pMemory->write(header.sp, pCPU->regB.PCl);
        pMemory->write(header.sp + 1, pCPU->regB.PCh);
    }
    memcpy(header.page5, pMemory->getPage(5), 16384);
    memcpy(header.page2, pMemory->getPage(2), 16384);
    memcpy(header.actpage, pMemory->getPage(header.p7FFD & 7), 16384);
    write(file, &header, size);

    if (size != 0xc01b)
    {   //pages fo 128k
        for (unsigned i = 0; i < 8; i++)
        {
            if (i == 2 || i == 5 || i == (header.p7FFD & 7)) continue;
                write(file, pMemory->getPage(i), 16384);
        }
    }
    close(file);
    return FALSE;
}

// setting tracing mode
void Computer::tracing(unsigned trac)
{
    trace = trac;
}

void Computer::visualize(unsigned fps)
{
    if (! trace) ::ZXLin->pGfxControl->proceed();    //proceed frame through filter
    pIOManager->showState(! trace);
    if (! trace)
    {
        if (pCPU->haltpos)
        {
            int progr = pCPU->haltpos * 100 / Configure::ULATicksPerFrame;
            ::ZXLin->pGfxControl->clearWindow(16, 450, progr, 2, 0xff0000);
            if (progr != 100)
                ::ZXLin->pGfxControl->clearWindow(16 + progr, 450, 100 - progr, 2, 0x0000ff);
            pCPU->haltpos = 0;
        }
        char szTmp[12];
        sprintf(szTmp, "%i.%02ifps", fps / 10, fps % 10);
        ::ZXLin->pGfxControl->printMask(16, 456, szTmp, 0xffffff, 0);
    }
}


unsigned Computer::frame(unsigned stepping, unsigned rendering)
{
    if (stepping ^ trace)
    {
        usleep(100);
        return 0;
    }
    do
    {
        if (pCPU->halted)
        {
            DWORD dif = (Configure::ULATicksPerFrame - pCPU->ticks - 1) / 4 + 1;
			pCPU->R += dif;
			dif <<= 2;
			pCPU->ticks += dif;
            pCPU->timeticks += dif;
            if (rendering)
                pULA->retrace();
            if (! maxSpeed)
                pSndManager->retrace();
            break;
        }
        if (pMemory->status & MEMSTAT_LEAVEROM)
        {
            if (pCPU->regB.PCh & 0xc0)
            {
                pMemory->status &= ~(MEMSTAT_LEAVEROM | MEMSTAT_DOSPORTS | MEMSTAT_TRDOS | MEMSTAT_SYSTEMROM);
                pMemory->updateState();
            }
            if (Configure::BETATraps && pMemory->getROMPage() == ERTrDOS)
                pBetaDisk->betaTraps();
        }
        if ((pMemory->status & MEMSTAT_SETDOSROM) && (pCPU->regB.PCh == 0x3d))
        {
            pMemory->status |= MEMSTAT_TRDOS;
            pMemory->updateState();
        }

		//unsigned ticks = pCPU->ticks;
        pCPU->step();
		//ticks = pCPU->ticks - ticks;
        if (rendering)
            pULA->renderUntil(pCPU->ticks);
        if (! maxSpeed) pSndManager->renderUntil(pCPU->ticks);
        if (pDebugger->isBreakPoint(pCPU->regP.PC)) return 1;
    }
    while ((pCPU->ticks < Configure::ULATicksPerFrame) && !trace);

	//if (pCPU->ticks >= Configure::ULATicksPerFrame)
	if (! trace)
    {
        timeStates += Configure::ULATicksPerFrame;

        WORD intadr = 0x38;
        if (pCPU->iff1)
        {
            if (pCPU->im == 2)
            {
                WORD vec = (pCPU->I << 8) + 0xff;
                intadr = pMemory->read(vec) + ((int)pMemory->read(vec + 1) << 8);
            }
            pCPU->_push(pCPU->regP.PC);
            pCPU->ticks += (pCPU->im < 2) ? 13 : 19;
            pCPU->timeticks += (pCPU->im < 2) ? 13 : 19;
            pCPU->halted = pCPU->iff1 = pCPU->iff2 = FALSE;
            pCPU->regP.PC = intadr;
        }
        if (! maxSpeed) pSndManager->renderUntil(pCPU->ticks);
        pCPU->ticks -= Configure::ULATicksPerFrame;
    }
    return 0;//(debug->isBreakPoint(pCPU->regP.PC));
}
