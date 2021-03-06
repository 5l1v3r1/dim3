/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: Script: model.animation object

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
#include "models.h"

JSBool js_model_animation_get_index(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_model_animation_get_currentAnimationName(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_model_animation_set_index(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_model_animation_start_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval);
JSBool js_model_animation_stop_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval);
JSBool js_model_animation_cancel_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval);
JSBool js_model_animation_change_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval);
JSBool js_model_animation_interrupt_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval);
JSBool js_model_animation_start_then_change_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval);
JSBool js_model_animation_fade_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval);

extern js_type			js;

JSClass			model_animation_class={"model_animation_class",0,
							script_add_property,JS_PropertyStub,
							JS_PropertyStub,JS_PropertyStub,
							JS_EnumerateStub,JS_ResolveStub,JS_ConvertStub,JS_FinalizeStub};

script_js_property	model_animation_props[]={
							{"index",					js_model_animation_get_index,					js_model_animation_set_index},
							{"currentAnimationName",	js_model_animation_get_currentAnimationName,	NULL},
							{0}};

script_js_function	model_animation_functions[]={
							{"start",					js_model_animation_start_func,					1},
							{"stop",					js_model_animation_stop_func,					0},
							{"cancel",					js_model_animation_cancel_func,					1},
							{"change",					js_model_animation_change_func,					1},
							{"interrupt",				js_model_animation_interrupt_func,				1},
							{"startThenChange",			js_model_animation_start_then_change_func,		2},
							{"fade",					js_model_animation_fade_func,					2},
							{0}};

extern model_draw* js_find_model_draw(JSObject *j_obj,bool is_child);

/* =======================================================

      Create Object
      
======================================================= */

void script_add_model_animation_object(JSObject *parent_obj)
{
	script_create_child_object(parent_obj,"animation",&model_animation_class,model_animation_props,model_animation_functions);
}

/* =======================================================

      Getters
      
======================================================= */

JSBool js_model_animation_get_index(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	model_draw			*draw;

	draw=js_find_model_draw(j_obj,TRUE);
	*vp=INT_TO_JSVAL(draw->script_animation_idx);

	return(JS_TRUE);
}

JSBool js_model_animation_get_currentAnimationName(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	char				name[64];
	model_draw			*draw;

	draw=js_find_model_draw(j_obj,TRUE);

	model_get_current_animation_name(draw,name);
	*vp=script_string_to_value(name);

	return(JS_TRUE);
}

/* =======================================================

      Setters
      
======================================================= */

JSBool js_model_animation_set_index(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	model_draw			*draw;

	draw=js_find_model_draw(j_obj,TRUE);

	draw->script_animation_idx=JSVAL_TO_INT(*vp);
	if ((draw->script_animation_idx<0) || (draw->script_animation_idx>=max_model_blend_animation)) draw->script_animation_idx=0;

	return(JS_TRUE);
}

/* =======================================================

      Model Animation Functions
      
======================================================= */

JSBool js_model_animation_start_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval)
{
	char			name[name_str_len];
	model_draw		*draw;
	
	draw=js_find_model_draw(j_obj,TRUE);

	script_value_to_string(argv[0],name,name_str_len);
	
	if (!model_start_animation(draw,name)) {
		JS_ReportError(js.cx,"Named animation does not exist: %s",name);
		return(JS_FALSE);
	}
	
	return(JS_TRUE);
}

JSBool js_model_animation_stop_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval)
{
	model_draw		*draw;
	
	draw=js_find_model_draw(j_obj,TRUE);
	
	model_stop_animation(draw);
	return(JS_TRUE);
}

JSBool js_model_animation_cancel_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval)
{
	char			name[name_str_len];
	model_draw		*draw;
	
	draw=js_find_model_draw(j_obj,TRUE);

	script_value_to_string(argv[0],name,name_str_len);
	if (!model_cancel_animation(draw,name)) {
		JS_ReportError(js.cx,"Named animation does not exist: %s",name);
		return(JS_FALSE);
	}
	
	return(JS_TRUE);
}

JSBool js_model_animation_change_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval)
{
	char			name[name_str_len];
	model_draw		*draw;
	
	draw=js_find_model_draw(j_obj,TRUE);

	script_value_to_string(argv[0],name,name_str_len);
	if (!model_change_animation(draw,name)) {
		JS_ReportError(js.cx,"Named animation does not exist: %s",name);
		return(JS_FALSE);
	}
	
	return(JS_TRUE);
}

JSBool js_model_animation_interrupt_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval)
{
	char			name[name_str_len];
	model_draw		*draw;
	
	draw=js_find_model_draw(j_obj,TRUE);

	script_value_to_string(argv[0],name,name_str_len);
	if (!model_interrupt_animation(draw,name)) {
		JS_ReportError(js.cx,"Named animation does not exist: %s",name);
		return(JS_FALSE);
	}
	
	return(JS_TRUE);
}

JSBool js_model_animation_start_then_change_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval)
{
	char			name[name_str_len];
	model_draw		*draw;
	
	draw=js_find_model_draw(j_obj,TRUE);

	script_value_to_string(argv[0],name,name_str_len);
	if (!model_start_animation(draw,name)) {
		JS_ReportError(js.cx,"Named animation does not exist: %s",name);
		return(JS_FALSE);
	}

	script_value_to_string(argv[1],name,name_str_len);
	if (!model_change_animation(draw,name)) {
		JS_ReportError(js.cx,"Named animation does not exist: %s",name);
		return(JS_FALSE);
	}

	return(JS_TRUE);
}

/* =======================================================

      Fades
      
======================================================= */

JSBool js_model_animation_fade_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval)
{
	model_draw		*draw;
	
	draw=js_find_model_draw(j_obj,TRUE);
	model_fade_start(draw,JSVAL_TO_INT(argv[1]),script_value_to_float(argv[0]));
	
	return(JS_TRUE);
}

