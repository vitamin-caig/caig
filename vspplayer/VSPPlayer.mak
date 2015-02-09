# Microsoft Developer Studio Generated NMAKE File, Based on VSPPlayer.dsp
!IF "$(CFG)" == ""
CFG=VSPPlayer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VSPPlayer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VSPPlayer - Win32 Release" && "$(CFG)" != "VSPPlayer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "VSPPlayer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\VSPPlayer.exe"


CLEAN :
	-@erase "$(INTDIR)\FileDlg.obj"
	-@erase "$(INTDIR)\GFXControl.obj"
	-@erase "$(INTDIR)\InfoDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VSPPlay.obj"
	-@erase "$(INTDIR)\VSPPlayer.obj"
	-@erase "$(INTDIR)\VSPPlayer.pch"
	-@erase "$(INTDIR)\VSPPlayer.res"
	-@erase "$(INTDIR)\VSPPlayerDlg.obj"
	-@erase "$(OUTDIR)\VSPPlayer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VSPPlayer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\VSPPlayer.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VSPPlayer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\VSPPlayer.pdb" /machine:I386 /out:"$(OUTDIR)\VSPPlayer.exe" /opt:nowin98 
LINK32_OBJS= \
	"$(INTDIR)\GFXControl.obj" \
	"$(INTDIR)\InfoDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VSPPlayer.obj" \
	"$(INTDIR)\VSPPlayerDlg.obj" \
	"$(INTDIR)\FileDlg.obj" \
	"$(INTDIR)\VSPPlay.obj" \
	"$(INTDIR)\VSPPlayer.res"

"$(OUTDIR)\VSPPlayer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VSPPlayer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VSPPlayer.exe"


CLEAN :
	-@erase "$(INTDIR)\FileDlg.obj"
	-@erase "$(INTDIR)\GFXControl.obj"
	-@erase "$(INTDIR)\InfoDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VSPPlay.obj"
	-@erase "$(INTDIR)\VSPPlayer.obj"
	-@erase "$(INTDIR)\VSPPlayer.pch"
	-@erase "$(INTDIR)\VSPPlayer.res"
	-@erase "$(INTDIR)\VSPPlayerDlg.obj"
	-@erase "$(OUTDIR)\VSPPlayer.exe"
	-@erase "$(OUTDIR)\VSPPlayer.ilk"
	-@erase "$(OUTDIR)\VSPPlayer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VSPPlayer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\VSPPlayer.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VSPPlayer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\VSPPlayer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\VSPPlayer.exe" /pdbtype:sept /opt:nowin98 
LINK32_OBJS= \
	"$(INTDIR)\GFXControl.obj" \
	"$(INTDIR)\InfoDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VSPPlayer.obj" \
	"$(INTDIR)\VSPPlayerDlg.obj" \
	"$(INTDIR)\FileDlg.obj" \
	"$(INTDIR)\VSPPlay.obj" \
	"$(INTDIR)\VSPPlayer.res"

"$(OUTDIR)\VSPPlayer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("VSPPlayer.dep")
!INCLUDE "VSPPlayer.dep"
!ELSE 
!MESSAGE Warning: cannot find "VSPPlayer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VSPPlayer - Win32 Release" || "$(CFG)" == "VSPPlayer - Win32 Debug"
SOURCE=.\GFXControl.cpp

"$(INTDIR)\GFXControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSPPlayer.pch"


SOURCE=.\InfoDlg.cpp

"$(INTDIR)\InfoDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSPPlayer.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "VSPPlayer - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VSPPlayer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VSPPlayer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VSPPlayer - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VSPPlayer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VSPPlayer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\VSPPlayer.cpp

"$(INTDIR)\VSPPlayer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSPPlayer.pch"


SOURCE=.\VSPPlayer.rc

"$(INTDIR)\VSPPlayer.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\VSPPlayerDlg.cpp

"$(INTDIR)\VSPPlayerDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSPPlayer.pch"


SOURCE=.\FileDlg.cpp

"$(INTDIR)\FileDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSPPlayer.pch"


SOURCE=.\VSPPlay.cpp

"$(INTDIR)\VSPPlay.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSPPlayer.pch"



!ENDIF 

