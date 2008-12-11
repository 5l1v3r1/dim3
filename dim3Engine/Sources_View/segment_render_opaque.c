/****************************** File *********************************

Module: dim3 Engine
Author: Brian Barnes
 Usage: Opaque Segment Rendering

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

#include "effects.h"
#include "consoles.h"
#include "video.h"

extern int				hilite_mode;

extern map_type			map;
extern server_type		server;
extern setup_type		setup;
extern camera_type		camera;
extern view_type		view;

extern int game_time_get(void);
extern bool fog_solid_on(void);
extern void view_compile_gl_list_attach(void);
extern void view_compile_gl_list_switch_to_color(void);
extern void view_compile_gl_list_switch_to_normal(void);
extern void view_compile_gl_list_dettach(void);

/* =======================================================

      Opaque Map Normal Textures
      
======================================================= */

void render_opaque_portal_normal(int mesh_cnt,int *mesh_list,int stencil_pass,bool is_fog_lighting)
{
	int					n,k,frame;
	map_mesh_type		*mesh;
	map_mesh_poly_type	*poly;
	texture_type		*texture;

		// setup drawing
		// if we are in fog lighting, then we need to
		// skip the mesh lighting and light by vertex

	glDisable(GL_BLEND);
	
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL,0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);

	glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);

	gl_texture_opaque_start(is_fog_lighting);
	
		// run through the meshes

	for (n=0;n!=mesh_cnt;n++) {

		mesh=&map.mesh.meshes[mesh_list[n]];

			// does this mesh have polys in the
			// stencil pass?

		if ((stencil_pass<mesh->draw.stencil_pass_start) || (stencil_pass>mesh->draw.stencil_pass_end)) continue;

			// run through the polys

		poly=mesh->polys;

		for (k=0;k!=mesh->npoly;k++) {

				// in stencil pass?

			if (poly->draw.stencil_pass!=stencil_pass) {
				poly++;
				continue;
			}

				// get texture

			texture=&map.textures[poly->txt_idx];
			if (texture->shader.on) {
				poly++;
				continue;
			}
			
			frame=(texture->animate.current_frame+poly->draw.txt_frame_offset)&max_texture_frame_mask;
			
				// setup texture

			gl_texture_opaque_set(texture->bitmaps[frame].gl_id);
			glStencilFunc(GL_ALWAYS,poly->draw.stencil_idx,0xFF);

				// draw polygon

			glDrawElements(GL_POLYGON,poly->ptsz,GL_UNSIGNED_INT,(GLvoid*)poly->draw.portal_v);
			
			poly++;
		}
	}

		// end drawing

	gl_texture_opaque_end();
}

/* =======================================================

      Opaque Map Bumping
      
======================================================= */

void render_opaque_portal_bump(int mesh_cnt,int *mesh_list,int stencil_pass,bool is_fog_lighting)
{
	int					n,k,frame;
	map_mesh_type		*mesh;
	map_mesh_poly_type	*poly;
	texture_type		*texture;

		// need to use normal map in color array

	view_compile_gl_list_switch_to_normal();

		// setup drawing

	glEnable(GL_BLEND);
	glBlendFunc(GL_ZERO,GL_SRC_COLOR);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);

	gl_texture_opaque_tesseled_bump_start();
	
		// run through the meshes

	for (n=0;n!=mesh_cnt;n++) {

		mesh=&map.mesh.meshes[mesh_list[n]];

			// does this mesh have polys in the
			// stencil pass?

		if ((stencil_pass<mesh->draw.stencil_pass_start) || (stencil_pass>mesh->draw.stencil_pass_end)) continue;

			// skip meshes without bumps

		if (!mesh->flag.has_bump) continue;

			// if hilite is on or this mesh is
			// hilited, then we need to clear the stencil
			// here as there will be no lighting pass

		if ((mesh->flag.hilite) || (hilite_mode==hilite_mode_hilite) || (is_fog_lighting)) {
			glStencilOp(GL_KEEP,GL_KEEP,GL_ZERO);
		}
		else {
			glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
		}

			// run through the polys

		poly=mesh->polys;

		for (k=0;k!=mesh->npoly;k++) {

				// in stencil pass?

			if (poly->draw.stencil_pass!=stencil_pass) {
				poly++;
				continue;
			}

				// get texture

			texture=&map.textures[poly->txt_idx];
			if (texture->shader.on) {
				poly++;
				continue;
			}

			frame=(texture->animate.current_frame+poly->draw.txt_frame_offset)&max_texture_frame_mask;

				// bump texture set?

			if (texture->bumpmaps[frame].gl_id==-1) {
				poly++;
				continue;
			}
			
				// blend in the bump

			gl_texture_opaque_tesseled_bump_set(texture->bumpmaps[frame].gl_id);
			glStencilFunc(GL_EQUAL,poly->draw.stencil_idx,0xFF);

				// draw either by lighting mesh or simple polygon

			if (poly->light.simple_tessel) {
				glDrawElements(GL_POLYGON,poly->ptsz,GL_UNSIGNED_INT,(GLvoid*)poly->draw.portal_v);
			}
			else {
				glDrawElements(GL_QUADS,(poly->light.nquad<<2),GL_UNSIGNED_INT,(GLvoid*)(mesh->light.quad_vertex_idx+poly->light.quad_offset));
			}

			poly++;
		}
	}

		// end drawing

	gl_texture_opaque_tesseled_bump_end();

		// restore original color array

	view_compile_gl_list_switch_to_color();
}

