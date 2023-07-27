out vec4 fragColor;

uniform vec3 diffuse;
uniform float opacity;

#include <common>
#include <color_pars_fragment>

void main()
{
	vec4 diffuseColor = vec4(diffuse, opacity);
	
	#include <color_fragment>

	ReflectedLight reflectedLight = ReflectedLight( vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ) );
  
	#ifdef USE_LIGHTMAP
	#else
		reflectedLight.indirectDiffuse = vec3(1.0);
	#endif
		reflectedLight.indirectDiffuse *= diffuseColor.rgb;

	vec3 outgoingLight = reflectedLight.indirectDiffuse;
	#include <output_fragment>
}