#include <QDebug>
#include <stb_image.h>

#include "./gl_util.h"

uint32_t GLUtil::createIndexBuffer(cppgl::CppGL &gl, std::vector<uint32_t> const &data, uint32_t usage)
{
	uint32_t buffer = 0;

	gl.GenBuffers(1, &buffer);
	gl.BindBuffer(cppgl::CPPGL_ELEMENT_ARRAY_BUFFER, buffer);
	gl.BufferData(cppgl::CPPGL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * data.size(), data.data(), usage);
	gl.BindBuffer(cppgl::CPPGL_ELEMENT_ARRAY_BUFFER, 0);

	return buffer;
}

uint32_t GLUtil::createShader(cppgl::CppGL &gl, uint32_t type, std::string const &code)
{
	int success = cppgl::CPPGL_TRUE;

	auto shader = gl.CreateShader(type);
	auto glsl_data = code.c_str();
	gl.ShaderSource(shader, 1, &glsl_data, nullptr);
	gl.CompileShader(shader);
	gl.GetShaderiv(shader, cppgl::CPPGL_COMPILE_STATUS, &success);

	if (success == cppgl::CPPGL_FALSE)
	{
		char log[1024] = {0};
		gl.GetShaderInfoLog(shader, sizeof(log), NULL, log);
		gl.DeleteShader(shader);
		qDebug() << code.c_str();
		qDebug() << log;
		throw std::invalid_argument(log);
	}

	return shader;
}

uint32_t GLUtil::createProgram(cppgl::CppGL &gl, std::string const &vertex, std::string const &fragment)
{
	uint32_t program = 0;
	uint32_t vertex_shader = 0;
	uint32_t fragment_shader = 0;

	try
	{
		int success = cppgl::CPPGL_TRUE;
		vertex_shader = createShader(gl, cppgl::CPPGL_VERTEX_SHADER, vertex);
		fragment_shader = createShader(gl, cppgl::CPPGL_FRAGMENT_SHADER, fragment);
		program = gl.CreateProgram();
		gl.AttachShader(program, vertex_shader);
		gl.AttachShader(program, fragment_shader);
		gl.LinkProgram(program);
		gl.DeleteShader(vertex_shader);
		gl.DeleteShader(fragment_shader);
		gl.GetProgramiv(program, cppgl::CPPGL_LINK_STATUS, &success);

		vertex_shader = 0;
		fragment_shader = 0;

		if (success == cppgl::CPPGL_FALSE)
		{
			char log[1024] = {0};
			gl.GetProgramInfoLog(program, sizeof(log), nullptr, log);
			throw std::invalid_argument(log);
		}
	}
	catch (std::invalid_argument const &e)
	{
		if (vertex_shader)
			gl.DeleteShader(vertex_shader);
		if (fragment_shader)
			gl.DeleteShader(fragment_shader);
		if (program)
			gl.DeleteProgram(program);

		throw e;
	}

	return program;
}

