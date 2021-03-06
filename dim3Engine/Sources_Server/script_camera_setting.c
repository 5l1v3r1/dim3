/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: Script: camera.setting object

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
#include "cameras.h"

extern camera_type		camera;
extern js_type			js;

JSBool js_camera_setting_get_type(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_camera_setting_get_attachObjectId(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_camera_setting_set_type(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_camera_setting_attach_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval);

JSClass			camera_setting_class={"camera_class",0,
							script_add_property,JS_PropertyStub,
							JS_PropertyStub,JS_PropertyStub,
							JS_EnumerateStub,JS_ResolveStub,JS_ConvertStub,JS_FinalizeStub};

script_js_property	camera_setting_props[]={
							{"type",				js_camera_setting_get_type,				js_camera_setting_set_type},
							{"attachObjectId",		js_camera_setting_get_attachObjectId,	NULL},
							{0}};

script_js_function	camera_setting_functions[]={
							{"attach",				js_camera_setting_attach_func,			1},
							{0}};

/* =======================================================

      Create Object
      
======================================================= */

void script_add_camera_setting_object(JSObject *parent_obj)
{
	script_create_child_object(parent_obj,"setting",&camera_setting_class,camera_setting_props,camera_setting_functions);
}

/* =======================================================

      Getters
      
======================================================= */

JSBool js_camera_setting_get_type(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	*vp=INT_TO_JSVAL(camera.mode+sd_camera_type_fpp);
	return(JS_TRUE);
}

JSBool js_camera_setting_get_attachObjectId(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	*vp=INT_TO_JSVAL(camera.obj_uid);
	return(JS_TRUE);
}

/* =======================================================

      Setters
      
======================================================= */

JSBool js_camera_setting_set_type(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	camera.mode=JSVAL_TO_INT(*vp)-sd_camera_type_fpp;
	return(JS_TRUE);
}

/* =======================================================

      State Function
      
======================================================= */

JSBool js_camera_setting_attach_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval)
{
	obj_type		*obj;

		// uid
	
	obj=script_find_obj_from_uid_arg(argv[0]);
	if (obj==NULL) return(JS_FALSE);

		// connect

	camera_connect(obj);

	return(JS_TRUE);
}
