# Microsoft Developer Studio Project File - Name="event_filter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86)  Application" 0x0101

CFG=event_filter - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "event_filter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "event_filter.mak" CFG="event_filter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "event_filter - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "event_filter - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "event_filter - Win32 Release"

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
# ADD CPP -MD /W3 /I "..\..\include" /I "$(QTDIR)\include" /I "V:\cvs\qwt\examples\event_filter" /I "moc" /I "v:\lib\qt\qt3_vc6\mkspecs\win32-msvc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D UNICODE /D QT_DLL /D QWT_DLL /D QT_THREAD_SUPPORT /D "QT_NO_DEBUG" /FD /c -nologo -Zm200 -O1 
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD LINK32  "qt-mt333.lib"  "qtmain.lib"  "kernel32.lib"  "user32.lib"  "gdi32.lib"  "comdlg32.lib"  "advapi32.lib"  "shell32.lib"  "ole32.lib"  "oleaut32.lib"  "uuid.lib"  "imm32.lib"  "winmm.lib"  "wsock32.lib"  "winspool.lib"  "..\..\lib\qwt.lib"  "kernel32.lib"  "user32.lib"  "gdi32.lib"  "comdlg32.lib"  "advapi32.lib"  "shell32.lib"  "ole32.lib"  "oleaut32.lib"  "uuid.lib"  "imm32.lib"  "winmm.lib"  "wsock32.lib"  "winspool.lib"  "opengl32.lib"  "glu32.lib"  "delayimp.lib"   /NOLOGO /SUBSYSTEM:windows /incremental:no /LIBPATH:"$(QTDIR)\lib" delayimp.lib /DELAYLOAD:comdlg32.dll /DELAYLOAD:oleaut32.dll /DELAYLOAD:winmm.dll /DELAYLOAD:wsock32.dll /DELAYLOAD:winspool.dll 


!ELSEIF  "$(CFG)" == "event_filter - Win32 Debug"

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
# ADD CPP -MDd /W3 /GZ /ZI /Od /I "..\..\include" /I "$(QTDIR)\include" /I "V:\cvs\qwt\examples\event_filter" /I "moc" /I "v:\lib\qt\qt3_vc6\mkspecs\win32-msvc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D UNICODE /D QT_DLL /D QWT_DLL /D QT_THREAD_SUPPORT /FD /c -nologo -Zm200 -Zi  
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD LINK32  "qt-mt333.lib"  "qtmain.lib"  "kernel32.lib"  "user32.lib"  "gdi32.lib"  "comdlg32.lib"  "advapi32.lib"  "shell32.lib"  "ole32.lib"  "oleaut32.lib"  "uuid.lib"  "imm32.lib"  "winmm.lib"  "wsock32.lib"  "winspool.lib"  "..\..\lib\qwt.lib"  "kernel32.lib"  "user32.lib"  "gdi32.lib"  "comdlg32.lib"  "advapi32.lib"  "shell32.lib"  "ole32.lib"  "oleaut32.lib"  "uuid.lib"  "imm32.lib"  "winmm.lib"  "wsock32.lib"  "winspool.lib"  "opengl32.lib"  "glu32.lib"  "delayimp.lib"   /NOLOGO /SUBSYSTEM:windows /incremental:no /LIBPATH:"$(QTDIR)\lib" /pdbtype:sept /DEBUG 


!ENDIF 

# Begin Target

# Name "event_filter - Win32 Release"
# Name "event_filter - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=canvaspicker.cpp
# End Source File
# Begin Source File

SOURCE=colorbar.cpp
# End Source File
# Begin Source File

SOURCE=event_filter.cpp
# End Source File
# Begin Source File

SOURCE=plot.cpp
# End Source File
# Begin Source File

SOURCE=scalepicker.cpp
# End Source File

# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=canvaspicker.h

USERDEP_canvaspicker=""$(QTDIR)\bin\moc.exe""

!IF  "$(CFG)" == "event_filter - Win32 Release"

# Begin Custom Build - Moc'ing canvaspicker.h...
InputPath=.\canvaspicker.h


BuildCmds= \
	$(QTDIR)\bin\moc canvaspicker.h -o moc\moc_canvaspicker.cpp \

"moc\moc_canvaspicker.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ELSEIF  "$(CFG)" == "event_filter - Win32 Debug"

# Begin Custom Build - Moc'ing canvaspicker.h...
InputPath=.\canvaspicker.h


BuildCmds= \
	$(QTDIR)\bin\moc canvaspicker.h -o moc\moc_canvaspicker.cpp \

"moc\moc_canvaspicker.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=colorbar.h

USERDEP_colorbar=""$(QTDIR)\bin\moc.exe""

!IF  "$(CFG)" == "event_filter - Win32 Release"

# Begin Custom Build - Moc'ing colorbar.h...
InputPath=.\colorbar.h


BuildCmds= \
	$(QTDIR)\bin\moc colorbar.h -o moc\moc_colorbar.cpp \

"moc\moc_colorbar.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ELSEIF  "$(CFG)" == "event_filter - Win32 Debug"

# Begin Custom Build - Moc'ing colorbar.h...
InputPath=.\colorbar.h


BuildCmds= \
	$(QTDIR)\bin\moc colorbar.h -o moc\moc_colorbar.cpp \

"moc\moc_colorbar.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=plot.h

USERDEP_plot=""$(QTDIR)\bin\moc.exe""

!IF  "$(CFG)" == "event_filter - Win32 Release"

# Begin Custom Build - Moc'ing plot.h...
InputPath=.\plot.h


BuildCmds= \
	$(QTDIR)\bin\moc plot.h -o moc\moc_plot.cpp \

"moc\moc_plot.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ELSEIF  "$(CFG)" == "event_filter - Win32 Debug"

# Begin Custom Build - Moc'ing plot.h...
InputPath=.\plot.h


BuildCmds= \
	$(QTDIR)\bin\moc plot.h -o moc\moc_plot.cpp \

"moc\moc_plot.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=scalepicker.h

USERDEP_scalepicker=""$(QTDIR)\bin\moc.exe""

!IF  "$(CFG)" == "event_filter - Win32 Release"

# Begin Custom Build - Moc'ing scalepicker.h...
InputPath=.\scalepicker.h


BuildCmds= \
	$(QTDIR)\bin\moc scalepicker.h -o moc\moc_scalepicker.cpp \

"moc\moc_scalepicker.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ELSEIF  "$(CFG)" == "event_filter - Win32 Debug"

# Begin Custom Build - Moc'ing scalepicker.h...
InputPath=.\scalepicker.h


BuildCmds= \
	$(QTDIR)\bin\moc scalepicker.h -o moc\moc_scalepicker.cpp \

"moc\moc_scalepicker.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF 

# End Source File

# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group







# Begin Group "Generated"
# Begin Source File

SOURCE=moc\moc_canvaspicker.cpp
# End Source File
# Begin Source File

SOURCE=moc\moc_colorbar.cpp
# End Source File
# Begin Source File

SOURCE=moc\moc_plot.cpp
# End Source File
# Begin Source File

SOURCE=moc\moc_scalepicker.cpp
# End Source File






# Prop Default_Filter "moc"
# End Group
# End Target
# End Project

