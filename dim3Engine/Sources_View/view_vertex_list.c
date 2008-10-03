/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: Map Vertex Lists

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

#include "lights.h"

extern map_type				map;
extern view_type			view;
extern setup_type			setup;

int							map_vertex_vbo_idx;

extern void view_next_vertex_object(void);
extern void view_bind_current_vertex_object(void);
extern void view_bind_specific_vertex_object(int vbo_cache_idx);
extern void view_unbind_current_vertex_object(void);
extern int view_lock_current_vertext_object(void);
extern void view_unlock_current_vertext_object(int vbo_cache_idx);

/* =======================================================

      Setup Light Change Cache
      
======================================================= */

bool view_compile_mesh_gl_list_init(void)
{
	int					n,k,t,cnt,sz;
	float				*pc,*pn;
	map_mesh_type		*mesh;
	map_mesh_poly_type	*poly;

	mesh=map.mesh.meshes;

	for (n=0;n!=map.mesh.nmesh;n++) {

			// light check starts not equal

		mesh->draw.nlight=-1;

			// memory for colors and normals

		poly=mesh->polys;
		
		for (k=0;k!=mesh->npoly;k++) {

				// number of vertexes

			cnt=poly->ptsz+poly->light.nvertex;

				// get memory

			sz=(cnt*3)*sizeof(float);

			poly->draw.p_color=(float*)valloc(sz);
			if (poly->draw.p_color==NULL) return(FALSE);

			poly->draw.p_normal=(float*)valloc(sz);
			if (poly->draw.p_normal==NULL) return(FALSE);

				// clear to default values

			pc=poly->draw.p_color;
			pn=poly->draw.p_normal;

			for (t=0;t!=cnt;t++) {
				*pc++=1.0f;
				*pc++=1.0f;
				*pc++=1.0f;
				*pn++=0.5f;
				*pn++=0.5f;
				*pn++=1.0f;
			}

			poly++;
		}

		mesh++;
	}

	return(TRUE);
}

void view_compile_mesh_gl_list_free(void)
{
	int					n,k;
	map_mesh_type		*mesh;
	map_mesh_poly_type	*poly;

	mesh=map.mesh.meshes;

	for (n=0;n!=map.mesh.nmesh;n++) {

		poly=mesh->polys;
		
		for (k=0;k!=mesh->npoly;k++) {
			free(poly->draw.p_color);
			free(poly->draw.p_normal);
			poly++;
		}

		mesh++;
	}
}

/* =======================================================

      Calculate Polygon Lighting
      
======================================================= */

void view_compile_mesh_gl_lists_poly_normal(map_mesh_type *mesh,map_mesh_poly_type *poly)
{
	int									n;
	float								*pc,*pn;
	d3pnt								*pnt;
	map_mesh_poly_tessel_vertex_type	*lv;

	pc=poly->draw.p_color;
	pn=poly->draw.p_normal;

	for (n=0;n!=poly->ptsz;n++) {
		pnt=&mesh->vertexes[poly->v[n]];
		map_calculate_light_color_normal((double)pnt->x,(double)pnt->y,(double)pnt->z,pc,pn);
		pc+=3;
		pn+=3;
	}

		// tesseled lighting vertexes

	lv=poly->light.vertexes;

	for (n=0;n!=poly->light.nvertex;n++) {
		map_calculate_light_color_normal((double)lv->x,(double)lv->y,(double)lv->z,pc,pn);
		pc+=3;
		pn+=3;
		lv++;
	}
}

void view_compile_mesh_gl_lists_poly_ray_trace(map_mesh_type *mesh,map_mesh_poly_type *poly)
{
	int									n;
	float								*pc,*pn;
	d3pnt								*pnt;
	map_mesh_poly_tessel_vertex_type	*lv;

	pc=poly->draw.p_color;
	pn=poly->draw.p_normal;

	for (n=0;n!=poly->ptsz;n++) {
		pnt=&mesh->vertexes[poly->v[n]];
		map_calculate_ray_trace_light_color_normal((double)pnt->x,(double)pnt->y,(double)pnt->z,pc,pn);
		pc+=3;
		pn+=3;
	}

		// tesseled lighting vertexes

	lv=poly->light.vertexes;

	for (n=0;n!=poly->light.nvertex;n++) {
		map_calculate_ray_trace_light_color_normal((double)lv->x,(double)lv->y,(double)lv->z,pc,pn);
		pc+=3;
		pn+=3;
		lv++;
	}
}

