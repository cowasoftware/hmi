#include <cstring>
#include <sstream>
#include <map>
#include <regex>

#include <cppgl.h>

#include "../../utils/string_util.h"
#include "../shaders/shader_chunk.h"

#include "./program.h"
#include "./uniforms.h"
#include "./attributes.h"
#include "./binding_states.h"
#include "./logger.h"

namespace three::gl
{
	static size_t s_id = 0;
	static Logger logger;

	static auto CreateShader = [](cppgl::CppGL &gl, uint32_t type, std::string const &source)
	{
		uint32_t id = gl.CreateShader(type);
		const char *data = source.c_str();
		gl.ShaderSource(id, 1, &data, nullptr);
		gl.CompileShader(id);
		return id;
	};

	static auto FilterEmptyLine = [](std::string const &str)
	{
		return !str.empty() && str.find("//") == std::string::npos;
	};

	ProgramParameters::ProgramParameters()
		: shader_id(0),
		  precision(Precision::HIGHP),
		  use_instancing(false),
		  instancing_color(vec3(0.0f, 0.0f, 0.0f)),
		  custom_vertex_shader_id(0),
		  custom_fragment_shader_id(0),
		  opaque(true),
		  transmisson(false),
		  num_directional_lights(0),
		  num_point_lights(0),
		  num_spot_lights(0),
		  num_rectarea_lights(0),
		  num_hemi_lights(0),
		  glsl_version(""),
		  raw_shader_material(false),
		  support_vertex_textures(false),
		  use_map(false),
		  use_env_map(false),
		  use_light_map(false),
		  use_ao_map(false),
		  use_emissive_map(false),
		  use_bump_map(false),
		  use_normal_map(false),
		  use_specular_map(false),
		  use_specular_color_map(false),
		  use_roughness_map(false),
		  use_metalness_map(false),
		  use_alpha_map(false),
		  use_transmission(false),
		  use_transmission_map(false),
		  use_thickness_map(false),
		  use_sheen_color_map(false),
		  use_sheen_roughness_map(false),
		  use_vertex_colors(false),
		  use_vertex_alphas(false),
		  use_vertex_uvs(false)
	{
	}

	Program::Program(cppgl::CppGL &_gl, std::string const &_cache_key, ProgramParameters const &parameters, BindingStates &_binding_states)
		: gl(_gl),
		  cache_key(_cache_key),
		  binding_states(_binding_states),
		  handle(0),
		  cached_uniforms(nullptr),
		  cached_attributes(nullptr)
	{
		auto vertex_shader_glsl = GenerateVertexGLSL(parameters);
		auto vertex_shader = CreateShader(gl, cppgl::CPPGL_VERTEX_SHADER, vertex_shader_glsl);

		auto fragment_shader_glsl = GenerateFragmentGLSL(parameters);
		auto fragment_shader = CreateShader(gl, cppgl::CPPGL_FRAGMENT_SHADER, fragment_shader_glsl);

		handle = gl.CreateProgram();
		gl.AttachShader(handle, vertex_shader);
		gl.AttachShader(handle, fragment_shader);
		gl.LinkProgram(handle);
		gl.DeleteShader(vertex_shader);
		gl.DeleteShader(fragment_shader);

		auto vertex_log = GetShaderErrors(gl, vertex_shader, cppgl::CPPGL_VERTEX_SHADER);
		auto fragment_log = GetShaderErrors(gl, fragment_shader, cppgl::CPPGL_FRAGMENT_SHADER);
		auto program_log = GetProgramErrors(gl, handle);

		auto print_shader = [](std::string const &code, std::string const &type)
		{
			std::stringstream ss;
			auto lines = StringUtil::Split(code, "\n");
			for (int i = 0; i < lines.size(); i++)
			{
				ss << i + 1 << ":\t" << lines[i] << '\n';
			}

			logger.Debug("\n{}\n{}", type, ss.str());
		};

		if (!vertex_log.empty())
		{
			print_shader(vertex_shader_glsl, "vertex");
			throw std::logic_error(vertex_log);
		}

		if (!fragment_log.empty())
		{
			print_shader(fragment_shader_glsl, "fragment");
			throw std::logic_error(fragment_log);
		}

		if (!program_log.empty())
		{
			throw std::logic_error(program_log);
		}

		cached_uniforms = new Uniforms(gl, handle);
		cached_attributes = new Attributes(gl, handle);

		id = ++s_id;
		use_times = 1;
	}

