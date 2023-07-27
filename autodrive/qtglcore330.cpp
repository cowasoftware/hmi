#include <iostream>

#include "qtglcore330.h"

QtGLCORE330::QtGLCORE330()
{
	funs_ = new QOpenGLFunctions_3_3_Core();
	funs_->initializeOpenGLFunctions();

	std::cout << "Use OpenGL core 330" << std::endl;
}

QtGLCORE330::QtGLCORE330(QOpenGLContext *context)
{
	funs_ = context->versionFunctions<QOpenGLFunctions_3_3_Core>();
	funs_->initializeOpenGLFunctions();

	std::cout << "Use OpenGL core 330" << std::endl;
}

QtGLCORE330::~QtGLCORE330()
{
	delete funs_;
}

cppgl::GLSLVersion QtGLCORE330::GetGLSLVersion()
{
	return cppgl::GLSLVersion{3, 3, 0, "core"};
}

void QtGLCORE330::BindTexture(cppgl::enumeration target, cppgl::uint texture)
{
	funs_->glBindTexture(target, texture);
}

void QtGLCORE330::BlendFunc(cppgl::enumeration sfactor, cppgl::enumeration dfactor)
{
	funs_->glBlendFunc(sfactor, dfactor);
}

void QtGLCORE330::Clear(cppgl::bitfield mask)
{
	funs_->glClear(mask);
}

void QtGLCORE330::ClearColor(cppgl::clampf red, cppgl::clampf green, cppgl::clampf blue, cppgl::clampf alpha)
{
	funs_->glClearColor(red, green, blue, alpha);
}

void QtGLCORE330::ClearStencil(int s)
{
	funs_->glClearStencil(s);
}

void QtGLCORE330::ColorMask(cppgl::boolean red, cppgl::boolean green, cppgl::boolean blue, cppgl::boolean alpha)
{
	funs_->glColorMask(red, green, blue, alpha);
}