/* =======================================================

      Compile OpenGL Lists MainLine
      
======================================================= */

bool view_compile_mesh_gl_lists(int tick,int mesh_cnt,int *mesh_list)
{
	int									n,k,t,sz,ntrig,cnt,
										v_count,v_idx,v_light_start_idx;
	float								fx,fy,fz;
	float								*vertex_ptr,*pv,*pp,*pc,*pn;
	bool								recalc_light;
	d3pnt								*pnt;
	map_mesh_type						*mesh;
	map_mesh_poly_type					*poly;
	map_mesh_poly_tessel_vertex_type	*lv;

		// no locked vbo yet
		
	map_vertex_vbo_idx=-1;
	
		// find total number of vertexes in
		// this seen

	v_count=0;

	for (n=0;n!=mesh_cnt;n++) {
		mesh=&map.mesh.meshes[mesh_list[n]];
		
		poly=mesh->polys;
		
		for (k=0;k!=mesh->npoly;k++) {
			v_count+=poly->ptsz;
			v_count+=poly->light.nvertex;
			poly++;
		}
		
		mesh++;
	}

	map.mesh_vertexes.draw_vertex_count=v_count;

		// get next VBO to use

	view_next_vertex_object();

		// map VBO to memory

	view_bind_current_vertex_object();

	sz=(map.mesh_vertexes.draw_vertex_count*(3+2+3+3))*sizeof(float);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB,sz,NULL,GL_STREAM_DRAW_ARB);

	vertex_ptr=(float*)glMapBufferARB(GL_ARRAY_BUFFER_ARB,GL_WRITE_ONLY_ARB);
	if (vertex_ptr==NULL) {
		view_unbind_current_vertex_object();
		return(FALSE);
	}
	
		// arrays and offsets

	map.mesh_vertexes.vert.sz=(v_count*3)*sizeof(float);
	map.mesh_vertexes.vert.offset=0;

	pv=vertex_ptr;

	map.mesh_vertexes.uv.sz=(v_count*2)*sizeof(float);
	map.mesh_vertexes.uv.offset=map.mesh_vertexes.vert.offset+map.mesh_vertexes.vert.sz;

	pp=pv+(v_count*3);

	map.mesh_vertexes.color.sz=(v_count*3)*sizeof(float);
	map.mesh_vertexes.color.offset=map.mesh_vertexes.uv.offset+map.mesh_vertexes.uv.sz;

	pc=pp+(v_count*2);

	map.mesh_vertexes.normal.sz=(v_count*3)*sizeof(float);
	map.mesh_vertexes.normal.offset=map.mesh_vertexes.color.offset+map.mesh_vertexes.color.sz;

	pn=pc+(v_count*3);

		// the eye offset

	fx=(float)view.camera.pnt.x;
	fy=(float)view.camera.pnt.y;
	fz=(float)view.camera.pnt.z;

	v_idx=0;
	
		// run throught the meshes

	for (n=0;n!=mesh_cnt;n++) {

		mesh=&map.mesh.meshes[mesh_list[n]];
		
			// calculate the lights touching
			// this mesh and find out if they need
			// to be recalculated

		map_calculate_light_reduce_mesh(mesh);
		recalc_light=!map_calculate_light_reduce_check_equal(mesh);
		map_calculate_light_reduce_save(mesh);

			// run through the polys

		poly=mesh->polys;
		
		for (k=0;k!=mesh->npoly;k++) {

				// calculate the vertex and mesh lighting

			if ((recalc_light) && (!mesh->flag.hilite)) {

				if (!setup.ray_trace_lighting) {
					view_compile_mesh_gl_lists_poly_normal(mesh,poly);
				}
				else {
					view_compile_mesh_gl_lists_poly_ray_trace(mesh,poly);
				}

			}

				// build the vertex, UV, color, and normal lists

			for (t=0;t!=poly->ptsz;t++) {
			
				pnt=&mesh->vertexes[poly->v[t]];

				*pv++=(((float)pnt->x)-fx);
				*pv++=(((float)pnt->y)-fy);
				*pv++=(fz-((float)pnt->z));
				
				*pp++=poly->gx[t]+poly->draw.x_shift_offset;
				*pp++=poly->gy[t]+poly->draw.y_shift_offset;
				
				poly->draw.portal_v[t]=v_idx;
				
				v_idx++;
			}

				// tesseled lighting vertexes

			v_light_start_idx=v_idx;
			lv=poly->light.vertexes;

			for (t=0;t!=poly->light.nvertex;t++) {

				*pv++=(((float)lv->x)-fx);
				*pv++=(((float)lv->y)-fy);
				*pv++=(fz-((float)lv->z));
				
				*pp++=lv->gx+poly->draw.x_shift_offset;
				*pp++=lv->gy+poly->draw.y_shift_offset;
				
				lv++;
				v_idx++;
			}

				// move over lighting and normal data

			cnt=(poly->ptsz+poly->light.nvertex)*3;
			sz=cnt*sizeof(float);

			if (!mesh->flag.hilite) memmove(pc,poly->draw.p_color,sz);
			memmove(pn,poly->draw.p_normal,sz);

			pc+=cnt;
			pn+=cnt;

				// create light mesh draw indexes by offset

			ntrig=poly->light.ntrig*3;

			for (t=0;t!=ntrig;t++) {
				poly->light.trig_vertex_draw_idx[t]=poly->light.trig_vertex_idx[t]+v_light_start_idx;
			}

			poly++;
		}
		
		mesh++;
	}

		// unmap VBO

	glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);

	view_unbind_current_vertex_object();
	
		// lock it so it won't be re-used until after
		// both the oqaque and transparent parts of the map
		// are rendered
		
	map_vertex_vbo_idx=view_lock_current_vertext_object();
	
	return(TRUE);
}