/* =======================================================

      Opaque Map Lighting
      
======================================================= */

void render_opaque_portal_lighting(int mesh_cnt,int *mesh_list,int stencil_pass)
{
	int					n,k,frame;
	map_mesh_type		*mesh;
	map_mesh_poly_type	*poly;
	texture_type		*texture;

		// setup drawing

	glEnable(GL_BLEND);
	glBlendFunc(GL_ZERO,GL_SRC_COLOR);
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);

	gl_texture_tesseled_lighting_start();

		// run through the meshes

	for (n=0;n!=mesh_cnt;n++) {

		mesh=&map.mesh.meshes[mesh_list[n]];

			// does this mesh have polys in the
			// stencil pass?

		if ((stencil_pass<mesh->draw.stencil_pass_start) || (stencil_pass>mesh->draw.stencil_pass_end)) continue;

			// skip hilited polygons

		if (mesh->flag.hilite) continue;

			// run through the polys

		poly=mesh->polys;

		for (k=0;k!=mesh->npoly;k++) {

				// in stencil pass?

			if (poly->draw.stencil_pass!=stencil_pass) {
				poly++;
				continue;
			}

				// simple tessels only need the lighting
				// fix pass as they don't draw with a mesh

			if (poly->light.simple_tessel) {
				poly++;
				continue;
			}

				// get texture

			texture=&map.textures[poly->txt_idx];
			if (texture->shader.on) {
				poly++;
				continue;
			}

			frame=(texture->animate.current_frame+poly->draw.txt_frame_offset)&max_texture_frame_mask;
			
				// if no specular pass, then clear stencil here
				
			if (texture->specularmaps[frame].gl_id!=-1) {
				glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
			}
			else {
				glStencilOp(GL_KEEP,GL_KEEP,GL_ZERO);
			}

				// draw lighting

			gl_texture_tesseled_lighting_set(-1,poly->dark_factor);
			glStencilFunc(GL_EQUAL,poly->draw.stencil_idx,0xFF);
			glDrawElements(GL_QUADS,(poly->light.nquad<<2),GL_UNSIGNED_INT,(GLvoid*)(mesh->light.quad_vertex_idx+poly->light.quad_offset));

			poly++;
		}
	}

		// end drawing

	gl_texture_tesseled_lighting_end();
}

