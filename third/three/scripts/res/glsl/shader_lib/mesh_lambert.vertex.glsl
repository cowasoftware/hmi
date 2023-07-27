out vec3 vViewPosition;

#include <common>
#include <color_pars_vertex>
#include <normal_pars_vertex>

void main()
{
  #include <color_vertex>

  #include <beginnormal_vertex>
	#include <defaultnormal_vertex>
	#include <normal_vertex>

  #include <begin_vertex>
  #include <project_vertex>
  vViewPosition = -mvPosition.xyz;
}