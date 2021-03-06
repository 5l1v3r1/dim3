# Microsoft Developer Studio Project File - Name="dim3Engine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=DIM3ENGINE - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dim3Engine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dim3Engine.mak" CFG="DIM3ENGINE - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dim3Engine - Win32 Release" (based on "Win32 (x86) Console Application")
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
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /Z7 /O2 /I "..\win32Includes\pthreads" /I "..\win32Includes\GLEW" /I "..\win32Includes\ZLib" /I "..\win32Includes\SDL" /I "..\win32Includes\OpenAL" /I "..\win32Includes\JS" /I "..\win32Includes\PNG" /I "..\..\dim3Engine\Headers_View" /I "..\..\dim3Engine\Headers_Server" /I "..\..\dim3Engine\Headers_Network" /I "..\..\dim3Engine\Headers" /I "..\..\dim3MapUtility\Headers" /I "..\..\dim3ModelUtility\Headers" /I "..\..\dim3BaseUtility\Headers" /I "..\..\dim3Common\Headers" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "D3_PCH" /D "D3_ENGINE" /YX"dim3Engine.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"..\..\..\dim3\dim3 Engine.exe"
# SUBTRACT LINK32 /map /debug
# Begin Target

# Name "dim3Engine - Win32 Release"
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Group "Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Common\Headers\baseutility.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Common\Headers\maputility.h
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
# Begin Group "OS Libraries"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\..\Program Files\Microsoft Visual Studio\VC98\Lib\WSOCK32.LIB"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Program Files\Microsoft Visual Studio\VC98\Lib\OPENGL32.LIB"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLU32.LIB"
# End Source File
# End Group
# Begin Group "glew"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\win32Includes\GLEW\glew.h
# End Source File
# Begin Source File

SOURCE=..\win32Includes\GLEW\wglew.h
# End Source File
# End Group
# Begin Group "SDL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\win32Includes\SDL\SDL.h
# End Source File
# Begin Source File

SOURCE=..\win32Includes\SDL\SDLmain.lib
# End Source File
# Begin Source File

SOURCE=..\win32Includes\SDL\SDL.lib
# End Source File
# End Group
# Begin Group "JS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\win32Includes\JS\jsapi.h
# End Source File
# Begin Source File

SOURCE=..\win32Includes\JS\jscompat.h
# End Source File
# Begin Source File

SOURCE=..\win32Includes\JS\jsconfig.h
# End Source File
# Begin Source File

SOURCE=..\win32Includes\JS\jscpucfg.h
# End Source File
# Begin Source File

SOURCE=..\win32Includes\JS\jslong.h
# End Source File
# Begin Source File

SOURCE=..\win32Includes\JS\jsosdep.h
# End Source File
# Begin Source File

SOURCE=..\win32Includes\JS\jsotypes.h
# End Source File
# Begin Source File

SOURCE=..\win32Includes\JS\jspubtd.h
# End Source File
# Begin Source File

SOURCE=..\win32Includes\JS\jstypes.h
# End Source File
# Begin Source File

SOURCE=..\win32Includes\JS\js32.lib
# End Source File
# End Group
# Begin Group "dim3 Libraries"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\win32Includes\dim3\dim3BaseUtility.lib
# End Source File
# Begin Source File

SOURCE=..\win32Includes\dim3\dim3ModelUtility.lib
# End Source File
# Begin Source File

SOURCE=..\win32Includes\dim3\dim3MapUtility.lib
# End Source File
# End Group
# End Group
# Begin Group "dim3Engine"

# PROP Default_Filter ""
# Begin Group "Engine Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Headers\dim3engine.h
# End Source File
# End Group
# Begin Group "Engine Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Sources\app.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources\debug.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources\file.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources\game.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources\loop.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources\main.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources\map.c
# End Source File
# End Group
# Begin Group "Server Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\camera_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\cameras.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\consoles.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\effects.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\interface_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\interfaces.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\lights.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\objects.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\physics.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\projectiles.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\remotes.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\scenery.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\script_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\scripts.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\server_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\setup_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\weapons.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Server\xmls.h
# End Source File
# End Group
# Begin Group "Server Sources"

