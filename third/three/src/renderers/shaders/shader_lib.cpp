#include <iostream>
#include <fstream>
#include <sstream>

#include "./shader_lib.h"



static const char *DEFAULT_VERTEX = 
    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec3 normal;\n"
    "out vec3 frag_normal;\n"
    "out vec3 frag_position;\n"
    "uniform mat4 model_matrix;\n"
    "uniform mat4 model_view_matrix;\n"
    "uniform mat4 projection_matrix;\n"
    "uniform mat4 normal_matrix;\n"
    "void main()\n"
    "{\n"
    "  \n"
    "  gl_Position = projection_matrix * model_view_matrix * vec4(position, 1.0);\n"
    "  frag_position = (model_matrix * vec4(position, 1.0)).xyz;\n"
    "  frag_normal = normal;\n"
    "}";
    
static const char *DEFAULT_FRAGMENT = 
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "  \n"
    "  FragColor = vec4(1.0,0.0,0.0, 1.0);\n"
    "}";
    
static const char *MESH_BASIC_VERTEX = 
    "#include <color_pars_vertex>\n"
    "void main()\n"
    "{\n"
    "  #include <color_vertex>\n"
    "  \n"
    "  #include <begin_vertex>\n"
    "  #include <project_vertex>\n"
    "}";
    
static const char *MESH_BASIC_FRAGMENT = 
    "out vec4 fragColor;\n"
    "uniform vec3 diffuse;\n"
    "uniform float opacity;\n"
    "#include <common>\n"
    "#include <color_pars_fragment>\n"
    "void main()\n"
    "{\n"
    "	vec4 diffuseColor = vec4(diffuse, opacity);\n"
    "	\n"
    "	#include <color_fragment>\n"
    "	ReflectedLight reflectedLight = ReflectedLight( vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ) );\n"
    "  \n"
    "	#ifdef USE_LIGHTMAP\n"
    "	#else\n"
    "		reflectedLight.indirectDiffuse = vec3(1.0);\n"
    "	#endif\n"
    "		reflectedLight.indirectDiffuse *= diffuseColor.rgb;\n"
    "	vec3 outgoingLight = reflectedLight.indirectDiffuse;\n"
    "	#include <output_fragment>\n"
    "}";
    
static const char *MESH_LAMBERT_VERTEX = 
    "out vec3 vViewPosition;\n"
    "#include <common>\n"
    "#include <color_pars_vertex>\n"
    "#include <normal_pars_vertex>\n"
    "void main()\n"
    "{\n"
    "  #include <color_vertex>\n"
    "  #include <beginnormal_vertex>\n"
    "	#include <defaultnormal_vertex>\n"
    "	#include <normal_vertex>\n"
    "  #include <begin_vertex>\n"
    "  #include <project_vertex>\n"
    "  vViewPosition = -mvPosition.xyz;\n"
    "}";
    
static const char *MESH_LAMBERT_FRAGMENT = 
    "out vec4 fragColor;\n"
    "uniform vec3 diffuse;\n"
    "uniform vec3 emissive;\n"
    "uniform float opacity;\n"
    "#include <common>\n"
    "#include <color_pars_fragment>\n"
    "#include <bsdfs>\n"
    "#include <lights_pars_begin>\n"
    "#include <normal_pars_fragment>\n"
    "#include <lights_lambert_pars_fragment>\n"
    "void main() {\n"
    "	vec4 diffuseColor = vec4( diffuse, opacity );\n"
    "	ReflectedLight reflectedLight = ReflectedLight( vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ) );\n"
    "	vec3 totalEmissiveRadiance = emissive;\n"
    "	#include <color_fragment>\n"
    "	#include <normal_fragment_begin>\n"
    "	#include <lights_lambert_fragment>\n"
    "	#include <lights_fragment_begin>\n"
    "	#include <lights_fragment_end>\n"
    "	vec3 outgoingLight = reflectedLight.directDiffuse + reflectedLight.indirectDiffuse + totalEmissiveRadiance;\n"
    "	#include <output_fragment>\n"
    "}";
    