void view_release_mesh_gl_lists(void)
{
	if (map_vertex_vbo_idx!=-1) view_unlock_current_vertext_object(map_vertex_vbo_idx);
}

/* =======================================================

      Use Map OpenGL Lists
      
======================================================= */

void view_compile_gl_list_attach(void)
{
		// use last compiled buffer

	view_bind_specific_vertex_object(map_vertex_vbo_idx);

		// vertexes

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,(void*)map.mesh_vertexes.vert.offset);

		// uvs
		
	glClientActiveTexture(GL_TEXTURE2);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2,GL_FLOAT,0,(void*)map.mesh_vertexes.uv.offset);

	glClientActiveTexture(GL_TEXTURE1);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2,GL_FLOAT,0,(void*)map.mesh_vertexes.uv.offset);
	
	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2,GL_FLOAT,0,(void*)map.mesh_vertexes.uv.offset);

		// color array

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3,GL_FLOAT,0,(void*)map.mesh_vertexes.color.offset);
}

void view_compile_gl_list_switch_to_color(void)
{
	glColorPointer(3,GL_FLOAT,0,(void*)map.mesh_vertexes.color.offset);
}

void view_compile_gl_list_switch_to_normal(void)
{
	glColorPointer(3,GL_FLOAT,0,(void*)map.mesh_vertexes.normal.offset);
}

void view_compile_gl_list_dettach(void)
{
	glDisableClientState(GL_COLOR_ARRAY);

	glClientActiveTexture(GL_TEXTURE2);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTexture(GL_TEXTURE1);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTexture(GL_TEXTURE0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisableClientState(GL_VERTEX_ARRAY);

	view_unbind_current_vertex_object();
}
