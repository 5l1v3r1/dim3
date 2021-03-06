/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: Setup XML

***************************** License ********************************

This code can be freely used as long as these conditions are met:

1. This header, in its entirety, is kept with the code
2. This credit �Created with dim3 Technology� is given on a single
application screen and in a single piece of the documentation
3. It is not resold, in it's current form or modified, as an
engine-only product

This code is presented as is. The author of dim3 takes no
responsibilities for any version of this code.

Any non-engine product (games, etc) created with this code is free
from any and all payment and/or royalties to the author of dim3,
and can be sold or given away.

(c) 2000-2007 Klink! Software www.klinksoftware.com
 
*********************************************************************/

#ifdef D3_PCH
	#include "dim3engine.h"
#endif

#include "xmls.h"

setup_type					setup;

/* =======================================================

      Default Preferences
      
======================================================= */

void setup_xml_default(void)
{
	setup.screen_wid=640;
	setup.screen_high=480;
	setup.lock_fps_refresh=FALSE;
	
	setup.anisotropic_mode=anisotropic_mode_none;
	setup.mipmap_mode=mipmap_mode_trilinear;
	setup.texture_compression=FALSE;
	setup.fsaa_mode=fsaa_mode_none;
	
	setup.decal_on=TRUE;
	setup.shadow_on=TRUE;
	
	setup.gamma=0.0f;
	setup.tint_color_idx=0;
	
	setup.sound_volume=0.6f;
	setup.music_on=TRUE;
	setup.music_volume=0.5f;
    
	setup.always_run=FALSE;
	setup.toggle_run=FALSE;
	setup.invert_look=FALSE;
	setup.mouse_smooth=TRUE;

	setup.mouse_x.speed=0.03f;
	setup.mouse_x.speed_min=0.0f;
	setup.mouse_x.speed_max=0.1f;
	setup.mouse_x.acceleration=0.6f;
	setup.mouse_x.acceleration_min=0.0f;
	setup.mouse_x.acceleration_max=1.0f;

	setup.mouse_y.speed=0.03f;
	setup.mouse_y.speed_min=0.0f;
	setup.mouse_y.speed_max=0.1f;
	setup.mouse_y.acceleration=0.6f;
	setup.mouse_y.acceleration_min=0.0f;
	setup.mouse_y.acceleration_max=1.0f;

	setup.joystick_x.speed=0.03f;
	setup.joystick_x.speed_min=0.0f;
	setup.joystick_x.speed_max=0.1f;
	setup.joystick_x.acceleration=0.6f;
	setup.joystick_x.acceleration_min=0.0f;
	setup.joystick_x.acceleration_max=1.0f;

	setup.joystick_y.speed=0.03f;
	setup.joystick_y.speed_min=0.0f;
	setup.joystick_y.speed_max=0.1f;
	setup.joystick_y.acceleration=0.6f;
	setup.joystick_y.acceleration_min=0.0f;
	setup.joystick_y.acceleration_max=1.0f;

	setup.joystick_mode=joystick_mode_not_used;

	setup.action_list.naction=0;

	strcpy(setup.network.name,"Player");
	setup.network.show_names=TRUE;
	setup.network.nhost=0;
	setup.network.noption=0;

	setup.network.last_map[0]=0x0;
	
	setup.network.bot.count=0;
	setup.network.bot.skill=2;

	setup.network.game_type=0;
	setup.network.last_map[0]=0x0;
	setup.network.score_limit=20;
	
	setup.debug_console=FALSE;
	setup.window=FALSE;
	setup.window_editor=TRUE;
}

/* =======================================================

      Setup Value Fixes
      
======================================================= */

void setup_xml_fix_axis(setup_axis_type *axis)
{
	if (axis->speed<axis->speed_min) axis->speed=axis->speed_min;
	if (axis->speed>axis->speed_max) axis->speed=axis->speed_max;
	if (axis->acceleration<axis->acceleration_min) axis->acceleration=axis->acceleration_min;
	if (axis->acceleration>axis->acceleration_max) axis->acceleration=axis->acceleration_max;
}

