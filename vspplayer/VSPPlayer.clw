; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVSPPlayerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VSPPlayer.h"

ClassCount=6
Class1=CVSPPlayerApp
Class2=CVSPPlayerDlg
Class3=CAboutDlg

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_VSPPLAYER_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDD_INFODIALOG
Class4=CInfoDlg
Resource6=IDD_SETUPDIALOG
Class5=CFileDlg
Resource7=IDD_FILEDIALOG
Class6=CSetupDialog
Resource8=IDD_VSPPLAYER_DIALOG (English (U.S.))

[CLS:CVSPPlayerApp]
Type=0
HeaderFile=VSPPlayer.h
ImplementationFile=VSPPlayer.cpp
Filter=N

[CLS:CVSPPlayerDlg]
Type=0
HeaderFile=VSPPlayerDlg.h
ImplementationFile=VSPPlayerDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CVSPPlayerDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=VSPPlayerDlg.h
ImplementationFile=VSPPlayerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_VSPPLAYER_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CVSPPlayerDlg

[DLG:IDD_VSPPLAYER_DIALOG (English (U.S.))]
Type=1
Class=CVSPPlayerDlg
ControlCount=13
Control1=IDC_SLIDER1,msctls_trackbar32,1342242840
Control2=IDC_OPENFILE,static,1342177550
Control3=IDC_PLPAUS,static,1342177550
Control4=IDC_STOP,static,1342177550
Control5=IDC_INFO,static,1342177550
Control6=IDC_SETUP,static,1342177550
Control7=IDC_ONTOP,static,1342177550
Control8=IDC_CLOSING,static,1342177550
Control9=IDC_MINIMIZING,static,1342177550
Control10=IDC_TIME,static,1342181383
Control11=IDC_TITLE,static,1342177294
Control12=IDC_ABOUT,static,1342177550
Control13=IDC_MAXIMIZING,static,1342177550

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_INFODIALOG]
Type=1
Class=CInfoDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_LIST1,listbox,1344356608
Control3=IDC_LIST2,listbox,1344356609

[CLS:CInfoDlg]
Type=0
HeaderFile=InfoDlg.h
ImplementationFile=InfoDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CInfoDlg

[DLG:IDD_FILEDIALOG]
Type=1
Class=CFileDlg
ControlCount=1
Control1=IDC_LIST1,listbox,1352728833

[CLS:CFileDlg]
Type=0
HeaderFile=FileDlg.h
ImplementationFile=FileDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST1

[DLG:IDD_SETUPDIALOG]
Type=1
Class=CSetupDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_COMBO1,combobox,1344339970

[CLS:CSetupDialog]
Type=0
HeaderFile=SetupDialog.h
ImplementationFile=SetupDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CSetupDialog
VirtualFilter=dWC