void QtGLCORE330::CopyTexImage2D(cppgl::enumeration target, int level, cppgl::enumeration internalformat, int x, int y, cppgl::sizei width, cppgl::sizei height, int border)
{
	funs_->glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

void QtGLCORE330::CopyTexSubImage2D(cppgl::enumeration target, int level, int xoffset, int yoffset, int x, int y, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

void QtGLCORE330::CullFace(cppgl::enumeration mode)
{
	funs_->glCullFace(mode);
}

void QtGLCORE330::DeleteTextures(cppgl::sizei n, const cppgl::uint *textures)
{
	funs_->glDeleteTextures(n, textures);
}

void QtGLCORE330::DepthFunc(cppgl::enumeration func)
{
	funs_->glDepthFunc(func);
}

void QtGLCORE330::DepthMask(cppgl::boolean flag)
{
	funs_->glDepthMask(flag);
}

void QtGLCORE330::Disable(cppgl::enumeration cap)
{
	funs_->glDisable(cap);
}

void QtGLCORE330::DrawArrays(cppgl::enumeration mode, int first, cppgl::sizei count)
{
	funs_->glDrawArrays(mode, first, count);
}

void QtGLCORE330::DrawElements(cppgl::enumeration mode, cppgl::sizei count, cppgl::enumeration type, const void *indices)
{
	funs_->glDrawElements(mode, count, type, indices);
}

void QtGLCORE330::Enable(cppgl::enumeration cap)
{
	funs_->glEnable(cap);
}

void QtGLCORE330::Finish()
{
	funs_->glFinish();
}

void QtGLCORE330::Flush()
{
	funs_->glFlush();
}

void QtGLCORE330::FrontFace(cppgl::enumeration mode)
{
	funs_->glFrontFace(mode);
}

void QtGLCORE330::GenTextures(cppgl::sizei n, cppgl::uint *textures)
{
	funs_->glGenTextures(n, textures);
}

void QtGLCORE330::GetBooleanv(cppgl::enumeration pname, cppgl::boolean *params)
{
	funs_->glGetBooleanv(pname, params);
}

cppgl::enumeration QtGLCORE330::GetError()
{
	return funs_->glGetError();
}

void QtGLCORE330::GetFloatv(cppgl::enumeration pname, float *params)
{
	funs_->glGetFloatv(pname, params);
}

void QtGLCORE330::GetIntegerv(cppgl::enumeration pname, int *params)
{
	funs_->glGetIntegerv(pname, params);
}

const cppgl::ubyte *QtGLCORE330::GetString(cppgl::enumeration name)
{
	return funs_->glGetString(name);
}

void QtGLCORE330::GetTexParameterfv(cppgl::enumeration target, cppgl::enumeration pname, float *params)
{
	funs_->glGetTexParameterfv(target, pname, params);
}

void QtGLCORE330::GetTexParameteriv(cppgl::enumeration target, cppgl::enumeration pname, int *params)
{
	funs_->glGetTexParameteriv(target, pname, params);
}

void QtGLCORE330::Hint(cppgl::enumeration target, cppgl::enumeration mode)
{
	funs_->glHint(target, mode);
}

cppgl::boolean QtGLCORE330::IsEnabled(cppgl::enumeration cap)
{
	return funs_->glIsEnabled(cap);
}

cppgl::boolean QtGLCORE330::IsTexture(cppgl::uint texture)
{
	return funs_->glIsTexture(texture);
}

void QtGLCORE330::LineWidth(float width)
{
	funs_->glLineWidth(width);
}

void QtGLCORE330::PixelStorei(cppgl::enumeration pname, int param)
{
	funs_->glPixelStorei(pname, param);
}

void QtGLCORE330::PolygonOffset(float factor, float units)
{
	funs_->glPolygonOffset(factor, units);
}

void QtGLCORE330::ReadPixels(int x, int y, cppgl::sizei width, cppgl::sizei height, cppgl::enumeration format, cppgl::enumeration type, void *pixels)
{
	funs_->glReadPixels(x, y, width, height, format, type, pixels);
}

void QtGLCORE330::Scissor(int x, int y, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glScissor(x, y, width, height);
}

void QtGLCORE330::StencilFunc(cppgl::enumeration func, int ref, cppgl::uint mask)
{
	funs_->glStencilFunc(func, ref, mask);
}

void QtGLCORE330::StencilMask(cppgl::uint mask)
{
	funs_->glStencilMask(mask);
}

void QtGLCORE330::StencilOp(cppgl::enumeration fail, cppgl::enumeration zfail, cppgl::enumeration zpass)
{
	funs_->glStencilOp(fail, zfail, zpass);
}

void QtGLCORE330::TexImage2D(cppgl::enumeration target, int level, int internalformat, cppgl::sizei width, cppgl::sizei height, int border, cppgl::enumeration format, cppgl::enumeration type, const void *pixels)
{
	funs_->glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void QtGLCORE330::TexImage2DMultisample(cppgl::enumeration target, cppgl::sizei samples, int internalformat, cppgl::sizei width, cppgl::sizei height, bool fixedsamplelocations)
{
	funs_->glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

void QtGLCORE330::TexParameterf(cppgl::enumeration target, cppgl::enumeration pname, float param)
{
	funs_->glTexParameterf(target, pname, param);
}

void QtGLCORE330::TexParameterfv(cppgl::enumeration target, cppgl::enumeration pname, const float *params)
{
	funs_->glTexParameterfv(target, pname, params);
}

void QtGLCORE330::TexParameteri(cppgl::enumeration target, cppgl::enumeration pname, int param)
{
	funs_->glTexParameteri(target, pname, param);
}

void QtGLCORE330::TexParameteriv(cppgl::enumeration target, cppgl::enumeration pname, const int *params)
{
	funs_->glTexParameteriv(target, pname, params);
}

void QtGLCORE330::TexSubImage2D(cppgl::enumeration target, int level, int xoffset, int yoffset, cppgl::sizei width, cppgl::sizei height, cppgl::enumeration format, cppgl::enumeration type, const void *pixels)
{
	funs_->glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void QtGLCORE330::Viewport(int x, int y, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glViewport(x, y, width, height);
}

void QtGLCORE330::ActiveTexture(cppgl::enumeration texture)
{
	funs_->glActiveTexture(texture);
}

void QtGLCORE330::AttachShader(cppgl::uint program, cppgl::uint shader)
{
	funs_->glAttachShader(program, shader);
}

void QtGLCORE330::BindAttribLocation(cppgl::uint program, cppgl::uint index, const char *name)
{
	funs_->glBindAttribLocation(program, index, name);
}

void QtGLCORE330::BindBuffer(cppgl::enumeration target, cppgl::uint buffer)
{
	funs_->glBindBuffer(target, buffer);
}

void QtGLCORE330::BindFramebuffer(cppgl::enumeration target, cppgl::uint framebuffer)
{
	funs_->glBindFramebuffer(target, framebuffer);
}

void QtGLCORE330::BindRenderbuffer(cppgl::enumeration target, cppgl::uint renderbuffer)
{
	funs_->glBindRenderbuffer(target, renderbuffer);
}

void QtGLCORE330::BlendColor(cppgl::clampf red, cppgl::clampf green, cppgl::clampf blue, cppgl::clampf alpha)
{
	funs_->glBlendColor(red, green, blue, alpha);
}

void QtGLCORE330::BlendEquation(cppgl::enumeration mode)
{
	funs_->glBlendEquation(mode);
}

void QtGLCORE330::BlendEquationSeparate(cppgl::enumeration modeRGB, cppgl::enumeration modeAlpha)
{
	funs_->glBlendEquationSeparate(modeRGB, modeAlpha);
}

void QtGLCORE330::BlendFuncSeparate(cppgl::enumeration srcRGB, cppgl::enumeration dstRGB, cppgl::enumeration srcAlpha, cppgl::enumeration dstAlpha)
{
	funs_->glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void QtGLCORE330::BufferData(cppgl::enumeration target, cppgl::sizeiptr size, const void *data, cppgl::enumeration usage)
{
	funs_->glBufferData(target, size, data, usage);
}

void QtGLCORE330::BufferSubData(cppgl::enumeration target, cppgl::intptr offset, cppgl::sizeiptr size, const void *data)
{
	funs_->glBufferSubData(target, offset, size, data);
}

cppgl::enumeration QtGLCORE330::CheckFramebufferStatus(cppgl::enumeration target)
{
	return funs_->glCheckFramebufferStatus(target);
}

void QtGLCORE330::ClearDepthf(cppgl::clampf depth)
{
	// funs_->glClearDepthf(depth);
}

void QtGLCORE330::CompileShader(cppgl::uint shader)
{
	funs_->glCompileShader(shader);
}

void QtGLCORE330::CompressedTexImage2D(cppgl::enumeration target, int level, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height, int border, cppgl::sizei imageSize, const void *data)
{
	funs_->glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

void QtGLCORE330::CompressedTexSubImage2D(cppgl::enumeration target, int level, int xoffset, int yoffset, cppgl::sizei width, cppgl::sizei height, cppgl::enumeration format, cppgl::sizei imageSize, const void *data)
{
	funs_->glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

cppgl::uint QtGLCORE330::CreateProgram()
{
	return funs_->glCreateProgram();
}

cppgl::uint QtGLCORE330::CreateShader(cppgl::enumeration type)
{
	return funs_->glCreateShader(type);
}

void QtGLCORE330::DeleteBuffers(cppgl::sizei n, const cppgl::uint *buffers)
{
	funs_->glDeleteBuffers(n, buffers);
}

void QtGLCORE330::DeleteFramebuffers(cppgl::sizei n, const cppgl::uint *framebuffers)
{
	funs_->glDeleteFramebuffers(n, framebuffers);
}

void QtGLCORE330::DeleteProgram(cppgl::uint program)
{
	funs_->glDeleteProgram(program);
}

void QtGLCORE330::DeleteRenderbuffers(cppgl::sizei n, const cppgl::uint *renderbuffers)
{
	funs_->glDeleteRenderbuffers(n, renderbuffers);
}

void QtGLCORE330::DeleteShader(cppgl::uint shader)
{
	funs_->glDeleteShader(shader);
}

void QtGLCORE330::DepthRangef(cppgl::clampf zNear, cppgl::clampf zFar)
{
	// funs_->glDepthRangef(zNear, zFar);
}

void QtGLCORE330::DetachShader(cppgl::uint program, cppgl::uint shader)
{
	funs_->glDetachShader(program, shader);
}

void QtGLCORE330::DisableVertexAttribArray(cppgl::uint index)
{
	funs_->glDisableVertexAttribArray(index);
}

void QtGLCORE330::EnableVertexAttribArray(cppgl::uint index)
{
	funs_->glEnableVertexAttribArray(index);
}

void QtGLCORE330::FramebufferRenderbuffer(cppgl::enumeration target, cppgl::enumeration attachment, cppgl::enumeration renderbuffertarget, cppgl::uint renderbuffer)
{
	funs_->glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void QtGLCORE330::FramebufferTexture2D(cppgl::enumeration target, cppgl::enumeration attachment, cppgl::enumeration textarget, cppgl::uint texture, int level)
{
	funs_->glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void QtGLCORE330::GenBuffers(cppgl::sizei n, cppgl::uint *buffers)
{
	funs_->glGenBuffers(n, buffers);
}

void QtGLCORE330::GenerateMipmap(cppgl::enumeration target)
{
	funs_->glGenerateMipmap(target);
}

void QtGLCORE330::GenFramebuffers(cppgl::sizei n, cppgl::uint *framebuffers)
{
	funs_->glGenFramebuffers(n, framebuffers);
}

void QtGLCORE330::GenRenderbuffers(cppgl::sizei n, cppgl::uint *renderbuffers)
{
	funs_->glGenRenderbuffers(n, renderbuffers);
}

void QtGLCORE330::GetActiveAttrib(cppgl::uint program, cppgl::uint index, cppgl::sizei bufsize, cppgl::sizei *length, int *size, cppgl::enumeration *type, char *name)
{
	funs_->glGetActiveAttrib(program, index, bufsize, length, size, type, name);
}

void QtGLCORE330::GetActiveUniform(cppgl::uint program, cppgl::uint index, cppgl::sizei bufsize, cppgl::sizei *length, int *size, cppgl::enumeration *type, char *name)
{
	funs_->glGetActiveUniform(program, index, bufsize, length, size, type, name);
}

void QtGLCORE330::GetAttachedShaders(cppgl::uint program, cppgl::sizei maxcount, cppgl::sizei *count, cppgl::uint *shaders)
{
	funs_->glGetAttachedShaders(program, maxcount, count, shaders);
}

int QtGLCORE330::GetAttribLocation(cppgl::uint program, const char *name)
{
	return funs_->glGetAttribLocation(program, name);
}

void QtGLCORE330::GetBufferParameteriv(cppgl::enumeration target, cppgl::enumeration pname, int *params)
{
	funs_->glGetBufferParameteriv(target, pname, params);
}

void QtGLCORE330::GetFramebufferAttachmentParameteriv(cppgl::enumeration target, cppgl::enumeration attachment, cppgl::enumeration pname, int *params)
{
	funs_->glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}

void QtGLCORE330::GetProgramiv(cppgl::uint program, cppgl::enumeration pname, int *params)
{
	funs_->glGetProgramiv(program, pname, params);
}

void QtGLCORE330::GetProgramInfoLog(cppgl::uint program, cppgl::sizei bufsize, cppgl::sizei *length, char *infolog)
{
	funs_->glGetProgramInfoLog(program, bufsize, length, infolog);
}

void QtGLCORE330::GetRenderbufferParameteriv(cppgl::enumeration target, cppgl::enumeration pname, int *params)
{
	funs_->glGetRenderbufferParameteriv(target, pname, params);
}

void QtGLCORE330::GetShaderiv(cppgl::uint shader, cppgl::enumeration pname, int *params)
{
	funs_->glGetShaderiv(shader, pname, params);
}

void QtGLCORE330::GetShaderInfoLog(cppgl::uint shader, cppgl::sizei bufsize, cppgl::sizei *length, char *infolog)
{
	funs_->glGetShaderInfoLog(shader, bufsize, length, infolog);
}

void QtGLCORE330::GetShaderPrecisionFormat(cppgl::enumeration shadertype, cppgl::enumeration precisiontype, int *range, int *precision)
{
	// funs_->glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}

void QtGLCORE330::GetShaderSource(cppgl::uint shader, cppgl::sizei bufsize, cppgl::sizei *length, char *source)
{
	funs_->glGetShaderSource(shader, bufsize, length, source);
}

void QtGLCORE330::GetUniformfv(cppgl::uint program, int location, float *params)
{
	funs_->glGetUniformfv(program, location, params);
}

void QtGLCORE330::GetUniformiv(cppgl::uint program, int location, int *params)
{
	funs_->glGetUniformiv(program, location, params);
}

int QtGLCORE330::GetUniformLocation(cppgl::uint program, const char *name)
{
	return funs_->glGetUniformLocation(program, name);
}

void QtGLCORE330::GetVertexAttribfv(cppgl::uint index, cppgl::enumeration pname, float *params)
{
	funs_->glGetVertexAttribfv(index, pname, params);
}

void QtGLCORE330::GetVertexAttribiv(cppgl::uint index, cppgl::enumeration pname, int *params)
{
	funs_->glGetVertexAttribiv(index, pname, params);
}

void QtGLCORE330::GetVertexAttribPointerv(cppgl::uint index, cppgl::enumeration pname, void **pointer)
{
	funs_->glGetVertexAttribPointerv(index, pname, pointer);
}

cppgl::boolean QtGLCORE330::IsBuffer(cppgl::uint buffer)
{
	return funs_->glIsBuffer(buffer);
}

cppgl::boolean QtGLCORE330::IsFramebuffer(cppgl::uint framebuffer)
{
	return funs_->glIsFramebuffer(framebuffer);
}

cppgl::boolean QtGLCORE330::IsProgram(cppgl::uint program)
{
	return funs_->glIsProgram(program);
}

cppgl::boolean QtGLCORE330::IsRenderbuffer(cppgl::uint renderbuffer)
{
	return funs_->glIsRenderbuffer(renderbuffer);
}

cppgl::boolean QtGLCORE330::IsShader(cppgl::uint shader)
{
	return funs_->glIsShader(shader);
}

void QtGLCORE330::LinkProgram(cppgl::uint program)
{
	funs_->glLinkProgram(program);
}

void QtGLCORE330::ReleaseShaderCompiler()
{
	// funs_->glReleaseShaderCompiler();
}

void QtGLCORE330::RenderbufferStorage(cppgl::enumeration target, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glRenderbufferStorage(target, internalformat, width, height);
}

void QtGLCORE330::SampleCoverage(cppgl::clampf value, cppgl::boolean invert)
{
	funs_->glSampleCoverage(value, invert);
}

void QtGLCORE330::ShaderBinary(int n, const cppgl::uint *shaders, cppgl::enumeration binaryformat, const void *binary, int length)
{
	// funs_->glShaderBinary(n, shaders, binaryformat, binary, length);
}

void QtGLCORE330::ShaderSource(cppgl::uint shader, cppgl::sizei count, const char **string, const int *length)
{
	funs_->glShaderSource(shader, count, string, length);
}

void QtGLCORE330::StencilFuncSeparate(cppgl::enumeration face, cppgl::enumeration func, int ref, cppgl::uint mask)
{
	funs_->glStencilFuncSeparate(face, func, ref, mask);
}

void QtGLCORE330::StencilMaskSeparate(cppgl::enumeration face, cppgl::uint mask)
{
	funs_->glStencilMaskSeparate(face, mask);
}

void QtGLCORE330::StencilOpSeparate(cppgl::enumeration face, cppgl::enumeration fail, cppgl::enumeration zfail, cppgl::enumeration zpass)
{
	funs_->glStencilOpSeparate(face, fail, zfail, zpass);
}

void QtGLCORE330::Uniform1f(int location, float x)
{
	funs_->glUniform1f(location, x);
}

void QtGLCORE330::Uniform1fv(int location, cppgl::sizei count, const float *v)
{
	funs_->glUniform1fv(location, count, v);
}

void QtGLCORE330::Uniform1i(int location, int x)
{
	funs_->glUniform1i(location, x);
}

void QtGLCORE330::Uniform1iv(int location, cppgl::sizei count, const int *v)
{
	funs_->glUniform1iv(location, count, v);
}

void QtGLCORE330::Uniform2f(int location, float x, float y)
{
	funs_->glUniform2f(location, x, y);
}

void QtGLCORE330::Uniform2fv(int location, cppgl::sizei count, const float *v)
{
	funs_->glUniform2fv(location, count, v);
}

void QtGLCORE330::Uniform2i(int location, int x, int y)
{
	funs_->glUniform2i(location, x, y);
}

void QtGLCORE330::Uniform2iv(int location, cppgl::sizei count, const int *v)
{
	funs_->glUniform2iv(location, count, v);
}

void QtGLCORE330::Uniform3f(int location, float x, float y, float z)
{
	funs_->glUniform3f(location, x, y, z);
}

void QtGLCORE330::Uniform3fv(int location, cppgl::sizei count, const float *v)
{
	funs_->glUniform3fv(location, count, v);
}

void QtGLCORE330::Uniform3i(int location, int x, int y, int z)
{
	funs_->glUniform3i(location, x, y, z);
}

void QtGLCORE330::Uniform3iv(int location, cppgl::sizei count, const int *v)
{
	funs_->glUniform3iv(location, count, v);
}

void QtGLCORE330::Uniform4f(int location, float x, float y, float z, float w)
{
	funs_->glUniform4f(location, x, y, z, w);
}

void QtGLCORE330::Uniform4fv(int location, cppgl::sizei count, const float *v)
{
	funs_->glUniform4fv(location, count, v);
}

void QtGLCORE330::Uniform4i(int location, int x, int y, int z, int w)
{
	funs_->glUniform4i(location, x, y, z, w);
}

void QtGLCORE330::Uniform4iv(int location, cppgl::sizei count, const int *v)
{
	funs_->glUniform4iv(location, count, v);
}

void QtGLCORE330::UniformMatrix2fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	funs_->glUniformMatrix2fv(location, count, transpose, value);
}

void QtGLCORE330::UniformMatrix3fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	funs_->glUniformMatrix3fv(location, count, transpose, value);
}

void QtGLCORE330::UniformMatrix4fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	funs_->glUniformMatrix4fv(location, count, transpose, value);
}

void QtGLCORE330::UseProgram(cppgl::uint program)
{
	funs_->glUseProgram(program);
}

void QtGLCORE330::ValidateProgram(cppgl::uint program)
{
	funs_->glValidateProgram(program);
}

void QtGLCORE330::VertexAttrib1f(cppgl::uint indx, float x)
{
	// funs_->glVertexAttrib1f(indx, x);
}

void QtGLCORE330::VertexAttrib1fv(cppgl::uint indx, const float *values)
{
	// funs_->glVertexAttrib1fv(indx, values);
}

void QtGLCORE330::VertexAttrib2f(cppgl::uint indx, float x, float y)
{
	// funs_->glVertexAttrib2f(indx, x, y);
}

void QtGLCORE330::VertexAttrib2fv(cppgl::uint indx, const float *values)
{
	// funs_->glVertexAttrib2fv(indx, values);
}

void QtGLCORE330::VertexAttrib3f(cppgl::uint indx, float x, float y, float z)
{
	// funs_->glVertexAttrib3f(indx, x, y, z);
}

void QtGLCORE330::VertexAttrib3fv(cppgl::uint indx, const float *values)
{
	// funs_->glVertexAttrib3fv(indx, values);
}

void QtGLCORE330::VertexAttrib4f(cppgl::uint indx, float x, float y, float z, float w)
{
	// funs_->glVertexAttrib4f(indx, x, y, z, w);
}

void QtGLCORE330::VertexAttrib4fv(cppgl::uint indx, const float *values)
{
	// funs_->glVertexAttrib4fv(indx, values);
}

void QtGLCORE330::VertexAttribPointer(cppgl::uint indx, int size, cppgl::enumeration type, cppgl::boolean normalized, cppgl::sizei stride, const void *ptr)
{
	funs_->glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
}

void QtGLCORE330::BeginQuery(cppgl::enumeration target, cppgl::uint id)
{
	funs_->glBeginQuery(target, id);
}

void QtGLCORE330::BeginTransformFeedback(cppgl::enumeration primitiveMode)
{
	funs_->glBeginTransformFeedback(primitiveMode);
}

void QtGLCORE330::BindBufferBase(cppgl::enumeration target, cppgl::uint index, cppgl::uint buffer)
{
	funs_->glBindBufferBase(target, index, buffer);
}

void QtGLCORE330::BindBufferRange(cppgl::enumeration target, cppgl::uint index, cppgl::uint buffer, cppgl::intptr offset, cppgl::sizeiptr size)
{
	funs_->glBindBufferRange(target, index, buffer, offset, size);
}

void QtGLCORE330::BindSampler(cppgl::uint unit, cppgl::uint sampler)
{
	funs_->glBindSampler(unit, sampler);
}

void QtGLCORE330::BindTransformFeedback(cppgl::enumeration target, cppgl::uint id)
{
	// funs_->glBindTransformFeedback(target, id);
}

void QtGLCORE330::BindVertexArray(cppgl::uint array)
{
	funs_->glBindVertexArray(array);
}

void QtGLCORE330::BlitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, cppgl::bitfield mask, cppgl::enumeration filter)
{
	funs_->glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void QtGLCORE330::ClearBufferfi(cppgl::enumeration buffer, int drawbuffer, float depth, int stencil)
{
	funs_->glClearBufferfi(buffer, drawbuffer, depth, stencil);
}

void QtGLCORE330::ClearBufferfv(cppgl::enumeration buffer, int drawbuffer, const float *value)
{
	funs_->glClearBufferfv(buffer, drawbuffer, value);
}

void QtGLCORE330::ClearBufferiv(cppgl::enumeration buffer, int drawbuffer, const int *value)
{
	funs_->glClearBufferiv(buffer, drawbuffer, value);
}

void QtGLCORE330::ClearBufferuiv(cppgl::enumeration buffer, int drawbuffer, const cppgl::uint *value)
{
	funs_->glClearBufferuiv(buffer, drawbuffer, value);
}

void QtGLCORE330::CompressedTexImage3D(cppgl::enumeration target, int level, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height, cppgl::sizei depth, int border, cppgl::sizei imageSize, const void *data)
{
	funs_->glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
}

void QtGLCORE330::CompressedTexSubImage3D(cppgl::enumeration target, int level, int xoffset, int yoffset, int zoffset, cppgl::sizei width, cppgl::sizei height, cppgl::sizei depth, cppgl::enumeration format, cppgl::sizei imageSize, const void *data)
{
	funs_->glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

void QtGLCORE330::CopyBufferSubData(cppgl::enumeration readTarget, cppgl::enumeration writeTarget, cppgl::intptr readOffset, cppgl::intptr writeOffset, cppgl::sizeiptr size)
{
	funs_->glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
}

void QtGLCORE330::CopyTexSubImage3D(cppgl::enumeration target, int level, int xoffset, int yoffset, int zoffset, int x, int y, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

void QtGLCORE330::DeleteQueries(cppgl::sizei n, const cppgl::uint *ids)
{
	funs_->glDeleteQueries(n, ids);
}

void QtGLCORE330::DeleteSamplers(cppgl::sizei count, const cppgl::uint *samplers)
{
	funs_->glDeleteSamplers(count, samplers);
}

void QtGLCORE330::DeleteTransformFeedbacks(cppgl::sizei n, const cppgl::uint *ids)
{
	// funs_->glDeleteTransformFeedbacks(n, ids);
}

void QtGLCORE330::DeleteVertexArrays(cppgl::sizei n, const cppgl::uint *arrays)
{
	funs_->glDeleteVertexArrays(n, arrays);
}

void QtGLCORE330::DrawArraysInstanced(cppgl::enumeration mode, int first, cppgl::sizei count, cppgl::sizei instancecount)
{
	funs_->glDrawArraysInstanced(mode, first, count, instancecount);
}

void QtGLCORE330::DrawBuffers(cppgl::sizei n, const cppgl::enumeration *bufs)
{
	funs_->glDrawBuffers(n, bufs);
}

void QtGLCORE330::DrawElementsInstanced(cppgl::enumeration mode, cppgl::sizei count, cppgl::enumeration type, const void *indices, cppgl::sizei instancecount)
{
	funs_->glDrawElementsInstanced(mode, count, type, indices, instancecount);
}

void QtGLCORE330::DrawRangeElements(cppgl::enumeration mode, cppgl::uint start, cppgl::uint end, cppgl::sizei count, cppgl::enumeration type, const void *indices)
{
	funs_->glDrawRangeElements(mode, start, end, count, type, indices);
}

void QtGLCORE330::EndQuery(cppgl::enumeration target)
{
	funs_->glEndQuery(target);
}

void QtGLCORE330::EndTransformFeedback()
{
	funs_->glEndTransformFeedback();
}

void QtGLCORE330::FlushMappedBufferRange(cppgl::enumeration target, cppgl::intptr offset, cppgl::sizeiptr length)
{
	funs_->glFlushMappedBufferRange(target, offset, length);
}

void QtGLCORE330::FramebufferTextureLayer(cppgl::enumeration target, cppgl::enumeration attachment, cppgl::uint texture, int level, int layer)
{
	funs_->glFramebufferTextureLayer(target, attachment, texture, level, layer);
}

void QtGLCORE330::GenQueries(cppgl::sizei n, cppgl::uint *ids)
{
	funs_->glGenQueries(n, ids);
}

void QtGLCORE330::GenSamplers(cppgl::sizei count, cppgl::uint *samplers)
{
	funs_->glGenSamplers(count, samplers);
}

void QtGLCORE330::GenTransformFeedbacks(cppgl::sizei n, cppgl::uint *ids)
{
	// funs_->glGenTransformFeedbacks(n, ids);
}

void QtGLCORE330::GenVertexArrays(cppgl::sizei n, cppgl::uint *arrays)
{
	funs_->glGenVertexArrays(n, arrays);
}

void QtGLCORE330::GetActiveUniformBlockName(cppgl::uint program, cppgl::uint uniformBlockIndex, cppgl::sizei bufSize, cppgl::sizei *length, char *uniformBlockName)
{
	funs_->glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
}

void QtGLCORE330::GetActiveUniformBlockiv(cppgl::uint program, cppgl::uint uniformBlockIndex, cppgl::enumeration pname, int *params)
{
	funs_->glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
}

void QtGLCORE330::GetActiveUniformsiv(cppgl::uint program, cppgl::sizei uniformCount, const cppgl::uint *uniformIndices, cppgl::enumeration pname, int *params)
{
	funs_->glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
}

void QtGLCORE330::GetBufferParameteri64v(cppgl::enumeration target, cppgl::enumeration pname, cppgl::int64 *params)
{
	funs_->glGetBufferParameteri64v(target, pname, params);
}

void QtGLCORE330::GetBufferPointerv(cppgl::enumeration target, cppgl::enumeration pname, void **params)
{
	funs_->glGetBufferPointerv(target, pname, params);
}

int QtGLCORE330::GetFragDataLocation(cppgl::uint program, const char *name)
{
	return funs_->glGetFragDataLocation(program, name);
}

void QtGLCORE330::GetInteger64i_v(cppgl::enumeration target, cppgl::uint index, cppgl::int64 *data)
{
	funs_->glGetInteger64i_v(target, index, data);
}

void QtGLCORE330::GetInteger64v(cppgl::enumeration pname, cppgl::int64 *data)
{
	funs_->glGetInteger64v(pname, data);
}

void QtGLCORE330::GetIntegeri_v(cppgl::enumeration target, cppgl::uint index, int *data)
{
	funs_->glGetIntegeri_v(target, index, data);
}

void QtGLCORE330::GetInternalformativ(cppgl::enumeration target, cppgl::enumeration internalformat, cppgl::enumeration pname, cppgl::sizei bufSize, int *params)
{
	// funs_->glGetInternalformativ(target, internalformat, pname, bufSize, params);
}

void QtGLCORE330::GetProgramBinary(cppgl::uint program, cppgl::sizei bufSize, cppgl::sizei *length, cppgl::enumeration *binaryFormat, void *binary)
{
	// funs_->glGetProgramBinary(program, bufSize, length, binaryFormat, binary);
}

void QtGLCORE330::GetQueryObjectuiv(cppgl::uint id, cppgl::enumeration pname, cppgl::uint *params)
{
	funs_->glGetQueryObjectuiv(id, pname, params);
}

void QtGLCORE330::GetQueryiv(cppgl::enumeration target, cppgl::enumeration pname, int *params)
{
	funs_->glGetQueryiv(target, pname, params);
}

void QtGLCORE330::GetSamplerParameterfv(cppgl::uint sampler, cppgl::enumeration pname, float *params)
{
	funs_->glGetSamplerParameterfv(sampler, pname, params);
}

void QtGLCORE330::GetSamplerParameteriv(cppgl::uint sampler, cppgl::enumeration pname, int *params)
{
	funs_->glGetSamplerParameteriv(sampler, pname, params);
}

const cppgl::ubyte *QtGLCORE330::GetStringi(cppgl::enumeration name, cppgl::uint index)
{
	return funs_->glGetStringi(name, index);
}

void QtGLCORE330::GetTransformFeedbackVarying(cppgl::uint program, cppgl::uint index, cppgl::sizei bufSize, cppgl::sizei *length, cppgl::sizei *size, cppgl::enumeration *type, char *name)
{
	funs_->glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
}

cppgl::uint QtGLCORE330::GetUniformBlockIndex(cppgl::uint program, const char *uniformBlockName)
{
	return funs_->glGetUniformBlockIndex(program, uniformBlockName);
}

void QtGLCORE330::GetUniformIndices(cppgl::uint program, cppgl::sizei uniformCount, const char *const *uniformNames, cppgl::uint *uniformIndices)
{
	funs_->glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
}

void QtGLCORE330::GetUniformuiv(cppgl::uint program, int location, cppgl::uint *params)
{
	funs_->glGetUniformuiv(program, location, params);
}

void QtGLCORE330::GetVertexAttribIiv(cppgl::uint index, cppgl::enumeration pname, int *params)
{
	funs_->glGetVertexAttribIiv(index, pname, params);
}

void QtGLCORE330::GetVertexAttribIuiv(cppgl::uint index, cppgl::enumeration pname, cppgl::uint *params)
{
	funs_->glGetVertexAttribIuiv(index, pname, params);
}

void QtGLCORE330::InvalidateFramebuffer(cppgl::enumeration target, cppgl::sizei numAttachments, const cppgl::enumeration *attachments)
{
	// funs_->glInvalidateFramebuffer(target, numAttachments, attachments);
}

void QtGLCORE330::InvalidateSubFramebuffer(cppgl::enumeration target, cppgl::sizei numAttachments, const cppgl::enumeration *attachments, int x, int y, cppgl::sizei width, cppgl::sizei height)
{
	// funs_->glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
}

cppgl::boolean QtGLCORE330::IsQuery(cppgl::uint id)
{
	return funs_->glIsQuery(id);
}

cppgl::boolean QtGLCORE330::IsSampler(cppgl::uint sampler)
{
	return funs_->glIsSampler(sampler);
}

cppgl::boolean QtGLCORE330::IsTransformFeedback(cppgl::uint id)
{
	// return funs_->glIsTransformFeedback(id);
	return 0;
}

cppgl::boolean QtGLCORE330::IsVertexArray(cppgl::uint array)
{
	return funs_->glIsVertexArray(array);
}

void *QtGLCORE330::MapBufferRange(cppgl::enumeration target, cppgl::intptr offset, cppgl::sizeiptr length, cppgl::bitfield access)
{
	return funs_->glMapBufferRange(target, offset, length, access);
}

void QtGLCORE330::PauseTransformFeedback()
{
	// funs_->glPauseTransformFeedback();
}

void QtGLCORE330::ProgramBinary(cppgl::uint program, cppgl::enumeration binaryFormat, const void *binary, cppgl::sizei length)
{
	// funs_->glProgramBinary(program, binaryFormat, binary, length);
}

void QtGLCORE330::ProgramParameteri(cppgl::uint program, cppgl::enumeration pname, int value)
{
	// funs_->glProgramParameteri(program, pname, value);
}

void QtGLCORE330::ReadBuffer(cppgl::enumeration src)
{
	funs_->glReadBuffer(src);
}

void QtGLCORE330::RenderbufferStorageMultisample(cppgl::enumeration target, cppgl::sizei samples, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}

void QtGLCORE330::ResumeTransformFeedback()
{
	// funs_->glResumeTransformFeedback();
}

void QtGLCORE330::SamplerParameterf(cppgl::uint sampler, cppgl::enumeration pname, float param)
{
	funs_->glSamplerParameterf(sampler, pname, param);
}

void QtGLCORE330::SamplerParameterfv(cppgl::uint sampler, cppgl::enumeration pname, const float *param)
{
	funs_->glSamplerParameterfv(sampler, pname, param);
}

void QtGLCORE330::SamplerParameteri(cppgl::uint sampler, cppgl::enumeration pname, int param)
{
	funs_->glSamplerParameteri(sampler, pname, param);
}

void QtGLCORE330::SamplerParameteriv(cppgl::uint sampler, cppgl::enumeration pname, const int *param)
{
	funs_->glSamplerParameteriv(sampler, pname, param);
}

void QtGLCORE330::TexImage3D(cppgl::enumeration target, int level, int internalformat, cppgl::sizei width, cppgl::sizei height, cppgl::sizei depth, int border, cppgl::enumeration format, cppgl::enumeration type, const void *pixels)
{
	funs_->glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

void QtGLCORE330::TexStorage2D(cppgl::enumeration target, cppgl::sizei levels, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height)
{
	// funs_->glTexStorage2D(target, levels, internalformat, width, height);
}

void QtGLCORE330::TexStorage3D(cppgl::enumeration target, cppgl::sizei levels, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height, cppgl::sizei depth)
{
	// funs_->glTexStorage3D(target, levels, internalformat, width, height, depth);
}

void QtGLCORE330::TexSubImage3D(cppgl::enumeration target, int level, int xoffset, int yoffset, int zoffset, cppgl::sizei width, cppgl::sizei height, cppgl::sizei depth, cppgl::enumeration format, cppgl::enumeration type, const void *pixels)
{
	funs_->glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

void QtGLCORE330::TransformFeedbackVaryings(cppgl::uint program, cppgl::sizei count, const char *const *varyings, cppgl::enumeration bufferMode)
{
	funs_->glTransformFeedbackVaryings(program, count, varyings, bufferMode);
}

void QtGLCORE330::Uniform1ui(int location, cppgl::uint v0)
{
	funs_->glUniform1ui(location, v0);
}

void QtGLCORE330::Uniform1uiv(int location, cppgl::sizei count, const cppgl::uint *value)
{
	funs_->glUniform1uiv(location, count, value);
}

void QtGLCORE330::Uniform2ui(int location, cppgl::uint v0, cppgl::uint v1)
{
	funs_->glUniform2ui(location, v0, v1);
}

void QtGLCORE330::Uniform2uiv(int location, cppgl::sizei count, const cppgl::uint *value)
{
	funs_->glUniform2uiv(location, count, value);
}

void QtGLCORE330::Uniform3ui(int location, cppgl::uint v0, cppgl::uint v1, cppgl::uint v2)
{
	funs_->glUniform3ui(location, v0, v1, v2);
}

void QtGLCORE330::Uniform3uiv(int location, cppgl::sizei count, const cppgl::uint *value)
{
	funs_->glUniform3uiv(location, count, value);
}

void QtGLCORE330::Uniform4ui(int location, cppgl::uint v0, cppgl::uint v1, cppgl::uint v2, cppgl::uint v3)
{
	funs_->glUniform4ui(location, v0, v1, v2, v3);
}

void QtGLCORE330::Uniform4uiv(int location, cppgl::sizei count, const cppgl::uint *value)
{
	funs_->glUniform4uiv(location, count, value);
}

void QtGLCORE330::UniformBlockBinding(cppgl::uint program, cppgl::uint uniformBlockIndex, cppgl::uint uniformBlockBinding)
{
	funs_->glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
}

void QtGLCORE330::UniformMatrix2x3fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	funs_->glUniformMatrix2x3fv(location, count, transpose, value);
}

void QtGLCORE330::UniformMatrix2x4fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	funs_->glUniformMatrix2x4fv(location, count, transpose, value);
}

void QtGLCORE330::UniformMatrix3x2fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	funs_->glUniformMatrix3x2fv(location, count, transpose, value);
}

void QtGLCORE330::UniformMatrix3x4fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	funs_->glUniformMatrix3x4fv(location, count, transpose, value);
}

void QtGLCORE330::UniformMatrix4x2fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	funs_->glUniformMatrix4x2fv(location, count, transpose, value);
}

void QtGLCORE330::UniformMatrix4x3fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	funs_->glUniformMatrix4x3fv(location, count, transpose, value);
}

cppgl::boolean QtGLCORE330::UnmapBuffer(cppgl::enumeration target)
{
	return funs_->glUnmapBuffer(target);
}

void QtGLCORE330::VertexAttribDivisor(cppgl::uint index, cppgl::uint divisor)
{
	funs_->glVertexAttribDivisor(index, divisor);
}

void QtGLCORE330::VertexAttribI4i(cppgl::uint index, int x, int y, int z, int w)
{
	// funs_->glVertexAttribI4i(index, x, y, z, w);
}

void QtGLCORE330::VertexAttribI4iv(cppgl::uint index, const int *v)
{
	// funs_->glVertexAttribI4iv(index, v);
}

void QtGLCORE330::VertexAttribI4ui(cppgl::uint index, cppgl::uint x, cppgl::uint y, cppgl::uint z, cppgl::uint w)
{
	// funs_->glVertexAttribI4ui(index, x, y, z, w);
}

void QtGLCORE330::VertexAttribI4uiv(cppgl::uint index, const cppgl::uint *v)
{
	// funs_->glVertexAttribI4uiv(index, v);
}

void QtGLCORE330::VertexAttribIPointer(cppgl::uint index, int size, cppgl::enumeration type, cppgl::sizei stride, const void *pointer)
{
	funs_->glVertexAttribIPointer(index, size, type, stride, pointer);
}

void QtGLCORE330::ActiveShaderProgram(cppgl::uint pipeline, cppgl::uint program)
{
	// funs_->glActiveShaderProgram(pipeline, program);
}

void QtGLCORE330::BindImageTexture(cppgl::uint unit, cppgl::uint texture, int level, cppgl::boolean layered, int layer, cppgl::enumeration access, cppgl::enumeration format)
{
	// funs_->glBindImageTexture(unit, texture, level, layered, layer, access, format);
}

void QtGLCORE330::BindProgramPipeline(cppgl::uint pipeline)
{
	// funs_->glBindProgramPipeline(pipeline);
}

void QtGLCORE330::BindVertexBuffer(cppgl::uint bindingindex, cppgl::uint buffer, cppgl::intptr offset, cppgl::sizei stride)
{
	// funs_->glBindVertexBuffer(bindingindex, buffer, offset, stride);
}

cppgl::uint QtGLCORE330::CreateShaderProgramv(cppgl::enumeration type, cppgl::sizei count, const char *const *strings)
{
	// return funs_->glCreateShaderProgramv(type, count, strings);
	return 0;
}

void QtGLCORE330::DeleteProgramPipelines(cppgl::sizei n, const cppgl::uint *pipelines)
{
	// funs_->glDeleteProgramPipelines(n, pipelines);
}

void QtGLCORE330::DispatchCompute(cppgl::uint num_groups_x, cppgl::uint num_groups_y, cppgl::uint num_groups_z)
{
	// funs_->glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
}

void QtGLCORE330::DispatchComputeIndirect(cppgl::intptr indirect)
{
	// funs_->glDispatchComputeIndirect(indirect);
}

void QtGLCORE330::DrawArraysIndirect(cppgl::enumeration mode, const void *indirect)
{
	// funs_->glDrawArraysIndirect(mode, indirect);
}

void QtGLCORE330::DrawElementsIndirect(cppgl::enumeration mode, cppgl::enumeration type, const void *indirect)
{
	// funs_->glDrawElementsIndirect(mode, type, indirect);
}

void QtGLCORE330::FramebufferParameteri(cppgl::enumeration target, cppgl::enumeration pname, int param)
{
	// funs_->glFramebufferParameteri(target, pname, param);
}

void QtGLCORE330::GenProgramPipelines(cppgl::sizei n, cppgl::uint *pipelines)
{
	// funs_->glGenProgramPipelines(n, pipelines);
}

void QtGLCORE330::GetBooleani_v(cppgl::enumeration target, cppgl::uint index, cppgl::boolean *data)
{
	// funs_->glGetBooleani_v(target, index, data);
}

void QtGLCORE330::GetFramebufferParameteriv(cppgl::enumeration target, cppgl::enumeration pname, int *params)
{
	// funs_->glGetFramebufferParameteriv(target, pname, params);
}

void QtGLCORE330::GetMultisamplefv(cppgl::enumeration pname, cppgl::uint index, float *val)
{
	// funs_->glGetMultisamplefv(pname, index, val);
}

void QtGLCORE330::GetProgramInterfaceiv(cppgl::uint program, cppgl::enumeration programInterface, cppgl::enumeration pname, int *params)
{
	// funs_->glGetProgramInterfaceiv(program, programInterface, pname, params);
}

void QtGLCORE330::GetProgramPipelineInfoLog(cppgl::uint pipeline, cppgl::sizei bufSize, cppgl::sizei *length, char *infoLog)
{
	// funs_->glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
}

void QtGLCORE330::GetProgramPipelineiv(cppgl::uint pipeline, cppgl::enumeration pname, int *params)
{
	// funs_->glGetProgramPipelineiv(pipeline, pname, params);
}

cppgl::uint QtGLCORE330::GetProgramResourceIndex(cppgl::uint program, cppgl::enumeration programInterface, const char *name)
{
	// return funs_->glGetProgramResourceIndex(program, programInterface, name);
	return 0;
}

int QtGLCORE330::GetProgramResourceLocation(cppgl::uint program, cppgl::enumeration programInterface, const char *name)
{
	// return funs_->glGetProgramResourceLocation(program, programInterface, name);
	return 0;
}

void QtGLCORE330::GetProgramResourceName(cppgl::uint program, cppgl::enumeration programInterface, cppgl::uint index, cppgl::sizei bufSize, cppgl::sizei *length, char *name)
{
	// funs_->glGetProgramResourceName(program, programInterface, index, bufSize, length, name);
}

void QtGLCORE330::GetProgramResourceiv(cppgl::uint program, cppgl::enumeration programInterface, cppgl::uint index, cppgl::sizei propCount, const cppgl::enumeration *props, cppgl::sizei bufSize, cppgl::sizei *length, int *params)
{
	// funs_->glGetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
}

void QtGLCORE330::GetTexLevelParameterfv(cppgl::enumeration target, int level, cppgl::enumeration pname, float *params)
{
	funs_->glGetTexLevelParameterfv(target, level, pname, params);
}

void QtGLCORE330::GetTexLevelParameteriv(cppgl::enumeration target, int level, cppgl::enumeration pname, int *params)
{
	funs_->glGetTexLevelParameteriv(target, level, pname, params);
}

cppgl::boolean QtGLCORE330::IsProgramPipeline(cppgl::uint pipeline)
{
	// return funs_->glIsProgramPipeline(pipeline);
	return 0;
}

void QtGLCORE330::MemoryBarrierByRegion(cppgl::bitfield barriers)
{
	// funs_->glMemoryBarrierByRegion(barriers);
}

void QtGLCORE330::ProgramUniform1f(cppgl::uint program, int location, float v0)
{
	// funs_->glProgramUniform1f(program, location, v0);
}

void QtGLCORE330::ProgramUniform1fv(cppgl::uint program, int location, cppgl::sizei count, const float *value)
{
	// funs_->glProgramUniform1fv(program, location, count, value);
}

void QtGLCORE330::ProgramUniform1i(cppgl::uint program, int location, int v0)
{
	// funs_->glProgramUniform1i(program, location, v0);
}

void QtGLCORE330::ProgramUniform1iv(cppgl::uint program, int location, cppgl::sizei count, const int *value)
{
	// funs_->glProgramUniform1iv(program, location, count, value);
}

void QtGLCORE330::ProgramUniform1ui(cppgl::uint program, int location, cppgl::uint v0)
{
	// funs_->glProgramUniform1ui(program, location, v0);
}

void QtGLCORE330::ProgramUniform1uiv(cppgl::uint program, int location, cppgl::sizei count, const cppgl::uint *value)
{
	// funs_->glProgramUniform1uiv(program, location, count, value);
}

void QtGLCORE330::ProgramUniform2f(cppgl::uint program, int location, float v0, float v1)
{
	// funs_->glProgramUniform2f(program, location, v0, v1);
}

void QtGLCORE330::ProgramUniform2fv(cppgl::uint program, int location, cppgl::sizei count, const float *value)
{
	// funs_->glProgramUniform2fv(program, location, count, value);
}

void QtGLCORE330::ProgramUniform2i(cppgl::uint program, int location, int v0, int v1)
{
	// funs_->glProgramUniform2i(program, location, v0, v1);
}

void QtGLCORE330::ProgramUniform2iv(cppgl::uint program, int location, cppgl::sizei count, const int *value)
{
	// funs_->glProgramUniform2iv(program, location, count, value);
}

void QtGLCORE330::ProgramUniform2ui(cppgl::uint program, int location, cppgl::uint v0, cppgl::uint v1)
{
	// funs_->glProgramUniform2ui(program, location, v0, v1);
}

void QtGLCORE330::ProgramUniform2uiv(cppgl::uint program, int location, cppgl::sizei count, const cppgl::uint *value)
{
	// funs_->glProgramUniform2uiv(program, location, count, value);
}

void QtGLCORE330::ProgramUniform3f(cppgl::uint program, int location, float v0, float v1, float v2)
{
	// funs_->glProgramUniform3f(program, location, v0, v1, v2);
}

void QtGLCORE330::ProgramUniform3fv(cppgl::uint program, int location, cppgl::sizei count, const float *value)
{
	// funs_->glProgramUniform3fv(program, location, count, value);
}

void QtGLCORE330::ProgramUniform3i(cppgl::uint program, int location, int v0, int v1, int v2)
{
	// funs_->glProgramUniform3i(program, location, v0, v1, v2);
}

void QtGLCORE330::ProgramUniform3iv(cppgl::uint program, int location, cppgl::sizei count, const int *value)
{
	// funs_->glProgramUniform3iv(program, location, count, value);
}

void QtGLCORE330::ProgramUniform3ui(cppgl::uint program, int location, cppgl::uint v0, cppgl::uint v1, cppgl::uint v2)
{
	// funs_->glProgramUniform3ui(program, location, v0, v1, v2);
}

void QtGLCORE330::ProgramUniform3uiv(cppgl::uint program, int location, cppgl::sizei count, const cppgl::uint *value)
{
	// funs_->glProgramUniform3uiv(program, location, count, value);
}

void QtGLCORE330::ProgramUniform4f(cppgl::uint program, int location, float v0, float v1, float v2, float v3)
{
	// funs_->glProgramUniform4f(program, location, v0, v1, v2, v3);
}

void QtGLCORE330::ProgramUniform4fv(cppgl::uint program, int location, cppgl::sizei count, const float *value)
{
	// funs_->glProgramUniform4fv(program, location, count, value);
}

void QtGLCORE330::ProgramUniform4i(cppgl::uint program, int location, int v0, int v1, int v2, int v3)
{
	// funs_->glProgramUniform4i(program, location, v0, v1, v2, v3);
}

void QtGLCORE330::ProgramUniform4iv(cppgl::uint program, int location, cppgl::sizei count, const int *value)
{
	// funs_->glProgramUniform4iv(program, location, count, value);
}

void QtGLCORE330::ProgramUniform4ui(cppgl::uint program, int location, cppgl::uint v0, cppgl::uint v1, cppgl::uint v2, cppgl::uint v3)
{
	// funs_->glProgramUniform4ui(program, location, v0, v1, v2, v3);
}

void QtGLCORE330::ProgramUniform4uiv(cppgl::uint program, int location, cppgl::sizei count, const cppgl::uint *value)
{
	// funs_->glProgramUniform4uiv(program, location, count, value);
}

void QtGLCORE330::ProgramUniformMatrix2fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	// funs_->glProgramUniformMatrix2fv(program, location, count, transpose, value);
}

void QtGLCORE330::ProgramUniformMatrix2x3fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	// funs_->glProgramUniformMatrix2x3fv(program, location, count, transpose, value);
}

void QtGLCORE330::ProgramUniformMatrix2x4fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	// funs_->glProgramUniformMatrix2x4fv(program, location, count, transpose, value);
}

void QtGLCORE330::ProgramUniformMatrix3fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	// funs_->glProgramUniformMatrix3fv(program, location, count, transpose, value);
}

void QtGLCORE330::ProgramUniformMatrix3x2fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	// funs_->glProgramUniformMatrix3x2fv(program, location, count, transpose, value);
}

void QtGLCORE330::ProgramUniformMatrix3x4fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	// funs_->glProgramUniformMatrix3x4fv(program, location, count, transpose, value);
}

