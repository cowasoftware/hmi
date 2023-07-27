uniform float size;
uniform float scale;

#include <common>
#include <color_pars_vertex>

void main() {
  #include <color_vertex>
	
	#include <begin_vertex>
	#include <project_vertex>

	gl_PointSize = size;

	#include <worldpos_vertex>

}