/* =======================================================

      Read Setup
      
======================================================= */

bool setup_xml_read_path(char *path)
{
	int							n,k,naction,nhost,noption,
								setup_tag,actions_tag,hosts_tag,options_tag,tag;
	char						tag_name[32];
	setup_action_type			*action;
	setup_network_hosts_type	*host;
	setup_network_option_type	*option;
	
		// read file
		
	setup_xml_default();

	if (!xml_open_file(path)) return(FALSE);
    
		// decode the file
       
    setup_tag=xml_findrootchild("Setup");
    if (setup_tag==-1) {
		xml_close_file();
		return(FALSE);
    }
	
		// keys

    xml_key_read_int(setup_tag,"Screen_Width",&setup.screen_wid);
    xml_key_read_int(setup_tag,"Screen_Height",&setup.screen_high);
	xml_key_read_boolean(setup_tag,"Lock_FPS_Refresh",&setup.lock_fps_refresh);
	xml_key_read_float(setup_tag,"Gamma",&setup.gamma);
    xml_key_read_int(setup_tag,"Tint",&setup.tint_color_idx);
    xml_key_read_boolean(setup_tag,"Texture_Compression",&setup.texture_compression);
    xml_key_read_int(setup_tag,"Anisotropic_Mode",&setup.anisotropic_mode);
    xml_key_read_int(setup_tag,"Mipmap_Mode",&setup.mipmap_mode);
	xml_key_read_int(setup_tag,"FSAA_Mode",&setup.fsaa_mode);
	xml_key_read_boolean(setup_tag,"Decal_On",&setup.decal_on);
	xml_key_read_boolean(setup_tag,"Shadow_On",&setup.shadow_on);
	xml_key_read_float(setup_tag,"Sound_Volume",&setup.sound_volume);
	xml_key_read_boolean(setup_tag,"Music_On",&setup.music_on);
	xml_key_read_float(setup_tag,"Music_Volume",&setup.music_volume);
	xml_key_read_boolean(setup_tag,"Always_Run",&setup.always_run);
	xml_key_read_boolean(setup_tag,"Toggle_Run",&setup.toggle_run);
	xml_key_read_boolean(setup_tag,"Invert_Look",&setup.invert_look);
	xml_key_read_boolean(setup_tag,"Mouse_Smooth",&setup.mouse_smooth);
	xml_key_read_float(setup_tag,"Mouse_X_Speed",&setup.mouse_x.speed);
	xml_key_read_float(setup_tag,"Mouse_X_Speed_Min",&setup.mouse_x.speed_min);
	xml_key_read_float(setup_tag,"Mouse_X_Speed_Max",&setup.mouse_x.speed_max);
	xml_key_read_float(setup_tag,"Mouse_X_Acceleration",&setup.mouse_x.acceleration);
	xml_key_read_float(setup_tag,"Mouse_X_Acceleration_Min",&setup.mouse_x.acceleration_min);
	xml_key_read_float(setup_tag,"Mouse_X_Acceleration_Max",&setup.mouse_x.acceleration_max);
	xml_key_read_float(setup_tag,"Mouse_Y_Speed",&setup.mouse_y.speed);
	xml_key_read_float(setup_tag,"Mouse_Y_Speed_Min",&setup.mouse_y.speed_min);
	xml_key_read_float(setup_tag,"Mouse_Y_Speed_Max",&setup.mouse_y.speed_max);
	xml_key_read_float(setup_tag,"Mouse_Y_Acceleration",&setup.mouse_y.acceleration);
	xml_key_read_float(setup_tag,"Mouse_Y_Acceleration_Min",&setup.mouse_y.acceleration_min);
	xml_key_read_float(setup_tag,"Mouse_Y_Acceleration_Max",&setup.mouse_y.acceleration_max);
	xml_key_read_float(setup_tag,"Joystick_X_Speed",&setup.joystick_x.speed);
	xml_key_read_float(setup_tag,"Joystick_X_Speed_Min",&setup.joystick_x.speed_min);
	xml_key_read_float(setup_tag,"Joystick_X_Speed_Max",&setup.joystick_x.speed_max);
	xml_key_read_float(setup_tag,"Joystick_X_Acceleration",&setup.joystick_x.acceleration);
	xml_key_read_float(setup_tag,"Joystick_X_Acceleration_Min",&setup.joystick_x.acceleration_min);
	xml_key_read_float(setup_tag,"Joystick_X_Acceleration_Max",&setup.joystick_x.acceleration_max);
	xml_key_read_float(setup_tag,"Joystick_Y_Speed",&setup.joystick_y.speed);
	xml_key_read_float(setup_tag,"Joystick_Y_Speed_Min",&setup.joystick_y.speed_min);
	xml_key_read_float(setup_tag,"Joystick_Y_Speed_Max",&setup.joystick_y.speed_max);
	xml_key_read_float(setup_tag,"Joystick_Y_Acceleration",&setup.joystick_y.acceleration);
	xml_key_read_float(setup_tag,"Joystick_Y_Acceleration_Min",&setup.joystick_y.acceleration_min);
	xml_key_read_float(setup_tag,"Joystick_Y_Acceleration_Max",&setup.joystick_y.acceleration_max);
	xml_key_read_int(setup_tag,"Joystick_Mode",&setup.joystick_mode);
	xml_key_read_text(setup_tag,"Network_Name",setup.network.name,name_str_len);
	xml_key_read_text(setup_tag,"Network_Last_Map",setup.network.last_map,name_str_len);
	xml_key_read_int(setup_tag,"Host_Bot_Count",&setup.network.bot.count);
	xml_key_read_int(setup_tag,"Host_Bot_Skill",&setup.network.bot.skill);
	xml_key_read_int(setup_tag,"Host_Game_Type",&setup.network.game_type);
	xml_key_read_int(setup_tag,"Host_Score_Limit",&setup.network.score_limit);
	xml_key_read_boolean(setup_tag,"Network_Show_Names",&setup.network.show_names);
	xml_key_read_boolean(setup_tag,"Debug_Console",&setup.debug_console);
	xml_key_read_boolean(setup_tag,"Window",&setup.window);
	xml_key_read_boolean(setup_tag,"Window_Editor",&setup.window_editor);

		// fix some items

	setup_xml_fix_axis(&setup.mouse_x);
	setup_xml_fix_axis(&setup.mouse_y);
	
		// actions

    actions_tag=xml_findfirstchild("Actions",setup_tag);
    if (actions_tag!=-1) {
	
		naction=xml_countchildren(actions_tag);
		tag=xml_findfirstchild("Action",actions_tag);
		
		setup.action_list.naction=naction;
		action=setup.action_list.actions;
		
        for (n=0;n!=naction;n++) {
			xml_get_attribute_text(tag,"name",action->name,32);
			
			for (k=0;k!=max_setup_action_attach;k++) {
				sprintf(tag_name,"attach_%d",k);
				if (!xml_get_attribute_text(tag,tag_name,action->attach[k],32)) action->attach[k][0]=0x0;
			}
           
			tag=xml_findnextchild(tag);
			
			action++;
        }
	}

		// hosts

    hosts_tag=xml_findfirstchild("Hosts",setup_tag);
    if (hosts_tag!=-1) {
	
		nhost=xml_countchildren(hosts_tag);
		tag=xml_findfirstchild("Host",hosts_tag);
		
		setup.network.nhost=nhost;
		host=setup.network.hosts;
		
        for (n=0;n!=nhost;n++) {
			xml_get_attribute_text(tag,"ip",host->ip,256);

			tag=xml_findnextchild(tag);
			host++;
        }
	}
	
 		// options

    options_tag=xml_findfirstchild("Options",setup_tag);
    if (options_tag!=-1) {
	
		noption=xml_countchildren(options_tag);
		tag=xml_findfirstchild("Option",options_tag);

		setup.network.noption=noption;
		option=setup.network.options;
		
        for (n=0;n!=noption;n++) {
			xml_get_attribute_text(tag,"name",option->name,name_str_len);
			
			tag=xml_findnextchild(tag);
  			option++;
		}
	}
  
	xml_close_file();
	
	return(TRUE);
}