void QtGLCORE330::ProgramUniformMatrix4fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	// funs_->glProgramUniformMatrix4fv(program, location, count, transpose, value);
}

void QtGLCORE330::ProgramUniformMatrix4x2fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	// funs_->glProgramUniformMatrix4x2fv(program, location, count, transpose, value);
}

void QtGLCORE330::ProgramUniformMatrix4x3fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float *value)
{
	// funs_->glProgramUniformMatrix4x3fv(program, location, count, transpose, value);
}

void QtGLCORE330::SampleMaski(cppgl::uint maskNumber, cppgl::bitfield mask)
{
	funs_->glSampleMaski(maskNumber, mask);
}

void QtGLCORE330::TexStorage2DMultisample(cppgl::enumeration target, cppgl::sizei samples, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height, cppgl::boolean fixedsamplelocations)
{
	// funs_->glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

void QtGLCORE330::UseProgramStages(cppgl::uint pipeline, cppgl::bitfield stages, cppgl::uint program)
{
	// funs_->glUseProgramStages(pipeline, stages, program);
}

void QtGLCORE330::ValidateProgramPipeline(cppgl::uint pipeline)
{
	// funs_->glValidateProgramPipeline(pipeline);
}

void QtGLCORE330::VertexAttribBinding(cppgl::uint attribindex, cppgl::uint bindingindex)
{
	// funs_->glVertexAttribBinding(attribindex, bindingindex);
}

void QtGLCORE330::VertexAttribFormat(cppgl::uint attribindex, int size, cppgl::enumeration type, cppgl::boolean normalized, cppgl::uint relativeoffset)
{
	// funs_->glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
}

void QtGLCORE330::VertexAttribIFormat(cppgl::uint attribindex, int size, cppgl::enumeration type, cppgl::uint relativeoffset)
{
	// funs_->glVertexAttribIFormat(attribindex, size, type, relativeoffset);
}

void QtGLCORE330::VertexBindingDivisor(cppgl::uint bindingindex, cppgl::uint divisor)
{
	// funs_->glVertexBindingDivisor(bindingindex, divisor);
}

void QtGLCORE330::BlendBarrier()
{
	// funs_->glBlendBarrier();
}

void QtGLCORE330::BlendEquationSeparatei(cppgl::uint buf, cppgl::enumeration modeRGB, cppgl::enumeration modeAlpha)
{
	// funs_->glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
}

void QtGLCORE330::BlendEquationi(cppgl::uint buf, cppgl::enumeration mode)
{
	// funs_->glBlendEquationi(buf, mode);
}

void QtGLCORE330::BlendFuncSeparatei(cppgl::uint buf, cppgl::enumeration srcRGB, cppgl::enumeration dstRGB, cppgl::enumeration srcAlpha, cppgl::enumeration dstAlpha)
{
	// funs_->glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void QtGLCORE330::BlendFunci(cppgl::uint buf, cppgl::enumeration src, cppgl::enumeration dst)
{
	// funs_->glBlendFunci(buf, src, dst);
}

void QtGLCORE330::ColorMaski(cppgl::uint index, cppgl::boolean r, cppgl::boolean g, cppgl::boolean b, cppgl::boolean a)
{
	funs_->glColorMaski(index, r, g, b, a);
}

void QtGLCORE330::CopyImageSubData(cppgl::uint srcName, cppgl::enumeration srcTarget, int srcLevel, int srcX, int srcY, int srcZ, cppgl::uint dstName, cppgl::enumeration dstTarget, int dstLevel, int dstX, int dstY, int dstZ, cppgl::sizei srcWidth, cppgl::sizei srcHeight, cppgl::sizei srcDepth)
{
	// funs_->glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}

void QtGLCORE330::DebugMessageCallback(cppgl::debugproc callback, const void *userParam)
{
	/// funs_->glDebugMessageCallback(callback, userParam);
}

void QtGLCORE330::DebugMessageControl(cppgl::enumeration source, cppgl::enumeration type, cppgl::enumeration severity, cppgl::sizei count, const cppgl::uint *ids, cppgl::boolean enabled)
{
	// funs_->glDebugMessageControl(source, type, severity, count, ids, enabled);
}

void QtGLCORE330::DebugMessageInsert(cppgl::enumeration source, cppgl::enumeration type, cppgl::uint id, cppgl::enumeration severity, cppgl::sizei length, const char *buf)
{
	// funs_->glDebugMessageInsert(source, type, id, severity, length, buf);
}

void QtGLCORE330::Disablei(cppgl::enumeration target, cppgl::uint index)
{
	funs_->glDisablei(target, index);
}

void QtGLCORE330::DrawElementsBaseVertex(cppgl::enumeration mode, cppgl::sizei count, cppgl::enumeration type, const void *indices, int basevertex)
{
	funs_->glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
}

void QtGLCORE330::DrawElementsInstancedBaseVertex(cppgl::enumeration mode, cppgl::sizei count, cppgl::enumeration type, const void *indices, cppgl::sizei instancecount, int basevertex)
{
	funs_->glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
}

void QtGLCORE330::DrawRangeElementsBaseVertex(cppgl::enumeration mode, cppgl::uint start, cppgl::uint end, cppgl::sizei count, cppgl::enumeration type, const void *indices, int basevertex)
{
	funs_->glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
}

void QtGLCORE330::Enablei(cppgl::enumeration target, cppgl::uint index)
{
	funs_->glEnablei(target, index);
}

void QtGLCORE330::FramebufferTexture(cppgl::enumeration target, cppgl::enumeration attachment, cppgl::uint texture, int level)
{
	funs_->glFramebufferTexture(target, attachment, texture, level);
}

cppgl::uint QtGLCORE330::GetDebugMessageLog(cppgl::uint count, cppgl::sizei bufSize, cppgl::enumeration *sources, cppgl::enumeration *types, cppgl::uint *ids, cppgl::enumeration *severities, cppgl::sizei *lengths, char *messageLog)
{
	// return funs_->glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
	return 0;
}

cppgl::enumeration QtGLCORE330::GetGraphicsResetStatus()
{
	// return funs_->glGetGraphicsResetStatus();
	return 0;
}

void QtGLCORE330::GetObjectLabel(cppgl::enumeration identifier, cppgl::uint name, cppgl::sizei bufSize, cppgl::sizei *length, char *label)
{
	// funs_->glGetObjectLabel(identifier, name, bufSize, length, label);
}

void QtGLCORE330::GetObjectPtrLabel(const void *ptr, cppgl::sizei bufSize, cppgl::sizei *length, char *label)
{
	// funs_->glGetObjectPtrLabel(ptr, bufSize, length, label);
}

void QtGLCORE330::GetPointerv(cppgl::enumeration pname, void **params)
{
	// funs_->glGetPointerv(pname, params);
}

void QtGLCORE330::GetSamplerParameterIiv(cppgl::uint sampler, cppgl::enumeration pname, int *params)
{
	// funs_->glGetSamplerParameterIiv(sampler, pname, params);
}

void QtGLCORE330::GetSamplerParameterIuiv(cppgl::uint sampler, cppgl::enumeration pname, cppgl::uint *params)
{
	// funs_->glGetSamplerParameterIuiv(sampler, pname, params);
}

void QtGLCORE330::GetTexParameterIiv(cppgl::enumeration target, cppgl::enumeration pname, int *params)
{
	// funs_->glGetTexParameterIiv(target, pname, params);
}

void QtGLCORE330::GetTexParameterIuiv(cppgl::enumeration target, cppgl::enumeration pname, cppgl::uint *params)
{
	// funs_->glGetTexParameterIuiv(target, pname, params);
}

void QtGLCORE330::GetnUniformfv(cppgl::uint program, int location, cppgl::sizei bufSize, float *params)
{
	// funs_->glGetnUniformfv(program, location, bufSize, params);
}

void QtGLCORE330::GetnUniformiv(cppgl::uint program, int location, cppgl::sizei bufSize, int *params)
{
	// funs_->glGetnUniformiv(program, location, bufSize, params);
}

void QtGLCORE330::GetnUniformuiv(cppgl::uint program, int location, cppgl::sizei bufSize, cppgl::uint *params)
{
	// funs_->glGetnUniformuiv(program, location, bufSize, params);
}

cppgl::boolean QtGLCORE330::IsEnabledi(cppgl::enumeration target, cppgl::uint index)
{
	return funs_->glIsEnabledi(target, index);
}

void QtGLCORE330::MinSampleShading(float value)
{
	// funs_->glMinSampleShading(value);
}

void QtGLCORE330::ObjectLabel(cppgl::enumeration identifier, cppgl::uint name, cppgl::sizei length, const char *label)
{
	// funs_->glObjectLabel(identifier, name, length, label);
}

void QtGLCORE330::ObjectPtrLabel(const void *ptr, cppgl::sizei length, const char *label)
{
	// funs_->glObjectPtrLabel(ptr, length, label);
}

void QtGLCORE330::PatchParameteri(cppgl::enumeration pname, int value)
{
	// funs_->glPatchParameteri(pname, value);
}

void QtGLCORE330::PopDebugGroup()
{
	// funs_->glPopDebugGroup();
}

void QtGLCORE330::PrimitiveBoundingBox(float minX, float minY, float minZ, float minW, float maxX, float maxY, float maxZ, float maxW)
{
	// funs_->glPrimitiveBoundingBox(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
}

void QtGLCORE330::PushDebugGroup(cppgl::enumeration source, cppgl::uint id, cppgl::sizei length, const char *message)
{
	// funs_->glPushDebugGroup(source, id, length, message);
}

void QtGLCORE330::ReadnPixels(int x, int y, cppgl::sizei width, cppgl::sizei height, cppgl::enumeration format, cppgl::enumeration type, cppgl::sizei bufSize, void *data)
{
	// funs_->glReadnPixels(x, y, width, height, format, type, bufSize, data);
}

void QtGLCORE330::SamplerParameterIiv(cppgl::uint sampler, cppgl::enumeration pname, const int *param)
{
	// funs_->glSamplerParameterIiv(sampler, pname, param);
}

void QtGLCORE330::SamplerParameterIuiv(cppgl::uint sampler, cppgl::enumeration pname, const cppgl::uint *param)
{
	// funs_->glSamplerParameterIuiv(sampler, pname, param);
}

void QtGLCORE330::TexBuffer(cppgl::enumeration target, cppgl::enumeration internalformat, cppgl::uint buffer)
{
	// funs_->glTexBuffer(target, internalformat, buffer);
}

void QtGLCORE330::TexBufferRange(cppgl::enumeration target, cppgl::enumeration internalformat, cppgl::uint buffer, cppgl::intptr offset, cppgl::sizeiptr size)
{
	// funs_->glTexBufferRange(target, internalformat, buffer, offset, size);
}

void QtGLCORE330::TexParameterIiv(cppgl::enumeration target, cppgl::enumeration pname, const int *params)
{
	// funs_->glTexParameterIiv(target, pname, params);
}

void QtGLCORE330::TexParameterIuiv(cppgl::enumeration target, cppgl::enumeration pname, const cppgl::uint *params)
{
	// funs_->glTexParameterIuiv(target, pname, params);
}

void QtGLCORE330::TexStorage3DMultisample(cppgl::enumeration target, cppgl::sizei samples, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height, cppgl::sizei depth, cppgl::boolean fixedsamplelocations)
{
	// funs_->glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}
