#include <cppgl.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace three::gl
{

	template <typename T>
	void Uniforms::SetValue(std::string const& name, T const& value)
	{
		auto iter = uniforms.find(name);

		if (iter == uniforms.end())
		{
			// zwarn("not exist uniform: %s", name.c_str());
			return;
		}

		auto& uniform = *static_cast<SimpleUniform<T> *>(iter->second.second);

		if constexpr (std::is_same<T, uint8_t>::value)
		{
			if (iter->second.first != cppgl::CPPGL_UNSIGNED_BYTE)
			{
				//zwarn("mismatch data type: %s", name.c_str());
			}
		}
		else if (std::is_same<T, int8_t>::value)
		{
			if (iter->second.first != cppgl::CPPGL_BYTE)
			{
				//zwarn("mismatch data type: %s", name.c_str());
			}
		}
		else if (std::is_same<T, uint16_t>::value)
		{
			if (iter->second.first != cppgl::CPPGL_UNSIGNED_SHORT)
			{
				//zwarn("mismatch data type: %s", name.c_str());
			}
		}
		else if (std::is_same<T, int16_t>::value)
		{
			if (iter->second.first != cppgl::CPPGL_SHORT)
			{
				// zwarn("mismatch data type: %s", name.c_str());
			}
		}
		else if (std::is_same<T, uint32_t>::value)
		{
			if (iter->second.first != cppgl::CPPGL_UNSIGNED_INT)
			{
				// zwarn("mismatch data type: %s", name.c_str());
			}
		}
		else if (std::is_same<T, int32_t>::value)
		{
			if (iter->second.first != cppgl::CPPGL_INT)
			{
				// zwarn("mismatch data type: %s", name.c_str());
			}
		}
		else if (std::is_same<T, float>::value)
		{
			if (iter->second.first != cppgl::CPPGL_FLOAT)
			{
				// zwarn("mismatch data type: %s", name.c_str());
			}
		}
		else if (std::is_same<T, vec2>::value)
		{
			if (iter->second.first != cppgl::CPPGL_FLOAT_VEC2)
			{
				// zwarn("mismatch data type: %s", name.c_str());
			}
		}
		else if (std::is_same<T, vec3>::value)
		{
			if (iter->second.first != cppgl::CPPGL_FLOAT_VEC3)
			{
				// zwarn("mismatch data type: %s", name.c_str());
			}
		}
		else if (std::is_same<T, vec4>::value)
		{
			if (iter->second.first != cppgl::CPPGL_FLOAT_VEC4)
			{
				// zwarn("mismatch data type: %s", name.c_str());
			}
		}
		else if (std::is_same<T, mat2>::value)
		{
			if (iter->second.first == cppgl::CPPGL_FLOAT_MAT2)
			{
				// zwarn("mismatch data type: %s", name.c_str());
			}
		}
		else if (std::is_same<T, mat3>::value)
		{
			if (iter->second.first != cppgl::CPPGL_FLOAT_MAT3)
			{
				// zwarn("mismatch data type: %s", name.c_str());
			}
		}
		else if (std::is_same<T, mat4>::value)
		{
			if (iter->second.first != cppgl::CPPGL_FLOAT_MAT4)
			{
				// zwarn("mismatch data type: %s", name.c_str());
			}
		}
		uniform.set(value);
	}
}