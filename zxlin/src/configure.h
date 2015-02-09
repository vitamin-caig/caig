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

#ifndef CONFIGURE_H_INCLUDED
#define CONFIGURE_H_INCLUDED

#include "types.h"
#include <SDL/SDL.h>
#include "options.h"
#include <qfiledialog.h>

/* keyboard settings */
#define ZX_CS 0x01
#define ZX_Z  0x02
#define ZX_X  0x04
#define ZX_C  0x08
#define ZX_V  0x10
#define ZX_A  0x21
#define ZX_S  0x22
#define ZX_D  0x24
#define ZX_F  0x28
#define ZX_G  0x30
#define ZX_Q  0x41
#define ZX_W  0x42
#define ZX_E  0x44
#define ZX_R  0x48
#define ZX_T  0x50
#define ZX_1  0x61
#define ZX_2  0x62
#define ZX_3  0x64
#define ZX_4  0x68
#define ZX_5  0x70
#define ZX_0  0x81
#define ZX_9  0x82
#define ZX_8  0x84
#define ZX_7  0x88
#define ZX_6  0x90
#define ZX_P  0xa1
#define ZX_O  0xa2
#define ZX_I  0xa4
#define ZX_U  0xa8
#define ZX_Y  0xb0
#define ZX_EN 0xc1
#define ZX_L  0xc2
#define ZX_K  0xc4
#define ZX_J  0xc8
#define ZX_H  0xd0
#define ZX_SP 0xe1
#define ZX_SS 0xe2
#define ZX_M  0xe4
#define ZX_N  0xe8
#define ZX_B  0xf0
#define ZX_KRIGHT 0x100
#define ZX_KLEFT 0x101
#define ZX_KDOWN 0x102
#define ZX_KUP 0x103
#define ZX_KFIRE 0x104

struct Keymap
{
    int pckey;
    int zxkey1;
    int zxkey2;
};

/* memory settings */
enum ERoms
{
    ERBasic128,
    ERBasic48,
    ERTrDOS,
    ERSystem,
    ERCache,
    ERRam
};

enum EDlgs
{
    EDOptions,
    EDOpenfile,

    EDLastDlg
};

/*
<? xml ?>
<zxlin version="..">
	<path>
		<basic128>path</basic128>
		<basic48>path</basic48>
		<trdos>path</trdos>
		<system>path</system>
		<images>path</images>
		<autostart>path</autostart>
	</path>
	<sound>
		<system>
			<type>auto,OSS,ALSA,none</type>
			<frequency>...</frequency>
			<output name="OSS">
				<device>/dev/dsp</device>
			</output>
			<output name="ALSA">
				<device>default</default>
				<buffertime>0</buffertime>
				<periodtime>0</periodtime>
			</output>
		</system>
		<device>
			<ay type="ay/ym" frq35="yes/no">0,0,0,0,0,0</ay>
			<soundrive>0</soundrive>
			<covoxDD>0</covoxDD>
			<covoxFB>0</covoxFB>
			<beeper>0</beeper>
		</device>
	</sound>
	<video>
		<fullscreen width="..." height="..." [hardware="1"]>0</fullscreen>
		<SDL>
			<hwsurface>1</hwsurface>
			<asyncblit>1</asyncblit>
			<doublebuf>1</doublebuf>
		</SDL>
		<skipframes>0</skipframes>
	</video>
	<ula>
		<ticksperframe>72800</ticksperframe>
		<ticksbeforepaper>18000</ticksbeforepaper>
		<ticksperline>224</ticksperline>
		<evenm1>1</evenm1>
	</ula>
	<memory>
		<type>Pent128</type>
		<cachesize>0</cachesize>
	</memory>
	<betadisk>
		<interleave>0</interleave>
		<nodelay>1</nodelay>
		<traps>1</traps>
		<diskA protected="0">...</diskA>
		<diskB protected="0">...</diskB>
		<diskC protected="0">...</diskC>
		<diskD protected="0">...</diskD>
	</betadisk>
</zxlin>
*/

/* alternate
<? xml ?>
<zxlin version="1.0">
<computer>
	<devices>
		<device name="ay" enabled="1">
			<type>ay</type>
			<frq35>1</frq35>
			<volume>0,0,0,0,0,0</volume>
		</device>
		<device name="covox" enabled="1">

		</device>
	</devices>
</computer>
</zxlin>
*/
class Configure
{
public:
    Configure();
    ~Configure();

    static unsigned loadIni(const char* filename);
    static unsigned saveIni();
/* Settings */
//paths
    static char VARBasic128ROM[MAX_PATH_LEN];
    static char VARBasic48ROM[MAX_PATH_LEN];
    static char VARTRDosROM[MAX_PATH_LEN];
    static char VARSystemROM[MAX_PATH_LEN];
    static char VARAutoLoad[MAX_PATH_LEN];
    static char VARImagesDir[MAX_PATH_LEN];

//Sound
    static char SNDDevice[MAX_PATH_LEN];
    static unsigned SNDFrequency;
    static unsigned SNDAYYM;
    static unsigned SNDAY35;
    static unsigned SNDVolAL;
    static unsigned SNDVolAR;
    static unsigned SNDVolBL;
    static unsigned SNDVolBR;
    static unsigned SNDVolCL;
    static unsigned SNDVolCR;
    static unsigned SNDVolSoundrv;
    static unsigned SNDVolCovDD;
    static unsigned SNDVolCovFB;
    static unsigned SNDVolBeepr;
//Video
    static char VIDPaletteNames[8][16];
    static DWORD VIDPalettes[8][16];
    static DWORD VIDPalette[16];
    static unsigned VIDFullScreen;
    static unsigned VIDHWSurface;
    static unsigned VIDAsyncBlit;
    static unsigned VIDDoubleBuf;
    static unsigned VIDSkipFrames;
    static unsigned VIDFullWidth;
    static unsigned VIDFullHeight;
//ULA
    static unsigned ULATicksPerFrame;
    static unsigned ULATicksBeforePaper;
    static unsigned ULATicksPerLine;
    static unsigned ULAEvenM1;
//Memory
    static unsigned MEMCacheSize;
    static unsigned MEMMemType;

//System
    static unsigned SYSResetTo;
	static unsigned SYSExtCommands;

//Beta
    static unsigned BETAInterleave;
    static unsigned BETAWriteProtect[4];
    static char BETAImages[4][MAX_PATH_LEN];
    static unsigned BETANoDelay;
    static unsigned BETATraps;
//Input
    static Keymap INKbdMap[256];
//LEDS
    static unsigned LEDAY_X;
    static unsigned LEDAY_Y;

    static unsigned LEDKBD_X;
    static unsigned LEDKBD_Y;

    static unsigned LEDMOUS_X;
    static unsigned LEDMOUS_Y;

    static unsigned LEDBETA_X;
    static unsigned LEDBETA_Y;

//dialogs
public:
    static OptionsDlg* pOptions;
    static QFileDialog* pOpenFile;

//privates
private:
    static unsigned loadKeymap(const char* filename);
private:
    QString dir;
};

#endif
