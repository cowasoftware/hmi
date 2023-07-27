#include "cppgl.h"
#include <string>

namespace cppgl
{
	GLSLVersion CppGL::GetGLSLVersion()
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetGlSLVersion] is unimplemented, please implement it.");
		return GLSLVersion();
	}

	void CppGL::BindTexture(enumeration target, uint texture)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindTexture] is unimplemented, please implement it.");
	}

	void CppGL::BlendFunc(enumeration sfactor, enumeration dfactor)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BlendFunc] is unimplemented, please implement it.");
	}

	void CppGL::Clear(bitfield mask)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Clear] is unimplemented, please implement it.");
	}

	void CppGL::ClearColor(clampf red, clampf green, clampf blue, clampf alpha)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ClearColor] is unimplemented, please implement it.");
	}

	void CppGL::ClearStencil(int s)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ClearStencil] is unimplemented, please implement it.");
	}

	void CppGL::ColorMask(boolean red, boolean green, boolean blue, boolean alpha)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ColorMask] is unimplemented, please implement it.");
	}

	void CppGL::CopyTexImage2D(enumeration target, int level, enumeration internalformat, int x, int y, sizei width, sizei height, int border)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CopyTexImage2D] is unimplemented, please implement it.");
	}

	void CppGL::CopyTexSubImage2D(enumeration target, int level, int xoffset, int yoffset, int x, int y, sizei width, sizei height)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CopyTexSubImage2D] is unimplemented, please implement it.");
	}

	void CppGL::CullFace(enumeration mode)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CullFace] is unimplemented, please implement it.");
	}

	void CppGL::DeleteTextures(sizei n, const uint *textures)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DeleteTextures] is unimplemented, please implement it.");
	}

	void CppGL::DepthFunc(enumeration func)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DepthFunc] is unimplemented, please implement it.");
	}

	void CppGL::DepthMask(boolean flag)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DepthMask] is unimplemented, please implement it.");
	}

	void CppGL::Disable(enumeration cap)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Disable] is unimplemented, please implement it.");
	}

	void CppGL::DrawArrays(enumeration mode, int first, sizei count)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DrawArrays] is unimplemented, please implement it.");
	}

	void CppGL::DrawElements(enumeration mode, sizei count, enumeration type, const void *indices)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DrawElements] is unimplemented, please implement it.");
	}

	void CppGL::Enable(enumeration cap)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Enable] is unimplemented, please implement it.");
	}

	void CppGL::Finish()
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Finish] is unimplemented, please implement it.");
	}

	void CppGL::Flush()
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Flush] is unimplemented, please implement it.");
	}

	void CppGL::FrontFace(enumeration mode)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[FrontFace] is unimplemented, please implement it.");
	}

	void CppGL::GenTextures(sizei n, uint *textures)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GenTextures] is unimplemented, please implement it.");
	}

	void CppGL::GetBooleanv(enumeration pname, boolean *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetBooleanv] is unimplemented, please implement it.");
	}

	enumeration CppGL::GetError()
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetError] is unimplemented, please implement it.");
		return 0;
	}

	void CppGL::GetFloatv(enumeration pname, float *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetFloatv] is unimplemented, please implement it.");
	}

	void CppGL::GetIntegerv(enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetIntegerv] is unimplemented, please implement it.");
	}

	const ubyte *CppGL::GetString(enumeration name)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetString] is unimplemented, please implement it.");
		return nullptr;
	}

	void CppGL::GetTexParameterfv(enumeration target, enumeration pname, float *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetTexParameterfv] is unimplemented, please implement it.");
	}

	void CppGL::GetTexParameteriv(enumeration target, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetTexParameteriv] is unimplemented, please implement it.");
	}

	void CppGL::Hint(enumeration target, enumeration mode)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Hint] is unimplemented, please implement it.");
	}

	boolean CppGL::IsEnabled(enumeration cap)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsEnabled] is unimplemented, please implement it.");
		return false;
	}

	boolean CppGL::IsTexture(uint texture)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsTexture] is unimplemented, please implement it.");
		return false;
	}

	void CppGL::LineWidth(float width)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[LineWidth] is unimplemented, please implement it.");
	}

	void CppGL::PixelStorei(enumeration pname, int param)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[PixelStorei] is unimplemented, please implement it.");
	}

	void CppGL::PolygonOffset(float factor, float units)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[PolygonOffset] is unimplemented, please implement it.");
	}

	void CppGL::ReadPixels(int x, int y, sizei width, sizei height, enumeration format, enumeration type, void *pixels)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ReadPixels] is unimplemented, please implement it.");
	}

	void CppGL::Scissor(int x, int y, sizei width, sizei height)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Scissor] is unimplemented, please implement it.");
	}

	void CppGL::StencilFunc(enumeration func, int ref, uint mask)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[StencilFunc] is unimplemented, please implement it.");
	}

	void CppGL::StencilMask(uint mask)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[StencilMask] is unimplemented, please implement it.");
	}

	void CppGL::StencilOp(enumeration fail, enumeration zfail, enumeration zpass)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[StencilOp] is unimplemented, please implement it.");
	}

	void CppGL::TexImage2D(enumeration target, int level, int internalformat, sizei width, sizei height, int border, enumeration format, enumeration type, const void *pixels)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexImage2D] is unimplemented, please implement it.");
	}

	void CppGL::TexImage2DMultisample(enumeration target, sizei samples, int internalformat, sizei width, sizei height, bool fixedsamplelocations)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexImage2DMultisample] is unimplemented, please implement it.");
	}

	void CppGL::TexParameterf(enumeration target, enumeration pname, float param)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexParameterf] is unimplemented, please implement it.");
	}

	void CppGL::TexParameterfv(enumeration target, enumeration pname, const float *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexParameterfv] is unimplemented, please implement it.");
	}

	void CppGL::TexParameteri(enumeration target, enumeration pname, int param)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexParameteri] is unimplemented, please implement it.");
	}

	void CppGL::TexParameteriv(enumeration target, enumeration pname, const int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexParameteriv] is unimplemented, please implement it.");
	}

	void CppGL::TexSubImage2D(enumeration target, int level, int xoffset, int yoffset, sizei width, sizei height, enumeration format, enumeration type, const void *pixels)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexSubImage2D] is unimplemented, please implement it.");
	}

	void CppGL::Viewport(int x, int y, sizei width, sizei height)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Viewport] is unimplemented, please implement it.");
	}

	void CppGL::ActiveTexture(enumeration texture)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ActiveTexture] is unimplemented, please implement it.");
	}

	void CppGL::AttachShader(uint program, uint shader)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[AttachShader] is unimplemented, please implement it.");
	}

	void CppGL::BindAttribLocation(uint program, uint index, const char *name)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindAttribLocation] is unimplemented, please implement it.");
	}

	void CppGL::BindBuffer(enumeration target, uint buffer)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindBuffer] is unimplemented, please implement it.");
	}

	void CppGL::BindFramebuffer(enumeration target, uint framebuffer)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindFramebuffer] is unimplemented, please implement it.");
	}

	void CppGL::BindRenderbuffer(enumeration target, uint renderbuffer)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindRenderbuffer] is unimplemented, please implement it.");
	}

	void CppGL::BlendColor(clampf red, clampf green, clampf blue, clampf alpha)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BlendColor] is unimplemented, please implement it.");
	}

	void CppGL::BlendEquation(enumeration mode)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BlendEquation] is unimplemented, please implement it.");
	}

	void CppGL::BlendEquationSeparate(enumeration modeRGB, enumeration modeAlpha)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BlendEquationSeparate] is unimplemented, please implement it.");
	}

	void CppGL::BlendFuncSeparate(enumeration srcRGB, enumeration dstRGB, enumeration srcAlpha, enumeration dstAlpha)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BlendFuncSeparate] is unimplemented, please implement it.");
	}

	void CppGL::BufferData(enumeration target, sizeiptr size, const void *data, enumeration usage)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BufferData] is unimplemented, please implement it.");
	}

	void CppGL::BufferSubData(enumeration target, intptr offset, sizeiptr size, const void *data)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BufferSubData] is unimplemented, please implement it.");
	}

	enumeration CppGL::CheckFramebufferStatus(enumeration target)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CheckFramebufferStatus] is unimplemented, please implement it.");
		return 0;
	}

	void CppGL::ClearDepthf(clampf depth)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ClearDepthf] is unimplemented, please implement it.");
	}

	void CppGL::CompileShader(uint shader)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CompileShader] is unimplemented, please implement it.");
	}

	void CppGL::CompressedTexImage2D(enumeration target, int level, enumeration internalformat, sizei width, sizei height, int border, sizei imageSize, const void *data)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CompressedTexImage2D] is unimplemented, please implement it.");
	}

	void CppGL::CompressedTexSubImage2D(enumeration target, int level, int xoffset, int yoffset, sizei width, sizei height, enumeration format, sizei imageSize, const void *data)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CompressedTexSubImage2D] is unimplemented, please implement it.");
	}

	uint CppGL::CreateProgram()
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CreateProgram] is unimplemented, please implement it.");
		return 0;
	}

	uint CppGL::CreateShader(enumeration type)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CreateShader] is unimplemented, please implement it.");
		return 0;
	}

	void CppGL::DeleteBuffers(sizei n, const uint *buffers)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DeleteBuffers] is unimplemented, please implement it.");
	}

	void CppGL::DeleteFramebuffers(sizei n, const uint *framebuffers)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DeleteFramebuffers] is unimplemented, please implement it.");
	}

	void CppGL::DeleteProgram(uint program)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DeleteProgram] is unimplemented, please implement it.");
	}

	void CppGL::DeleteRenderbuffers(sizei n, const uint *renderbuffers)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DeleteRenderbuffers] is unimplemented, please implement it.");
	}

	void CppGL::DeleteShader(uint shader)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DeleteShader] is unimplemented, please implement it.");
	}

	void CppGL::DepthRangef(clampf zNear, clampf zFar)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DepthRangef] is unimplemented, please implement it.");
	}

	void CppGL::DetachShader(uint program, uint shader)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DetachShader] is unimplemented, please implement it.");
	}

	void CppGL::DisableVertexAttribArray(uint index)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DisableVertexAttribArray] is unimplemented, please implement it.");
	}

	void CppGL::EnableVertexAttribArray(uint index)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[EnableVertexAttribArray] is unimplemented, please implement it.");
	}

	void CppGL::FramebufferRenderbuffer(enumeration target, enumeration attachment, enumeration renderbuffertarget, uint renderbuffer)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[FramebufferRenderbuffer] is unimplemented, please implement it.");
	}

	void CppGL::FramebufferTexture2D(enumeration target, enumeration attachment, enumeration textarget, uint texture, int level)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[FramebufferTexture2D] is unimplemented, please implement it.");
	}

	void CppGL::GenBuffers(sizei n, uint *buffers)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GenBuffers] is unimplemented, please implement it.");
	}

	void CppGL::GenerateMipmap(enumeration target)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GenerateMipmap] is unimplemented, please implement it.");
	}

	void CppGL::GenFramebuffers(sizei n, uint *framebuffers)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GenFramebuffers] is unimplemented, please implement it.");
	}

	void CppGL::GenRenderbuffers(sizei n, uint *renderbuffers)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GenRenderbuffers] is unimplemented, please implement it.");
	}

	void CppGL::GetActiveAttrib(uint program, uint index, sizei bufsize, sizei *length, int *size, enumeration *type, char *name)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetActiveAttrib] is unimplemented, please implement it.");
	}

	void CppGL::GetActiveUniform(uint program, uint index, sizei bufsize, sizei *length, int *size, enumeration *type, char *name)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetActiveUniform] is unimplemented, please implement it.");
	}

	void CppGL::GetAttachedShaders(uint program, sizei maxcount, sizei *count, uint *shaders)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetAttachedShaders] is unimplemented, please implement it.");
	}

	int CppGL::GetAttribLocation(uint program, const char *name)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetAttribLocation] is unimplemented, please implement it.");
		return 0;
	}

	void CppGL::GetBufferParameteriv(enumeration target, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetBufferParameteriv] is unimplemented, please implement it.");
	}

	void CppGL::GetFramebufferAttachmentParameteriv(enumeration target, enumeration attachment, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetFramebufferAttachmentParameteriv] is unimplemented, please implement it.");
	}

	void CppGL::GetProgramiv(uint program, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetProgramiv] is unimplemented, please implement it.");
	}

	void CppGL::GetProgramInfoLog(uint program, sizei bufsize, sizei *length, char *infolog)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetProgramInfoLog] is unimplemented, please implement it.");
	}

	void CppGL::GetRenderbufferParameteriv(enumeration target, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetRenderbufferParameteriv] is unimplemented, please implement it.");
	}

	void CppGL::GetShaderiv(uint shader, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetShaderiv] is unimplemented, please implement it.");
	}

	void CppGL::GetShaderInfoLog(uint shader, sizei bufsize, sizei *length, char *infolog)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetShaderInfoLog] is unimplemented, please implement it.");
	}

	void CppGL::GetShaderPrecisionFormat(enumeration shadertype, enumeration precisiontype, int *range, int *precision)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetShaderPrecisionFormat] is unimplemented, please implement it.");
	}

	void CppGL::GetShaderSource(uint shader, sizei bufsize, sizei *length, char *source)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetShaderSource] is unimplemented, please implement it.");
	}

	void CppGL::GetUniformfv(uint program, int location, float *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetUniformfv] is unimplemented, please implement it.");
	}

	void CppGL::GetUniformiv(uint program, int location, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetUniformiv] is unimplemented, please implement it.");
	}

	int CppGL::GetUniformLocation(uint program, const char *name)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetUniformLocation] is unimplemented, please implement it.");
		return 0;
	}

	void CppGL::GetVertexAttribfv(uint index, enumeration pname, float *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetVertexAttribfv] is unimplemented, please implement it.");
	}

	void CppGL::GetVertexAttribiv(uint index, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetVertexAttribiv] is unimplemented, please implement it.");
	}

	void CppGL::GetVertexAttribPointerv(uint index, enumeration pname, void **pointer)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetVertexAttribPointerv] is unimplemented, please implement it.");
	}

	boolean CppGL::IsBuffer(uint buffer)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsBuffer] is unimplemented, please implement it.");
		return false;
	}

	boolean CppGL::IsFramebuffer(uint framebuffer)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsFramebuffer] is unimplemented, please implement it.");
		return false;
	}

	boolean CppGL::IsProgram(uint program)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsProgram] is unimplemented, please implement it.");
		return false;
	}

	boolean CppGL::IsRenderbuffer(uint renderbuffer)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsRenderbuffer] is unimplemented, please implement it.");
		return false;
	}

	boolean CppGL::IsShader(uint shader)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsShader] is unimplemented, please implement it.");
		return false;
	}

	void CppGL::LinkProgram(uint program)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[LinkProgram] is unimplemented, please implement it.");
	}

	void CppGL::ReleaseShaderCompiler()
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ReleaseShaderCompiler] is unimplemented, please implement it.");
	}

	void CppGL::RenderbufferStorage(enumeration target, enumeration internalformat, sizei width, sizei height)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[RenderbufferStorage] is unimplemented, please implement it.");
	}

	void CppGL::SampleCoverage(clampf value, boolean invert)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[SampleCoverage] is unimplemented, please implement it.");
	}

	void CppGL::ShaderBinary(int n, const uint *shaders, enumeration binaryformat, const void *binary, int length)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ShaderBinary] is unimplemented, please implement it.");
	}

	void CppGL::ShaderSource(uint shader, sizei count, const char **string, const int *length)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ShaderSource] is unimplemented, please implement it.");
	}

	void CppGL::StencilFuncSeparate(enumeration face, enumeration func, int ref, uint mask)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[StencilFuncSeparate] is unimplemented, please implement it.");
	}

	void CppGL::StencilMaskSeparate(enumeration face, uint mask)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[StencilMaskSeparate] is unimplemented, please implement it.");
	}

	void CppGL::StencilOpSeparate(enumeration face, enumeration fail, enumeration zfail, enumeration zpass)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[StencilOpSeparate] is unimplemented, please implement it.");
	}

	void CppGL::Uniform1f(int location, float x)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform1f] is unimplemented, please implement it.");
	}

	void CppGL::Uniform1fv(int location, sizei count, const float *v)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform1fv] is unimplemented, please implement it.");
	}

	void CppGL::Uniform1i(int location, int x)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform1i] is unimplemented, please implement it.");
	}

	void CppGL::Uniform1iv(int location, sizei count, const int *v)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform1iv] is unimplemented, please implement it.");
	}

	void CppGL::Uniform2f(int location, float x, float y)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform2f] is unimplemented, please implement it.");
	}

	void CppGL::Uniform2fv(int location, sizei count, const float *v)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform2fv] is unimplemented, please implement it.");
	}

	void CppGL::Uniform2i(int location, int x, int y)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform2i] is unimplemented, please implement it.");
	}

	void CppGL::Uniform2iv(int location, sizei count, const int *v)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform2iv] is unimplemented, please implement it.");
	}

	void CppGL::Uniform3f(int location, float x, float y, float z)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform3f] is unimplemented, please implement it.");
	}

	void CppGL::Uniform3fv(int location, sizei count, const float *v)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform3fv] is unimplemented, please implement it.");
	}

	void CppGL::Uniform3i(int location, int x, int y, int z)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform3i] is unimplemented, please implement it.");
	}

	void CppGL::Uniform3iv(int location, sizei count, const int *v)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform3iv] is unimplemented, please implement it.");
	}

	void CppGL::Uniform4f(int location, float x, float y, float z, float w)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform4f] is unimplemented, please implement it.");
	}

	void CppGL::Uniform4fv(int location, sizei count, const float *v)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform4fv] is unimplemented, please implement it.");
	}

	void CppGL::Uniform4i(int location, int x, int y, int z, int w)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform4i] is unimplemented, please implement it.");
	}

	void CppGL::Uniform4iv(int location, sizei count, const int *v)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform4iv] is unimplemented, please implement it.");
	}

	void CppGL::UniformMatrix2fv(int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UniformMatrix2fv] is unimplemented, please implement it.");
	}

	void CppGL::UniformMatrix3fv(int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UniformMatrix3fv] is unimplemented, please implement it.");
	}

	void CppGL::UniformMatrix4fv(int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UniformMatrix4fv] is unimplemented, please implement it.");
	}

	void CppGL::UseProgram(uint program)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UseProgram] is unimplemented, please implement it.");
	}

	void CppGL::ValidateProgram(uint program)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ValidateProgram] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttrib1f(uint indx, float x)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttrib1f] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttrib1fv(uint indx, const float *values)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttrib1fv] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttrib2f(uint indx, float x, float y)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttrib2f] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttrib2fv(uint indx, const float *values)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttrib2fv] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttrib3f(uint indx, float x, float y, float z)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttrib3f] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttrib3fv(uint indx, const float *values)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttrib3fv] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttrib4f(uint indx, float x, float y, float z, float w)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttrib4f] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttrib4fv(uint indx, const float *values)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttrib4fv] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttribPointer(uint indx, int size, enumeration type, boolean normalized, sizei stride, const void *ptr)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttribPointer] is unimplemented, please implement it.");
	}

	void CppGL::BeginQuery(enumeration target, uint id)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BeginQuery] is unimplemented, please implement it.");
	}

	void CppGL::BeginTransformFeedback(enumeration primitiveMode)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BeginTransformFeedback] is unimplemented, please implement it.");
	}

	void CppGL::BindBufferBase(enumeration target, uint index, uint buffer)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindBufferBase] is unimplemented, please implement it.");
	}

	void CppGL::BindBufferRange(enumeration target, uint index, uint buffer, intptr offset, sizeiptr size)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindBufferRange] is unimplemented, please implement it.");
	}

	void CppGL::BindSampler(uint unit, uint sampler)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindSampler] is unimplemented, please implement it.");
	}

	void CppGL::BindTransformFeedback(enumeration target, uint id)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindTransformFeedback] is unimplemented, please implement it.");
	}

	void CppGL::BindVertexArray(uint array)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindVertexArray] is unimplemented, please implement it.");
	}

	void CppGL::BlitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, bitfield mask, enumeration filter)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BlitFramebuffer] is unimplemented, please implement it.");
	}

	void CppGL::ClearBufferfi(enumeration buffer, int drawbuffer, float depth, int stencil)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ClearBufferfi] is unimplemented, please implement it.");
	}

	void CppGL::ClearBufferfv(enumeration buffer, int drawbuffer, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ClearBufferfv] is unimplemented, please implement it.");
	}

	void CppGL::ClearBufferiv(enumeration buffer, int drawbuffer, const int *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ClearBufferiv] is unimplemented, please implement it.");
	}

	void CppGL::ClearBufferuiv(enumeration buffer, int drawbuffer, const uint *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ClearBufferuiv] is unimplemented, please implement it.");
	}

	void CppGL::CompressedTexImage3D(enumeration target, int level, enumeration internalformat, sizei width, sizei height, sizei depth, int border, sizei imageSize, const void *data)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CompressedTexImage3D] is unimplemented, please implement it.");
	}

	void CppGL::CompressedTexSubImage3D(enumeration target, int level, int xoffset, int yoffset, int zoffset, sizei width, sizei height, sizei depth, enumeration format, sizei imageSize, const void *data)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CompressedTexSubImage3D] is unimplemented, please implement it.");
	}

	void CppGL::CopyBufferSubData(enumeration readTarget, enumeration writeTarget, intptr readOffset, intptr writeOffset, sizeiptr size)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CopyBufferSubData] is unimplemented, please implement it.");
	}

	void CppGL::CopyTexSubImage3D(enumeration target, int level, int xoffset, int yoffset, int zoffset, int x, int y, sizei width, sizei height)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CopyTexSubImage3D] is unimplemented, please implement it.");
	}

	void CppGL::DeleteQueries(sizei n, const uint *ids)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DeleteQueries] is unimplemented, please implement it.");
	}

	void CppGL::DeleteSamplers(sizei count, const uint *samplers)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DeleteSamplers] is unimplemented, please implement it.");
	}

	void CppGL::DeleteTransformFeedbacks(sizei n, const uint *ids)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DeleteTransformFeedbacks] is unimplemented, please implement it.");
	}

	void CppGL::DeleteVertexArrays(sizei n, const uint *arrays)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DeleteVertexArrays] is unimplemented, please implement it.");
	}

	void CppGL::DrawArraysInstanced(enumeration mode, int first, sizei count, sizei instancecount)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DrawArraysInstanced] is unimplemented, please implement it.");
	}

	void CppGL::DrawBuffers(sizei n, const enumeration *bufs)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DrawBuffers] is unimplemented, please implement it.");
	}

	void CppGL::DrawElementsInstanced(enumeration mode, sizei count, enumeration type, const void *indices, sizei instancecount)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DrawElementsInstanced] is unimplemented, please implement it.");
	}

	void CppGL::DrawRangeElements(enumeration mode, uint start, uint end, sizei count, enumeration type, const void *indices)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DrawRangeElements] is unimplemented, please implement it.");
	}

	void CppGL::EndQuery(enumeration target)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[EndQuery] is unimplemented, please implement it.");
	}

	void CppGL::EndTransformFeedback()
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[EndTransformFeedback] is unimplemented, please implement it.");
	}

	void CppGL::FlushMappedBufferRange(enumeration target, intptr offset, sizeiptr length)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[FlushMappedBufferRange] is unimplemented, please implement it.");
	}

	void CppGL::FramebufferTextureLayer(enumeration target, enumeration attachment, uint texture, int level, int layer)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[FramebufferTextureLayer] is unimplemented, please implement it.");
	}

	void CppGL::GenQueries(sizei n, uint *ids)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GenQueries] is unimplemented, please implement it.");
	}

	void CppGL::GenSamplers(sizei count, uint *samplers)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GenSamplers] is unimplemented, please implement it.");
	}

	void CppGL::GenTransformFeedbacks(sizei n, uint *ids)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GenTransformFeedbacks] is unimplemented, please implement it.");
	}

	void CppGL::GenVertexArrays(sizei n, uint *arrays)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GenVertexArrays] is unimplemented, please implement it.");
	}

	void CppGL::GetActiveUniformBlockName(uint program, uint uniformBlockIndex, sizei bufSize, sizei *length, char *uniformBlockName)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetActiveUniformBlockName] is unimplemented, please implement it.");
	}

	void CppGL::GetActiveUniformBlockiv(uint program, uint uniformBlockIndex, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetActiveUniformBlockiv] is unimplemented, please implement it.");
	}

	void CppGL::GetActiveUniformsiv(uint program, sizei uniformCount, const uint *uniformIndices, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetActiveUniformsiv] is unimplemented, please implement it.");
	}

	void CppGL::GetBufferParameteri64v(enumeration target, enumeration pname, int64 *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetBufferParameteri64v] is unimplemented, please implement it.");
	}

	void CppGL::GetBufferPointerv(enumeration target, enumeration pname, void **params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetBufferPointerv] is unimplemented, please implement it.");
	}

	int CppGL::GetFragDataLocation(uint program, const char *name)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetFragDataLocation] is unimplemented, please implement it.");
		return 0;
	}

	void CppGL::GetInteger64i_v(enumeration target, uint index, int64 *data)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetInteger64i_v] is unimplemented, please implement it.");
	}

	void CppGL::GetInteger64v(enumeration pname, int64 *data)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetInteger64v] is unimplemented, please implement it.");
	}

	void CppGL::GetIntegeri_v(enumeration target, uint index, int *data)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetIntegeri_v] is unimplemented, please implement it.");
	}

	void CppGL::GetInternalformativ(enumeration target, enumeration internalformat, enumeration pname, sizei bufSize, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetInternalformativ] is unimplemented, please implement it.");
	}

	void CppGL::GetProgramBinary(uint program, sizei bufSize, sizei *length, enumeration *binaryFormat, void *binary)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetProgramBinary] is unimplemented, please implement it.");
	}

	void CppGL::GetQueryObjectuiv(uint id, enumeration pname, uint *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetQueryObjectuiv] is unimplemented, please implement it.");
	}

	void CppGL::GetQueryiv(enumeration target, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetQueryiv] is unimplemented, please implement it.");
	}

	void CppGL::GetSamplerParameterfv(uint sampler, enumeration pname, float *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetSamplerParameterfv] is unimplemented, please implement it.");
	}

	void CppGL::GetSamplerParameteriv(uint sampler, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetSamplerParameteriv] is unimplemented, please implement it.");
	}

	const ubyte *CppGL::GetStringi(enumeration name, uint index)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetStringi] is unimplemented, please implement it.");
		return nullptr;
	}

	void CppGL::GetTransformFeedbackVarying(uint program, uint index, sizei bufSize, sizei *length, sizei *size, enumeration *type, char *name)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetTransformFeedbackVarying] is unimplemented, please implement it.");
	}

	uint CppGL::GetUniformBlockIndex(uint program, const char *uniformBlockName)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetUniformBlockIndex] is unimplemented, please implement it.");
		return 0;
	}

	void CppGL::GetUniformIndices(uint program, sizei uniformCount, const char *const *uniformNames, uint *uniformIndices)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetUniformIndices] is unimplemented, please implement it.");
	}

	void CppGL::GetUniformuiv(uint program, int location, uint *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetUniformuiv] is unimplemented, please implement it.");
	}

	void CppGL::GetVertexAttribIiv(uint index, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetVertexAttribIiv] is unimplemented, please implement it.");
	}

	void CppGL::GetVertexAttribIuiv(uint index, enumeration pname, uint *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetVertexAttribIuiv] is unimplemented, please implement it.");
	}

	void CppGL::InvalidateFramebuffer(enumeration target, sizei numAttachments, const enumeration *attachments)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[InvalidateFramebuffer] is unimplemented, please implement it.");
	}

	void CppGL::InvalidateSubFramebuffer(enumeration target, sizei numAttachments, const enumeration *attachments, int x, int y, sizei width, sizei height)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[InvalidateSubFramebuffer] is unimplemented, please implement it.");
	}

	boolean CppGL::IsQuery(uint id)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsQuery] is unimplemented, please implement it.");
		return false;
	}

	boolean CppGL::IsSampler(uint sampler)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsSampler] is unimplemented, please implement it.");
		return false;
	}

	boolean CppGL::IsTransformFeedback(uint id)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsTransformFeedback] is unimplemented, please implement it.");
		return false;
	}

	boolean CppGL::IsVertexArray(uint array)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsVertexArray] is unimplemented, please implement it.");
		return false;
	}

	void *CppGL::MapBufferRange(enumeration target, intptr offset, sizeiptr length, bitfield access)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[MapBufferRange] is unimplemented, please implement it.");
		return nullptr;
	}

	void CppGL::PauseTransformFeedback()
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[PauseTransformFeedback] is unimplemented, please implement it.");
	}

	void CppGL::ProgramBinary(uint program, enumeration binaryFormat, const void *binary, sizei length)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramBinary] is unimplemented, please implement it.");
	}

	void CppGL::ProgramParameteri(uint program, enumeration pname, int value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramParameteri] is unimplemented, please implement it.");
	}

	void CppGL::ReadBuffer(enumeration src)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ReadBuffer] is unimplemented, please implement it.");
	}

	void CppGL::RenderbufferStorageMultisample(enumeration target, sizei samples, enumeration internalformat, sizei width, sizei height)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[RenderbufferStorageMultisample] is unimplemented, please implement it.");
	}

	void CppGL::ResumeTransformFeedback()
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ResumeTransformFeedback] is unimplemented, please implement it.");
	}

	void CppGL::SamplerParameterf(uint sampler, enumeration pname, float param)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[SamplerParameterf] is unimplemented, please implement it.");
	}

	void CppGL::SamplerParameterfv(uint sampler, enumeration pname, const float *param)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[SamplerParameterfv] is unimplemented, please implement it.");
	}

	void CppGL::SamplerParameteri(uint sampler, enumeration pname, int param)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[SamplerParameteri] is unimplemented, please implement it.");
	}

	void CppGL::SamplerParameteriv(uint sampler, enumeration pname, const int *param)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[SamplerParameteriv] is unimplemented, please implement it.");
	}

	void CppGL::TexImage3D(enumeration target, int level, int internalformat, sizei width, sizei height, sizei depth, int border, enumeration format, enumeration type, const void *pixels)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexImage3D] is unimplemented, please implement it.");
	}

	void CppGL::TexStorage2D(enumeration target, sizei levels, enumeration internalformat, sizei width, sizei height)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexStorage2D] is unimplemented, please implement it.");
	}

	void CppGL::TexStorage3D(enumeration target, sizei levels, enumeration internalformat, sizei width, sizei height, sizei depth)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexStorage3D] is unimplemented, please implement it.");
	}

	void CppGL::TexSubImage3D(enumeration target, int level, int xoffset, int yoffset, int zoffset, sizei width, sizei height, sizei depth, enumeration format, enumeration type, const void *pixels)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexSubImage3D] is unimplemented, please implement it.");
	}

	void CppGL::TransformFeedbackVaryings(uint program, sizei count, const char *const *varyings, enumeration bufferMode)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TransformFeedbackVaryings] is unimplemented, please implement it.");
	}

	void CppGL::Uniform1ui(int location, uint v0)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform1ui] is unimplemented, please implement it.");
	}

	void CppGL::Uniform1uiv(int location, sizei count, const uint *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform1uiv] is unimplemented, please implement it.");
	}

	void CppGL::Uniform2ui(int location, uint v0, uint v1)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform2ui] is unimplemented, please implement it.");
	}

	void CppGL::Uniform2uiv(int location, sizei count, const uint *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform2uiv] is unimplemented, please implement it.");
	}

	void CppGL::Uniform3ui(int location, uint v0, uint v1, uint v2)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform3ui] is unimplemented, please implement it.");
	}

	void CppGL::Uniform3uiv(int location, sizei count, const uint *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform3uiv] is unimplemented, please implement it.");
	}

	void CppGL::Uniform4ui(int location, uint v0, uint v1, uint v2, uint v3)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform4ui] is unimplemented, please implement it.");
	}

	void CppGL::Uniform4uiv(int location, sizei count, const uint *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Uniform4uiv] is unimplemented, please implement it.");
	}

	void CppGL::UniformBlockBinding(uint program, uint uniformBlockIndex, uint uniformBlockBinding)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UniformBlockBinding] is unimplemented, please implement it.");
	}

	void CppGL::UniformMatrix2x3fv(int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UniformMatrix2x3fv] is unimplemented, please implement it.");
	}

	void CppGL::UniformMatrix2x4fv(int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UniformMatrix2x4fv] is unimplemented, please implement it.");
	}

	void CppGL::UniformMatrix3x2fv(int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UniformMatrix3x2fv] is unimplemented, please implement it.");
	}

	void CppGL::UniformMatrix3x4fv(int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UniformMatrix3x4fv] is unimplemented, please implement it.");
	}

	void CppGL::UniformMatrix4x2fv(int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UniformMatrix4x2fv] is unimplemented, please implement it.");
	}

	void CppGL::UniformMatrix4x3fv(int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UniformMatrix4x3fv] is unimplemented, please implement it.");
	}

	boolean CppGL::UnmapBuffer(enumeration target)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UnmapBuffer] is unimplemented, please implement it.");
		return false;
	}

	void CppGL::VertexAttribDivisor(uint index, uint divisor)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttribDivisor] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttribI4i(uint index, int x, int y, int z, int w)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttribI4i] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttribI4iv(uint index, const int *v)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttribI4iv] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttribI4ui(uint index, uint x, uint y, uint z, uint w)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttribI4ui] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttribI4uiv(uint index, const uint *v)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttribI4uiv] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttribIPointer(uint index, int size, enumeration type, sizei stride, const void *pointer)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttribIPointer] is unimplemented, please implement it.");
	}

	void CppGL::ActiveShaderProgram(uint pipeline, uint program)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ActiveShaderProgram] is unimplemented, please implement it.");
	}

	void CppGL::BindImageTexture(uint unit, uint texture, int level, boolean layered, int layer, enumeration access, enumeration format)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindImageTexture] is unimplemented, please implement it.");
	}

	void CppGL::BindProgramPipeline(uint pipeline)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindProgramPipeline] is unimplemented, please implement it.");
	}

	void CppGL::BindVertexBuffer(uint bindingindex, uint buffer, intptr offset, sizei stride)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BindVertexBuffer] is unimplemented, please implement it.");
	}

	uint CppGL::CreateShaderProgramv(enumeration type, sizei count, const char *const *strings)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CreateShaderProgramv] is unimplemented, please implement it.");
		return 0;
	}

	void CppGL::DeleteProgramPipelines(sizei n, const uint *pipelines)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DeleteProgramPipelines] is unimplemented, please implement it.");
	}

	void CppGL::DispatchCompute(uint num_groups_x, uint num_groups_y, uint num_groups_z)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DispatchCompute] is unimplemented, please implement it.");
	}

	void CppGL::DispatchComputeIndirect(intptr indirect)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DispatchComputeIndirect] is unimplemented, please implement it.");
	}

	void CppGL::DrawArraysIndirect(enumeration mode, const void *indirect)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DrawArraysIndirect] is unimplemented, please implement it.");
	}

	void CppGL::DrawElementsIndirect(enumeration mode, enumeration type, const void *indirect)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DrawElementsIndirect] is unimplemented, please implement it.");
	}

	void CppGL::FramebufferParameteri(enumeration target, enumeration pname, int param)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[FramebufferParameteri] is unimplemented, please implement it.");
	}

	void CppGL::GenProgramPipelines(sizei n, uint *pipelines)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GenProgramPipelines] is unimplemented, please implement it.");
	}

	void CppGL::GetBooleani_v(enumeration target, uint index, boolean *data)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetBooleani_v] is unimplemented, please implement it.");
	}

	void CppGL::GetFramebufferParameteriv(enumeration target, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetFramebufferParameteriv] is unimplemented, please implement it.");
	}

	void CppGL::GetMultisamplefv(enumeration pname, uint index, float *val)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetMultisamplefv] is unimplemented, please implement it.");
	}

	void CppGL::GetProgramInterfaceiv(uint program, enumeration programInterface, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetProgramInterfaceiv] is unimplemented, please implement it.");
	}

	void CppGL::GetProgramPipelineInfoLog(uint pipeline, sizei bufSize, sizei *length, char *infoLog)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetProgramPipelineInfoLog] is unimplemented, please implement it.");
	}

	void CppGL::GetProgramPipelineiv(uint pipeline, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetProgramPipelineiv] is unimplemented, please implement it.");
	}

	uint CppGL::GetProgramResourceIndex(uint program, enumeration programInterface, const char *name)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetProgramResourceIndex] is unimplemented, please implement it.");
		return 0;
	}

	int CppGL::GetProgramResourceLocation(uint program, enumeration programInterface, const char *name)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetProgramResourceLocation] is unimplemented, please implement it.");
		return 0;
	}

	void CppGL::GetProgramResourceName(uint program, enumeration programInterface, uint index, sizei bufSize, sizei *length, char *name)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetProgramResourceName] is unimplemented, please implement it.");
	}

	void CppGL::GetProgramResourceiv(uint program, enumeration programInterface, uint index, sizei propCount, const enumeration *props, sizei bufSize, sizei *length, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetProgramResourceiv] is unimplemented, please implement it.");
	}

	void CppGL::GetTexLevelParameterfv(enumeration target, int level, enumeration pname, float *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetTexLevelParameterfv] is unimplemented, please implement it.");
	}

	void CppGL::GetTexLevelParameteriv(enumeration target, int level, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetTexLevelParameteriv] is unimplemented, please implement it.");
	}

	boolean CppGL::IsProgramPipeline(uint pipeline)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsProgramPipeline] is unimplemented, please implement it.");
		return false;
	}

	void CppGL::MemoryBarrier(bitfield barriers)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[MemoryBarrier] is unimplemented, please implement it.");
	}

	void CppGL::MemoryBarrierByRegion(bitfield barriers)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[MemoryBarrierByRegion] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform1f(uint program, int location, float v0)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform1f] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform1fv(uint program, int location, sizei count, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform1fv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform1i(uint program, int location, int v0)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform1i] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform1iv(uint program, int location, sizei count, const int *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform1iv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform1ui(uint program, int location, uint v0)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform1ui] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform1uiv(uint program, int location, sizei count, const uint *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform1uiv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform2f(uint program, int location, float v0, float v1)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform2f] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform2fv(uint program, int location, sizei count, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform2fv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform2i(uint program, int location, int v0, int v1)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform2i] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform2iv(uint program, int location, sizei count, const int *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform2iv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform2ui(uint program, int location, uint v0, uint v1)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform2ui] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform2uiv(uint program, int location, sizei count, const uint *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform2uiv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform3f(uint program, int location, float v0, float v1, float v2)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform3f] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform3fv(uint program, int location, sizei count, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform3fv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform3i(uint program, int location, int v0, int v1, int v2)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform3i] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform3iv(uint program, int location, sizei count, const int *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform3iv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform3ui(uint program, int location, uint v0, uint v1, uint v2)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform3ui] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform3uiv(uint program, int location, sizei count, const uint *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform3uiv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform4f(uint program, int location, float v0, float v1, float v2, float v3)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform4f] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform4fv(uint program, int location, sizei count, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform4fv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform4i(uint program, int location, int v0, int v1, int v2, int v3)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform4i] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform4iv(uint program, int location, sizei count, const int *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform4iv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform4ui(uint program, int location, uint v0, uint v1, uint v2, uint v3)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform4ui] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniform4uiv(uint program, int location, sizei count, const uint *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniform4uiv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniformMatrix2fv(uint program, int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniformMatrix2fv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniformMatrix2x3fv(uint program, int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniformMatrix2x3fv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniformMatrix2x4fv(uint program, int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniformMatrix2x4fv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniformMatrix3fv(uint program, int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniformMatrix3fv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniformMatrix3x2fv(uint program, int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniformMatrix3x2fv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniformMatrix3x4fv(uint program, int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniformMatrix3x4fv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniformMatrix4fv(uint program, int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniformMatrix4fv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniformMatrix4x2fv(uint program, int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniformMatrix4x2fv] is unimplemented, please implement it.");
	}

	void CppGL::ProgramUniformMatrix4x3fv(uint program, int location, sizei count, boolean transpose, const float *value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ProgramUniformMatrix4x3fv] is unimplemented, please implement it.");
	}

	void CppGL::SampleMaski(uint maskNumber, bitfield mask)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[SampleMaski] is unimplemented, please implement it.");
	}

	void CppGL::TexStorage2DMultisample(enumeration target, sizei samples, enumeration internalformat, sizei width, sizei height, boolean fixedsamplelocations)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexStorage2DMultisample] is unimplemented, please implement it.");
	}

	void CppGL::UseProgramStages(uint pipeline, bitfield stages, uint program)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[UseProgramStages] is unimplemented, please implement it.");
	}

	void CppGL::ValidateProgramPipeline(uint pipeline)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ValidateProgramPipeline] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttribBinding(uint attribindex, uint bindingindex)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttribBinding] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttribFormat(uint attribindex, int size, enumeration type, boolean normalized, uint relativeoffset)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttribFormat] is unimplemented, please implement it.");
	}

	void CppGL::VertexAttribIFormat(uint attribindex, int size, enumeration type, uint relativeoffset)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexAttribIFormat] is unimplemented, please implement it.");
	}

	void CppGL::VertexBindingDivisor(uint bindingindex, uint divisor)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[VertexBindingDivisor] is unimplemented, please implement it.");
	}

	void CppGL::BlendBarrier()
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BlendBarrier] is unimplemented, please implement it.");
	}

	void CppGL::BlendEquationSeparatei(uint buf, enumeration modeRGB, enumeration modeAlpha)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BlendEquationSeparatei] is unimplemented, please implement it.");
	}

	void CppGL::BlendEquationi(uint buf, enumeration mode)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BlendEquationi] is unimplemented, please implement it.");
	}

	void CppGL::BlendFuncSeparatei(uint buf, enumeration srcRGB, enumeration dstRGB, enumeration srcAlpha, enumeration dstAlpha)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BlendFuncSeparatei] is unimplemented, please implement it.");
	}

	void CppGL::BlendFunci(uint buf, enumeration src, enumeration dst)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[BlendFunci] is unimplemented, please implement it.");
	}

	void CppGL::ColorMaski(uint index, boolean r, boolean g, boolean b, boolean a)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ColorMaski] is unimplemented, please implement it.");
	}

	void CppGL::CopyImageSubData(uint srcName, enumeration srcTarget, int srcLevel, int srcX, int srcY, int srcZ, uint dstName, enumeration dstTarget, int dstLevel, int dstX, int dstY, int dstZ, sizei srcWidth, sizei srcHeight, sizei srcDepth)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[CopyImageSubData] is unimplemented, please implement it.");
	}

	void CppGL::DebugMessageCallback(debugproc callback, const void *userParam)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DebugMessageCallback] is unimplemented, please implement it.");
	}

	void CppGL::DebugMessageControl(enumeration source, enumeration type, enumeration severity, sizei count, const uint *ids, boolean enabled)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DebugMessageControl] is unimplemented, please implement it.");
	}

	void CppGL::DebugMessageInsert(enumeration source, enumeration type, uint id, enumeration severity, sizei length, const char *buf)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DebugMessageInsert] is unimplemented, please implement it.");
	}

	void CppGL::Disablei(enumeration target, uint index)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Disablei] is unimplemented, please implement it.");
	}

	void CppGL::DrawElementsBaseVertex(enumeration mode, sizei count, enumeration type, const void *indices, int basevertex)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DrawElementsBaseVertex] is unimplemented, please implement it.");
	}

	void CppGL::DrawElementsInstancedBaseVertex(enumeration mode, sizei count, enumeration type, const void *indices, sizei instancecount, int basevertex)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DrawElementsInstancedBaseVertex] is unimplemented, please implement it.");
	}

	void CppGL::DrawRangeElementsBaseVertex(enumeration mode, uint start, uint end, sizei count, enumeration type, const void *indices, int basevertex)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[DrawRangeElementsBaseVertex] is unimplemented, please implement it.");
	}

	void CppGL::Enablei(enumeration target, uint index)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[Enablei] is unimplemented, please implement it.");
	}

	void CppGL::FramebufferTexture(enumeration target, enumeration attachment, uint texture, int level)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[FramebufferTexture] is unimplemented, please implement it.");
	}

	uint CppGL::GetDebugMessageLog(uint count, sizei bufSize, enumeration *sources, enumeration *types, uint *ids, enumeration *severities, sizei *lengths, char *messageLog)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetDebugMessageLog] is unimplemented, please implement it.");
		return 0;
	}

	enumeration CppGL::GetGraphicsResetStatus()
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetGraphicsResetStatus] is unimplemented, please implement it.");
		return 0;
	}

	void CppGL::GetObjectLabel(enumeration identifier, uint name, sizei bufSize, sizei *length, char *label)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetObjectLabel] is unimplemented, please implement it.");
	}

	void CppGL::GetObjectPtrLabel(const void *ptr, sizei bufSize, sizei *length, char *label)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetObjectPtrLabel] is unimplemented, please implement it.");
	}

	void CppGL::GetPointerv(enumeration pname, void **params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetPointerv] is unimplemented, please implement it.");
	}

	void CppGL::GetSamplerParameterIiv(uint sampler, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetSamplerParameterIiv] is unimplemented, please implement it.");
	}

	void CppGL::GetSamplerParameterIuiv(uint sampler, enumeration pname, uint *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetSamplerParameterIuiv] is unimplemented, please implement it.");
	}

	void CppGL::GetTexParameterIiv(enumeration target, enumeration pname, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetTexParameterIiv] is unimplemented, please implement it.");
	}

	void CppGL::GetTexParameterIuiv(enumeration target, enumeration pname, uint *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetTexParameterIuiv] is unimplemented, please implement it.");
	}

	void CppGL::GetnUniformfv(uint program, int location, sizei bufSize, float *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetnUniformfv] is unimplemented, please implement it.");
	}

	void CppGL::GetnUniformiv(uint program, int location, sizei bufSize, int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetnUniformiv] is unimplemented, please implement it.");
	}

	void CppGL::GetnUniformuiv(uint program, int location, sizei bufSize, uint *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[GetnUniformuiv] is unimplemented, please implement it.");
	}

	boolean CppGL::IsEnabledi(enumeration target, uint index)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[IsEnabledi] is unimplemented, please implement it.");
		return false;
	}

	void CppGL::MinSampleShading(float value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[MinSampleShading] is unimplemented, please implement it.");
	}

	void CppGL::ObjectLabel(enumeration identifier, uint name, sizei length, const char *label)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ObjectLabel] is unimplemented, please implement it.");
	}

	void CppGL::ObjectPtrLabel(const void *ptr, sizei length, const char *label)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ObjectPtrLabel] is unimplemented, please implement it.");
	}

	void CppGL::PatchParameteri(enumeration pname, int value)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[PatchParameteri] is unimplemented, please implement it.");
	}

	void CppGL::PopDebugGroup()
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[PopDebugGroup] is unimplemented, please implement it.");
	}

	void CppGL::PrimitiveBoundingBox(float minX, float minY, float minZ, float minW, float maxX, float maxY, float maxZ, float maxW)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[PrimitiveBoundingBox] is unimplemented, please implement it.");
	}

	void CppGL::PushDebugGroup(enumeration source, uint id, sizei length, const char *message)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[PushDebugGroup] is unimplemented, please implement it.");
	}

	void CppGL::ReadnPixels(int x, int y, sizei width, sizei height, enumeration format, enumeration type, sizei bufSize, void *data)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[ReadnPixels] is unimplemented, please implement it.");
	}

	void CppGL::SamplerParameterIiv(uint sampler, enumeration pname, const int *param)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[SamplerParameterIiv] is unimplemented, please implement it.");
	}

	void CppGL::SamplerParameterIuiv(uint sampler, enumeration pname, const uint *param)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[SamplerParameterIuiv] is unimplemented, please implement it.");
	}

	void CppGL::TexBuffer(enumeration target, enumeration internalformat, uint buffer)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexBuffer] is unimplemented, please implement it.");
	}

	void CppGL::TexBufferRange(enumeration target, enumeration internalformat, uint buffer, intptr offset, sizeiptr size)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexBufferRange] is unimplemented, please implement it.");
	}

	void CppGL::TexParameterIiv(enumeration target, enumeration pname, const int *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexParameterIiv] is unimplemented, please implement it.");
	}

	void CppGL::TexParameterIuiv(enumeration target, enumeration pname, const uint *params)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexParameterIuiv] is unimplemented, please implement it.");
	}

	void CppGL::TexStorage3DMultisample(enumeration target, sizei samples, enumeration internalformat, sizei width, sizei height, sizei depth, boolean fixedsamplelocations)
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "the function[TexStorage3DMultisample] is unimplemented, please implement it.");
	}

}