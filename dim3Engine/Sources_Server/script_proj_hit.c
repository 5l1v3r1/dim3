/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: Script: proj.hit object

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
#include "projectiles.h"

extern map_type			map;
extern server_type		server;
extern js_type			js;

JSBool js_proj_hit_get_type(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_proj_hit_get_name(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_proj_hit_get_id(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_proj_hit_get_isPlayer(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_proj_hit_get_startTick(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_proj_hit_get_materialName(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_proj_hit_get_ejectVector(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_proj_hit_get_reflectVector(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);

JSClass			proj_hit_class={"proj_hit_class",0,
							script_add_property,JS_PropertyStub,
							JS_PropertyStub,JS_PropertyStub,
							JS_EnumerateStub,JS_ResolveStub,JS_ConvertStub,JS_FinalizeStub};

script_js_property	proj_hit_props[]={
							{"type",				js_proj_hit_get_type,				NULL},
							{"name",				js_proj_hit_get_name,				NULL},
							{"id",					js_proj_hit_get_id,					NULL},
							{"isPlayer",			js_proj_hit_get_isPlayer,			NULL},
							{"startTick",			js_proj_hit_get_startTick,			NULL},
							{"materialName",		js_proj_hit_get_materialName,		NULL},
							{"ejectVector",			js_proj_hit_get_ejectVector,		NULL},
							{"reflectVector",		js_proj_hit_get_reflectVector,		NULL},
							{0}};

/* =======================================================

      Create Object
      
======================================================= */

void script_add_proj_hit_object(JSObject *parent_obj)
{
	script_create_child_object(parent_obj,"hit",&proj_hit_class,proj_hit_props,NULL);
}

/* =======================================================

      Getters Utilities
      
======================================================= */

int js_get_proj_hit_type(proj_type *proj)
{
	map_mesh_poly_type	*poly;

		// check auto hits
		
	if (proj->action.hit_tick!=0) {
		if ((proj->start_tick+proj->action.hit_tick)<=js.time.current_tick) return(sd_proj_hit_type_auto);
	}

		// object or projectile hits

    if (proj->contact.obj_uid!=-1) return(sd_proj_hit_type_object);
	if (proj->contact.proj_uid!=-1) return(sd_proj_hit_type_projectile);
	if (proj->contact.melee) return(sd_proj_hit_type_melee);

		// map hits
		// we use wall like flag to determine if
		// it's a wall hit, and floor/ceiling
		// hits by proximity to projectile Y

	if (proj->contact.hit_poly.mesh_idx==-1) return(sd_proj_hit_type_none);
	
	poly=&map.mesh.meshes[proj->contact.hit_poly.mesh_idx].polys[proj->contact.hit_poly.poly_idx];
	if (poly->box.wall_like) return(sd_proj_hit_type_wall);
	
	if (proj->pnt.y>poly->box.mid.y) return(sd_proj_hit_type_ceiling);

	return(sd_proj_hit_type_floor);
}

void js_get_proj_hit_name(proj_type *proj,int hit_type,char *name)
{
	obj_type			*hit_obj;
	proj_type			*hit_proj;
	proj_setup_type		*hit_proj_setup;
	
	switch (hit_type) {
	
		case sd_proj_hit_type_object:
			hit_obj=object_find_uid(proj->contact.obj_uid);
			strcpy(name,hit_obj->name);
			return;
		
		case sd_proj_hit_type_projectile:
			hit_proj=projectile_find_uid(proj->contact.proj_uid);
			hit_proj_setup=proj_setups_find_uid(hit_proj->proj_setup_uid);
			strcpy(name,hit_proj_setup->name);
			return;
		
		default:
			name[0]=0x0;
			return;
			
	}
}

void js_get_proj_hit_material_name(proj_type *proj,int hit_type,char *name)
{
	int					mesh_idx;
	map_mesh_poly_type	*mesh_poly;
	texture_type		*texture;

		// get hit poly

	mesh_idx=proj->contact.hit_poly.mesh_idx;
	if (mesh_idx==-1) {
		name[0]=0x0;
		return;
	}

	mesh_poly=&map.mesh.meshes[mesh_idx].polys[proj->contact.hit_poly.poly_idx];
	
		// get material name

	texture=&map.textures[mesh_poly->txt_idx];
	strcpy(name,texture->material_name);
}

/* =======================================================

      Getters
      
======================================================= */

JSBool js_proj_hit_get_type(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	proj_type			*proj;

	proj=proj_get_attach();
	if (proj==NULL) return(JS_TRUE);

	*vp=INT_TO_JSVAL(js_get_proj_hit_type(proj));
	
	return(JS_TRUE);
}

JSBool js_proj_hit_get_name(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	int					hit_type;
	char				hit_name[name_str_len];
	proj_type			*proj;

	proj=proj_get_attach();
	if (proj==NULL) return(JS_TRUE);

	hit_type=js_get_proj_hit_type(proj);
	js_get_proj_hit_name(proj,hit_type,hit_name);
	*vp=script_string_to_value(hit_name);
	
	return(JS_TRUE);
}

JSBool js_proj_hit_get_id(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	proj_type			*proj;

	proj=proj_get_attach();
	if (proj==NULL) return(JS_TRUE);

	*vp=INT_TO_JSVAL(proj->contact.obj_uid);
	
	return(JS_TRUE);
}

JSBool js_proj_hit_get_isPlayer(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	proj_type			*proj;

	proj=proj_get_attach();
	if (proj==NULL) return(JS_TRUE);

	*vp=BOOLEAN_TO_JSVAL(proj->contact.obj_uid==server.player_obj_uid);
	
	return(JS_TRUE);
}

JSBool js_proj_hit_get_startTick(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	proj_type			*proj;

	proj=proj_get_attach();
	if (proj==NULL) return(JS_TRUE);

	*vp=INT_TO_JSVAL(proj->start_tick);
	
	return(JS_TRUE);
}

JSBool js_proj_hit_get_materialName(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	int					hit_type;
	char				hit_name[name_str_len];
	proj_type			*proj;

	proj=proj_get_attach();
	if (proj==NULL) return(JS_TRUE);

	hit_type=js_get_proj_hit_type(proj);
	js_get_proj_hit_material_name(proj,hit_type,hit_name);
	*vp=script_string_to_value(hit_name);
	
	return(JS_TRUE);
}

JSBool js_proj_hit_get_ejectVector(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	d3vct				vct;
	proj_type			*proj;

	proj=proj_get_attach();
	if (proj==NULL) return(JS_TRUE);

	projectile_eject_vector(proj,&vct);
	*vp=script_angle_to_value(vct.x,vct.y,vct.z);
	
	return(JS_TRUE);
}

JSBool js_proj_hit_get_reflectVector(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	d3vct				vct;
	proj_type			*proj;

	proj=proj_get_attach();
	if (proj==NULL) return(JS_TRUE);

	projectile_reflect_vector(proj,&vct);
	*vp=script_angle_to_value(vct.x,vct.y,vct.z);
	
	return(JS_TRUE);
}