	Program::~Program()
	{
		binding_states.ReleaseProgramStates(*this);
		delete cached_uniforms;
		delete cached_attributes;
		gl.DeleteProgram(handle);
	}

	Program::operator unsigned int()
	{
		return handle;
	}

	std::string Program::GenerateVertexGLSL(ProgramParameters const &parameters)
	{
		std::string version = parameters.glsl_version.empty() ? "" : "#version " + parameters.glsl_version + "\n";
		std::string prefix_vertex_glsl = "";
		std::string vertex_glsl = "";

		if (parameters.raw_shader_material)
		{
			std::vector<std::string> prefix_vertex_lines = {
				GenerateDefines(parameters.defines),
			};

			prefix_vertex_glsl = StringUtil::Join(prefix_vertex_lines, "\n", FilterEmptyLine);
		}
		else
		{
			// zinfo("use instanceing: %d", parameters.use_instancing);
			std::vector<std::string> prefix_vertex_lines = {
				GeneratePrecision(parameters.precision),
				GenerateDefines(parameters.defines),
				parameters.use_instancing ? "#define USE_INSTANCING" : "",
				// parameters.instancing ? "#define USE_INSTANCING_COLOR" : "",
				// parameters.support_vertex_textures ? "#define VERTEX_TEXTURES" : "",
				// parameters.use_map ? "#define USE_MAP" : "",
				// parameters.use_env_map ? "#define USE_ENVMAP" : "",
				// parameters.use_light_map ? "#define USE_LIGHTMAP" : "",
				// parameters.use_ao_map ? "#define USE_AOMAP" : "",
				// parameters.use_emissive_map ? "#define USE_EMISSIVEMAP" : "",
				// parameters.use_bump_map ? "#define USE_BUMPMAP" : "",
				// parameters.use_normal_map ? "#define USE_NORMALMAP" : "",
				// parameters.use_specular_map ? "#define USE_SPECULARMAP" : "",
				// parameters.use_specular_color_map ? "#define USE_SPECULARCOLORMAP" : "",
				// parameters.use_roughness_map ? "#define USE_ROUGHNESSMAP" : "",
				// parameters.use_metalness_map ? "#define USE_METALNESSMAP" : "",
				// parameters.use_alpha_map ? "#define USE_ALPHAMAP" : "",
				// parameters.use_transmission ? "#define USE_TRANSMISSION" : "",
				// parameters.use_transmission_map ? "#define USE_TRANSMISSIONMAP" : "",
				// parameters.use_thickness_map ? "#define USE_THICKNESSMAP" : "",
				// parameters.use_sheen_color_map ? "#define USE_SHEENCOLORMAP" : "",
				// parameters.use_sheen_roughness_map ? "#define USE_SHEENROUGHNESSMAP" : "",
				parameters.use_vertex_colors ? "#define USE_COLOR" : "",
				parameters.use_vertex_alphas ? "#define USE_COLOR_ALPHA" : "",
				// parameters.use_vertex_uvs ? "#define USE_UV" : "",
				GenerateAttributes(parameters),

				"uniform mat4 modelMatrix;",
				"uniform mat4 modelViewMatrix;",
				"uniform mat4 projectionMatrix;",
				"uniform mat4 viewMatrix;",
				"uniform mat3 normalMatrix;",
				"uniform vec3 cameraPosition;",
				"uniform bool isOrthographic;",
			};

			prefix_vertex_glsl = StringUtil::Join(prefix_vertex_lines, "\n", FilterEmptyLine);
		}
		vertex_glsl = ResolveIncludes(parameters.vertex_shader);
		vertex_glsl = ReplaceLightNums(vertex_glsl, parameters);
		return version + "\n" + prefix_vertex_glsl + "\n" + vertex_glsl;
	}