void render_opaque_portal_lighting_mesh_debug(int mesh_cnt,int *mesh_list,int stencil_pass)
{
	int					n,k;
	map_mesh_type		*mesh;
	map_mesh_poly_type	*poly;

		// setup drawing

	glDisable(GL_BLEND);
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);

	glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);

	glColor4f(1.0f,1.0f,1.0f,1.0f);

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

		// run through the meshes

	for (n=0;n!=mesh_cnt;n++) {

		mesh=&map.mesh.meshes[mesh_list[n]];

			// does this mesh have polys in the
			// stencil pass?

		if ((stencil_pass<mesh->draw.stencil_pass_start) || (stencil_pass>mesh->draw.stencil_pass_end)) continue;

			// skip hilited polygons

		if (mesh->flag.hilite) continue;

			// run through the polys

		poly=mesh->polys;

		for (k=0;k!=mesh->npoly;k++) {

				// in stencil pass?

			if (poly->draw.stencil_pass!=stencil_pass) {
				poly++;
				continue;
			}

				// draw lighting

			gl_texture_tesseled_lighting_set(-1,poly->dark_factor);
			glStencilFunc(GL_EQUAL,poly->draw.stencil_idx,0xFF);

				// draw either by lighting mesh or simple polygon

			if (poly->light.simple_tessel) {
				glDrawElements(GL_POLYGON,poly->ptsz,GL_UNSIGNED_INT,(GLvoid*)poly->draw.portal_v);
			}
			else {
				glDrawElements(GL_QUADS,(poly->light.nquad<<2),GL_UNSIGNED_INT,(GLvoid*)(mesh->light.quad_vertex_idx+poly->light.quad_offset));
			}

			poly++;
		}
	}

		// end drawing

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void render_opaque_portal_lighting_fix(int mesh_cnt,int *mesh_list,int stencil_pass)
{
	int					n,k;
	map_mesh_type		*mesh;
	map_mesh_poly_type	*poly;

		// this draws over the entire polygon
		// to catch any pixels that show up between the
		// tesselated quads

		// setup drawing

	glEnable(GL_BLEND);
	glBlendFunc(GL_ZERO,GL_SRC_COLOR);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);

	glStencilOp(GL_KEEP,GL_KEEP,GL_ZERO);

	gl_texture_tesseled_lighting_start();

		// run through the meshes

	for (n=0;n!=mesh_cnt;n++) {

		mesh=&map.mesh.meshes[mesh_list[n]];

			// does this mesh have polys in the
			// stencil pass?

		if ((stencil_pass<mesh->draw.stencil_pass_start) || (stencil_pass>mesh->draw.stencil_pass_end)) continue;

			// skip hilited polygons

		if (mesh->flag.hilite) continue;

			// run through the polys

		poly=mesh->polys;

		for (k=0;k!=mesh->npoly;k++) {

				// in stencil pass?

			if (poly->draw.stencil_pass!=stencil_pass) {
				poly++;
				continue;
			}

				// draw lighting

			gl_texture_tesseled_lighting_set(-1,poly->dark_factor);
			glStencilFunc(GL_EQUAL,poly->draw.stencil_idx,0xFF);

			glDrawElements(GL_POLYGON,poly->ptsz,GL_UNSIGNED_INT,(GLvoid*)poly->draw.portal_v);

			poly++;
		}
	}

		// end drawing

	gl_texture_tesseled_lighting_end();
}

/* =======================================================

      Opaque Map Speculars
      
======================================================= */

void render_opaque_portal_specular(int mesh_cnt,int *mesh_list,int stencil_pass)
{
	int					n,k,frame;
	map_mesh_type		*mesh;
	map_mesh_poly_type	*poly;
	texture_type		*texture;
	
		// setup drawing

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);

	gl_texture_tesseled_specular_start();
	
		// run through the meshes

	for (n=0;n!=mesh_cnt;n++) {

		mesh=&map.mesh.meshes[mesh_list[n]];

			// does this mesh have polys in the
			// stencil pass?

		if ((stencil_pass<mesh->draw.stencil_pass_start) || (stencil_pass>mesh->draw.stencil_pass_end)) continue;

			// skip hilited polygons
			// or meshes with no speculars

		if ((!mesh->flag.has_specular) || (mesh->flag.hilite)) continue;

			// run through the polys

		poly=mesh->polys;

		for (k=0;k!=mesh->npoly;k++) {

				// in stencil pass?

			if (poly->draw.stencil_pass!=stencil_pass) {
				poly++;
				continue;
			}

				// get texture

			texture=&map.textures[poly->txt_idx];
			if (texture->shader.on) {
				poly++;
				continue;
			}

			frame=(texture->animate.current_frame+poly->draw.txt_frame_offset)&max_texture_frame_mask;

				// specular texture set?

			if (texture->specularmaps[frame].gl_id==-1) {
				poly++;
				continue;
			}

				// draw specular

			gl_texture_tesseled_specular_set(texture->specularmaps[frame].gl_id);
			glStencilFunc(GL_EQUAL,poly->draw.stencil_idx,0xFF);

				// draw either by lighting mesh or simple polygon
				// if simple tessel, we need to keep the stencil around
				// as the lighting "fix" pass is the only pass

			if (poly->light.simple_tessel) {
				glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
				glDrawElements(GL_POLYGON,poly->ptsz,GL_UNSIGNED_INT,(GLvoid*)poly->draw.portal_v);
			}
			else {
				glStencilOp(GL_KEEP,GL_KEEP,GL_ZERO);
				glDrawElements(GL_QUADS,(poly->light.nquad<<2),GL_UNSIGNED_INT,(GLvoid*)(mesh->light.quad_vertex_idx+poly->light.quad_offset));
			}

			poly++;
		}
	}

		// end drawing

	gl_texture_tesseled_specular_end();
}