uint32_t GLUtil::create2DTexture(cppgl::CppGL &gl, std::string const &file, uint32_t filter, uint32_t wrap)
{
	uint32_t texture = 0;

	gl.GenTextures(1, &texture);
	gl.BindTexture(cppgl::CPPGL_TEXTURE_2D, texture);

	// stbi_set_flip_vertically_on_load( true ) ;

	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char *data = nullptr;

	try
	{
		if ((data = stbi_load(file.c_str(), &width, &height, &channels, 0)) != nullptr)
		{
			if (channels == 3)
			{
				gl.TexImage2D(cppgl::CPPGL_TEXTURE_2D,
							 0, cppgl::CPPGL_RGB, width, height, 0, cppgl::CPPGL_RGB, cppgl::CPPGL_UNSIGNED_BYTE, data);
			}
			else if (channels == 4)
			{
				gl.TexImage2D(cppgl::CPPGL_TEXTURE_2D,
							 0, cppgl::CPPGL_RGBA, width, height, 0, cppgl::CPPGL_RGBA, cppgl::CPPGL_UNSIGNED_BYTE, data);
			}
			else
			{
				throw std::invalid_argument("unsupport image format: " + file);
			}
			gl.GenerateMipmap(cppgl::CPPGL_TEXTURE_2D);
			gl.TexParameteri(cppgl::CPPGL_TEXTURE_2D, cppgl::CPPGL_TEXTURE_WRAP_S, cppgl::CPPGL_REPEAT);
			gl.TexParameteri(cppgl::CPPGL_TEXTURE_2D, cppgl::CPPGL_TEXTURE_WRAP_T, cppgl::CPPGL_REPEAT);
			gl.TexParameteri(cppgl::CPPGL_TEXTURE_2D, cppgl::CPPGL_TEXTURE_MIN_FILTER, cppgl::CPPGL_LINEAR_MIPMAP_LINEAR);
			gl.TexParameteri(cppgl::CPPGL_TEXTURE_2D, cppgl::CPPGL_TEXTURE_MAG_FILTER, cppgl::CPPGL_LINEAR);
		}
		else
		{
			throw std::invalid_argument("nonexist image: " + file);
		}
	}
	catch (std::invalid_argument const &e)
	{
		if (data)
			stbi_image_free(data);
		if (texture)
			gl.DeleteTextures(1, &texture);
		throw e;
	}

	return texture;
}

uint32_t GLUtil::createCubeTexture(cppgl::CppGL &gl, std::vector<std::string> const &files, uint32_t filter, uint32_t wrap)
{
	uint32_t texture = 0;

	gl.GenTextures(1, &texture);
	gl.BindTexture(cppgl::CPPGL_TEXTURE_CUBE_MAP, texture);

	// stbi_set_flip_vertically_on_load( true ) ;

	int index = 0;
	for (auto &file : files)
	{
		int width = 0;
		int height = 0;
		int channels = 0;
		unsigned char *data = nullptr;

		try
		{
			if ((data = stbi_load(file.c_str(), &width, &height, &channels, 0)) != nullptr)
			{
				if (channels == 3)
				{
					gl.TexImage2D(cppgl::CPPGL_TEXTURE_CUBE_MAP_POSITIVE_X + index,
								 0, cppgl::CPPGL_RGB, width, height, 0, cppgl::CPPGL_RGB, cppgl::CPPGL_UNSIGNED_BYTE, data);
				}
				else if (channels == 4)
				{
					gl.TexImage2D(cppgl::CPPGL_TEXTURE_CUBE_MAP_POSITIVE_X + index,
								 0, cppgl::CPPGL_RGBA, width, height, 0, cppgl::CPPGL_RGBA, cppgl::CPPGL_UNSIGNED_BYTE, data);
				}
				else
				{
					throw std::invalid_argument("unsupport image format: " + file);
				}

				gl.TexParameteri(cppgl::CPPGL_TEXTURE_CUBE_MAP, cppgl::CPPGL_TEXTURE_MIN_FILTER, filter);
				gl.TexParameteri(cppgl::CPPGL_TEXTURE_CUBE_MAP, cppgl::CPPGL_TEXTURE_MAG_FILTER, filter);
				gl.TexParameteri(cppgl::CPPGL_TEXTURE_CUBE_MAP, cppgl::CPPGL_TEXTURE_WRAP_S, wrap);
				gl.TexParameteri(cppgl::CPPGL_TEXTURE_CUBE_MAP, cppgl::CPPGL_TEXTURE_WRAP_T, wrap);
				gl.TexParameteri(cppgl::CPPGL_TEXTURE_CUBE_MAP, cppgl::CPPGL_TEXTURE_WRAP_R, wrap);
			}
			else
			{
				throw std::invalid_argument("nonexist image: " + file);
			}

			index++;
		}
		catch (std::invalid_argument const &e)
		{
			if (data)
				stbi_image_free(data);
			if (texture)
				gl.DeleteTextures(1, &texture);
			throw e;
		}
	}

	return texture;
}