	std::string Program::GenerateFragmentGLSL(ProgramParameters const &parameters)
	{
		std::string version = parameters.glsl_version.empty() ? "" : "#version " + parameters.glsl_version + "\n";
		std::string prefix_fragment_glsl;
		std::string fragment_glsl;

		if (parameters.raw_shader_material)
		{
			std::vector<std::string> prefix_fragment_lines = {
				GenerateDefines(parameters.defines),
			};

			prefix_fragment_glsl = StringUtil::Join(prefix_fragment_lines, "\n");
		}
		else
		{
			std::vector<std::string> prefix_fragment_lines = {
				GeneratePrecision(parameters.precision),
				GenerateDefines(parameters.defines),
				parameters.use_instancing ? "#define USE_INSTANCING" : "",
				// parameters.instancing ? "#define USE_INSTANCING_COLOR" : "",
				// parameters.support_vertex_textures ? "#define VERTEX_TEXTURES" : "",
				// parameters.use_map ? "#define USE_MAP" : "",
				// parameters.use_env_map ? "#define USE_ENVMAP" : "",
				// parameters.use_light_map ? "#define USE_LIGHTMAP" : "",
				// parameters.use_ao_map ? "#define USE_AOMAP" : "",
				// parameters.use_emissive_map ? "#define USE_EMISSIVEMAP" : "",
				// parameters.use_bump_map ? "#define USE_BUMPMAP" : "",
				// parameters.use_normal_map ? "#define USE_NORMALMAP" : "",
				// parameters.use_specular_map ? "#define USE_SPECULARMAP" : "",
				// parameters.use_specular_color_map ? "#define USE_SPECULARCOLORMAP" : "",
				// parameters.use_roughness_map ? "#define USE_ROUGHNESSMAP" : "",
				// parameters.use_metalness_map ? "#define USE_METALNESSMAP" : "",
				// parameters.use_alpha_map ? "#define USE_ALPHAMAP" : "",
				// parameters.use_transmission ? "#define USE_TRANSMISSION" : "",
				// parameters.use_transmission_map ? "#define USE_TRANSMISSIONMAP" : "",
				// parameters.use_thickness_map ? "#define USE_THICKNESSMAP" : "",
				// parameters.use_sheen_color_map ? "#define USE_SHEENCOLORMAP" : "",
				// parameters.use_sheen_roughness_map ? "#define USE_SHEENROUGHNESSMAP" : "",
				parameters.use_vertex_colors ? "#define USE_COLOR" : "",
				parameters.use_vertex_alphas ? "#define USE_COLOR_ALPHA" : "",
				// parameters.use_vertex_uvs ? "#define USE_UV" : "",
				"uniform mat4 viewMatrix;",
				"uniform bool isOrthographic;",
			};
			auto filter = [](std::string const &str)
			{ return !str.empty(); };

			prefix_fragment_glsl = StringUtil::Join(prefix_fragment_lines, "\n", filter);
		}

		fragment_glsl = ResolveIncludes(parameters.fragment_shader);
		fragment_glsl = ReplaceLightNums(fragment_glsl, parameters);

		return version + "\n" + prefix_fragment_glsl + "\n" + fragment_glsl;
	}

	std::string Program::ToSource(Precision precision)
	{
		switch (precision)
		{
		case Precision::LOW:
			return "lowp";
		case Precision::MEDIUMP:
			return "mediump";
		case Precision::HIGHP:
			return "highp";
		default:
			// zwarn("Unsupport Precision: %d", (int)precision);
			return "";
		}
	}

	std::string Program::ToSource(ToneMapping mapping)
	{
		switch (mapping)
		{
		case ToneMapping::LINEAR:
			return "Linear";
			break;

		case ToneMapping::REINHARD:
			return "Reinhard";
			break;

		case ToneMapping::CINEON:
			return "OptimizedCineon";
			break;

		case ToneMapping::ACES_FILMIC:
			return "ACESFilmic";
			break;

		case ToneMapping::CUSTOM:
			return "Custom";
			break;

		default:
			// zwarn("Unsupported ToneMapping: %d", (int)mapping);
			return "";
		}
	}

	std::string Program::GetShaderErrors(cppgl::CppGL &gl, unsigned int shader, int type)
	{
		int success;
		char log[1024] = {0};
		gl.GetProgramiv(shader, cppgl::CPPGL_COMPILE_STATUS, &success);

		// if (!success)
		{
			gl.GetShaderInfoLog(shader, 1024, nullptr, log);
		}

		return log;
	}

	std::string Program::GetProgramErrors(cppgl::CppGL &gl, unsigned int program)
	{
		int success;
		char log[1024] = {0};
		gl.GetProgramiv(program, cppgl::CPPGL_LINK_STATUS, &success);

		if (success)
		{
			gl.GetProgramInfoLog(program, 1024, NULL, log);
		}

		return log;
	}

	std::string Program::GenerateTexelEncodingFunction(std::string const &name, TexelEncoding encoding)
	{
		std::stringstream ss;

		std::pair<std::string, std::string> value;
		switch (encoding)
		{
		case TexelEncoding::LINEAR:
			value = {"Linear", "( value )"};
			break;
		case TexelEncoding::SRGB:
			value = {"sRGB", "( value )"};
		default:
			// zwarn("Unsupport TexelEncoding: %d", (int)encoding);
			value = {"Linear", "( value )"};
			break;
		}
		ss << "vec4 " << name << "( vec4 value ) { return LinearTo" << value.first << value.second << "; }";
		return ss.str();
	}

