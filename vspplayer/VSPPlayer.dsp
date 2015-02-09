# Microsoft Developer Studio Project File - Name="VSPPlayer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VSPPlayer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VSPPlayer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VSPPlayer.mak" CFG="VSPPlayer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VSPPlayer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VSPPlayer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VSPPlayer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gr /Zp8 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /opt:nowin98
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "VSPPlayer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /opt:nowin98
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "VSPPlayer - Win32 Release"
# Name "VSPPlayer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\GFXControl.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetupDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VSPPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\VSPPlayer.rc
# End Source File
# Begin Source File

SOURCE=.\VSPPlayerDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\encode.h
# End Source File
# Begin Source File

SOURCE=.\GFXControl.h
# End Source File
# Begin Source File

SOURCE=.\InfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SetupDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VSPPlayer.h
# End Source File
# Begin Source File

SOURCE=.\VSPPlayerDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\about1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\about2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\close1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\close2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\digits.bmp
# End Source File
# Begin Source File

SOURCE=.\res\info1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\info2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\maximize1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\maximize2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\minimize1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\minimize2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ontop1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ontop2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\open1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\open2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\setup1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\setup2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VSPPlayer.ico
# End Source File
# Begin Source File

SOURCE=.\res\VSPPlayer.rc2
# End Source File
# End Group
# Begin Group "Player"

# PROP Default_Filter ""
# Begin Group "Filter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ScaleFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\ScaleFilter.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\FileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDlg.h
# End Source File
# Begin Source File

SOURCE=.\VSPPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\VSPPlay.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
