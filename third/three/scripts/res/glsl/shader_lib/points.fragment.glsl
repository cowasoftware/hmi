out vec4 fragColor;

uniform vec3 diffuse;
uniform float opacity;

#include <common>
#include <color_pars_fragment>

void main() {

	vec3 outgoingLight = vec3( 0.0 );
	vec4 diffuseColor = vec4( diffuse, opacity );

	#include <color_fragment>
	
	outgoingLight = diffuseColor.rgb;

	#include <output_fragment>
}