# Microsoft Developer Studio Project File - Name="dials" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86)  Application" 0x0101

CFG=dials - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dials.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dials.mak" CFG="dials - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dials - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dials - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dials - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "obj"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "obj"
# PROP Target_Dir ""
# ADD CPP -MD /W3 /I "..\..\include" /I "$(QTDIR)\include" /I "V:\cvs\qwt\examples\dials" /I "moc" /I "v:\lib\qt\qt3_vc6\mkspecs\win32-msvc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D UNICODE /D QT_DLL /D QWT_DLL /D QT_THREAD_SUPPORT /D "QT_NO_DEBUG" /FD /c -nologo -Zm200 -O1 
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD LINK32  "qt-mt333.lib"  "qtmain.lib"  "kernel32.lib"  "user32.lib"  "gdi32.lib"  "comdlg32.lib"  "advapi32.lib"  "shell32.lib"  "ole32.lib"  "oleaut32.lib"  "uuid.lib"  "imm32.lib"  "winmm.lib"  "wsock32.lib"  "winspool.lib"  "..\..\lib\qwt.lib"  "kernel32.lib"  "user32.lib"  "gdi32.lib"  "comdlg32.lib"  "advapi32.lib"  "shell32.lib"  "ole32.lib"  "oleaut32.lib"  "uuid.lib"  "imm32.lib"  "winmm.lib"  "wsock32.lib"  "winspool.lib"  "opengl32.lib"  "glu32.lib"  "delayimp.lib"   /NOLOGO /SUBSYSTEM:windows /incremental:no /LIBPATH:"$(QTDIR)\lib" delayimp.lib /DELAYLOAD:comdlg32.dll /DELAYLOAD:oleaut32.dll /DELAYLOAD:winmm.dll /DELAYLOAD:wsock32.dll /DELAYLOAD:winspool.dll 


!ELSEIF  "$(CFG)" == "dials - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD CPP -MDd /W3 /GZ /ZI /Od /I "..\..\include" /I "$(QTDIR)\include" /I "V:\cvs\qwt\examples\dials" /I "moc" /I "v:\lib\qt\qt3_vc6\mkspecs\win32-msvc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D UNICODE /D QT_DLL /D QWT_DLL /D QT_THREAD_SUPPORT /FD /c -nologo -Zm200 -Zi  
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD LINK32  "qt-mt333.lib"  "qtmain.lib"  "kernel32.lib"  "user32.lib"  "gdi32.lib"  "comdlg32.lib"  "advapi32.lib"  "shell32.lib"  "ole32.lib"  "oleaut32.lib"  "uuid.lib"  "imm32.lib"  "winmm.lib"  "wsock32.lib"  "winspool.lib"  "..\..\lib\qwt.lib"  "kernel32.lib"  "user32.lib"  "gdi32.lib"  "comdlg32.lib"  "advapi32.lib"  "shell32.lib"  "ole32.lib"  "oleaut32.lib"  "uuid.lib"  "imm32.lib"  "winmm.lib"  "wsock32.lib"  "winspool.lib"  "opengl32.lib"  "glu32.lib"  "delayimp.lib"   /NOLOGO /SUBSYSTEM:windows /incremental:no /LIBPATH:"$(QTDIR)\lib" /pdbtype:sept /DEBUG 


!ENDIF 

# Begin Target

# Name "dials - Win32 Release"
# Name "dials - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=attitude_indicator.cpp
# End Source File
# Begin Source File

SOURCE=cockpit_grid.cpp
# End Source File
# Begin Source File

SOURCE=compass_grid.cpp
# End Source File
# Begin Source File

SOURCE=dials.cpp
# End Source File
# Begin Source File

SOURCE=speedo_meter.cpp
# End Source File

# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=attitude_indicator.h

USERDEP_attitude_indicator=""$(QTDIR)\bin\moc.exe""

!IF  "$(CFG)" == "dials - Win32 Release"

# Begin Custom Build - Moc'ing attitude_indicator.h...
InputPath=.\attitude_indicator.h


BuildCmds= \
	$(QTDIR)\bin\moc attitude_indicator.h -o moc\moc_attitude_indicator.cpp \

"moc\moc_attitude_indicator.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ELSEIF  "$(CFG)" == "dials - Win32 Debug"

# Begin Custom Build - Moc'ing attitude_indicator.h...
InputPath=.\attitude_indicator.h


BuildCmds= \
	$(QTDIR)\bin\moc attitude_indicator.h -o moc\moc_attitude_indicator.cpp \

"moc\moc_attitude_indicator.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=cockpit_grid.h

USERDEP_cockpit_grid=""$(QTDIR)\bin\moc.exe""

!IF  "$(CFG)" == "dials - Win32 Release"

# Begin Custom Build - Moc'ing cockpit_grid.h...
InputPath=.\cockpit_grid.h


BuildCmds= \
	$(QTDIR)\bin\moc cockpit_grid.h -o moc\moc_cockpit_grid.cpp \

"moc\moc_cockpit_grid.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ELSEIF  "$(CFG)" == "dials - Win32 Debug"

# Begin Custom Build - Moc'ing cockpit_grid.h...
InputPath=.\cockpit_grid.h


BuildCmds= \
	$(QTDIR)\bin\moc cockpit_grid.h -o moc\moc_cockpit_grid.cpp \

"moc\moc_cockpit_grid.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=compass_grid.h

# End Source File
# Begin Source File

SOURCE=speedo_meter.h

# End Source File

# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group







# Begin Group "Generated"
# Begin Source File

SOURCE=moc\moc_attitude_indicator.cpp
# End Source File
# Begin Source File

SOURCE=moc\moc_cockpit_grid.cpp
# End Source File






# Prop Default_Filter "moc"
# End Group
# End Target
# End Project

