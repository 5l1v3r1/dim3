/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: Script: weap.altAmmo object

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

extern js_type				js;

JSBool js_weap_alt_ammo_get_clip(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_get_count(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_get_initCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_get_maxCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_get_clipCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_get_initClipCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_get_maxClipCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_get_lastReloadTick(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_set_clip(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_set_count(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_set_initCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_set_maxCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_set_clipCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_set_initClipCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_set_maxClipCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_weap_alt_ammo_use_ammo_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval);
JSBool js_weap_alt_ammo_add_ammo_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval);
JSBool js_weap_alt_ammo_change_clip_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval);

JSClass			weap_alt_ammo_class={"weap_alt_ammo_class",0,
							script_add_property,JS_PropertyStub,
							JS_PropertyStub,JS_PropertyStub,
							JS_EnumerateStub,JS_ResolveStub,JS_ConvertStub,JS_FinalizeStub};

script_js_property	weap_alt_ammo_props[]={
							{"clip",				js_weap_alt_ammo_get_clip,				js_weap_alt_ammo_set_clip},
							{"count",				js_weap_alt_ammo_get_count,				js_weap_alt_ammo_set_count},
							{"initCount",			js_weap_alt_ammo_get_initCount,			js_weap_alt_ammo_set_initCount},
							{"maxCount",			js_weap_alt_ammo_get_maxCount,			js_weap_alt_ammo_set_maxCount},
							{"clipCount",			js_weap_alt_ammo_get_clipCount,			js_weap_alt_ammo_set_clipCount},
							{"initClipCount",		js_weap_alt_ammo_get_initClipCount,		js_weap_alt_ammo_set_initClipCount},
							{"maxClipCount",		js_weap_alt_ammo_get_maxClipCount,		js_weap_alt_ammo_set_maxClipCount},
							{"lastReloadTick",		js_weap_alt_ammo_get_lastReloadTick,	NULL},
							{0}};
							
script_js_function	weap_alt_ammo_functions[]={
							{"useAmmo",				js_weap_alt_ammo_use_ammo_func,			1},
							{"addAmmo",				js_weap_alt_ammo_add_ammo_func,			1},
							{"changeClip",			js_weap_alt_ammo_change_clip_func,		0},
							{0}};

/* =======================================================

      Create Object
      
======================================================= */

void script_add_weap_alt_ammo_object(JSObject *parent_obj)
{
	script_create_child_object(parent_obj,"altAmmo",&weap_alt_ammo_class,weap_alt_ammo_props,weap_alt_ammo_functions);
}

/* =======================================================

      Getters
      
======================================================= */

JSBool js_weap_alt_ammo_get_clip(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;

	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;
	
	*vp=BOOLEAN_TO_JSVAL(alt_ammo->use_clips);
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_get_count(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;

	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	if (weap->dual.in_dual) {
		*vp=INT_TO_JSVAL(alt_ammo->count_dual);
	}
	else {
		*vp=INT_TO_JSVAL(alt_ammo->count);
	}
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_get_initCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;

	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	*vp=INT_TO_JSVAL(alt_ammo->init_count);
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_get_maxCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;

	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	*vp=INT_TO_JSVAL(alt_ammo->max_count);
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_get_clipCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;

	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	*vp=INT_TO_JSVAL(alt_ammo->clip_count);
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_get_initClipCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;

	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	*vp=INT_TO_JSVAL(alt_ammo->init_clip_count);
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_get_maxClipCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;

	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	*vp=INT_TO_JSVAL(alt_ammo->max_clip_count);
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_get_lastReloadTick(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;

	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;
	
	if (weap->dual.in_dual) {
		*vp=INT_TO_JSVAL(alt_ammo->last_reload_dual_tick);
	}
	else {
		*vp=INT_TO_JSVAL(alt_ammo->last_reload_tick);
	}
	
	return(JS_TRUE);
}

/* =======================================================

      Setters
      
======================================================= */

JSBool js_weap_alt_ammo_set_clip(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;
	
	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;
	
	alt_ammo->use_clips=JSVAL_TO_BOOLEAN(*vp);
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_set_count(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;
	
	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	if (weap->dual.in_dual) {
		alt_ammo->count_dual=JSVAL_TO_INT(*vp);
	}
	else {
		alt_ammo->count=JSVAL_TO_INT(*vp);
	}
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_set_initCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;
	
	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	alt_ammo->init_count=JSVAL_TO_INT(*vp);
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_set_maxCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;
	
	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	alt_ammo->max_count=JSVAL_TO_INT(*vp);
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_set_clipCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;
	
	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	alt_ammo->clip_count=JSVAL_TO_INT(*vp);
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_set_initClipCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;
	
	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	alt_ammo->init_clip_count=JSVAL_TO_INT(*vp);
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_set_maxClipCount(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;
	
	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	alt_ammo->max_clip_count=JSVAL_TO_INT(*vp);
	
	return(JS_TRUE);
}

/* =======================================================

      Alternate Ammo Functions
      
======================================================= */

JSBool js_weap_alt_ammo_use_ammo_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval)
{
	int				count;
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;
	
	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	count=JSVAL_TO_INT(argv[0]);
	
	*rval=JSVAL_FALSE;
	
	if (weap->dual.in_dual) {
		if (alt_ammo->count_dual>=count) {
			alt_ammo->count_dual-=count;
			*rval=JSVAL_TRUE;
		}
	}
	else {
		if (alt_ammo->count>=count) {
			alt_ammo->count-=count;
			*rval=JSVAL_TRUE;
		}
	}
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_add_ammo_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval)
{
	int				add;
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;
	
	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;
	
	add=JSVAL_TO_INT(argv[0]);
	
	*rval=JSVAL_TRUE;

	if (weap->dual.in_dual) {
		if (alt_ammo->count_dual==alt_ammo->max_count) {
			*rval=JSVAL_FALSE;
		}
		else {
			alt_ammo->count_dual+=add;
			if (alt_ammo->count_dual>alt_ammo->max_count) alt_ammo->count_dual=alt_ammo->max_count;
		}
	}
	else {
		if (alt_ammo->count==alt_ammo->max_count) {
			*rval=JSVAL_FALSE;
		}
		else {
			alt_ammo->count+=add;
			if (alt_ammo->count>alt_ammo->max_count) alt_ammo->count=alt_ammo->max_count;
		}
	}
	
	return(JS_TRUE);
}

JSBool js_weap_alt_ammo_change_clip_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval)
{
	obj_type		*obj;
	weapon_type		*weap;
	weap_ammo_type	*alt_ammo;
	
	weap=weapon_find_uid(js.attach.thing_uid);
	alt_ammo=&weap->alt_ammo;

	obj=object_find_uid(weap->obj_uid);
	
		// is this a clip based weapon and enough clips?
		
	if ((!alt_ammo->use_clips) || (alt_ammo->clip_count==0)) {
		*rval=JSVAL_FALSE;
		return(JS_TRUE);
	}
	
		// change the clip
		
	if (weap->dual.in_dual) {
		alt_ammo->count_dual=alt_ammo->max_count;
		alt_ammo->last_reload_dual_tick=js.time.current_tick;
	}
	else {
		alt_ammo->count=alt_ammo->max_count;
		alt_ammo->last_reload_tick=js.time.current_tick;
	}
	
	alt_ammo->clip_count--;
	
		// alert object of clip change
		
	scripts_post_event_console(&obj->attach,sd_event_weapon_fire,sd_event_weapon_fire_clip_change,0);
	
	*rval=JSVAL_TRUE;
	return(JS_TRUE);
}