# PROP Default_Filter ""
# Begin Group "Script API"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_camera.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_camera_angle.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_camera_chase.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_camera_chase_angle.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_camera_chase_offset.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_camera_chase_slop.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_camera_plane.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_camera_position.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_camera_setting.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_camera_state.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_camera_static_position.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_data.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_event.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_game_join.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_game_score.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_game_setting.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_interface.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_interface_bar.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_interface_bitmap.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_interface_console.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_interface_fade.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_interface_interaction.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_interface_radar.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_interface_screen.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_interface_text.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_map.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_map_action.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_map_fog.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_map_fog_color.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_map_group.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_map_info.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_map_light_color.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_map_movement.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_map_node.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_map_object.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_map_setting.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_map_spot.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_model.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_model_animation.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_model_bone.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_model_fill.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_model_halo.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_model_light.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_model_light_color.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_model_mesh.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_model_offset.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_model_rotate.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_model_shadow.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_model_spin.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_multiplayer.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_multiplayer_bot.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_multiplayer_score.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_multiplayer_setting.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_angle.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_click.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_forward_speed.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_health.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_held.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_hit.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_hit_angle.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_hit_position.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_lock.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_look.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_melee.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_motion_angle.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_motion_vector.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_object_speed.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_object_thrust.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_pickup.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_position.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_radar.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_rigid_body.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_score.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_setting.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_side_speed.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_sight.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_size.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_status.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_touch.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_touch_angle.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_touch_position.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_turn_speed.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_vehicle.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_vert_speed.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_watch.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_weapon.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_obj_weapon_fire.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_proj_action.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_proj_hit.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_proj_mark.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_proj_melee.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_proj_motion_angle.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_proj_motion_vector.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_proj_origin.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_proj_position.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_proj_push.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_proj_setting.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_proj_size.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_proj_speed.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_sound.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_spawn.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_utility.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_utility_angle.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_utility_pack.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_utility_point.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_utility_random.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_alt_ammo.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_ammo.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_crosshair.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_crosshair_color.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_crosshair_empty_color.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_crosshair_pickup_color.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_dual.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_fire.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_hand.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_hand_angle.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_hand_position.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_kickback.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_melee.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_projectile.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_recoil.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_setting.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_target.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_target_color.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_weap_zoom.c
# End Source File
# End Group
# Begin Group "Objects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\obj_action.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\obj_auto_walk.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\obj_ext_move.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\obj_find.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\obj_grow.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\obj_held.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\obj_liquid.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\obj_move.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\obj_rigid_body.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\obj_state.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\obj_turn.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\obj_watch.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\objects.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\player.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\remote.c
# End Source File
# End Group
# Begin Group "Weapons"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\weapon.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\weapon_melee.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\weapon_projectile.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\weapon_select.c
# End Source File
# End Group
# Begin Group "Projectiles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\projectile.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\projectile_hit.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\projectile_hitscan.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\projectile_move.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\projectile_setup.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\camera.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\camera_chase.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\camera_fpp.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\camera_static.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\chooser.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\collision.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\collision_map.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\collision_utility.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\console.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\crosshair.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\decals.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\effects.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\effects_spawn.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\game_time.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\group_change.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\group_move.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\halos.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\hud.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\item.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\map_light_trace.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\map_movement.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\map_ray_trace.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\map_y_check.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\menu.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\model.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\model_animate.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\model_draw_setup.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\model_effect.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\model_fade.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\model_mesh.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\particles.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\rings.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\scenery.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\script_timers.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\scripts.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\scripts_convert.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\scripts_data.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\scripts_defines.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\scripts_events.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\scripts_file.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\scripts_lookup.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\scripts_objects.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\scripts_run.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\scripts_state.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\server.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\server_run.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\xml_crosshairs.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\xml_halos.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\xml_interface.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\xml_marks.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\xml_particles.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\xml_rings.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Server\xml_setup.c
# End Source File
# End Group
# Begin Group "View Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_View\input_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_View\inputs.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_View\sound_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_View\sounds.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_View\video.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_View\video_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_View\view_defs.h
# End Source File
# End Group
# Begin Group "View Sources"

# PROP Default_Filter ""
# Begin Group "Audio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\al_ambient.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\al_buffer.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\al_music.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\al_play.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\al_setup.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\ambients.c
# End Source File
# End Group
# Begin Group "Video"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\gl_back_render.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\gl_check.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\gl_frames.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\gl_light.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\gl_renderer.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\gl_shader.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\gl_text.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\gl_texture.c
# End Source File
# End Group
# Begin Group "Render Map"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\render_map_liquid.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\render_map_opaque.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\render_map_setup.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\render_map_transparent.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\render_model.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\render_shadow.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\chooser_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\console_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\crosshair_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\cursor.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\decals_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\effects_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\elemets.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\error.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\fade.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\files.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\fog.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\gui.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\halo_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\hand.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\host.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\hud_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\input.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\input_joystick.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\input_keyboard.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\input_mouse.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\intro.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\join.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\map_pick.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\menu_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\movie.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\network_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\particles_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\player_input.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\progress.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\radar_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\rain.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\remote_status.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\rings_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\score_limit.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\setup_game.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\setup_network.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\sky.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\story.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\tint.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\title.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\view.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\view_bounds.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\view_draw.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\view_images.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\view_run.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\view_setup.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\view_vertex_list.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\view_vertex_object.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\xml_action.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\xml_shaders.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\xml_sound.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_View\zoom_draw.c
# End Source File
# End Group
# Begin Group "Network Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Network\network.h
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Headers_Network\network_defs.h
# End Source File
# End Group
# Begin Group "Network Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Network\net_client_join_host.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Network\net_client_receive.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Network\net_client_send.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Network\net_host.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Network\net_host_broadcast.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Network\net_host_client_handler.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Network\net_host_players.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Network\net_read_queue.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Network\net_socket.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Network\net_socket_udp.c
# End Source File
# Begin Source File

SOURCE=..\..\dim3Engine\Sources_Network\net_utility.c
# End Source File
# End Group
# End Group
# End Target
# End Project
