#pragma once

#include <string>
#include <map>
#include <functional>

namespace three
{
	class Material;
	class Texture;

	namespace gl
	{
		class Uniforms;
		class Program;

		class MaterialProperty
		{
		public:
			MaterialProperty();

		public:
			Uniforms *uniforms;
			Program *current_program;
			std::map<std::string, Program *> programs;
		};

		class Properties final
		{
		public:
			Properties();
			~Properties();

		public:
			MaterialProperty &Get(Material &material);

			void Remove(Material &material);

		private:
			std::map<Material *, MaterialProperty *> material_properties_;
		};

	}
}