static const char *MESH_PHONG_VERTEX = 
    "out vec3 vViewPosition;\n"
    "#include <common>\n"
    "#include <color_pars_vertex>\n"
    "#include <normal_pars_vertex>\n"
    "void main()\n"
    "{\n"
    "  #include <color_vertex>\n"
    "  #include <beginnormal_vertex>\n"
    "	#include <defaultnormal_vertex>\n"
    "	#include <normal_vertex>\n"
    "  #include <begin_vertex>\n"
    "  #include <project_vertex>\n"
    "  vViewPosition = -mvPosition.xyz;\n"
    "}";
    
static const char *MESH_PHONG_FRAGMENT = 
    "out vec4 fragColor;\n"
    "uniform vec3 diffuse;\n"
    "uniform vec3 emissive;\n"
    "uniform vec3 specular;\n"
    "uniform float shininess;\n"
    "uniform float opacity;\n"
    "#include <common>\n"
    "#include <color_pars_fragment>\n"
    "#include <bsdfs>\n"
    "#include <lights_pars_begin>\n"
    "#include <normal_pars_fragment>\n"
    "#include <lights_phong_pars_fragment>\n"
    "#include <specularmap_pars_fragment>\n"
    "void main() {\n"
    "	vec4 diffuseColor = vec4( diffuse, opacity );\n"
    "	ReflectedLight reflectedLight = ReflectedLight( vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ), vec3( 0.0 ) );\n"
    "	vec3 totalEmissiveRadiance = emissive;\n"
    "	#include <color_fragment>\n"
    "	#include <specularmap_fragment>\n"
    "	#include <normal_fragment_begin>\n"
    "	#include <lights_phong_fragment>\n"
    "	#include <lights_fragment_begin>\n"
    "	#include <lights_fragment_end>\n"
    "	vec3 outgoingLight = reflectedLight.directDiffuse + reflectedLight.indirectDiffuse + reflectedLight.directSpecular + reflectedLight.indirectSpecular + totalEmissiveRadiance;\n"
    "	#include <output_fragment>\n"
    "}";
    
static const char *POINTS_VERTEX = 
    "uniform float size;\n"
    "uniform float scale;\n"
    "#include <common>\n"
    "#include <color_pars_vertex>\n"
    "void main() {\n"
    "  #include <color_vertex>\n"
    "	\n"
    "	#include <begin_vertex>\n"
    "	#include <project_vertex>\n"
    "	gl_PointSize = size;\n"
    "	#include <worldpos_vertex>\n"
    "}";
    
static const char *POINTS_FRAGMENT = 
    "out vec4 fragColor;\n"
    "uniform vec3 diffuse;\n"
    "uniform float opacity;\n"
    "#include <common>\n"
    "#include <color_pars_fragment>\n"
    "void main() {\n"
    "	vec3 outgoingLight = vec3( 0.0 );\n"
    "	vec4 diffuseColor = vec4( diffuse, opacity );\n"
    "	#include <color_fragment>\n"
    "	\n"
    "	outgoingLight = diffuseColor.rgb;\n"
    "	#include <output_fragment>\n"
    "}";
    

static const std::map<ShaderLib::ID,Shader> shader_lib_map = {
	{ ShaderLib::DEFAULT, Shader{ DEFAULT_VERTEX ,DEFAULT_FRAGMENT} } ,
	{ ShaderLib::MESH_BASIC, Shader{ MESH_BASIC_VERTEX ,MESH_BASIC_FRAGMENT} } ,
	{ ShaderLib::MESH_LAMBERT, Shader{ MESH_LAMBERT_VERTEX ,MESH_LAMBERT_FRAGMENT} } ,
	{ ShaderLib::MESH_PHONG, Shader{ MESH_PHONG_VERTEX ,MESH_PHONG_FRAGMENT} } ,
	{ ShaderLib::POINTS, Shader{ POINTS_VERTEX ,POINTS_FRAGMENT} }
};




Shader ShaderLib::Get(ID id)
{
	auto iter = shader_lib_map.find(id);

	if(iter != shader_lib_map.end())
	{
		return iter->second;
	}
	else
	{	
		std::cerr << __FILE__ << ":" << __LINE__ << "invalid shader id: " << id << std::endl;
		return Shader();
	}
	
}