	std::string Program::GenerateToneMappingFunction(std::string const &name, ToneMapping mapping)
	{
		std::stringstream ss;
		ss << " vec3 " << name << "(vec3 color) { return " + ToSource(mapping) << "ToneMapping( color ); }";
		return ss.str();
	}

	std::string Program::GenerateDefines(std::map<std::string, std::string> const &defines)
	{
		std::vector<std::string> strs;

		for (auto &define : defines)
		{
			strs.emplace_back("#define " + define.first + " " + define.second);
		}

		return StringUtil::Join(strs, "\n");
	}

	std::string Program::GenerateAttributes(ProgramParameters const &parameters)
	{
		std::vector<std::string> lines = {
			"vec3 position;",
			"vec3 normal;",
			parameters.use_vertex_uvs ? "ve2 uv;" : "",
			parameters.use_vertex_colors ? (parameters.use_vertex_alphas ? "vec4 color;" : "vec3 color;") : "",
			parameters.use_instancing ? "mat4 instanceMatrix;" : "",
		};

		std::stringstream ss;

		int index = 0;

		for (auto &line : lines)
		{
			if (!line.empty())
			{
				ss << "layout(location = " << index++ << ") in " << line << "\n";
			}
		}

		return ss.str();
	}

	std::string Program::GeneratePrecision(Precision precision)
	{
		std::stringstream ss;
		std::string str = ToSource(precision);

		ss << "precision " << str << " float;\nprecision " << str << " int;";

		switch (precision)
		{
		case Precision::HIGHP:
			ss << "\n#define HIGH_PRECISION";
			break;

		case Precision::MEDIUMP:
			ss << "\n#define MEDIUM_PRECISION";
			break;
		case Precision::LOW:
			ss << "\n#define LOW_PRECISION";
			break;
		}

		return ss.str();
	}

	std::string Program::ReplaceLightNums(std::string const &code, ProgramParameters const &parameters)
	{
		std::string result = code;
		std::stringstream ss;
		std::string substr;
		ss << parameters.num_directional_lights;
		substr = ss.str();
		result = std::regex_replace(result, std::regex("NUM_DIR_LIGHTS"), substr);

		ss.str("");
		ss << parameters.num_point_lights;
		substr = ss.str();
		result = std::regex_replace(result, std::regex("NUM_POINT_LIGHTS"), substr);

		ss.str("");
		ss << parameters.num_spot_lights;
		substr = ss.str();
		result = std::regex_replace(result, std::regex("NUM_SPOT_LIGHTS"), substr);

		ss.str("");
		ss << parameters.num_rectarea_lights;
		substr = ss.str();
		result = std::regex_replace(result, std::regex("NUM_RECT_AREA_LIGHTS"), substr);

		ss.str("");
		ss << parameters.num_hemi_lights;
		substr = ss.str();
		result = std::regex_replace(result, std::regex("NUM_HEMI_LIGHTS"), substr);

		return result;
	}

	std::string Program::ResolveIncludes(std::string code, int level)
	{

		auto replace_call = [level](std::sregex_iterator const &group)
		{
			std::string tab;
			tab.assign(level * 4, ' ');
			auto sub_code = tab + ShaderChunk::Get((*group)[1]);
			sub_code = StringUtil::Replace(sub_code, "\n", "\n" + tab);
			return ResolveIncludes(sub_code, level + 1);
		};

		return StringUtil::Replace(code, std::regex("[ \\t]*#include[ \\s]*<(\\w+)>"), replace_call);
	}

	std::map<std::string, ProgramAttribute *> *Program::FetchAttributeLocations(cppgl::CppGL &gl, uint32_t program)
	{
		auto &attributes = *new std::map<std::string, ProgramAttribute *>();

		int32_t n;
		gl.GetProgramiv(program, cppgl::CPPGL_ACTIVE_ATTRIBUTES, &n);

		// zinfo("attributes count: %d", n);
		char name[1024];
		int32_t length;
		int32_t size;
		uint32_t type;

		for (int i = 0; i < n; i++)
		{
			memset(name, 0, sizeof(name));
			gl.GetActiveAttrib(program, i, sizeof(name), &length, &size, &type, name);

			// zinfo("%d %s: %d, %d, %d", i, name, length, size, type);
		}

		return new std::map<std::string, ProgramAttribute *>();
	}

}
