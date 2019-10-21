# Microsoft Developer Studio Project File - Name="StagedConnect" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=StagedConnect - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pong.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pong.mak" CFG="StagedConnect - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StagedConnect - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "StagedConnect - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StagedConnect - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib dplay.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "StagedConnect - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib winmm.lib dsound.lib ddraw.lib dplay.lib dinput.lib /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "StagedConnect - Win32 Release"
# Name "StagedConnect - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\cBall.h
# End Source File
# Begin Source File

SOURCE=.\cCircle.h
# End Source File
# Begin Source File

SOURCE=.\cPaddle_H.h
# End Source File
# Begin Source File

SOURCE=.\cPaddle_V.h
# End Source File
# Begin Source File

SOURCE=.\cPlayer.h
# End Source File
# Begin Source File

SOURCE=.\cWall.h
# End Source File
# Begin Source File

SOURCE=.\cWallList.h
# End Source File
# Begin Source File

SOURCE=.\ddutil.cpp
# End Source File
# Begin Source File

SOURCE=.\ddutil.h
# End Source File
# Begin Source File

SOURCE=.\dpconnect.cpp
# End Source File
# Begin Source File

SOURCE=.\dpstage.cpp
# End Source File
# Begin Source File

SOURCE=.\dsutil.c
# End Source File
# Begin Source File

SOURCE=.\keybdimm.cpp
# End Source File
# Begin Source File

SOURCE=.\mousenon.cpp
# End Source File
# Begin Source File

SOURCE=.\qDraw.h
# End Source File
# Begin Source File

SOURCE=.\qMap.h
# End Source File
# Begin Source File

SOURCE=.\readme.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\winmain.cpp
# End Source File
# Begin Source File

SOURCE=.\winmain.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE="..\..\Program Files\Microsoft Visual Studio\Vc98\Include\Basetsd.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\ABC.bmp
# End Source File
# Begin Source File

SOURCE=.\Cell1.bmp
# End Source File
# Begin Source File

SOURCE=.\DONUTS.bmp
# End Source File
# Begin Source File

SOURCE=.\jump.wav
# End Source File
# Begin Source File

SOURCE=.\MiniMap.bmp
# End Source File
# Begin Source File

SOURCE=.\miss01.wav
# End Source File
# Begin Source File

SOURCE=.\miss02.wav
# End Source File
# Begin Source File

SOURCE=.\paddle.bmp
# End Source File
# Begin Source File

SOURCE=.\paddle_Horz.bmp
# End Source File
# Begin Source File

SOURCE=.\paddle_Vert.bmp
# End Source File
# Begin Source File

SOURCE=.\Pong.ico
# End Source File
# Begin Source File

SOURCE=.\SCREEN.bmp
# End Source File
# Begin Source File

SOURCE=.\stop.wav
# End Source File
# Begin Source File

SOURCE=.\strike01.wav
# End Source File
# Begin Source File

SOURCE=.\strike02.wav
# End Source File
# Begin Source File

SOURCE=.\stunned.wav
# End Source File
# Begin Source File

SOURCE=.\throw.wav
# End Source File
# Begin Source File

SOURCE=.\wall.bmp
# End Source File
# End Group
# End Target
# End Project
