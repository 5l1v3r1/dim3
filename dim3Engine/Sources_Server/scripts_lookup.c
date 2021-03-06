/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: Script Lookup Utilities

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

#include "scripts.h"
#include "objects.h"
#include "weapons.h"
#include "projectiles.h"
#include "interfaces.h"

extern int group_find_by_index(char *name);

extern map_type			map;
extern js_type			js;

/* =======================================================

      Objects and Weapons
      
======================================================= */

obj_type* script_find_obj_from_uid_arg(jsval arg)
{
	int				uid;
	obj_type		*obj;

	uid=JSVAL_TO_INT(arg);
	
	obj=object_find_uid(uid);
	if (obj==NULL) {
		JS_ReportError(js.cx,"No object exists with this ID: %d",uid);
		return(NULL);
	}
	
	return(obj);
}	

weapon_type* script_find_weapon_from_name_arg(obj_type *obj,jsval arg)
{
	char			name[name_str_len];
	weapon_type		*weap;

	script_value_to_string(arg,name,name_str_len);
	
	weap=weapon_find_name(obj,name);
	if (weap==NULL) {
		JS_ReportError(js.cx,"Named weapon does not exist in object: %s",name);
		return(NULL);
	}
	
	return(weap);
}	

/* =======================================================

      Spots and Nodes
      
======================================================= */

spot_type* script_find_spot_from_idx_arg(jsval arg)
{
	int				idx;

	idx=JSVAL_TO_INT(arg);
	if ((idx<0) || (idx>=map.nspot)) {
		JS_ReportError(js.cx,"No spot exists with this id: %d",idx);
		return(NULL);
	}
	
	return(&map.spots[idx]);
}

spot_type* script_find_spot_from_name_type(jsval arg_0,jsval arg_1)
{
	int				idx;
	char			name[name_str_len],type[name_str_len];

	script_value_to_string(arg_0,name,name_str_len);
	script_value_to_string(arg_1,type,name_str_len);
	
	idx=map_find_random_spot(&map,name,type);
	if (idx==-1) {
		JS_ReportError(js.cx,"No spot exists with this name-type: %s-%s",name,type);
		return(NULL);
	}
	
	return(&map.spots[idx]);
}

spot_type* script_find_network_spot(obj_type *obj)
{
	int				idx;
	
	idx=object_find_network_spawn_spot(obj);
	if (idx==-1) {
		JS_ReportError(js.cx,"Could not find a new network spawn spot");
		return(NULL);
	}
	
	return(&map.spots[idx]);
}

node_type* script_find_node_from_idx_arg(jsval arg)
{
	int				idx;

	idx=JSVAL_TO_INT(arg);
	if ((idx<0) || (idx>=map.nnode)) {
		JS_ReportError(js.cx,"No node exists with this id: %d",idx);
		return(NULL);
	}
	
	return(&map.nodes[idx]);
}

/* =======================================================

      HUD Elements
      
======================================================= */

hud_text_type* script_find_text_from_name(jsval arg)
{
	char			name[name_str_len];
	hud_text_type	*text;

	script_value_to_string(arg,name,name_str_len);
	text=hud_texts_find(name);
	if (text==NULL) {
		JS_ReportError(js.cx,"No interface text exists with the name: %s",name);
		return(NULL);
	}
	
	return(text);
}

hud_bitmap_type* script_find_bitmap_from_name(jsval arg)
{
	char			name[name_str_len];
	hud_bitmap_type	*bitmap;

	script_value_to_string(arg,name,name_str_len);
	bitmap=hud_bitmaps_find(name);
	if (bitmap==NULL) {
		JS_ReportError(js.cx,"No interface bitmap exists with the name: %s",name);
		return(NULL);
	}
	
	return(bitmap);
}

hud_bar_type* script_find_bar_from_name(jsval arg)
{
	char			name[name_str_len];
	hud_bar_type	*bar;

	script_value_to_string(arg,name,name_str_len);
	bar=hud_bars_find(name);
	if (bar==NULL) {
		JS_ReportError(js.cx,"No interface bar exists with the name: %s",name);
		return(NULL);
	}
	
	return(bar);
}

/* =======================================================

      Segment Groups
      
======================================================= */

int script_find_group_from_name(jsval arg)
{
	int				idx;
	char			name[name_str_len];
	
	script_value_to_string(arg,name,name_str_len);
	idx=group_find_by_index(name);
	if (idx==-1) {
		JS_ReportError(js.cx,"No segment group exists with the name: %s",name);
		return(-1);
	}
	
	return(idx);
}

/* =======================================================

      Map Movements
      
======================================================= */

int script_find_map_movement_from_name(jsval arg)
{
	int				idx;
	char			name[name_str_len];
	
	script_value_to_string(arg,name,name_str_len);
	idx=map_movement_find(&map,name);
	if (idx==-1) {
		JS_ReportError(js.cx,"No map movement exists with the name: %s",name);
		return(-1);
	}
	
	return(idx);
}

/* =======================================================

      Attached Objects
      
======================================================= */

int script_get_attached_object_uid(void)
{
	weapon_type		*weap;
	proj_type		*proj;

	if (js.attach.thing_type==thing_type_object) return(js.attach.thing_uid);

	if (js.attach.thing_type==thing_type_weapon) {
		weap=weapon_find_uid(js.attach.thing_uid);
		if (weap!=NULL) return(weap->obj_uid);
	}

	if (js.attach.thing_type==thing_type_projectile) {
		proj=projectile_find_uid(js.attach.thing_uid);
		if (proj!=NULL) return(proj->obj_uid);
	}

	return(-1);
}
