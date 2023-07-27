#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cppgl.h>

#ifdef __linux__
#include <GL/gl.h>
#endif

class GLUtil
{
public:
	static uint32_t createIndexBuffer(cppgl::CppGL &gl, std::vector<uint32_t> const &data, uint32_t usage = cppgl::CPPGL_STATIC_DRAW);
	static uint32_t createShader(cppgl::CppGL &gl, uint32_t type, std::string const &code);
	static uint32_t createProgram(cppgl::CppGL &gl, std::string const &vertex, std::string const &fragment);
	static uint32_t create2DTexture(cppgl::CppGL &gl, std::string const &file, uint32_t filter = cppgl::CPPGL_LINEAR, uint32_t wrap = cppgl::CPPGL_CLAMP_TO_EDGE);
	static uint32_t createCubeTexture(cppgl::CppGL &gl, std::vector<std::string> const &files, uint32_t filter = cppgl::CPPGL_LINEAR, uint32_t wrap = cppgl::CPPGL_CLAMP_TO_EDGE);

	template <typename T>
	static uint32_t createArrayBuffer(cppgl::CppGL &gl, std::vector<T> const &data, uint32_t usage = cppgl::CPPGL_STATIC_DRAW);
};

template <typename T>
uint32_t GLUtil::createArrayBuffer(cppgl::CppGL& gl, std::vector<T> const &data, uint32_t usage)
{
	uint32_t buffer = 0;

	gl.GenBuffers(1, &buffer);
	gl.BindBuffer(cppgl::CPPGL_ARRAY_BUFFER, buffer);
	gl.BufferData(cppgl::CPPGL_ARRAY_BUFFER, sizeof(T) * data.size(), data.data(), usage);
	gl.BindBuffer(cppgl::CPPGL_ARRAY_BUFFER, 0);

	return buffer;
}
