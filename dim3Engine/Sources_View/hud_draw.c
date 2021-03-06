/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: HUD Routines

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

#include "objects.h"
#include "remotes.h"
#include "consoles.h"
#include "interfaces.h"
#include "effects.h"
#include "video.h"
#include "sounds.h"

extern server_type			server;
extern view_type			view;
extern hud_type				hud;
extern setup_type			setup;
extern network_setup_type	net_setup;
extern render_info_type		render_info;

/* =======================================================

      Run HUD Item Fades
      
======================================================= */

bool hud_item_fade_run(int tick,hud_item_fade_type *fade,float *alpha)
{
	int			fade_tick;
	float		achg;

		// if fade not on then do nothing
	
	if (!fade->on) return(FALSE);
	
		// fade still on?
		
	fade_tick=tick-fade->start_tick;
	
	if (fade_tick>=(fade->fade_in_tick+fade->life_tick+fade->fade_out_tick)) {
		fade->on=FALSE;
		return(TRUE);
	}
	
	if (fade_tick>(fade->fade_in_tick+fade->life_tick)) {
		achg=1.0f-((float)(fade_tick-(fade->fade_in_tick+fade->life_tick))/(float)fade->fade_out_tick);
	}
	else {
		if (fade_tick>fade->fade_in_tick) {
			achg=1.0f;
		}
		else {
			achg=(float)fade_tick/(float)fade->fade_in_tick;
		}
	}
	
	*alpha=(*alpha)*achg;

	return(FALSE);
}

/* =======================================================

      Draw HUD Bitmaps
      
======================================================= */

