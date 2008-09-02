/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: Script: weap.hand object

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
#include "weapons.h"

extern js_type			js;

JSBool js_get_weap_hand_property(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);
JSBool js_set_weap_hand_property(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp);

JSClass			weap_hand_class={"weap_hand_class",0,
							script_add_property,JS_PropertyStub,
							js_get_weap_hand_property,js_set_weap_hand_property,
							JS_EnumerateStub,JS_ResolveStub,JS_ConvertStub,JS_FinalizeStub};

JSPropertySpec	weap_hand_props[]={
							{"raiseTick",			weap_hand_prop_raise_tick,				JSPROP_PERMANENT|JSPROP_SHARED},
							{"lowerTick",			weap_hand_prop_lower_tick,				JSPROP_PERMANENT|JSPROP_SHARED},
							{"selectShift",			weap_hand_prop_select_shift,			JSPROP_PERMANENT|JSPROP_SHARED},
							{"bobSpeed",			weap_hand_prop_bob_speed,				JSPROP_PERMANENT|JSPROP_SHARED},
							{"bobAngle",			weap_hand_prop_bob_angle,				JSPROP_PERMANENT|JSPROP_SHARED},
							{0}};

/* =======================================================

      Create Object
      
======================================================= */

void script_add_weap_hand_object(JSObject *parent_obj)
{
    JSObject		*j_obj;

	j_obj=JS_DefineObject(js.cx,parent_obj,"hand",&weap_hand_class,NULL,0);
	JS_DefineProperties(js.cx,j_obj,weap_hand_props);
}

/* =======================================================

      Properties
      
======================================================= */

JSBool js_get_weap_hand_property(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;

	if (!JSVAL_IS_INT(id)) return(JS_TRUE);

	weap=weapon_find_uid(js.attach.thing_uid);
	
	switch (JSVAL_TO_INT(id)) {
	
		case weap_hand_prop_raise_tick:
			*vp=INT_TO_JSVAL(weap->hand.raise_tick);
			break;
		case weap_hand_prop_lower_tick:
			*vp=INT_TO_JSVAL(weap->hand.lower_tick);
			break;
		case weap_hand_prop_select_shift:
			*vp=INT_TO_JSVAL(weap->hand.select_shift);
			break;
		case weap_hand_prop_bob_speed:
			*vp=script_float_to_value(weap->hand.bounce_speed);
			break;
		case weap_hand_prop_bob_angle:
			*vp=script_float_to_value(weap->hand.bounce_ang);
			break;
			
	}
	
	return(JS_TRUE);
}

JSBool js_set_weap_hand_property(JSContext *cx,JSObject *j_obj,jsval id,jsval *vp)
{
	weapon_type		*weap;
	
	if (!JSVAL_IS_INT(id)) return(JS_TRUE);

	weap=weapon_find_uid(js.attach.thing_uid);
	
	switch (JSVAL_TO_INT(id)) {
	
		case weap_hand_prop_raise_tick:
			weap->hand.raise_tick=JSVAL_TO_INT(*vp);
			break;
		case weap_hand_prop_lower_tick:
			weap->hand.lower_tick=JSVAL_TO_INT(*vp);
			break;
		case weap_hand_prop_select_shift:
			weap->hand.select_shift=JSVAL_TO_INT(*vp);
			break;
		case weap_hand_prop_bob_speed:
			weap->hand.bounce_speed=script_value_to_float(*vp);
			break;
		case weap_hand_prop_bob_angle:
			weap->hand.bounce_ang=script_value_to_float(*vp);
			break;

	}
	
	return(JS_TRUE);
}



