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

#include "UI.h"
#include "configure.h"

#define TXTCOLOR 0xffffff
#define DISCOLOR 0x808080
#define BKGCOLOR 0x0000ff

extern CUIWidget memFrame;
extern CUIWidget memSelPent128;
extern CUIWidget memSelScorp256;
extern CUIWidget memSelPent512;
extern CUIWidget memSelATM512;
extern CUIWidget memSelProfi1024;
extern CUIWidget memSelScorp1024;

extern CUIWidget sysFrame;
extern CUIWidget sysResetBas48;
extern CUIWidget sysResetBas128;
extern CUIWidget sysResetTRDos;
extern CUIWidget sysResetCache;
extern CUIWidget sysResetRAM;
extern CUIWidget sysExtCommands;

#define LASTWIDGET sysExtCommands

//memory select
CUIWindow memSelDlg = {"Fast settings", &memFrame, 15, 10, 50, 12,  TXTCOLOR, DISCOLOR, BKGCOLOR};

CUIWidget memFrame = {"Memory", WIDGET_FRAME, 0, NULL, 1, 1, 24, 10, &LASTWIDGET, &memSelPent128, 0};
CUIWidget memSelPent128 = {"Pentagon &128k", WIDGET_RADIO, 0, &Configure::MEMMemType, 2, 2, 20, 1, &memFrame, &memSelScorp256, MEM_PENT128};
CUIWidget memSelScorp256 = {"Scorpion 25&6k", WIDGET_RADIO, 0, &Configure::MEMMemType, 2, 3, 20, 1, &memSelPent128, &memSelPent512, MEM_SCORP256};
CUIWidget memSelPent512 = {"Pentagon 51&2k", WIDGET_RADIO, 0, &Configure::MEMMemType, 2, 4, 20, 1, &memSelScorp256, &memSelATM512, MEM_PENT512};
CUIWidget memSelATM512 = {"&ATM Turbo 512k", WIDGET_RADIO, 0, &Configure::MEMMemType, 2, 5, 20, 1, &memSelPent512, &memSelProfi1024, MEM_ATM512};
CUIWidget memSelProfi1024 = {"&Profi 1024k", WIDGET_RADIO, 0, &Configure::MEMMemType, 2, 6, 20, 1, &memSelATM512, &memSelScorp1024, MEM_PROFI1024};
CUIWidget memSelScorp1024 = {"Scorpion 102&4k", WIDGET_RADIO, 0, &Configure::MEMMemType, 2, 7, 20, 1, &memSelProfi1024, &sysFrame, MEM_SCORP1024};

CUIWidget sysFrame = {"System", WIDGET_FRAME, 0, NULL, 25, 1, 24, 10, &memSelScorp1024, &sysResetBas48, 0};
CUIWidget sysResetBas48 = {"Reset to Basic4&8", WIDGET_RADIO, 0, &Configure::SYSResetTo, 26, 2, 20, 1, &sysFrame, &sysResetBas128, ERBasic48};
CUIWidget sysResetBas128 = {"Reset to &Basic128", WIDGET_RADIO, 0, &Configure::SYSResetTo, 26, 3, 20, 1, &sysResetBas48, &sysResetTRDos, ERBasic128};
CUIWidget sysResetTRDos = {"Reset to &TrDOS", WIDGET_RADIO, 0, &Configure::SYSResetTo, 26, 4, 20, 1, &sysResetBas128, &sysResetCache, ERTrDOS};
CUIWidget sysResetCache = {"Reset to &Cache", WIDGET_RADIO, 0, &Configure::SYSResetTo, 26, 5, 20, 1, &sysResetTRDos, &sysResetRAM, ERCache};
CUIWidget sysResetRAM = {"Reset to &RAM", WIDGET_RADIO, 0, &Configure::SYSResetTo, 26, 6, 20, 1, &sysResetCache, &sysExtCommands, ERRam};
CUIWidget sysExtCommands = {"&Ext commands set", WIDGET_CHECK, 0, &Configure::SYSExtCommands, 26, 8, 20, 1, &sysResetRAM, &memFrame, 0};

