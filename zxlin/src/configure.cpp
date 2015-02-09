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

#include "types.h"
#include "configure.h"
#include "options.h"
#include "zxlin.h"

#include "libini.h"


//paths
char Configure::VARBasic128ROM[MAX_PATH_LEN] = "../../src/pentagon.rom:0";
char Configure::VARBasic48ROM[MAX_PATH_LEN] = "../../src/pentagon.rom:1";
char Configure::VARTRDosROM[MAX_PATH_LEN] = "../../src/trdos.rom";
char Configure::VARSystemROM[MAX_PATH_LEN] = "";
char Configure::VARAutoLoad[MAX_PATH_LEN] = "";
char Configure::VARImagesDir[MAX_PATH_LEN] = "/mnt/D/Spectrum/Images";

//Sound
char Configure::SNDDevice[MAX_PATH_LEN] = "/dev/dsp";
unsigned Configure::SNDFrequency = 44100;
unsigned Configure::SNDAYYM = 0;
unsigned Configure::SNDAY35 = 0;
unsigned Configure::SNDVolAL = 90;
unsigned Configure::SNDVolAR = 10;
unsigned Configure::SNDVolBL = 50;
unsigned Configure::SNDVolBR = 50;
unsigned Configure::SNDVolCL = 10;
unsigned Configure::SNDVolCR = 90;
unsigned Configure::SNDVolSoundrv = 90;
unsigned Configure::SNDVolCovDD = 90;
unsigned Configure::SNDVolCovFB = 90;
unsigned Configure::SNDVolBeepr = 90;

//ula
unsigned Configure::ULATicksPerFrame = 71680;
unsigned Configure::ULATicksBeforePaper = 17989;
unsigned Configure::ULATicksPerLine = 224;
unsigned Configure::ULAEvenM1 = FALSE;
//video
char Configure::VIDPaletteNames[8][16] = {"", "", "", "", "", "", "", ""};
DWORD Configure::VIDPalettes[8][16];
DWORD Configure::VIDPalette[16] = {0x000000, 0x000080, 0x800000, 0x800080,
                                0x008000, 0x008080, 0x808000, 0x808080,
                                0x000000, 0x0000ff, 0xff0000, 0xff00ff,
                                0x00ff00, 0x00ffff, 0xffff00, 0xffffff};
unsigned Configure::VIDFullScreen = FALSE;
unsigned Configure::VIDHWSurface = TRUE;
unsigned Configure::VIDAsyncBlit = FALSE;
unsigned Configure::VIDDoubleBuf = TRUE;
unsigned Configure::VIDSkipFrames = 32;
unsigned Configure::VIDFullWidth = W_WIDTH;
unsigned Configure::VIDFullHeight = W_HEIGHT;

//memory
unsigned Configure::MEMCacheSize = 8192;
unsigned Configure::MEMMemType = MEM_PENT128;

//system
unsigned Configure::SYSResetTo = ERBasic128;
unsigned Configure::SYSExtCommands = TRUE;
//beta
unsigned Configure::BETAInterleave = 0;
unsigned Configure::BETAWriteProtect[4] = {0, 0, 0, 0};
char Configure::BETAImages[4][MAX_PATH_LEN] = {"", "", "", ""};
unsigned Configure::BETANoDelay = TRUE;
unsigned Configure::BETATraps = TRUE;

