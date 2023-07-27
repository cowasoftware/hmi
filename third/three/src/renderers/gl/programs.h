#pragma once

#include <string>
#include <map>

#include "./program.h"

namespace cppgl
{
	class CppGL;
}

class Object;
class Scene;
class Material;

namespace three::gl
{
	class LightsState;
	class Extensions;
	class Capabilities;
	class BindingStates;
	class Program;
	class ShaderCache;

	class Programs final
	{
	public:
		Programs(cppgl::CppGL& gl, Extensions& extensions, Capabilities& capabilities, BindingStates& binding_states);
		~Programs();

	public:
		ProgramParameters MakeParameters(Material& mateiral, LightsState& lights, Object& object);
		std::string MakeProgramCacheKey(ProgramParameters& parameters);
		void GetUniforms(Material& material);
		Program* AcquireProgram(ProgramParameters& parameters, std::string const& cache_key);
		void ReleaseProgram(Program& program);
		void ReleaseShaderCache(Material& material);

	private:
		std::string MakeProgramCacheKeyParameters(ProgramParameters& parameters);
		std::string MakeProgramCacheKeyBooleans(ProgramParameters& parameters);
	private:
		cppgl::CppGL& gl;
		Extensions& extensions;
		Capabilities& capabilities;
		BindingStates& binding_states;

	private:
		ShaderCache* custom_shaders_;
		std::map<std::string, Program*> programs_;
	};

}
