/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: OpenGL Lights

***************************** License ********************************

This code can be freely used as long as these conditions are met:

1. This header, in its entirety, is kept with the code
2. This credit “Created with dim3 Technology” is given on a single
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

#include "lights.h"
#include "cameras.h"
#include "consoles.h"
#include "video.h"

extern map_type				map;
extern view_type			view;
extern setup_type			setup;

extern int					nlight,nlight_reduce,light_reduce_list[max_light_spot];
extern light_spot_type		lspot_cache[max_light_spot];

/* =======================================================

      Lights
      
======================================================= */

void gl_lights_start(void)
{
	GLfloat				glf[4];	

	glEnable(GL_LIGHTING);
	
		// enable colored materials for dark factor

	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

		// ambient lighting

	glf[0]=map.ambient.light_color.r+setup.gamma;
	glf[1]=map.ambient.light_color.g+setup.gamma;
	glf[2]=map.ambient.light_color.b+setup.gamma;
	glf[3]=1.0f;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,glf);
}

void gl_lights_end(void)
{
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
}


// supergumba -- use all lights version
// we will need to clean this up as it's way to slow
// this version does not consider the reduced list and is a lot slower

void gl_lights_build_from_reduced_light_list(d3pnt *pnt,bool *light_on)
{
	int						n,k,light_id,
							idx,cnt,sort_list[max_light_spot];
	float					f;
	double					d,dx,dy,dz,sort_dist[max_light_spot];
	light_spot_type			*lspot;
	GLfloat					glf[4];	

		// sort the light list

	cnt=0;

	for (n=0;n!=nlight;n++) {
		lspot=&lspot_cache[n];

			// get distance

		dx=(double)(lspot->pnt.x-pnt->x);
		dy=(double)(lspot->pnt.y-pnt->y);
		dz=(double)(lspot->pnt.z-pnt->z);

		d=sqrt((dx*dx)+(dy*dy)+(dz*dz));

			// find position in list (top is closest)

		idx=-1;
	
		for (k=0;k!=cnt;k++) {
			if (sort_dist[k]>d) {
				idx=k;
				break;
			}
		}
	
			// insert at end of list
			
		if (idx==-1) {
			sort_dist[cnt]=d;
			sort_list[cnt]=n;
			cnt++;
			continue;
		}
		
			// insert in list
			
		memmove(&sort_dist[idx+1],&sort_dist[idx],(sizeof(double)*(cnt-idx)));
		memmove(&sort_list[idx+1],&sort_list[idx],(sizeof(int)*(cnt-idx)));
		
		sort_dist[idx]=d;
		sort_list[idx]=n;
		
		cnt++;
	}
	
		// only use max_view_lights_per_poly lights per polygon
		
	for (n=0;n!=max_view_lights_per_poly;n++) {
		lspot=&lspot_cache[sort_list[n]];
		
		light_id=GL_LIGHT0+n;
		
			// null lights
			
		if (n>=cnt) {					// supergumba -- in future, we will need shaders for 1, 2, or 3 lights
			glDisable(light_id);
			
			glLightf(light_id,GL_CONSTANT_ATTENUATION,0.0f);
			glLightf(light_id,GL_LINEAR_ATTENUATION,0.0f);
			glLightf(light_id,GL_QUADRATIC_ATTENUATION,0.0f);

			light_on[n]=FALSE;
		}
		
			// regular lights
			
		else {
			glEnable(light_id);			// supergumba -- do this outside of this routine!
			
			glf[0]=(float)lspot->pnt.x;
			glf[1]=(float)lspot->pnt.y;
			glf[2]=(float)lspot->pnt.z;
			glf[3]=1.0f;
			glLightfv(light_id,GL_POSITION,glf);

			glLightf(light_id,GL_CONSTANT_ATTENUATION,0.0f);
			glLightf(light_id,GL_LINEAR_ATTENUATION,0.0f);

			f=(float)lspot->intensity;
			f=f*0.4f;
			f=f*f;
			glLightf(light_id,GL_QUADRATIC_ATTENUATION,(1.0f/f));

			glf[0]=lspot->col.r;
			glf[1]=lspot->col.g;
			glf[2]=lspot->col.b;
			glf[3]=1.0f;
			glLightfv(light_id,GL_AMBIENT,glf);
			glLightfv(light_id,GL_DIFFUSE,glf);
			glLightfv(light_id,GL_SPECULAR,glf);

			light_on[n]=TRUE;
		}
	}
}
