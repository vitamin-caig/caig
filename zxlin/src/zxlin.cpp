/***************************************************************************
                        zxlin.cpp  -  description
                           -------------------
  begin                : ����12 21:05:58 MSK 2005
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

#include "zxlin.h"
#include "configure.h"

#include <qfile.h>
#include "disasm.h"

#include <SDL/SDL_thread.h>

#include "UI.h"

#include "options.h"

//static working thread procedure
int ThreadProc(void*)
{
    while (1)
        ZXLin->threadEvent();
}

//quit procedure
void QuitProc()
{
    delete ZXLin;
    SDL_Quit();
    printf("See you later!\n");
}

// Zxlin description
Zxlin::Zxlin()
{
#ifdef _DEBUG_
    printf("Zxlin\n");
#endif
//configure: read settings
    pConfigure = new Configure;

    // Init SDL subsystems
    if ( ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ) )
    {
        printf("%s\n", SDL_GetError());
        exit( -1 );
    }
    else
        atexit(QuitProc);

//2 gfxcontrol
    if (Configure::VIDFullScreen)
        fullScr = inputLock = TRUE;
    else
        fullScr = inputLock = FALSE;

    pGfxControl = new GfxControl;

    SDL_ShowCursor(inputLock ? SDL_DISABLE : SDL_ENABLE);

    pCUIControl = new CUIControl(pGfxControl);

    paused = FALSE;
}

Zxlin::~Zxlin()
{
//    SDL_KillThread(pThread);
    delete pComputer;
    delete pCUIControl;
    delete pGfxControl;
    delete pConfigure;
#ifdef _DEBUG_
    printf("~Zxlin\n");
#endif
}

unsigned Zxlin::openFile(const char* filename)
{
const char* pExt = strrchr(filename, '.');
static char pTmp[MAXPATHLEN];
int var1;

    var1 = -1;
    do
    {
        var1++;
        pTmp[var1] = tolower(pExt[var1]);
    }
    while (pTmp[var1]);

    if (!strcmp(pTmp, ".sna"))
    {
        pComputer->loadSna(filename);
        return TRUE;
    }

    var1 = 0;
    if (!strcmp(pTmp, ".trd") || sscanf(pTmp, ".trd:%i", &var1))
    {
        strcpy(pTmp, filename);
        pTmp[pExt - filename + 4] = 0;
        return pComputer->pBetaDisk->openTRD(pTmp, var1);
    }
    var1 = 0;
    if (!strcmp(pTmp, ".scl") || sscanf(pTmp, ".scl:%i", &var1))
    {
        strcpy(pTmp, filename);
        pTmp[pExt - filename + 4] = 0;
        return pComputer->pBetaDisk->openSCL(pTmp, var1);
    }
    printf("Unknown filetype %s\n", pTmp);
    return FALSE;
}


void Zxlin::run()
{
SDL_Event g_Event;

    pComputer = new Computer;
    watchdog = 10000;
//    pThread = SDL_CreateThread(ThreadProc, this);

    while (watchdog--)
    {
        threadEvent();
        while (SDL_PollEvent(&g_Event))
        {
            switch (g_Event.type)
            {
            case SDL_QUIT:
                exit(0);
                break;

            case SDL_KEYDOWN:
                keyPressEvent(&g_Event.key.keysym);
                break;

            case SDL_MOUSEBUTTONUP:
                if (! inputLock && g_Event.button.button == SDL_BUTTON_LEFT)
                {
                    inputLock = TRUE;
                    SDL_ShowCursor(SDL_DISABLE);
                }
                break;

            case SDL_USEREVENT:
                watchdog = 10000;
                break;

            default:
                printf("Unknown event %i\n", g_Event.type);
                break;
            }
        }
//        usleep(1000);
    }
    printf("Watchdog exit!\n");
    exit(2);
}

//processing keypressing
void Zxlin::keyPressEvent(SDL_keysym* pKey)
{
static int scrshotnum = 0;
static char tmpstr[32];

    //alt+alt = input lockout
    if ((!fullScr) && pKey->sym == SDLK_RALT && (pKey->mod & KMOD_LALT))
    {
        inputLock = FALSE;
        SDL_ShowCursor(SDL_ENABLE);
        return;
    }

    //alt+alt+enter = toggle fullscreen
    if (pKey->sym == SDLK_RETURN &&
        (pKey->mod & (KMOD_LALT | KMOD_RALT)) == (KMOD_LALT | KMOD_RALT))
    {
        if (!fullScr)
        {
            pGfxControl->toFull();
            SDL_ShowCursor(SDL_DISABLE);
            inputLock = TRUE;
        }
        else
            pGfxControl->toWin();
        fullScr = !fullScr;
        return;
    }

    // translate to debugger if tracing mode
    if (pComputer->isTracing())
        pComputer->pDebugger->keyPressEvent(pKey);
    else
    {
        //translate keys to CUILib
        if (pCUIControl->processKeyPress(pKey)) return;

        //if paused only PAUSE & ESCAPE is valid
        if (paused)
        {
            //unpause
            if (pKey->sym == SDLK_ESCAPE || pKey->sym == SDLK_PAUSE)
            {
                if (paused) paused = TRUE + TRUE;   //preview!
            }

            return;
        }

        //pause
        if (pKey->sym == SDLK_PAUSE)
        {
            pGfxControl->printMask(65, 48, "paused", 0xffffff, 0);
			pComputer->pSndManager->pause(paused = TRUE);
            pGfxControl->putBuffer();
            return;
        }

        //save sna/trd
        if (pKey->sym == SDLK_F2)
        {
			pComputer->pSndManager->pause(paused = TRUE);
            QString filter = QString("Snapshot (*.sna *.SNA);;"
                                     "Disk A (*.trd *.TRD)");
            QString name = Configure::pOpenFile->getSaveFileName(".", filter, NULL, NULL, "Save snapshot or image file");
            if (! name.isEmpty())
            {
                if (name.findRev(".sna", -1, FALSE) != -1)
                    pComputer->saveSna(name);
                else if (name.findRev(".trd", -1, FALSE) != -1)
                        pComputer->pBetaDisk->saveTRD(name, 0);
            }
			pComputer->pSndManager->pause(paused = FALSE);
            return;
        }
        //fast settings
        if (pKey->sym == SDLK_F4)
        {
			pComputer->pSndManager->pause(paused = TRUE);
			pCUIControl->showWindow(&memSelDlg);
            return;
        }

        //scrshot
        if (pKey->sym == SDLK_F8)
        {
            sprintf(tmpstr, "scrshot%03i", scrshotnum++);
            printf("Saving %s", tmpstr);
            pComputer->pULA->saveShot(tmpstr);
            return;
        }

        //turbo
        if (pKey->sym == SDLK_NUMLOCK)
        {
            pComputer->maxSpeed = pComputer->maxSpeed ? 0 : Configure::VIDSkipFrames;
            return;
        }

        //debugger
        if (pKey->sym == SDLK_DELETE)
        {
            pComputer->pDebugger->show();
            return;
        }

        //open file (snapshot, trdos image, etc)
        if (pKey->sym == SDLK_F3)
        {
			pComputer->pSndManager->pause(paused = TRUE);
			pConfigure->pOpenFile->setFilters(QString("All files (*.*);;"
                                                      "Snapshots (*.sna *.SNA);;"
                                                      "TR-Dos (*.trd *.TRD);;"
                                                      "TR-Dos (*.scl *.SCL)"));
            pConfigure->pOpenFile->setMode(QFileDialog::AnyFile);
            if (pConfigure->pOpenFile->exec() == QDialog::Accepted)
                openFile(pConfigure->pOpenFile->selectedFile());
            pConfigure->pOpenFile->setMode(QFileDialog::ExistingFile);
			pComputer->pSndManager->pause(paused = FALSE);
			return;
        }

        // options
        if (pKey->sym == SDLK_F1)
        {
			pComputer->pSndManager->pause(paused = TRUE);
			pConfigure->pOptions->exec();
			pComputer->pSndManager->pause(paused = FALSE);
			return;
        }

        // nmi
        if (pKey->sym == SDLK_F11)
        {
            if (pKey->mod & KMOD_RSHIFT)
            {
                pComputer->pMemory->status = MEMSTAT_TRDOS;
                pComputer->pMemory->updateState();
            }
            pComputer->pCPU->NMI();
            return;
        }
        //reset (+modifiers)
        if (pKey->sym == SDLK_F12)
        {
            unsigned tmpres = Configure::SYSResetTo;
            if (pKey->mod & KMOD_RSHIFT)
                Configure::SYSResetTo = ERTrDOS;
            else
                if (pKey->mod & KMOD_LSHIFT)
                    Configure::SYSResetTo = ERBasic48;
            pComputer->reset();
            Configure::SYSResetTo = tmpres;
            return ;
        }
    }
}

#include <sys/time.h>
#include <time.h>
void Zxlin::threadEvent()
{
static unsigned skipper = 0;
static unsigned ctr = 10;
static Uint32 prevtime;
int mouseX, mouseY;
Uint8 mouseStat;
Uint8* pKbdStat;
static Uint32 tmr;
static SDL_Event usrevent = {SDL_USEREVENT};

//    SDL_PumpEvents();
    pKbdStat = SDL_GetKeyState(NULL);
    mouseStat = SDL_GetMouseState(&mouseX, &mouseY);
    //alt+f4 = exit
    if (pKbdStat[SDLK_F4] && (pKbdStat[SDLK_RALT] || pKbdStat[SDLK_LALT]))
        exit(0);

    SDL_PushEvent(&usrevent);
    if (paused == 2 && ! pKbdStat[SDLK_ESCAPE] && !pKbdStat[SDLK_PAUSE])
		pComputer->pSndManager->pause(paused = FALSE); //reset
    if (paused)
    {
        usleep(1000);
        return;
    }

    for (skipper = 0; skipper < pComputer->maxSpeed + 1; skipper++)
    {
        if (!pComputer->isTracing())
        {
            if ( !pComputer->maxSpeed)
            {
                pComputer->pSndManager->startFrame();

                if (inputLock)
                {
                    pComputer->pMouse->setState(mouseX, mouseY, mouseStat, pKbdStat);
                    pComputer->pKbd->setState(mouseX, mouseY, mouseStat, pKbdStat);
                }
            }
            if ( ! --ctr )
            {
                pComputer->pULA->doFlash();
                ctr = 10;
            }
            pComputer->pULA->startFrame();
        }
        if ( pComputer->frame(FALSE, skipper == pComputer->maxSpeed))
        {
            pComputer->pDebugger->show();
            break;
        }
    }

    if (! pComputer->isTracing())
    {
        if (ctr == 10)
        {
            struct timeval tv;
            gettimeofday(&tv, NULL);
            Uint32 thistime = tv.tv_sec * 1000000 + tv.tv_usec;
            tmr = thistime - prevtime;
            prevtime = thistime;

            if (pComputer->maxSpeed)
                tmr = (QWORD)100000000 * Configure::VIDSkipFrames / tmr;
            else
                tmr = (QWORD)100000000 / tmr;
        }
        pComputer->visualize(tmr);
        ::ZXLin->pGfxControl->putBuffer();
    }
}