//input
Keymap Configure::INKbdMap[256] = {
    {SDLK_1,      ZX_1,  0},
    {SDLK_2,      ZX_2,  0},
    {SDLK_3,      ZX_3,  0},
    {SDLK_4,      ZX_4,  0},
    {SDLK_5,      ZX_5,  0},
    {SDLK_6,      ZX_6,  0},
    {SDLK_7,      ZX_7,  0},
    {SDLK_8,      ZX_8,  0},
    {SDLK_9,      ZX_9,  0},
    {SDLK_0,      ZX_0,  0},
    {SDLK_q,      ZX_Q,  0},
    {SDLK_w,      ZX_W,  0},
    {SDLK_e,      ZX_E,  0},
    {SDLK_r,      ZX_R,  0},
    {SDLK_t,      ZX_T,  0},
    {SDLK_y,      ZX_Y,  0},
    {SDLK_u,      ZX_U,  0},
    {SDLK_i,      ZX_I,  0},
    {SDLK_o,      ZX_O,  0},
    {SDLK_p,      ZX_P,  0},
    {SDLK_a,      ZX_A,  0},
    {SDLK_s,      ZX_S,  0},
    {SDLK_d,      ZX_D,  0},
    {SDLK_f,      ZX_F,  0},
    {SDLK_g,      ZX_G,  0},
    {SDLK_h,      ZX_H,  0},
    {SDLK_j,      ZX_J,  0},
    {SDLK_k,      ZX_K,  0},
    {SDLK_l,      ZX_L,  0},
    {SDLK_RETURN, ZX_EN, 0},
    {SDLK_LSHIFT, ZX_CS, 0},
    {SDLK_RSHIFT, ZX_CS, 0},
    {SDLK_z,      ZX_Z,  0},
    {SDLK_x,      ZX_X,  0},
    {SDLK_c,      ZX_C,  0},
    {SDLK_v,      ZX_V,  0},
    {SDLK_b,      ZX_B,  0},
    {SDLK_n,      ZX_N,  0},
    {SDLK_m,      ZX_M,  0},
    {SDLK_LALT,   ZX_SS, 0},
    {SDLK_RALT,   ZX_SS, 0},
    {SDLK_SPACE,  ZX_SP, 0},

    {SDLK_LCTRL,      ZX_CS, ZX_SS}, //ext
    {SDLK_RCTRL,      ZX_CS, ZX_SS}, //ext
    {SDLK_ESCAPE,     ZX_CS, ZX_1},  //edit
    {SDLK_CAPSLOCK,   ZX_CS, ZX_2},  //caps
    {SDLK_PAGEUP,     ZX_CS, ZX_3},  //pgup
    {SDLK_PAGEDOWN,   ZX_CS, ZX_4},  //pgdwn
    {SDLK_LEFT,       ZX_CS, ZX_5},  //left
    {SDLK_DOWN,       ZX_CS, ZX_6},  //down
    {SDLK_UP,         ZX_CS, ZX_7},  //up
    {SDLK_RIGHT,      ZX_CS, ZX_8},  //right
    {SDLK_BACKSPACE,  ZX_CS, ZX_0},  //delete
    {SDLK_SEMICOLON,  ZX_SS, ZX_O},  // ;
    {SDLK_QUOTEDBL,   ZX_SS, ZX_P},  // "
    {SDLK_MINUS,      ZX_SS, ZX_J},  // -
    {SDLK_PLUS,       ZX_SS, ZX_K},  // +
    {SDLK_EQUALS,     ZX_SS, ZX_L},  // =
    {SDLK_SLASH,      ZX_SS, ZX_V},  // /
    {SDLK_COMMA,      ZX_SS, ZX_N},  // ,
    {SDLK_PERIOD,     ZX_SS, ZX_M},  // .
    {SDLK_KP6,        ZX_KLEFT, 0},  //kjoy left
    {SDLK_KP4,        ZX_KRIGHT, 0}, //kjoy right
    {SDLK_KP2,        ZX_KDOWN, 0},  //kjoy down
    {SDLK_KP8,        ZX_KUP, 0},    //kjoy up
    {SDLK_KP5,        ZX_KFIRE, 0},  //kjoy fire
    {-1, 0, 0}
};

//LEDS
unsigned Configure::LEDAY_X = 2;
unsigned Configure::LEDAY_Y = 2;

unsigned Configure::LEDKBD_X = 32;
unsigned Configure::LEDKBD_Y = 8;

unsigned Configure::LEDMOUS_X = 64;
unsigned Configure::LEDMOUS_Y = 8;

unsigned Configure::LEDBETA_X = 528;
unsigned Configure::LEDBETA_Y = 8;

//Dialogs
OptionsDlg* Configure::pOptions = NULL;
QFileDialog* Configure::pOpenFile = NULL;


Configure::Configure()
{
#ifdef _DEBUG_
    printf("Configure\n");
#endif
    pOptions = new OptionsDlg();

    dir = VARImagesDir;
    pOpenFile = new QFileDialog(dir, "*.*", NULL, "Open file");
}

Configure::~ Configure()
{
    delete pOptions;
    delete pOpenFile;
#ifdef _DEBUG_
    printf("~Configure\n");
#endif
}

