/****************************** File *********************************

Module: dim3 Animator
Author: Brian Barnes
 Usage: Nudge/Rotate Dialog

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

(c) 2000-2006 Klink! Software www.klinksoftware.com
 
*********************************************************************/

#include "dialog.h"

#define kXValue						FOUR_CHAR_CODE('xxxx')
#define kZValue						FOUR_CHAR_CODE('zzzz')
#define kYValue						FOUR_CHAR_CODE('yyyy')

bool					dialog_nudge_rotate_cancel;
WindowRef				dialog_nudge_rotate_wind;

/* =======================================================

      Nudge/Rotate Event Handlers
      
======================================================= */

static pascal OSStatus nudge_rotate_event_proc(EventHandlerCallRef handler,EventRef event,void *data)
{
	HICommand		cmd;
	
	switch (GetEventKind(event)) {
	
		case kEventProcessCommand:
			GetEventParameter(event,kEventParamDirectObject,typeHICommand,NULL,sizeof(HICommand),NULL,&cmd);
			
			switch (cmd.commandID) {
			
				case kHICommandOK:
					QuitAppModalLoopForWindow(dialog_nudge_rotate_wind);
					return(noErr);
					
				case kHICommandCancel:
					dialog_nudge_rotate_cancel=TRUE;
					QuitAppModalLoopForWindow(dialog_nudge_rotate_wind);
					return(noErr);
			}

			return(eventNotHandledErr);
	
	}
	
	return(eventNotHandledErr);
}

/* =======================================================

      Run Nudge/Rotate Dialog
      
======================================================= */

bool dialog_nudge_rotate_run(int *x,int *z,int *y,char *diag_name,int def_value)
{
	EventHandlerUPP					event_upp;
	EventTypeSpec					event_list[]={{kEventClassCommand,kEventProcessCommand}};
	
		// open the dialog
		
	dialog_open(&dialog_nudge_rotate_wind,diag_name);
	
		// setup the controls
		
	dialog_set_int(dialog_nudge_rotate_wind,kXValue,0,def_value);
	dialog_set_int(dialog_nudge_rotate_wind,kZValue,0,def_value);
	dialog_set_int(dialog_nudge_rotate_wind,kYValue,0,def_value);
	
		// show window
	
	ShowWindow(dialog_nudge_rotate_wind);
	
		// install event handler
		
	event_upp=NewEventHandlerUPP(nudge_rotate_event_proc);
	InstallWindowEventHandler(dialog_nudge_rotate_wind,event_upp,GetEventTypeCount(event_list),event_list,NULL,NULL);
	
		// modal window
		
	dialog_nudge_rotate_cancel=FALSE;
	
	RunAppModalLoopForWindow(dialog_nudge_rotate_wind);
	
	if (!dialog_nudge_rotate_cancel) {
		*x=dialog_get_int(dialog_nudge_rotate_wind,kXValue,0);
		*z=dialog_get_int(dialog_nudge_rotate_wind,kZValue,0);
		*y=dialog_get_int(dialog_nudge_rotate_wind,kYValue,0);
	}
	
		// close window

	DisposeWindow(dialog_nudge_rotate_wind);
	
	return(!dialog_nudge_rotate_cancel);
}

