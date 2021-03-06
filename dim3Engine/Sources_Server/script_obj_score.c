/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: Script: obj.score object

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

extern map_type			map;
extern js_type			js;

JSBool js_obj_score_get_kill(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_obj_score_get_death(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_obj_score_get_suicide(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_obj_score_get_goal(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_obj_score_get_score(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_obj_score_add_goal_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval);

JSClass			obj_score_class={"obj_score_class",0,
							script_add_property,JS_PropertyStub,
							JS_PropertyStub,JS_PropertyStub,
							JS_EnumerateStub,JS_ResolveStub,JS_ConvertStub,JS_FinalizeStub};

script_js_property	obj_score_props[]={
							{"kill",				js_obj_score_get_kill,				NULL},
							{"death",				js_obj_score_get_death,				NULL},
							{"suicide",				js_obj_score_get_suicide,			NULL},
							{"goal",				js_obj_score_get_goal,				NULL},
							{"score",				js_obj_score_get_score,				NULL},
							{0}};

script_js_function	obj_score_functions[]={
							{"addGoal",				js_obj_score_add_goal_func,			0},
							{0}};

/* =======================================================

      Create Object
      
======================================================= */

void script_add_obj_score_object(JSObject *parent_obj)
{
	script_create_child_object(parent_obj,"score",&obj_score_class,obj_score_props,obj_score_functions);
}

/* =======================================================

      Getters
      
======================================================= */

JSBool js_obj_score_get_kill(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	obj_type		*obj;

	obj=object_find_uid(js.attach.thing_uid);
	*vp=INT_TO_JSVAL(obj->score.kill);
	
	return(JS_TRUE);
}

JSBool js_obj_score_get_death(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	obj_type		*obj;

	obj=object_find_uid(js.attach.thing_uid);
	*vp=INT_TO_JSVAL(obj->score.death);
	
	return(JS_TRUE);
}

JSBool js_obj_score_get_suicide(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	obj_type		*obj;

	obj=object_find_uid(js.attach.thing_uid);
	*vp=INT_TO_JSVAL(obj->score.suicide);
	
	return(JS_TRUE);
}

JSBool js_obj_score_get_goal(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	obj_type		*obj;

	obj=object_find_uid(js.attach.thing_uid);
	*vp=INT_TO_JSVAL(obj->score.goal);
	
	return(JS_TRUE);
}

JSBool js_obj_score_get_score(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	obj_type		*obj;

	obj=object_find_uid(js.attach.thing_uid);
	*vp=INT_TO_JSVAL(obj->score.score);
	
	return(JS_TRUE);
}

/* =======================================================

      Functions
      
======================================================= */

JSBool js_obj_score_add_goal_func(JSContext *cx,JSObject *j_obj,uintN argc,jsval *argv,jsval *rval)
{
	obj_type		*obj;
	
	obj=object_find_uid(js.attach.thing_uid);
	object_score_goal(obj);

	return(JS_TRUE);
}