/* =======================================================

      Opaque Map Glows
      
======================================================= */

void render_opaque_portal_glow(int mesh_cnt,int *mesh_list)
{
	int					n,k,frame;
	map_mesh_type		*mesh;
	map_mesh_poly_type	*poly;
	texture_type		*texture;

		// setup drawing

	glDisable(GL_BLEND);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL,0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_EQUAL);
	glDepthMask(GL_FALSE);

	gl_texture_opaque_glow_start();
	
		// run through the meshes

	for (n=0;n!=mesh_cnt;n++) {

		mesh=&map.mesh.meshes[mesh_list[n]];

			// skip hilited meshes
			// or meshes with no glows

		if ((!mesh->flag.has_glow) || (mesh->flag.hilite)) continue;

			// run through the polys

		poly=mesh->polys;

		for (k=0;k!=mesh->npoly;k++) {

				// get texture

			texture=&map.textures[poly->txt_idx];
			if (texture->shader.on) {
				poly++;
				continue;
			}

			frame=(texture->animate.current_frame+poly->draw.txt_frame_offset)&max_texture_frame_mask;

				// glow maps happen outside of stenciling
				// so we need to check for transparencies here

			if ((texture->bitmaps[frame].alpha_mode==alpha_mode_transparent) || (poly->alpha!=1.0f)) {
				poly++;
				continue;
			}

				// glow texture set?

			if (texture->glowmaps[frame].gl_id==-1) {
				poly++;
				continue;
			}

			gl_texture_opaque_glow_set(texture->bitmaps[frame].gl_id,texture->glowmaps[frame].gl_id,texture->glow.current_color);

				// draw polygon

			glDrawElements(GL_POLYGON,poly->ptsz,GL_UNSIGNED_INT,(GLvoid*)poly->draw.portal_v);

			poly++;
		}
	}

		// end drawing

	gl_texture_opaque_glow_end();
}

/* =======================================================

      Opaque Map Shaders
      
======================================================= */

void render_opaque_portal_shader(int mesh_cnt,int *mesh_list)
{

	int					n,k,frame;
	map_mesh_type		*mesh;
	map_mesh_poly_type	*poly;
	texture_type		*texture;

		// setup drawing

	glDisable(GL_BLEND);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL,0);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);

	gl_shader_program_start(max_map_texture,map.textures);
	gl_texture_shader_start();
	
		// run through the meshes

	for (n=0;n!=mesh_cnt;n++) {

		mesh=&map.mesh.meshes[mesh_list[n]];

			// run through the polys

		poly=mesh->polys;

		for (k=0;k!=mesh->npoly;k++) {

				// get texture

			texture=&map.textures[poly->txt_idx];
			if (!texture->shader.on) {
				poly++;
				continue;
			}

			frame=(texture->animate.current_frame+poly->draw.txt_frame_offset)&max_texture_frame_mask;

				// shaders happen outside of stenciling
				// so we need to check for transparencies here

			if ((texture->bitmaps[frame].alpha_mode==alpha_mode_transparent) || (poly->alpha!=1.0f)) {
				poly++;
				continue;
			}

				// setup shader

			gl_texture_shader_set(texture->bitmaps[frame].gl_id,texture->bumpmaps[frame].gl_id,texture->specularmaps[frame].gl_id,texture->glowmaps[frame].gl_id);
			gl_shader_set_program(texture->shader.program_obj);
				
			gl_shader_set_variables(texture->shader.program_obj,&poly->box.mid,texture);

				// draw polygon

			glDrawElements(GL_POLYGON,poly->ptsz,GL_UNSIGNED_INT,(GLvoid*)poly->draw.portal_v);

			poly++;
		}
	}

		// end drawing

	gl_texture_shader_end();
	gl_shader_program_end();
}