void hud_bitmaps_draw(int tick)
{
	int							n,r,wrap_count,
								px[4],py[4],sx,sy,rx,ry,
								wid,high,repeat_count;
	float						gx,gy,gx2,gy2,g_size,alpha,cur_alpha;
	GLuint						cur_gl_id;
	d3col						tint,cur_tint,team_tint;
	hud_bitmap_type				*bitmap;
	obj_type					*obj;
	bitmap_type					*bitmap_data;
		
	cur_gl_id=-1;
	cur_alpha=1.0f;
	cur_tint.r=cur_tint.g=cur_tint.b=1.0f;
	
	obj=object_find_uid(server.player_obj_uid);
	object_get_tint(obj,&team_tint);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glColor4f(0.0f,0.0f,0.0f,1.0f);

	gl_texture_simple_start();
	
		// draw bitmaps
		
	for (n=0;n!=hud.count.bitmap;n++) {
		bitmap=&hud.bitmaps[n];
		if (!bitmap->show) continue;

			// flashing

		if (bitmap->flash) {
			if (((tick>>9)&0x1)==0x0) continue;		// half-second flash
		}
		
			// fading?
			
		alpha=bitmap->alpha;
		if (hud_item_fade_run(tick,&bitmap->fade,&alpha)) {
			bitmap->show=FALSE;			// a fade has turned off bitmap
			continue;
		}
		
			// tint
			
		if (!bitmap->team_tint) {
			tint.r=tint.g=tint.b=1.0f;
		}
		else {
			memmove(&tint,&team_tint,sizeof(d3col));
		}

            // get bitmap and position
			
		bitmap_data=view_images_get_bitmap(bitmap->image_idx);
            
		sx=bitmap->x;
		sy=bitmap->y;
		
		wid=bitmap->x_size;
		if (wid==-1) {
			wid=bitmap_data->wid;
		}
		high=bitmap->y_size;
		if (high==-1) {
			high=bitmap_data->high;
		}
		
			// setup images
			
		effect_image_animate_get_uv((tick-bitmap->show_tick),&bitmap->animate,&gx,&gy,&g_size);

            // flips
           
		if (!bitmap->flip_horz) {
			gx2=gx+g_size;
		}
		else {
			gx2=gx;
			gx+=g_size;
		}

		if (!bitmap->flip_vert) {
			gy2=gy+g_size;
		}
		else {
			gy2=gy;
			gy+=g_size;
		}

			// need to change texture?

		if ((cur_gl_id!=bitmap_data->gl_id) || (cur_alpha!=alpha) || (cur_tint.r!=tint.r) || (cur_tint.g!=tint.g) || (cur_tint.b!=tint.b)) {
			cur_gl_id=bitmap_data->gl_id;
			cur_alpha=alpha;
			memmove(&cur_tint,&tint,sizeof(d3col));
			gl_texture_simple_set(cur_gl_id,TRUE,tint.r,tint.g,tint.b,cur_alpha);
		}
		
			// find the repeat count
		
		if (bitmap->repeat.on) {
			repeat_count=bitmap->repeat.count;
			if (repeat_count<1) continue;
		}
		else {
			repeat_count=1;
		}

			// scale and rotate bitmap

		rx=sx+wid;
		ry=sy+high;

		px[0]=px[3]=sx;
		px[1]=px[2]=rx;

		py[0]=py[1]=sy;
		py[2]=py[3]=ry;

		if (bitmap->rot!=0.0f) rotate_2D_polygon(4,px,py,((sx+rx)>>1),((sy+ry)>>1),bitmap->rot);

		rx=bitmap->repeat.x_add;
		ry=bitmap->repeat.y_add;
		
		wrap_count=0;

			// draw bitmaps

		glBegin(GL_QUADS);

		for (r=0;r!=repeat_count;r++) {

				// quad

			glTexCoord2f(gx,gy);
			glVertex2i(px[0],py[0]);
			glTexCoord2f(gx2,gy);
			glVertex2i(px[1],py[1]);
			glTexCoord2f(gx2,gy2);
			glVertex2i(px[2],py[2]);
			glTexCoord2f(gx,gy2);
			glVertex2i(px[3],py[3]);
			
				// column wrapping repeats
				
			if (bitmap->repeat.col!=0) {
				px[0]+=rx;
				px[1]+=rx;
				px[2]+=rx;
				px[3]+=rx;

				wrap_count++;
				if (wrap_count==bitmap->repeat.col) {
					wrap_count=0;
					
					px[0]=px[3]=sx;
					px[1]=px[2]=sx+wid;

					py[0]+=ry;
					py[1]+=ry;
					py[2]+=ry;
					py[3]+=ry;
				}
			}
			
			else {
			
					// row wrapping repeats
					
				if (bitmap->repeat.row!=0) {
					py[0]+=ry;
					py[1]+=ry;
					py[2]+=ry;
					py[3]+=ry;

					wrap_count++;
					if (wrap_count==bitmap->repeat.row) {
						wrap_count=0;
						
						py[0]=py[1]=sy;
						py[2]=py[3]=sy+high;
						
						px[0]+=rx;
						px[1]+=rx;
						px[2]+=rx;
						px[3]+=rx;
					}
				}
				
					// regular repeats
					
				else {
					px[0]+=rx;
					px[1]+=rx;
					px[2]+=rx;
					px[3]+=rx;
					py[0]+=ry;
					py[1]+=ry;
					py[2]+=ry;
					py[3]+=ry;
				}
			}
		}
			
		glEnd();
	}
	
	gl_texture_simple_end();
}

/* =======================================================

      Draw HUD Text
      
======================================================= */

void hud_texts_fps(char *data)
{
	if (view.fps.total==0) {
		strcpy(data,"--.--");
	}
	else {
		if ((setup.lock_fps_refresh) && (view.fps.total>render_info.monitor_refresh_rate)) {
			sprintf(data,"%d.00",render_info.monitor_refresh_rate);
		}
		else {
			sprintf(data,"%.2f",view.fps.total);
		}
	}
}

void hud_texts_draw_return(int x,int y,int ysz,char *data,int just,d3col *col,float alpha)
{
	char			*c,*c2;
	
	c=data;
	
	while (*c!=0x0) {
		c2=strstr(c,"{r}");
		if (c2!=NULL) *c2=0x0;
		
		gl_text_draw(x,y,c,just,FALSE,col,alpha);
		
		if (c2==NULL) return;
		
		*c2='{';
		
		c=c2+3;
		y+=ysz;
	}
}