/*
extern CUIWidget betaDrives;
extern CUIWidget betaWPA;
extern CUIWidget betaFileA;
extern CUIWidget betaOpenA;
extern CUIWidget betaCloseA;
extern CUIWidget betaWPB;
extern CUIWidget betaFileB;
extern CUIWidget betaOpenB;
extern CUIWidget betaCloseB;
extern CUIWidget betaWPC;
extern CUIWidget betaFileC;
extern CUIWidget betaOpenC;
extern CUIWidget betaCloseC;
extern CUIWidget betaWPD;
extern CUIWidget betaFileD;
extern CUIWidget betaOpenD;
extern CUIWidget betaCloseD;
extern CUIWidget betaSelInterleave;
extern CUIWidget betaSelIl0;
extern CUIWidget betaSelIl1;
extern CUIWidget betaSelIl2;
extern CUIWidget betaSelOther;
extern CUIWidget betaSelNoDelay;

#define LASTBETA betaSelNoDelay

CUIWindow betaSelDlg = {"BetaDisk interface", &betaDrives, 10, 5, 60, 18, TXTCOLOR, DISCOLOR, BKGCOLOR};

CUIWidget betaDrives = {"Drives", WIDGET_FRAME, WSTATE_DISABLED, NULL, 2, 1, 56, 10, &LASTBETA, &betaWPA};
CUIWidget betaWPA = {"write protect", WIDGET_CHECK, 0, Configure::WriteProtect + 0, 18, 2, 20, 1, &betaDrives, &betaFileA};
CUIWidget betaFileA = {"Drive &A", WIDGET_EDITBOX, 0, Configure::DiskImages + 0, 4, 2, 36, 1, &betaWPA, &betaOpenA, MAX_PATH_LEN};
CUIWidget betaOpenA = {"open", WIDGET_BUTTON + 0, 0, NULL, 41, 3, 6, 1, &betaFileA, &betaCloseA};
CUIWidget betaCloseA = {"close", WIDGET_BUTTON + 0, 0, NULL, 48, 3, 7, 1, &betaOpenA, &betaWPB};

CUIWidget betaWPB = {"write protect", WIDGET_CHECK, 0, Configure::WriteProtect + 1, 18, 4, 20, 1, &betaCloseA, &betaFileB};
CUIWidget betaFileB = {"Drive &B", WIDGET_EDITBOX, 0, Configure::DiskImages + 1, 4, 4, 36, 1, &betaWPB, &betaOpenB, MAX_PATH_LEN};
CUIWidget betaOpenB = {"open", WIDGET_BUTTON + 1, 0, NULL, 41, 5, 6, 1, &betaFileB, &betaCloseB};
CUIWidget betaCloseB = {"close", WIDGET_BUTTON + 1, 0, NULL, 48, 5, 7, 1, &betaOpenB, &betaWPC};

CUIWidget betaWPC = {"write protect", WIDGET_CHECK, 0, Configure::WriteProtect + 2, 18, 6, 20, 1, &betaFileB, &betaFileC};
CUIWidget betaFileC = {"Drive &C", WIDGET_EDITBOX, 0, Configure::DiskImages + 2, 4, 6, 36, 1, &betaWPC, &betaOpenC, MAX_PATH_LEN};
CUIWidget betaOpenC = {"open", WIDGET_BUTTON + 2, 0, NULL, 41, 7, 6, 1, &betaFileC, &betaCloseC};
CUIWidget betaCloseC = {"close", WIDGET_BUTTON + 2, 0, NULL, 48, 7, 7, 1, &betaOpenC, &betaWPD};

CUIWidget betaWPD = {"write protect", WIDGET_CHECK, 0, Configure::WriteProtect + 3, 18, 8, 20, 1, &betaFileC, &betaFileD};
CUIWidget betaFileD = {"Drive &D", WIDGET_EDITBOX, 0, Configure::DiskImages + 3, 4, 8, 36, 1, &betaWPD, &betaOpenD, MAX_PATH_LEN};
CUIWidget betaOpenD = {"open", WIDGET_BUTTON + 2, 0, NULL, 41, 9, 6, 1, &betaFileD, &betaCloseD};
CUIWidget betaCloseD = {"close", WIDGET_BUTTON + 2, 0, NULL, 48, 9, 7, 1, &betaOpenD, &betaSelInterleave};

CUIWidget betaSelInterleave = {"Disk interleave", WIDGET_FRAME, WSTATE_DISABLED, NULL, 2, 11, 18, 5, &betaFileD, &betaSelIl0};
CUIWidget betaSelIl0 = {"Interleave&0", WIDGET_RADIO, 0, &Configure::TrDOSInterleave, 3, 12, 16, 1, &betaSelInterleave, &betaSelIl1, 0};
CUIWidget betaSelIl1 = {"Interleave&1", WIDGET_RADIO, 0, &Configure::TrDOSInterleave, 3, 13, 16, 1, &betaSelIl0, &betaSelIl2, 1};
CUIWidget betaSelIl2 = {"Interleave&2", WIDGET_RADIO, 0, &Configure::TrDOSInterleave, 3, 14, 16, 1, &betaSelIl1, &betaSelOther, 2};
CUIWidget betaSelOther = {"Other", WIDGET_FRAME, WSTATE_DISABLED, NULL, 21, 11, 18, 5, &betaSelIl2, &betaSelNoDelay};
CUIWidget betaSelNoDelay = {"&No delay", WIDGET_CHECK, 0, &Configure::BETANoDelay, 22, 12, 16, 1, &betaSelOther, &betaDrives};
*/