/* =======================================================

      Opaque Map Stenciling Setup
      
======================================================= */

int render_opaque_mesh_stencil_mark(int mesh_cnt,int *mesh_list)
{
	int					n,k,frame,stencil_pass,stencil_idx;
	map_mesh_type		*mesh;
	map_mesh_poly_type	*poly;
	texture_type		*texture;

	stencil_pass=0;
	stencil_idx=stencil_poly_start;

	for (n=0;n!=mesh_cnt;n++) {

		mesh=&map.mesh.meshes[mesh_list[n]];
		mesh->draw.stencil_pass_start=stencil_pass;

		poly=mesh->polys;

		for (k=0;k!=mesh->npoly;k++) {

				// shaders and transparent polys won't be
				// drawing in these routines, so skip them
				// here so they won't be included in drawing 

			texture=&map.textures[poly->txt_idx];
			frame=(texture->animate.current_frame+poly->draw.txt_frame_offset)&max_texture_frame_mask;

			if ((texture->bitmaps[frame].alpha_mode==alpha_mode_transparent) || (poly->alpha!=1.0f) || (texture->shader.on)) {
				poly->draw.stencil_pass=-1;
			}

				// create stencil
				
			else {
			
				poly->draw.stencil_pass=stencil_pass;
				poly->draw.stencil_idx=stencil_idx;

				stencil_idx++;
				if (stencil_idx>stencil_poly_end) {
					stencil_idx=stencil_poly_start;
					stencil_pass++;
				}
			}
			
			poly++;
		}

		mesh->draw.stencil_pass_end=stencil_pass;
	}

	return(stencil_pass);
}

/* =======================================================

      Opaque Map Rendering
      
======================================================= */

void render_opaque_map(int mesh_cnt,int *mesh_list)
{
	int					stencil_pass,stencil_pass_cnt;
	bool				is_fog_lighting;
	
		// setup view

	gl_setup_viewport(console_y_offset());
	gl_3D_view(&view.camera);
	gl_3D_rotate(&view.camera.ang);
	gl_setup_project();

		// texture binding optimization

	gl_texture_bind_start();

		// detect obscuring fog lighting

	is_fog_lighting=fog_solid_on();

		// create stencil passes

	stencil_pass_cnt=render_opaque_mesh_stencil_mark(mesh_cnt,mesh_list);

		// attach map complied open gl list

	view_compile_gl_list_attach();
		
		// might need multiple passes to
		// get under stencil resolution limit

	glEnable(GL_STENCIL_TEST);

	for (stencil_pass=0;stencil_pass<=stencil_pass_cnt;stencil_pass++) {

		render_opaque_portal_normal(mesh_cnt,mesh_list,stencil_pass,is_fog_lighting);
		render_opaque_portal_bump(mesh_cnt,mesh_list,stencil_pass,is_fog_lighting);

		if (!is_fog_lighting) {
			
			switch (hilite_mode) {

				case hilite_mode_off:
					render_opaque_portal_lighting(mesh_cnt,mesh_list,stencil_pass);
					render_opaque_portal_specular(mesh_cnt,mesh_list,stencil_pass);
					render_opaque_portal_lighting_fix(mesh_cnt,mesh_list,stencil_pass);
					break;

				case hilite_mode_mesh:
					render_opaque_portal_lighting_mesh_debug(mesh_cnt,mesh_list,stencil_pass);
					glClear(GL_STENCIL_BUFFER_BIT);		// need to clear stencil since mesh lighting isn't drawing
					break;

			}

		}
	}

	glDisable(GL_STENCIL_TEST);

		// glow maps and shaders happen outside
		// of stenciling

	render_opaque_portal_glow(mesh_cnt,mesh_list);
	render_opaque_portal_shader(mesh_cnt,mesh_list);

		// dettach any attached lists

	view_compile_gl_list_dettach();

}