/***************************
Keymap files:
; comment
PC_KEY ZX_KEY1 [ZX_KEY2]
---
PC_KEYS:
ESC      F1  F2  F3  F4     F5  F6  F7  F8    F9  F10 F11 F12
TIL    1   2   3   4   5   6   7   8   9   0 MINUS PLUS BACKSL BACK  PRSCR SCLOCK PAUSE  NUMLOCK GRDIV GRMUL GRSUB
TAB     Q   W   E   R   T   Y   U   I   O   P   LB    RB               INS  HOME  PGUP     N7     N8    N9  GRADD
CAPS     A   S   D   F   G   H   J   K   L   COL QUOTE ENTER           DEL   END  PGDN     N4     N5    N6
LSHIFT    Z   X   C   V   B   N   M COMMA POINT SLASH RSHIFT                  UP           N1     N2    N3  GRENTER
LCONTROL LWIN LALT     SPACE                 RALT RWIN RCONTROL         LEFT DOWN RIGHT    N0           NP

ZX_KEYS:
 1  2  3  4  5  6  7  8  9  0
 Q  W  E  R  T  Y  U  I  O  P
 A  S  D  F  G  H  J  K  L ENT
CAP Z  X  C  V  B  N  M SYM SPC

KLEFT, KRIGHT, KUP, KDOWN, KFIRE

*****************************/

int getPCZXKey(const char* keytxt, unsigned zx)
{
#include "keydefs.h"
const KeyDef* pKey = zx ? ZXKeys : PCKeys;

    while (pKey->value != -1)
    {
        if (! strcmp(pKey->name, keytxt)) return pKey->value;
        pKey++;
    }
    return -1;
}

unsigned Configure::loadKeymap(const char* filename)
{
FILE* file = fopen(filename, "rt");

    if (file == NULL) return TRUE;

char string[MAX_PATH_LEN];
Keymap* pKey = INKbdMap;

    memset(INKbdMap, 0, 256 * sizeof(Keymap));
    while (! feof(file))
    {
        fgets(string, MAX_PATH_LEN, file);
        char* par = strrchr(string, ';');
        if (par) *par = 0;
        par = strrchr(string, '\n');
        if (par) *par = 0;
        par = string;
        while (*par && *par == ' ') par++;
        if (! *par) continue;  //empty string

        char* tpar = par;
        while (*tpar && *tpar != ' ') *tpar = toupper(*tpar), tpar++;
        if (! *tpar) continue;  //one param
        *tpar++ = 0;

        int pckey = getPCZXKey(par, FALSE);
        if (pckey == -1) continue;

        par = tpar;
        while (*par && *par == ' ') par++;
        if (! *par) continue;  //one param
        tpar = par;
        while (*tpar && *tpar != ' ') *tpar = toupper(*tpar), tpar++;
        if (! *tpar) tpar[1] = 0;
        *tpar++ = 0;

        int zxkey1 = getPCZXKey(par, TRUE);
        int zxkey2 = 0;
        if (zxkey1 == -1) continue;

        par = tpar;
        while (*par && *par == ' ') par++;
        if (*par)
        {
            tpar = par;
            while (*tpar && *tpar != ' ') *tpar = toupper(*tpar), tpar++;
            *tpar = 0;
            zxkey2 = getPCZXKey(par, TRUE);
            if (zxkey2 == -1) continue;
        }

        if (pckey == -SDLK_LCTRL)
        {
            pKey->pckey = SDLK_LCTRL;
            pKey->zxkey1 = zxkey1;
            pKey->zxkey2 = zxkey2;
            pckey =  SDLK_RCTRL;
            pKey++;
        }
        if (pckey == -SDLK_LSUPER)
        {
            pKey->pckey = SDLK_LSUPER;
            pKey->zxkey1 = zxkey1;
            pKey->zxkey2 = zxkey2;
            pckey =  SDLK_RSUPER;
            pKey++;
        }
        if (pckey == -SDLK_LALT)
        {
            pKey->pckey = SDLK_LALT;
            pKey->zxkey1 = zxkey1;
            pKey->zxkey2 = zxkey2;
            pckey =  SDLK_RALT;
            pKey++;
        }
        if (pckey == -SDLK_LSHIFT)
        {
            pKey->pckey = SDLK_LSHIFT;
            pKey->zxkey1 = zxkey1;
            pKey->zxkey2 = zxkey2;
            pckey =  SDLK_RSHIFT;
            pKey++;
        }
        pKey->pckey = pckey;
        pKey->zxkey1 = zxkey1;
        pKey->zxkey2 = zxkey2;
        pKey++;
        if (pKey >= INKbdMap + 254) break;
    }
    pKey->pckey = -1;

    fclose(file);
    return FALSE;
}

