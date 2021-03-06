/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: Scripts Run

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

#include "projectiles.h"
#include "scripts.h"

extern js_type				js;

/* =======================================================

      Run Scripts
      
======================================================= */

void scripts_run(int tick)
{
	js.time.current_tick=tick;					// internal script tick
	
	if (tick<js.time.timer_tick) return;				// scripts run 10 times a second
	
	while (tick>=js.time.timer_tick) {
		js.time.timer_tick+=100;
		
			// run timers
			
		timers_run();
		
            // dispose projectiles killed in timers

		projectile_dispose();
	}
}

