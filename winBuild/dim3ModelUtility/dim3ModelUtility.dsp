# Microsoft Developer Studio Project File - Name="dim3ModelUtility" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=dim3ModelUtility - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dim3ModelUtility.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dim3ModelUtility.mak" CFG="dim3ModelUtility - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dim3ModelUtility - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\win32Includes\GLEW" /I "..\win32Includes\ZLib" /I "..\win32Includes\SDL" /I "..\win32Includes\JS" /I "..\win32Includes\PNG" /I "..\..\dim3ModelUtility\Headers" /I "..\..\dim3Common\Headers" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_LIB" /D "D3_PCH" /YX"dim3ModelUtility.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\win32Includes\dim3\\dim3ModelUtility.lib"
# Begin Target

# Name "dim3ModelUtility - Win32 Release"
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Group "headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Common\Headers\baseutility.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Common\Headers\modelutility.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Common\Headers\os_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Common\Headers\win32_os_defs.h
# End Source File
# End Group
# Begin Group "dim3 Libraries"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\win32Includes\dim3\dim3BaseUtility.lib
# End Source File
# End Group
# End Group
# Begin Group "dim3ModelUtility"

# PROP Default_Filter ""
# Begin Group "win32Code"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\win32Code\dim3ModelUtility.def
# End Source File
# End Group
# Begin Group "ModelHeaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Headers\dim3modelutility.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Headers\modelprivate.h
# End Source File
# End Group
# Begin Group "ModelSources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\animation.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\bone.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\calculate.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\draw_bones.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\draw_normals.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\draw_setup.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\draw_vertexes.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\file_model_animate.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\file_model_mesh.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\file_model_mesh_v1.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\file_model_mesh_v2.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\file_model_pose.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\file_model_texture.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\hit_box.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\lookup.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\mesh.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\model_frames.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\model_main.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\model_transform.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\normals.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\pose.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\positions.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3ModelUtility\Sources\size.c
# End Source File
# End Group
# End Group
# End Target
# End Project