/*********************************
ini files:

[MAIN]
version=vers

[ROMS]
Basic128=
Basic48=
TRDos=
System=

[SOUND]
Device=
Frequency=
AYYM=AY/YM
AY35MHz=
AYVolume=,..,..
SoundriveVolume=
CovoxDDVolume=
CovoxFBVolume=
BeeperVolume=

[VIDEO]
Palettes=...,...
Palette=..,..,
FullScreen=
HWSurface=
AsyncBlit=
DoubleBuffer=
SkipFrames=
FullScreenSize=

[ULA]
TicksPerFrame=
TicksBeforePaper=
TicksPerLine=
EvenM1=

[MEMORY]
Type=
Cache

[SYSTEM]
ResetTo=
ExtCommands

[BETA]
Interleave=
NoDelay=
Traps=
ImagesDir=
WriteProtect=


[LEDS]
AY=
KBD=
MOUSE=
BETA=

[INPUT]
Keyboard=

[PALETTES]
..=..,..,..,..
**********************************/

unsigned Configure::loadIni(const char* filename)
{
ini_fd_t inifile = ini_open(filename, "ri", ";#");
double doubletype;
int inttype;
char stringtype[MAX_PATH_LEN];

    printf("Reading %s\n", filename);
    if (inifile == NULL)
    {
        printf("Cannot open\n");
        return TRUE;
    }
    if (! ini_locateHeading(inifile, "MAIN") && ! ini_locateKey(inifile, "version"))
    {

        if (ini_readDouble(inifile, &doubletype) + 1)
        {
            if (doubletype > MAX_VERSION)
            {
                printf("Unsupported version %f\n", doubletype);
                return TRUE;
            }
        }
    }

    if (! ini_locateHeading(inifile, "ROMS"))
    {
        if (! ini_locateKey(inifile, "Basic128") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            strcpy(VARBasic128ROM, stringtype);
        if (! ini_locateKey(inifile, "Basic48") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            strcpy(VARBasic48ROM, stringtype);
        if (! ini_locateKey(inifile, "TRDos") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            strcpy(VARTRDosROM, stringtype);
        if (! ini_locateKey(inifile, "System") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            strcpy(VARSystemROM, stringtype);
    }

    if (! ini_locateHeading(inifile, "SOUND"))
    {
        if (! ini_locateKey(inifile, "Device") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            strcpy(SNDDevice, stringtype);
        if (! ini_locateKey(inifile, "Frequency") && 1 + ini_readInt(inifile, &inttype))
            SNDFrequency = inttype;
        if (! ini_locateKey(inifile, "AYYM") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            SNDAYYM = !strcmp(stringtype, "YM");
        if (! ini_locateKey(inifile, "AY35MHz") && 1 + ini_readInt(inifile, &inttype))
            SNDAY35 = inttype;
        if (! ini_locateKey(inifile, "AYVolume") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            sscanf(stringtype, "%i,%i,%i,%i,%i,%i", &SNDVolAL, &SNDVolAR, &SNDVolBL, &SNDVolBR, &SNDVolCL, &SNDVolCR);
        if (! ini_locateKey(inifile, "SoundriveVolume") && 1 + ini_readInt(inifile, &inttype))
            SNDVolSoundrv = inttype;
        if (! ini_locateKey(inifile, "CovoxDDVolume") && 1 + ini_readInt(inifile, &inttype))
            SNDVolCovDD = inttype;
        if (! ini_locateKey(inifile, "CovoxFBVolume") && 1 + ini_readInt(inifile, &inttype))
            SNDVolCovFB = inttype;
        if (! ini_locateKey(inifile, "BeeperVolume") && 1 + ini_readInt(inifile, &inttype))
            SNDVolBeepr = inttype;
    }

    if (! ini_locateHeading(inifile, "VIDEO"))
    {
        if (! ini_locateKey(inifile, "Palettes") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
        {
            inttype = 0;
            char* pBeg = stringtype;
            while (pBeg && *pBeg)
            {
                char* pEnd = strrchr(pBeg, ',');
                if (pEnd) *pEnd = 0;
                strcpy(VIDPaletteNames[inttype++], pBeg);
                if (pEnd)
                    pBeg = pEnd + 1;
                else
                    break;
            }
            *VIDPaletteNames[inttype] = 0;
        }
        if (! ini_locateKey(inifile, "Palette") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            sscanf(stringtype, "%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx",
                    VIDPalette, VIDPalette + 1, VIDPalette + 2, VIDPalette + 3,
                    VIDPalette + 4, VIDPalette + 5, VIDPalette + 6, VIDPalette + 7,
                    VIDPalette + 8, VIDPalette + 9, VIDPalette + 10, VIDPalette + 11,
                    VIDPalette + 12, VIDPalette + 13, VIDPalette + 14, VIDPalette + 15);
        if (! ini_locateKey(inifile, "FullScreen") && 1 + ini_readInt(inifile, &inttype))
            VIDFullScreen = inttype;
        if (! ini_locateKey(inifile, "HWSurface") && 1 + ini_readInt(inifile, &inttype))
            VIDHWSurface = inttype;
        if (! ini_locateKey(inifile, "AsyncBlit") && 1 + ini_readInt(inifile, &inttype))
            VIDAsyncBlit = inttype;
        if (! ini_locateKey(inifile, "DoubleBuffer") && 1 + ini_readInt(inifile, &inttype))
            VIDDoubleBuf = inttype;
        if (! ini_locateKey(inifile, "SkipFrames") && 1 + ini_readInt(inifile, &inttype))
            VIDSkipFrames = inttype;
        if (! ini_locateKey(inifile, "FullScreenSize") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            sscanf(stringtype, "%i,%i", &VIDFullWidth, &VIDFullHeight);
    }

    if (! ini_locateHeading(inifile, "MEMORY"))
    {
        if (! ini_locateKey(inifile, "Type") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
        {
            if (! strcmp(stringtype, "Scorp1024"))
                MEMMemType = MEM_SCORP1024;
            else if (! strcmp(stringtype, "Profi1024"))
                     MEMMemType = MEM_PROFI1024;
                 else if (! strcmp(stringtype, "ATM512"))
                          MEMMemType = MEM_ATM512;
                      else if (! strcmp(stringtype, "Scorp256"))
                               MEMMemType = MEM_SCORP256;
                           else if (! strcmp(stringtype, "Pent512"))
                                    MEMMemType = MEM_PENT512;
                                else
                                    MEMMemType = MEM_PENT128;
        }
        if (! ini_locateKey(inifile, "Cache") && 1 + ini_readInt(inifile, &inttype))
            MEMCacheSize = inttype;
	}

	if (! ini_locateHeading(inifile, "SYSTEM"))
	{
        if (! ini_locateKey(inifile, "ResetTo") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
        {
            if (! strcmp(stringtype, "Ram"))
                SYSResetTo = ERRam;
            else if (! strcmp(stringtype, "Cache"))
                     SYSResetTo = ERCache;
                 else if (! strcmp(stringtype, "System"))
                          SYSResetTo = ERSystem;
                      else if (! strcmp(stringtype, "TrDOS"))
                               SYSResetTo = ERTrDOS;
                           else if (! strcmp(stringtype, "Basic48"))
                                    SYSResetTo = ERBasic48;
                                else
                                    SYSResetTo = ERBasic128;
        }

		if (! ini_locateKey(inifile, "ExtCommands") && 1 + ini_readInt(inifile, &inttype))
			SYSExtCommands = inttype;

    }
    if (! ini_locateHeading(inifile, "ULA"))
    {
        if (! ini_locateKey(inifile, "TicksPerFrame") && 1 + ini_readInt(inifile, &inttype))
            ULATicksPerFrame = inttype;
        if (! ini_locateKey(inifile, "TicksBeforePaper") && 1 + ini_readInt(inifile, &inttype))
            ULATicksBeforePaper = inttype;
        if (! ini_locateKey(inifile, "TicksPerLine") && 1 + ini_readInt(inifile, &inttype))
            ULATicksPerLine = inttype;
        if (! ini_locateKey(inifile, "EvenM1") && 1 + ini_readInt(inifile, &inttype))
            ULAEvenM1 = inttype;
    }

    if (! ini_locateHeading(inifile, "BETA"))
    {
        if (! ini_locateKey(inifile, "Interleave") && 1 + ini_readInt(inifile, &inttype))
            BETAInterleave = inttype;
        if (! ini_locateKey(inifile, "NoDelay") && 1 + ini_readInt(inifile, &inttype))
            BETANoDelay = inttype;
        if (! ini_locateKey(inifile, "Traps") && 1 + ini_readInt(inifile, &inttype))
            BETATraps = inttype;
        if (! ini_locateKey(inifile, "WriteProtect") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            sscanf(stringtype, "%i,%i,%i,%i", BETAWriteProtect, BETAWriteProtect + 1,
                                            BETAWriteProtect + 2, BETAWriteProtect + 3);
        if (! ini_locateKey(inifile, "ImagesDir") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            strcpy(VARImagesDir, stringtype);
    }
    if (! ini_locateHeading(inifile, "LEDS"))
    {
        if (! ini_locateKey(inifile, "AY") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            sscanf(stringtype, "%i,%i", &LEDAY_X, &LEDAY_Y);
        if (! ini_locateKey(inifile, "KBD") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            sscanf(stringtype, "%i,%i", &LEDKBD_X, &LEDKBD_Y);
        if (! ini_locateKey(inifile, "MOUSE") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            sscanf(stringtype, "%i,%i", &LEDMOUS_X, &LEDAY_Y);
        if (! ini_locateKey(inifile, "BETA") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            sscanf(stringtype, "%i,%i", &LEDBETA_X, &LEDBETA_Y);
    }
    if (! ini_locateHeading(inifile, "INPUT"))
    {
        if (! ini_locateKey(inifile, "Keyboard") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN) && *stringtype)
            Configure::loadKeymap(stringtype);
    }
    //read palettes
    if (! ini_locateHeading(inifile, "PALETTES"))
    {
        inttype = 0;
        while (VIDPaletteNames[inttype])
        {
            if (! ini_locateKey(inifile, VIDPaletteNames[inttype]) && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
            sscanf(stringtype, "%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx",
                    VIDPalettes[inttype], VIDPalettes[inttype] + 1, VIDPalettes[inttype] + 2, VIDPalettes[inttype] + 3,
                    VIDPalettes[inttype] + 4, VIDPalettes[inttype] + 5, VIDPalettes[inttype] + 6, VIDPalettes[inttype] + 7,
                    VIDPalettes[inttype] + 8, VIDPalettes[inttype] + 9, VIDPalettes[inttype] + 10, VIDPalettes[inttype] + 11,
                    VIDPalettes[inttype] + 12, VIDPalettes[inttype] + 13, VIDPalettes[inttype] + 14, VIDPalettes[inttype] + 15);
            inttype++;
        }
    }
    ini_close(inifile);
    return FALSE;
}

unsigned Configure::saveIni()
{
ini_fd_t inifile = ini_open("zxlin.ini", "ai", ";#");
//double doubletype;
//int inttype;
char stringtype[MAX_PATH_LEN];

    printf("Writing zxlin.ini\n");
    if (inifile == NULL)
    {
        printf("Cannot open\n");
        return TRUE;
    }

    if (! ini_locateHeading(inifile, "SOUND"))
    {
        if (! ini_locateKey(inifile, "Device"))
            ini_writeString(inifile, SNDDevice);
        if (! ini_locateKey(inifile, "Frequency"))
            ini_writeInt(inifile, SNDFrequency);
        if (! ini_locateKey(inifile, "AYYM"))
            ini_writeString(inifile, SNDAYYM ? "YM" : "AY");
        if (! ini_locateKey(inifile, "AY35MHz"))
            ini_writeInt(inifile, SNDAY35);
        if (! ini_locateKey(inifile, "AYVolume"))
        {
            sprintf(stringtype, "%i,%i,%i,%i,%i,%i", SNDVolAL, SNDVolAR, SNDVolBL, SNDVolBR, SNDVolCL, SNDVolCR);
            ini_writeString(inifile, stringtype);
        }
        if (! ini_locateKey(inifile, "SoundriveVolume"))
            ini_writeInt(inifile, SNDVolSoundrv);
        if (! ini_locateKey(inifile, "CovoxDDVolume"))
            ini_writeInt(inifile, SNDVolCovDD);
        if (! ini_locateKey(inifile, "CovoxFBVolume"))
            ini_writeInt(inifile, SNDVolCovFB);
        if (! ini_locateKey(inifile, "BeeperVolume"))
            ini_writeInt(inifile, SNDVolBeepr);
    }

    if (! ini_locateHeading(inifile, "VIDEO"))
    {
        if (! ini_locateKey(inifile, "Palette"))
        {
            sprintf(stringtype, "%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx",
                    VIDPalette[0], VIDPalette[1], VIDPalette[2], VIDPalette[3],
                    VIDPalette[4], VIDPalette[5], VIDPalette[6], VIDPalette[7],
                    VIDPalette[8], VIDPalette[9], VIDPalette[10], VIDPalette[11],
                    VIDPalette[12], VIDPalette[13], VIDPalette[14], VIDPalette[15]);
            ini_writeString(inifile, stringtype);
        }
        if (! ini_locateKey(inifile, "FullScreen"))
            ini_writeInt(inifile, VIDFullScreen);
        if (! ini_locateKey(inifile, "HWSurface"))
            ini_writeInt(inifile, VIDHWSurface);
        if (! ini_locateKey(inifile, "AsyncBlit"))
            ini_writeInt(inifile, VIDAsyncBlit);
        if (! ini_locateKey(inifile, "DoubleBuffer"))
            ini_writeInt(inifile, VIDDoubleBuf);
        if (! ini_locateKey(inifile, "SkipFrames"))
            ini_writeInt(inifile, VIDSkipFrames);
    }

    if (! ini_locateHeading(inifile, "MEMORY"))
    {
        if (! ini_locateKey(inifile, "Type") && 1 + ini_readString(inifile, stringtype, MAX_PATH_LEN))
        {
            if (MEMMemType == MEM_SCORP1024)
                ini_writeString(inifile, "Scorp1024");
            else if (MEMMemType == MEM_PROFI1024)
                    ini_writeString(inifile, "Profi1024");
                else if (MEMMemType == MEM_ATM512)
                        ini_writeString(inifile, "ATM512");
                    else if (MEMMemType == MEM_SCORP256)
                            ini_writeString(inifile, "Scorp256");
                        else if (MEMMemType == MEM_PENT512)
                            ini_writeString(inifile, "Pent512");
                        else
                            ini_writeString(inifile, "Pent128");
        }
        if (! ini_locateKey(inifile, "Cache"))
            ini_writeInt(inifile, MEMCacheSize);
	}

	if (! ini_locateHeading(inifile, "SYSTEM"))
	{
        if (! ini_locateKey(inifile, "ResetTo"))
        {
            if (SYSResetTo == ERRam)
                ini_writeString(inifile, "Ram");
            else if (SYSResetTo == ERCache)
                    ini_writeString(inifile, "Cache");
                else if (SYSResetTo == ERSystem)
                        ini_writeString(inifile, "System");
                    else if (SYSResetTo == ERTrDOS)
                            ini_writeString(inifile, "TrDOS");
                        else if (SYSResetTo == ERBasic48)
                                ini_writeString(inifile, "Basic48");
                            else
                                ini_writeString(inifile, "Basic128");
        }

		if (! ini_locateKey(inifile, "ExtCommands"))
			ini_writeInt(inifile, SYSExtCommands);
    }

    if (! ini_locateHeading(inifile, "ULA"))
    {
        if (! ini_locateKey(inifile, "TicksPerFrame"))
            ini_writeInt(inifile, ULATicksPerFrame);
        if (! ini_locateKey(inifile, "TicksBeforePaper"))
            ini_writeInt(inifile, ULATicksBeforePaper);
        if (! ini_locateKey(inifile, "TicksPerLine"))
            ini_writeInt(inifile, ULATicksPerLine);
        if (! ini_locateKey(inifile, "EvenM1"))
            ini_writeInt(inifile, ULAEvenM1);
    }

    if (! ini_locateHeading(inifile, "BETA"))
    {
        if (! ini_locateKey(inifile, "Interleave"))
            ini_writeInt(inifile, BETAInterleave);
        if (! ini_locateKey(inifile, "NoDelay"))
            ini_writeInt(inifile, BETANoDelay);
        if (! ini_locateKey(inifile, "Traps"))
            ini_writeInt(inifile, BETATraps);
    }

    ini_close(inifile);
    return FALSE;
}