bool setup_xml_read(void)
{
	char				path[1024];
	
		// check user specific setup XML file.  If it exists, use that,
		// otherwise use default XML file
		
	if (!file_paths_documents_exist(&setup.file_path_setup,path,"Settings","Setup","xml")) {
		file_paths_data(&setup.file_path_setup,path,"Settings","Setup","xml");
	}

	return(setup_xml_read_path(path));
}

bool setup_xml_reset(void)
{
	char				path[1024];
	
		// read directly from the default
		
	file_paths_data(&setup.file_path_setup,path,"Settings","Setup","xml");

	return(setup_xml_read_path(path));
}

/* =======================================================

      Write Setup
      
======================================================= */

bool setup_xml_write(void)
{
	int							n,k;
	char						path[1024],tag_name[32];
	bool						ok;
	setup_action_type			*action;
	setup_network_hosts_type	*host;
	setup_network_option_type	*option;
	
		// start the setup file
		
    xml_new_file();
    
    xml_add_tagstart("Setup");
    xml_add_tagend(FALSE);
	
		// keys

    xml_key_write_int("Screen_Width",setup.screen_wid);
    xml_key_write_int("Screen_Height",setup.screen_high);
    xml_key_write_boolean("Lock_FPS_Refresh",setup.lock_fps_refresh);
	xml_key_write_float("Gamma",setup.gamma);
	xml_key_write_int("Tint",setup.tint_color_idx);
	xml_key_write_boolean("Texture_Compression",setup.texture_compression);
	xml_key_write_int("Anisotropic_Mode",setup.anisotropic_mode);
    xml_key_write_int("Mipmap_Mode",setup.mipmap_mode);
	xml_key_write_int("FSAA_Mode",setup.fsaa_mode);
	xml_key_write_boolean("Decal_On",setup.decal_on);
	xml_key_write_boolean("Shadow_On",setup.shadow_on);
	xml_key_write_float("Sound_Volume",setup.sound_volume);
	xml_key_write_boolean("Music_On",setup.music_on);
	xml_key_write_float("Music_Volume",setup.music_volume);
	xml_key_write_boolean("Always_Run",setup.always_run);
	xml_key_write_boolean("Toggle_Run",setup.toggle_run);
	xml_key_write_boolean("Invert_Look",setup.invert_look);
	xml_key_write_boolean("Mouse_Smooth",setup.mouse_smooth);
	xml_key_write_float("Mouse_X_Speed",setup.mouse_x.speed);
	xml_key_write_float("Mouse_X_Speed_Min",setup.mouse_x.speed_min);
	xml_key_write_float("Mouse_X_Speed_Max",setup.mouse_x.speed_max);
	xml_key_write_float("Mouse_X_Acceleration",setup.mouse_x.acceleration);
	xml_key_write_float("Mouse_X_Acceleration_Min",setup.mouse_x.acceleration_min);
	xml_key_write_float("Mouse_X_Acceleration_Max",setup.mouse_x.acceleration_max);
	xml_key_write_float("Mouse_Y_Speed",setup.mouse_y.speed);
	xml_key_write_float("Mouse_Y_Speed_Min",setup.mouse_y.speed_min);
	xml_key_write_float("Mouse_Y_Speed_Max",setup.mouse_y.speed_max);
	xml_key_write_float("Mouse_Y_Acceleration",setup.mouse_y.acceleration);
	xml_key_write_float("Mouse_Y_Acceleration_Min",setup.mouse_y.acceleration_min);
	xml_key_write_float("Mouse_Y_Acceleration_Max",setup.mouse_y.acceleration_max);
	xml_key_write_float("Joystick_X_Speed",setup.joystick_x.speed);
	xml_key_write_float("Joystick_X_Speed_Min",setup.joystick_x.speed_min);
	xml_key_write_float("Joystick_X_Speed_Max",setup.joystick_x.speed_max);
	xml_key_write_float("Joystick_X_Acceleration",setup.joystick_x.acceleration);
	xml_key_write_float("Joystick_X_Acceleration_Min",setup.joystick_x.acceleration_min);
	xml_key_write_float("Joystick_X_Acceleration_Max",setup.joystick_x.acceleration_max);
	xml_key_write_float("Joystick_Y_Speed",setup.joystick_y.speed);
	xml_key_write_float("Joystick_Y_Speed_Min",setup.joystick_y.speed_min);
	xml_key_write_float("Joystick_Y_Speed_Max",setup.joystick_y.speed_max);
	xml_key_write_float("Joystick_Y_Acceleration",setup.joystick_y.acceleration);
	xml_key_write_float("Joystick_Y_Acceleration_Min",setup.joystick_y.acceleration_min);
	xml_key_write_float("Joystick_Y_Acceleration_Max",setup.joystick_y.acceleration_max);
	xml_key_write_int("Joystick_Mode",setup.joystick_mode);
	xml_key_write_text("Network_Name",setup.network.name);
	xml_key_write_text("Network_Last_Map",setup.network.last_map);
	xml_key_write_int("Host_Bot_Count",setup.network.bot.count);
	xml_key_write_int("Host_Bot_Skill",setup.network.bot.skill);
	xml_key_write_int("Host_Game_Type",setup.network.game_type);
	xml_key_write_int("Host_Score_Limit",setup.network.score_limit);
	xml_key_write_boolean("Network_Show_Names",setup.network.show_names);
	xml_key_write_boolean("Debug_Console",setup.debug_console);
	xml_key_write_boolean("Window",setup.window);
	xml_key_write_boolean("Window_Editor",setup.window_editor);
	
		// actions

    xml_add_tagstart("Actions");
    xml_add_tagend(FALSE);
	
	action=setup.action_list.actions;
		
	for (n=0;n!=setup.action_list.naction;n++) {
		xml_add_tagstart("Action");
		xml_add_attribute_text("name",action->name);
			
		for (k=0;k!=max_setup_action_attach;k++) {
			if (action->attach[k][0]!=0x0) {
				sprintf(tag_name,"attach_%d",k);
				xml_add_attribute_text(tag_name,action->attach[k]);
			}
		}
           
	    xml_add_tagend(TRUE);
		action++;
	}

    xml_add_tagclose("Actions");
	
		// hosts

    xml_add_tagstart("Hosts");
    xml_add_tagend(FALSE);
	
	host=setup.network.hosts;
		
	for (n=0;n!=setup.network.nhost;n++) {
		xml_add_tagstart("Host");
		xml_add_attribute_text("ip",host->ip);
	    xml_add_tagend(TRUE);
		host++;
	}

    xml_add_tagclose("Hosts");
	
		// options
		
    xml_add_tagstart("Options");
    xml_add_tagend(FALSE);
	
	option=setup.network.options;
		
	for (n=0;n!=setup.network.noption;n++) {
		xml_add_tagstart("Option");
		xml_add_attribute_text("name",option->name);
	    xml_add_tagend(TRUE);
		option++;
	}

    xml_add_tagclose("Options");
		
		// close setup
		
    xml_add_tagclose("Setup");

        // save the setup
		// always save to user specific data
		
	file_paths_documents(&setup.file_path_setup,path,"Settings","Setup","xml");
		
	ok=xml_save_file(path);
    xml_close_file();
	
	return(ok);
}

/* =======================================================

      Restore Setup on Bad Startup
      
======================================================= */

void setup_restore(void)
{
		// reset important defaults
		// to their simpliest form
		
	setup.screen_wid=640;
	setup.screen_high=480;
	setup.lock_fps_refresh=FALSE;
	
	setup.decal_on=FALSE;
	setup.shadow_on=FALSE;
	
	setup.anisotropic_mode=anisotropic_mode_none;
	setup.mipmap_mode=mipmap_mode_none;
	setup.texture_compression=FALSE;
	setup.fsaa_mode=fsaa_mode_none;
	
	setup.music_on=FALSE;

	setup.debug_console=TRUE;
	setup.window=FALSE;
	setup.window_editor=TRUE;
	
		// save XML
		
	setup_xml_write();
}