void hud_texts_draw(int tick)
{
	int				n,high,cur_size;
	float			alpha;
	hud_text_type  *text;

	cur_size=-1;

	text=hud.texts;
	
	for (n=0;n!=hud.count.text;n++) {

		if (text->show) {

				// time for a new text size?

			if (text->size!=cur_size) {
				cur_size=text->size;

				gl_text_start(cur_size);
				high=gl_text_get_char_height(cur_size);
			}

				// fading?
		
			alpha=text->alpha;
			if (hud_item_fade_run(tick,&text->fade,&alpha)) {
				text->show=FALSE;			// a fade has turned off bitmap
				continue;
			}

				// draw text

			if (text->fps) hud_texts_fps(text->data);

			if (text->has_return) {
				hud_texts_draw_return(text->x,text->y,high,text->data,text->just,&text->color,alpha);
			}
			else {
				gl_text_draw(text->x,text->y,text->data,text->just,FALSE,&text->color,alpha);
			}
		}

		text++;
	}
	
	gl_text_end();		// OK to call text_end without a text_start
}

/* =======================================================

      Draw HUD Bars
      
======================================================= */

void hud_bars_draw(void)
{
	int					n,lx,rx,ty,by,wid,high;
	d3col				fill_end_color;
	hud_bar_type		*bar;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
		// draw bars
		
	for (n=0;n!=hud.count.bar;n++) {
		bar=&hud.bars[n];
		if (!bar->show) continue;
		
			// find size
			
		wid=bar->x_size;
		high=bar->y_size;
		
		if (!bar->vert) {
			wid=(int)(((float)wid)*bar->value);
		}
		else {
			high=(int)(((float)high)*bar->value);
		}
		
			// find the color
			
		memmove(&fill_end_color,&bar->fill_end_color,sizeof(d3col));
		fill_end_color.r+=((bar->fill_end_color.r-bar->fill_start_color.r)*bar->value);
		fill_end_color.g+=((bar->fill_end_color.g-bar->fill_start_color.g)*bar->value);
		fill_end_color.b+=((bar->fill_end_color.b-bar->fill_start_color.b)*bar->value);
		
			// draw bar
			
		lx=bar->x;
		rx=lx+wid;
		by=bar->y+bar->y_size;
		ty=by-high;
			
		if (!bar->vert) {
			view_draw_next_vertex_object_2D_color_quad(lx,by,&bar->fill_start_color,lx,ty,&bar->fill_start_color,rx,ty,&fill_end_color,rx,by,&fill_end_color,bar->fill_alpha);
		}
		else {
			view_draw_next_vertex_object_2D_color_quad(lx,ty,&fill_end_color,rx,ty,&fill_end_color,rx,by,&bar->fill_start_color,lx,by,&bar->fill_start_color,bar->fill_alpha);
		}
		
			// draw outline
			
		if (bar->outline) {
		
			lx=bar->x;
			rx=lx+bar->x_size;
			ty=bar->y;
			by=ty+bar->y_size;
			
			glLineWidth((float)setup.screen.x_sz/(float)hud.scale_x);
			
			glColor4f(bar->outline_color.r,bar->outline_color.g,bar->outline_color.b,bar->outline_alpha);
			view_draw_next_vertex_object_2D_line_quad(lx,rx,ty,by);
			
			glLineWidth(1.0f);
		}
	}
}

/* =======================================================

      HUD Sounds
      
======================================================= */

void hud_click(void)
{
	int			buffer_idx;

	if (hud.click_sound[0]==0x0) return;
	
	buffer_idx=al_find_buffer(hud.click_sound);
	if (buffer_idx!=-1) al_play_source(buffer_idx,NULL,1,FALSE,FALSE,TRUE,FALSE);
}

/* =======================================================

      Draw HUD
      
======================================================= */

void hud_draw(int tick)
{
		// set up view
		
	gl_2D_view_interface();
	
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL,0);
	
	glDisable(GL_DEPTH_TEST);
	
		// draw the bitmaps, bars, and text
		
	hud_bitmaps_draw(tick);
	hud_bars_draw();
	hud_texts_draw(tick);
	
		// reset any color changes
		
	glColor4f(0.0f,0.0f,0.0f,1.0f);
}

