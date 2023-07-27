#include <iostream>

#include "./qtgles3.h"

QtGLES3::QtGLES3()
{
	funs_ = new QOpenGLExtraFunctions();
	funs_->initializeOpenGLFunctions();

	std::cout << "Use OpenGL ES 300" << std::endl;
}

QtGLES3::QtGLES3(QOpenGLContext *context)
{
	funs_ = context->extraFunctions();
	funs_->initializeOpenGLFunctions();
}

QtGLES3::~QtGLES3()
{
	delete funs_;
}

cppgl::GLSLVersion QtGLES3::GetGLSLVersion()
{
	return cppgl::GLSLVersion{3,0,0,"es"};
}

void QtGLES3::BindTexture(cppgl::enumeration target, cppgl::uint texture)
{
	funs_->glBindTexture(target, texture);
}

void QtGLES3::BlendFunc(cppgl::enumeration sfactor, cppgl::enumeration dfactor)
{
	funs_->glBlendFunc(sfactor, dfactor);
}

void QtGLES3::Clear(cppgl::bitfield mask)
{
	funs_->glClear(mask);
}

void QtGLES3::ClearColor(cppgl::clampf red, cppgl::clampf green, cppgl::clampf blue, cppgl::clampf alpha)
{
	funs_->glClearColor(red, green, blue, alpha);
}

void QtGLES3::ClearStencil(int s)
{
	funs_->glClearStencil(s);
}

void QtGLES3::ColorMask(cppgl::boolean red, cppgl::boolean green, cppgl::boolean blue, cppgl::boolean alpha)
{
	funs_->glColorMask(red, green, blue, alpha);
}

void QtGLES3::CopyTexImage2D(cppgl::enumeration target, int level, cppgl::enumeration internalformat, int x, int y, cppgl::sizei width, cppgl::sizei height, int border)
{
	funs_->glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

void QtGLES3::CopyTexSubImage2D(cppgl::enumeration target, int level, int xoffset, int yoffset, int x, int y, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

void QtGLES3::CullFace(cppgl::enumeration mode)
{
	funs_->glCullFace(mode);
}

void QtGLES3::DeleteTextures(cppgl::sizei n, const cppgl::uint* textures)
{
	funs_->glDeleteTextures(n, textures);
}

void QtGLES3::DepthFunc(cppgl::enumeration func)
{
	funs_->glDepthFunc(func);
}

void QtGLES3::DepthMask(cppgl::boolean flag)
{
	funs_->glDepthMask(flag);
}

void QtGLES3::Disable(cppgl::enumeration cap)
{
	funs_->glDisable(cap);
}

void QtGLES3::DrawArrays(cppgl::enumeration mode, int first, cppgl::sizei count)
{
	funs_->glDrawArrays(mode, first, count);
}

void QtGLES3::DrawElements(cppgl::enumeration mode, cppgl::sizei count, cppgl::enumeration type, const void* indices)
{
	funs_->glDrawElements(mode, count, type, indices);
}

void QtGLES3::Enable(cppgl::enumeration cap)
{
	funs_->glEnable(cap);
}

void QtGLES3::Finish()
{
	funs_->glFinish();
}

void QtGLES3::Flush()
{
	funs_->glFlush();
}

void QtGLES3::FrontFace(cppgl::enumeration mode)
{
	funs_->glFrontFace(mode);
}

void QtGLES3::GenTextures(cppgl::sizei n, cppgl::uint* textures)
{
	funs_->glGenTextures(n, textures);
}

void QtGLES3::GetBooleanv(cppgl::enumeration pname, cppgl::boolean* params)
{
	funs_->glGetBooleanv(pname, params);
}

cppgl::enumeration QtGLES3::GetError()
{
	return funs_->glGetError();
}

void QtGLES3::GetFloatv(cppgl::enumeration pname, float* params)
{
	funs_->glGetFloatv(pname, params);
}

void QtGLES3::GetIntegerv(cppgl::enumeration pname, int* params)
{
	funs_->glGetIntegerv(pname, params);
}

const cppgl::ubyte* QtGLES3::GetString(cppgl::enumeration name)
{
	return funs_->glGetString(name);
}

void QtGLES3::GetTexParameterfv(cppgl::enumeration target, cppgl::enumeration pname, float* params)
{
	funs_->glGetTexParameterfv(target, pname, params);
}

void QtGLES3::GetTexParameteriv(cppgl::enumeration target, cppgl::enumeration pname, int* params)
{
	funs_->glGetTexParameteriv(target, pname, params);
}

void QtGLES3::Hint(cppgl::enumeration target, cppgl::enumeration mode)
{
	funs_->glHint(target, mode);
}

cppgl::boolean QtGLES3::IsEnabled(cppgl::enumeration cap)
{
	return funs_->glIsEnabled(cap);
}

cppgl::boolean QtGLES3::IsTexture(cppgl::uint texture)
{
	return funs_->glIsTexture(texture);
}

void QtGLES3::LineWidth(float width)
{
	funs_->glLineWidth(width);
}

void QtGLES3::PixelStorei(cppgl::enumeration pname, int param)
{
	funs_->glPixelStorei(pname, param);
}

void QtGLES3::PolygonOffset(float factor, float units)
{
	funs_->glPolygonOffset(factor, units);
}

void QtGLES3::ReadPixels(int x, int y, cppgl::sizei width, cppgl::sizei height, cppgl::enumeration format, cppgl::enumeration type, void* pixels)
{
	funs_->glReadPixels(x, y, width, height, format, type, pixels);
}

void QtGLES3::Scissor(int x, int y, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glScissor(x, y, width, height);
}

void QtGLES3::StencilFunc(cppgl::enumeration func, int ref, cppgl::uint mask)
{
	funs_->glStencilFunc(func, ref, mask);
}

void QtGLES3::StencilMask(cppgl::uint mask)
{
	funs_->glStencilMask(mask);
}

void QtGLES3::StencilOp(cppgl::enumeration fail, cppgl::enumeration zfail, cppgl::enumeration zpass)
{
	funs_->glStencilOp(fail, zfail, zpass);
}

void QtGLES3::TexImage2D(cppgl::enumeration target, int level, int internalformat, cppgl::sizei width, cppgl::sizei height, int border, cppgl::enumeration format, cppgl::enumeration type, const void* pixels)
{
	funs_->glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void QtGLES3::TexParameterf(cppgl::enumeration target, cppgl::enumeration pname, float param)
{
	funs_->glTexParameterf(target, pname, param);
}

void QtGLES3::TexParameterfv(cppgl::enumeration target, cppgl::enumeration pname, const float* params)
{
	funs_->glTexParameterfv(target, pname, params);
}

void QtGLES3::TexParameteri(cppgl::enumeration target, cppgl::enumeration pname, int param)
{
	funs_->glTexParameteri(target, pname, param);
}

void QtGLES3::TexParameteriv(cppgl::enumeration target, cppgl::enumeration pname, const int* params)
{
	funs_->glTexParameteriv(target, pname, params);
}

void QtGLES3::TexSubImage2D(cppgl::enumeration target, int level, int xoffset, int yoffset, cppgl::sizei width, cppgl::sizei height, cppgl::enumeration format, cppgl::enumeration type, const void* pixels)
{
	funs_->glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void QtGLES3::Viewport(int x, int y, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glViewport(x, y, width, height);
}

void QtGLES3::ActiveTexture(cppgl::enumeration texture)
{
	funs_->glActiveTexture(texture);
}

void QtGLES3::AttachShader(cppgl::uint program, cppgl::uint shader)
{
	funs_->glAttachShader(program, shader);
}

void QtGLES3::BindAttribLocation(cppgl::uint program, cppgl::uint index, const char* name)
{
	funs_->glBindAttribLocation(program, index, name);
}

void QtGLES3::BindBuffer(cppgl::enumeration target, cppgl::uint buffer)
{
	funs_->glBindBuffer(target, buffer);
}

void QtGLES3::BindFramebuffer(cppgl::enumeration target, cppgl::uint framebuffer)
{
	funs_->glBindFramebuffer(target, framebuffer);
}

void QtGLES3::BindRenderbuffer(cppgl::enumeration target, cppgl::uint renderbuffer)
{
	funs_->glBindRenderbuffer(target, renderbuffer);
}

void QtGLES3::BlendColor(cppgl::clampf red, cppgl::clampf green, cppgl::clampf blue, cppgl::clampf alpha)
{
	funs_->glBlendColor(red, green, blue, alpha);
}

void QtGLES3::BlendEquation(cppgl::enumeration mode)
{
	funs_->glBlendEquation(mode);
}

void QtGLES3::BlendEquationSeparate(cppgl::enumeration modeRGB, cppgl::enumeration modeAlpha)
{
	funs_->glBlendEquationSeparate(modeRGB, modeAlpha);
}

void QtGLES3::BlendFuncSeparate(cppgl::enumeration srcRGB, cppgl::enumeration dstRGB, cppgl::enumeration srcAlpha, cppgl::enumeration dstAlpha)
{
	funs_->glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void QtGLES3::BufferData(cppgl::enumeration target, cppgl::sizeiptr size, const void* data, cppgl::enumeration usage)
{
	funs_->glBufferData(target, size, data, usage);
}

void QtGLES3::BufferSubData(cppgl::enumeration target, cppgl::intptr offset, cppgl::sizeiptr size, const void* data)
{
	funs_->glBufferSubData(target, offset, size, data);
}

cppgl::enumeration QtGLES3::CheckFramebufferStatus(cppgl::enumeration target)
{
	return funs_->glCheckFramebufferStatus(target);
}

void QtGLES3::ClearDepthf(cppgl::clampf depth)
{
	funs_->glClearDepthf(depth);
}

void QtGLES3::CompileShader(cppgl::uint shader)
{
	funs_->glCompileShader(shader);
}

void QtGLES3::CompressedTexImage2D(cppgl::enumeration target, int level, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height, int border, cppgl::sizei imageSize, const void* data)
{
	funs_->glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

void QtGLES3::CompressedTexSubImage2D(cppgl::enumeration target, int level, int xoffset, int yoffset, cppgl::sizei width, cppgl::sizei height, cppgl::enumeration format, cppgl::sizei imageSize, const void* data)
{
	funs_->glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

cppgl::uint QtGLES3::CreateProgram()
{
	return funs_->glCreateProgram();
}

cppgl::uint QtGLES3::CreateShader(cppgl::enumeration type)
{
	return funs_->glCreateShader(type);
}

void QtGLES3::DeleteBuffers(cppgl::sizei n, const cppgl::uint* buffers)
{
	funs_->glDeleteBuffers(n, buffers);
}

void QtGLES3::DeleteFramebuffers(cppgl::sizei n, const cppgl::uint* framebuffers)
{
	funs_->glDeleteFramebuffers(n, framebuffers);
}

void QtGLES3::DeleteProgram(cppgl::uint program)
{
	funs_->glDeleteProgram(program);
}

void QtGLES3::DeleteRenderbuffers(cppgl::sizei n, const cppgl::uint* renderbuffers)
{
	funs_->glDeleteRenderbuffers(n, renderbuffers);
}

void QtGLES3::DeleteShader(cppgl::uint shader)
{
	funs_->glDeleteShader(shader);
}

void QtGLES3::DepthRangef(cppgl::clampf zNear, cppgl::clampf zFar)
{
	funs_->glDepthRangef(zNear, zFar);
}

void QtGLES3::DetachShader(cppgl::uint program, cppgl::uint shader)
{
	funs_->glDetachShader(program, shader);
}

void QtGLES3::DisableVertexAttribArray(cppgl::uint index)
{
	funs_->glDisableVertexAttribArray(index);
}

void QtGLES3::EnableVertexAttribArray(cppgl::uint index)
{
	funs_->glEnableVertexAttribArray(index);
}

void QtGLES3::FramebufferRenderbuffer(cppgl::enumeration target, cppgl::enumeration attachment, cppgl::enumeration renderbuffertarget, cppgl::uint renderbuffer)
{
	funs_->glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void QtGLES3::FramebufferTexture2D(cppgl::enumeration target, cppgl::enumeration attachment, cppgl::enumeration textarget, cppgl::uint texture, int level)
{
	funs_->glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void QtGLES3::GenBuffers(cppgl::sizei n, cppgl::uint* buffers)
{
	funs_->glGenBuffers(n, buffers);
}

void QtGLES3::GenerateMipmap(cppgl::enumeration target)
{
	funs_->glGenerateMipmap(target);
}

void QtGLES3::GenFramebuffers(cppgl::sizei n, cppgl::uint* framebuffers)
{
	funs_->glGenFramebuffers(n, framebuffers);
}

void QtGLES3::GenRenderbuffers(cppgl::sizei n, cppgl::uint* renderbuffers)
{
	funs_->glGenRenderbuffers(n, renderbuffers);
}

void QtGLES3::GetActiveAttrib(cppgl::uint program, cppgl::uint index, cppgl::sizei bufsize, cppgl::sizei* length, int* size, cppgl::enumeration* type, char* name)
{
	funs_->glGetActiveAttrib(program, index, bufsize, length, size, type, name);
}

void QtGLES3::GetActiveUniform(cppgl::uint program, cppgl::uint index, cppgl::sizei bufsize, cppgl::sizei* length, int* size, cppgl::enumeration* type, char* name)
{
	funs_->glGetActiveUniform(program, index, bufsize, length, size, type, name);
}

void QtGLES3::GetAttachedShaders(cppgl::uint program, cppgl::sizei maxcount, cppgl::sizei* count, cppgl::uint* shaders)
{
	funs_->glGetAttachedShaders(program, maxcount, count, shaders);
}

int QtGLES3::GetAttribLocation(cppgl::uint program, const char* name)
{
	return funs_->glGetAttribLocation(program, name);
}

void QtGLES3::GetBufferParameteriv(cppgl::enumeration target, cppgl::enumeration pname, int* params)
{
	funs_->glGetBufferParameteriv(target, pname, params);
}

void QtGLES3::GetFramebufferAttachmentParameteriv(cppgl::enumeration target, cppgl::enumeration attachment, cppgl::enumeration pname, int* params)
{
	funs_->glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}

void QtGLES3::GetProgramiv(cppgl::uint program, cppgl::enumeration pname, int* params)
{
	funs_->glGetProgramiv(program, pname, params);
}

void QtGLES3::GetProgramInfoLog(cppgl::uint program, cppgl::sizei bufsize, cppgl::sizei* length, char* infolog)
{
	funs_->glGetProgramInfoLog(program, bufsize, length, infolog);
}

void QtGLES3::GetRenderbufferParameteriv(cppgl::enumeration target, cppgl::enumeration pname, int* params)
{
	funs_->glGetRenderbufferParameteriv(target, pname, params);
}

void QtGLES3::GetShaderiv(cppgl::uint shader, cppgl::enumeration pname, int* params)
{
	funs_->glGetShaderiv(shader, pname, params);
}

void QtGLES3::GetShaderInfoLog(cppgl::uint shader, cppgl::sizei bufsize, cppgl::sizei* length, char* infolog)
{
	funs_->glGetShaderInfoLog(shader, bufsize, length, infolog);
}

void QtGLES3::GetShaderPrecisionFormat(cppgl::enumeration shadertype, cppgl::enumeration precisiontype, int* range, int* precision)
{
	funs_->glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}

void QtGLES3::GetShaderSource(cppgl::uint shader, cppgl::sizei bufsize, cppgl::sizei* length, char* source)
{
	funs_->glGetShaderSource(shader, bufsize, length, source);
}

void QtGLES3::GetUniformfv(cppgl::uint program, int location, float* params)
{
	funs_->glGetUniformfv(program, location, params);
}

void QtGLES3::GetUniformiv(cppgl::uint program, int location, int* params)
{
	funs_->glGetUniformiv(program, location, params);
}

int QtGLES3::GetUniformLocation(cppgl::uint program, const char* name)
{
	return funs_->glGetUniformLocation(program, name);
}

void QtGLES3::GetVertexAttribfv(cppgl::uint index, cppgl::enumeration pname, float* params)
{
	funs_->glGetVertexAttribfv(index, pname, params);
}

void QtGLES3::GetVertexAttribiv(cppgl::uint index, cppgl::enumeration pname, int* params)
{
	funs_->glGetVertexAttribiv(index, pname, params);
}

void QtGLES3::GetVertexAttribPointerv(cppgl::uint index, cppgl::enumeration pname, void** pointer)
{
	funs_->glGetVertexAttribPointerv(index, pname, pointer);
}

cppgl::boolean QtGLES3::IsBuffer(cppgl::uint buffer)
{
	return funs_->glIsBuffer(buffer);
}

cppgl::boolean QtGLES3::IsFramebuffer(cppgl::uint framebuffer)
{
	return funs_->glIsFramebuffer(framebuffer);
}

cppgl::boolean QtGLES3::IsProgram(cppgl::uint program)
{
	return funs_->glIsProgram(program);
}

cppgl::boolean QtGLES3::IsRenderbuffer(cppgl::uint renderbuffer)
{
	return funs_->glIsRenderbuffer(renderbuffer);
}

cppgl::boolean QtGLES3::IsShader(cppgl::uint shader)
{
	return funs_->glIsShader(shader);
}

void QtGLES3::LinkProgram(cppgl::uint program)
{
	funs_->glLinkProgram(program);
}

void QtGLES3::ReleaseShaderCompiler()
{
	funs_->glReleaseShaderCompiler();
}

void QtGLES3::RenderbufferStorage(cppgl::enumeration target, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glRenderbufferStorage(target, internalformat, width, height);
}

void QtGLES3::SampleCoverage(cppgl::clampf value, cppgl::boolean invert)
{
	funs_->glSampleCoverage(value, invert);
}

void QtGLES3::ShaderBinary(int n, const cppgl::uint* shaders, cppgl::enumeration binaryformat, const void* binary, int length)
{
	funs_->glShaderBinary(n, shaders, binaryformat, binary, length);
}

void QtGLES3::ShaderSource(cppgl::uint shader, cppgl::sizei count, const char** string, const int* length)
{
	funs_->glShaderSource(shader, count, string, length);
}

void QtGLES3::StencilFuncSeparate(cppgl::enumeration face, cppgl::enumeration func, int ref, cppgl::uint mask)
{
	funs_->glStencilFuncSeparate(face, func, ref, mask);
}

void QtGLES3::StencilMaskSeparate(cppgl::enumeration face, cppgl::uint mask)
{
	funs_->glStencilMaskSeparate(face, mask);
}

void QtGLES3::StencilOpSeparate(cppgl::enumeration face, cppgl::enumeration fail, cppgl::enumeration zfail, cppgl::enumeration zpass)
{
	funs_->glStencilOpSeparate(face, fail, zfail, zpass);
}

void QtGLES3::Uniform1f(int location, float x)
{
	funs_->glUniform1f(location, x);
}

void QtGLES3::Uniform1fv(int location, cppgl::sizei count, const float* v)
{
	funs_->glUniform1fv(location, count, v);
}

void QtGLES3::Uniform1i(int location, int x)
{
	funs_->glUniform1i(location, x);
}

void QtGLES3::Uniform1iv(int location, cppgl::sizei count, const int* v)
{
	funs_->glUniform1iv(location, count, v);
}

void QtGLES3::Uniform2f(int location, float x, float y)
{
	funs_->glUniform2f(location, x, y);
}

void QtGLES3::Uniform2fv(int location, cppgl::sizei count, const float* v)
{
	funs_->glUniform2fv(location, count, v);
}

void QtGLES3::Uniform2i(int location, int x, int y)
{
	funs_->glUniform2i(location, x, y);
}

void QtGLES3::Uniform2iv(int location, cppgl::sizei count, const int* v)
{
	funs_->glUniform2iv(location, count, v);
}

void QtGLES3::Uniform3f(int location, float x, float y, float z)
{
	funs_->glUniform3f(location, x, y, z);
}

void QtGLES3::Uniform3fv(int location, cppgl::sizei count, const float* v)
{
	funs_->glUniform3fv(location, count, v);
}

void QtGLES3::Uniform3i(int location, int x, int y, int z)
{
	funs_->glUniform3i(location, x, y, z);
}

void QtGLES3::Uniform3iv(int location, cppgl::sizei count, const int* v)
{
	funs_->glUniform3iv(location, count, v);
}

void QtGLES3::Uniform4f(int location, float x, float y, float z, float w)
{
	funs_->glUniform4f(location, x, y, z, w);
}

void QtGLES3::Uniform4fv(int location, cppgl::sizei count, const float* v)
{
	funs_->glUniform4fv(location, count, v);
}

void QtGLES3::Uniform4i(int location, int x, int y, int z, int w)
{
	funs_->glUniform4i(location, x, y, z, w);
}

void QtGLES3::Uniform4iv(int location, cppgl::sizei count, const int* v)
{
	funs_->glUniform4iv(location, count, v);
}

void QtGLES3::UniformMatrix2fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float* value)
{
	funs_->glUniformMatrix2fv(location, count, transpose, value);
}

void QtGLES3::UniformMatrix3fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float* value)
{
	funs_->glUniformMatrix3fv(location, count, transpose, value);
}

void QtGLES3::UniformMatrix4fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float* value)
{
	funs_->glUniformMatrix4fv(location, count, transpose, value);
}

void QtGLES3::UseProgram(cppgl::uint program)
{
	funs_->glUseProgram(program);
}

void QtGLES3::ValidateProgram(cppgl::uint program)
{
	funs_->glValidateProgram(program);
}

void QtGLES3::VertexAttrib1f(cppgl::uint indx, float x)
{
	funs_->glVertexAttrib1f(indx, x);
}

void QtGLES3::VertexAttrib1fv(cppgl::uint indx, const float* values)
{
	funs_->glVertexAttrib1fv(indx, values);
}

void QtGLES3::VertexAttrib2f(cppgl::uint indx, float x, float y)
{
	funs_->glVertexAttrib2f(indx, x, y);
}

void QtGLES3::VertexAttrib2fv(cppgl::uint indx, const float* values)
{
	funs_->glVertexAttrib2fv(indx, values);
}

void QtGLES3::VertexAttrib3f(cppgl::uint indx, float x, float y, float z)
{
	funs_->glVertexAttrib3f(indx, x, y, z);
}

void QtGLES3::VertexAttrib3fv(cppgl::uint indx, const float* values)
{
	funs_->glVertexAttrib3fv(indx, values);
}

void QtGLES3::VertexAttrib4f(cppgl::uint indx, float x, float y, float z, float w)
{
	funs_->glVertexAttrib4f(indx, x, y, z, w);
}

void QtGLES3::VertexAttrib4fv(cppgl::uint indx, const float* values)
{
	funs_->glVertexAttrib4fv(indx, values);
}

void QtGLES3::VertexAttribPointer(cppgl::uint indx, int size, cppgl::enumeration type, cppgl::boolean normalized, cppgl::sizei stride, const void* ptr)
{
	funs_->glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
}

void QtGLES3::BeginQuery(cppgl::enumeration target, cppgl::uint id)
{
	funs_->glBeginQuery(target, id);
}

void QtGLES3::BeginTransformFeedback(cppgl::enumeration primitiveMode)
{
	funs_->glBeginTransformFeedback(primitiveMode);
}

void QtGLES3::BindBufferBase(cppgl::enumeration target, cppgl::uint index, cppgl::uint buffer)
{
	funs_->glBindBufferBase(target, index, buffer);
}

void QtGLES3::BindBufferRange(cppgl::enumeration target, cppgl::uint index, cppgl::uint buffer, cppgl::intptr offset, cppgl::sizeiptr size)
{
	funs_->glBindBufferRange(target, index, buffer, offset, size);
}

void QtGLES3::BindSampler(cppgl::uint unit, cppgl::uint sampler)
{
	funs_->glBindSampler(unit, sampler);
}

void QtGLES3::BindTransformFeedback(cppgl::enumeration target, cppgl::uint id)
{
	funs_->glBindTransformFeedback(target, id);
}

void QtGLES3::BindVertexArray(cppgl::uint array)
{
	funs_->glBindVertexArray(array);
}

void QtGLES3::BlitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, cppgl::bitfield mask, cppgl::enumeration filter)
{
	funs_->glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void QtGLES3::ClearBufferfi(cppgl::enumeration buffer, int drawbuffer, float depth, int stencil)
{
	funs_->glClearBufferfi(buffer, drawbuffer, depth, stencil);
}

void QtGLES3::ClearBufferfv(cppgl::enumeration buffer, int drawbuffer, const float * value)
{
	funs_->glClearBufferfv(buffer, drawbuffer, value);
}

void QtGLES3::ClearBufferiv(cppgl::enumeration buffer, int drawbuffer, const int * value)
{
	funs_->glClearBufferiv(buffer, drawbuffer, value);
}

void QtGLES3::ClearBufferuiv(cppgl::enumeration buffer, int drawbuffer, const cppgl::uint * value)
{
	funs_->glClearBufferuiv(buffer, drawbuffer, value);
}

void QtGLES3::CompressedTexImage3D(cppgl::enumeration target, int level, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height, cppgl::sizei depth, int border, cppgl::sizei imageSize, const void * data)
{
	funs_->glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
}

void QtGLES3::CompressedTexSubImage3D(cppgl::enumeration target, int level, int xoffset, int yoffset, int zoffset, cppgl::sizei width, cppgl::sizei height, cppgl::sizei depth, cppgl::enumeration format, cppgl::sizei imageSize, const void * data)
{
	funs_->glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

void QtGLES3::CopyBufferSubData(cppgl::enumeration readTarget, cppgl::enumeration writeTarget, cppgl::intptr readOffset, cppgl::intptr writeOffset, cppgl::sizeiptr size)
{
	funs_->glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
}

void QtGLES3::CopyTexSubImage3D(cppgl::enumeration target, int level, int xoffset, int yoffset, int zoffset, int x, int y, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

void QtGLES3::DeleteQueries(cppgl::sizei n, const cppgl::uint * ids)
{
	funs_->glDeleteQueries(n, ids);
}

void QtGLES3::DeleteSamplers(cppgl::sizei count, const cppgl::uint * samplers)
{
	funs_->glDeleteSamplers(count, samplers);
}

void QtGLES3::DeleteTransformFeedbacks(cppgl::sizei n, const cppgl::uint * ids)
{
	funs_->glDeleteTransformFeedbacks(n, ids);
}

void QtGLES3::DeleteVertexArrays(cppgl::sizei n, const cppgl::uint * arrays)
{
	funs_->glDeleteVertexArrays(n, arrays);
}

void QtGLES3::DrawArraysInstanced(cppgl::enumeration mode, int first, cppgl::sizei count, cppgl::sizei instancecount)
{
	funs_->glDrawArraysInstanced(mode, first, count, instancecount);
}

void QtGLES3::DrawBuffers(cppgl::sizei n, const cppgl::enumeration * bufs)
{
	funs_->glDrawBuffers(n, bufs);
}

void QtGLES3::DrawElementsInstanced(cppgl::enumeration mode, cppgl::sizei count, cppgl::enumeration type, const void * indices, cppgl::sizei instancecount)
{
	funs_->glDrawElementsInstanced(mode, count, type, indices, instancecount);
}

void QtGLES3::DrawRangeElements(cppgl::enumeration mode, cppgl::uint start, cppgl::uint end, cppgl::sizei count, cppgl::enumeration type, const void * indices)
{
	funs_->glDrawRangeElements(mode, start, end, count, type, indices);
}

void QtGLES3::EndQuery(cppgl::enumeration target)
{
	funs_->glEndQuery(target);
}

void QtGLES3::EndTransformFeedback()
{
	funs_->glEndTransformFeedback();
}

void QtGLES3::FlushMappedBufferRange(cppgl::enumeration target, cppgl::intptr offset, cppgl::sizeiptr length)
{
	funs_->glFlushMappedBufferRange(target, offset, length);
}

void QtGLES3::FramebufferTextureLayer(cppgl::enumeration target, cppgl::enumeration attachment, cppgl::uint texture, int level, int layer)
{
	funs_->glFramebufferTextureLayer(target, attachment, texture, level, layer);
}

void QtGLES3::GenQueries(cppgl::sizei n, cppgl::uint* ids)
{
	funs_->glGenQueries(n, ids);
}

void QtGLES3::GenSamplers(cppgl::sizei count, cppgl::uint* samplers)
{
	funs_->glGenSamplers(count, samplers);
}

void QtGLES3::GenTransformFeedbacks(cppgl::sizei n, cppgl::uint* ids)
{
	funs_->glGenTransformFeedbacks(n, ids);
}

void QtGLES3::GenVertexArrays(cppgl::sizei n, cppgl::uint* arrays)
{
	funs_->glGenVertexArrays(n, arrays);
}

void QtGLES3::GetActiveUniformBlockName(cppgl::uint program, cppgl::uint uniformBlockIndex, cppgl::sizei bufSize, cppgl::sizei* length, char* uniformBlockName)
{
	funs_->glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
}

void QtGLES3::GetActiveUniformBlockiv(cppgl::uint program, cppgl::uint uniformBlockIndex, cppgl::enumeration pname, int* params)
{
	funs_->glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
}

void QtGLES3::GetActiveUniformsiv(cppgl::uint program, cppgl::sizei uniformCount, const cppgl::uint * uniformIndices, cppgl::enumeration pname, int* params)
{
	funs_->glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
}

void QtGLES3::GetBufferParameteri64v(cppgl::enumeration target, cppgl::enumeration pname, cppgl::int64* params)
{
	funs_->glGetBufferParameteri64v(target, pname, params);
}

void QtGLES3::GetBufferPointerv(cppgl::enumeration target, cppgl::enumeration pname, void ** params)
{
	funs_->glGetBufferPointerv(target, pname, params);
}

int QtGLES3::GetFragDataLocation(cppgl::uint program, const char * name)
{
	return funs_->glGetFragDataLocation(program, name);
}

void QtGLES3::GetInteger64i_v(cppgl::enumeration target, cppgl::uint index, cppgl::int64* data)
{
	funs_->glGetInteger64i_v(target, index, data);
}

void QtGLES3::GetInteger64v(cppgl::enumeration pname, cppgl::int64* data)
{
	funs_->glGetInteger64v(pname, data);
}

void QtGLES3::GetIntegeri_v(cppgl::enumeration target, cppgl::uint index, int* data)
{
	funs_->glGetIntegeri_v(target, index, data);
}

void QtGLES3::GetInternalformativ(cppgl::enumeration target, cppgl::enumeration internalformat, cppgl::enumeration pname, cppgl::sizei bufSize, int* params)
{
	funs_->glGetInternalformativ(target, internalformat, pname, bufSize, params);
}

void QtGLES3::GetProgramBinary(cppgl::uint program, cppgl::sizei bufSize, cppgl::sizei* length, cppgl::enumeration* binaryFormat, void * binary)
{
	funs_->glGetProgramBinary(program, bufSize, length, binaryFormat, binary);
}

void QtGLES3::GetQueryObjectuiv(cppgl::uint id, cppgl::enumeration pname, cppgl::uint* params)
{
	funs_->glGetQueryObjectuiv(id, pname, params);
}

void QtGLES3::GetQueryiv(cppgl::enumeration target, cppgl::enumeration pname, int* params)
{
	funs_->glGetQueryiv(target, pname, params);
}

void QtGLES3::GetSamplerParameterfv(cppgl::uint sampler, cppgl::enumeration pname, float* params)
{
	funs_->glGetSamplerParameterfv(sampler, pname, params);
}

void QtGLES3::GetSamplerParameteriv(cppgl::uint sampler, cppgl::enumeration pname, int* params)
{
	funs_->glGetSamplerParameteriv(sampler, pname, params);
}

const cppgl::ubyte * QtGLES3::GetStringi(cppgl::enumeration name, cppgl::uint index)
{
	return funs_->glGetStringi(name, index);
}

void QtGLES3::GetTransformFeedbackVarying(cppgl::uint program, cppgl::uint index, cppgl::sizei bufSize, cppgl::sizei* length, cppgl::sizei* size, cppgl::enumeration* type, char* name)
{
	funs_->glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
}

cppgl::uint QtGLES3::GetUniformBlockIndex(cppgl::uint program, const char * uniformBlockName)
{
	return funs_->glGetUniformBlockIndex(program, uniformBlockName);
}

void QtGLES3::GetUniformIndices(cppgl::uint program, cppgl::sizei uniformCount, const char *const* uniformNames, cppgl::uint* uniformIndices)
{
	funs_->glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
}

void QtGLES3::GetUniformuiv(cppgl::uint program, int location, cppgl::uint* params)
{
	funs_->glGetUniformuiv(program, location, params);
}

void QtGLES3::GetVertexAttribIiv(cppgl::uint index, cppgl::enumeration pname, int* params)
{
	funs_->glGetVertexAttribIiv(index, pname, params);
}

void QtGLES3::GetVertexAttribIuiv(cppgl::uint index, cppgl::enumeration pname, cppgl::uint* params)
{
	funs_->glGetVertexAttribIuiv(index, pname, params);
}

void QtGLES3::InvalidateFramebuffer(cppgl::enumeration target, cppgl::sizei numAttachments, const cppgl::enumeration * attachments)
{
	funs_->glInvalidateFramebuffer(target, numAttachments, attachments);
}

void QtGLES3::InvalidateSubFramebuffer(cppgl::enumeration target, cppgl::sizei numAttachments, const cppgl::enumeration * attachments, int x, int y, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
}

cppgl::boolean QtGLES3::IsQuery(cppgl::uint id)
{
	return funs_->glIsQuery(id);
}

cppgl::boolean QtGLES3::IsSampler(cppgl::uint sampler)
{
	return funs_->glIsSampler(sampler);
}

cppgl::boolean QtGLES3::IsTransformFeedback(cppgl::uint id)
{
	return funs_->glIsTransformFeedback(id);
}

cppgl::boolean QtGLES3::IsVertexArray(cppgl::uint array)
{
	return funs_->glIsVertexArray(array);
}

void * QtGLES3::MapBufferRange(cppgl::enumeration target, cppgl::intptr offset, cppgl::sizeiptr length, cppgl::bitfield access)
{
	return funs_->glMapBufferRange(target, offset, length, access);
}

void QtGLES3::PauseTransformFeedback()
{
	funs_->glPauseTransformFeedback();
}

void QtGLES3::ProgramBinary(cppgl::uint program, cppgl::enumeration binaryFormat, const void * binary, cppgl::sizei length)
{
	funs_->glProgramBinary(program, binaryFormat, binary, length);
}

void QtGLES3::ProgramParameteri(cppgl::uint program, cppgl::enumeration pname, int value)
{
	funs_->glProgramParameteri(program, pname, value);
}

void QtGLES3::ReadBuffer(cppgl::enumeration src)
{
	funs_->glReadBuffer(src);
}

void QtGLES3::RenderbufferStorageMultisample(cppgl::enumeration target, cppgl::sizei samples, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}

void QtGLES3::ResumeTransformFeedback()
{
	funs_->glResumeTransformFeedback();
}

void QtGLES3::SamplerParameterf(cppgl::uint sampler, cppgl::enumeration pname, float param)
{
	funs_->glSamplerParameterf(sampler, pname, param);
}

void QtGLES3::SamplerParameterfv(cppgl::uint sampler, cppgl::enumeration pname, const float * param)
{
	funs_->glSamplerParameterfv(sampler, pname, param);
}

void QtGLES3::SamplerParameteri(cppgl::uint sampler, cppgl::enumeration pname, int param)
{
	funs_->glSamplerParameteri(sampler, pname, param);
}

void QtGLES3::SamplerParameteriv(cppgl::uint sampler, cppgl::enumeration pname, const int * param)
{
	funs_->glSamplerParameteriv(sampler, pname, param);
}

void QtGLES3::TexImage3D(cppgl::enumeration target, int level, int internalformat, cppgl::sizei width, cppgl::sizei height, cppgl::sizei depth, int border, cppgl::enumeration format, cppgl::enumeration type, const void * pixels)
{
	funs_->glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

void QtGLES3::TexStorage2D(cppgl::enumeration target, cppgl::sizei levels, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height)
{
	funs_->glTexStorage2D(target, levels, internalformat, width, height);
}

void QtGLES3::TexStorage3D(cppgl::enumeration target, cppgl::sizei levels, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height, cppgl::sizei depth)
{
	funs_->glTexStorage3D(target, levels, internalformat, width, height, depth);
}

void QtGLES3::TexSubImage3D(cppgl::enumeration target, int level, int xoffset, int yoffset, int zoffset, cppgl::sizei width, cppgl::sizei height, cppgl::sizei depth, cppgl::enumeration format, cppgl::enumeration type, const void * pixels)
{
	funs_->glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

void QtGLES3::TransformFeedbackVaryings(cppgl::uint program, cppgl::sizei count, const char *const* varyings, cppgl::enumeration bufferMode)
{
	funs_->glTransformFeedbackVaryings(program, count, varyings, bufferMode);
}

void QtGLES3::Uniform1ui(int location, cppgl::uint v0)
{
	funs_->glUniform1ui(location, v0);
}

void QtGLES3::Uniform1uiv(int location, cppgl::sizei count, const cppgl::uint * value)
{
	funs_->glUniform1uiv(location, count, value);
}

void QtGLES3::Uniform2ui(int location, cppgl::uint v0, cppgl::uint v1)
{
	funs_->glUniform2ui(location, v0, v1);
}

void QtGLES3::Uniform2uiv(int location, cppgl::sizei count, const cppgl::uint * value)
{
	funs_->glUniform2uiv(location, count, value);
}

void QtGLES3::Uniform3ui(int location, cppgl::uint v0, cppgl::uint v1, cppgl::uint v2)
{
	funs_->glUniform3ui(location, v0, v1, v2);
}

void QtGLES3::Uniform3uiv(int location, cppgl::sizei count, const cppgl::uint * value)
{
	funs_->glUniform3uiv(location, count, value);
}

void QtGLES3::Uniform4ui(int location, cppgl::uint v0, cppgl::uint v1, cppgl::uint v2, cppgl::uint v3)
{
	funs_->glUniform4ui(location, v0, v1, v2, v3);
}

void QtGLES3::Uniform4uiv(int location, cppgl::sizei count, const cppgl::uint * value)
{
	funs_->glUniform4uiv(location, count, value);
}

void QtGLES3::UniformBlockBinding(cppgl::uint program, cppgl::uint uniformBlockIndex, cppgl::uint uniformBlockBinding)
{
	funs_->glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
}

void QtGLES3::UniformMatrix2x3fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glUniformMatrix2x3fv(location, count, transpose, value);
}

void QtGLES3::UniformMatrix2x4fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glUniformMatrix2x4fv(location, count, transpose, value);
}

void QtGLES3::UniformMatrix3x2fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glUniformMatrix3x2fv(location, count, transpose, value);
}

void QtGLES3::UniformMatrix3x4fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glUniformMatrix3x4fv(location, count, transpose, value);
}

void QtGLES3::UniformMatrix4x2fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glUniformMatrix4x2fv(location, count, transpose, value);
}

void QtGLES3::UniformMatrix4x3fv(int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glUniformMatrix4x3fv(location, count, transpose, value);
}

cppgl::boolean QtGLES3::UnmapBuffer(cppgl::enumeration target)
{
	return funs_->glUnmapBuffer(target);
}

void QtGLES3::VertexAttribDivisor(cppgl::uint index, cppgl::uint divisor)
{
	funs_->glVertexAttribDivisor(index, divisor);
}

void QtGLES3::VertexAttribI4i(cppgl::uint index, int x, int y, int z, int w)
{
	funs_->glVertexAttribI4i(index, x, y, z, w);
}

void QtGLES3::VertexAttribI4iv(cppgl::uint index, const int * v)
{
	funs_->glVertexAttribI4iv(index, v);
}

void QtGLES3::VertexAttribI4ui(cppgl::uint index, cppgl::uint x, cppgl::uint y, cppgl::uint z, cppgl::uint w)
{
	funs_->glVertexAttribI4ui(index, x, y, z, w);
}

void QtGLES3::VertexAttribI4uiv(cppgl::uint index, const cppgl::uint * v)
{
	funs_->glVertexAttribI4uiv(index, v);
}

void QtGLES3::VertexAttribIPointer(cppgl::uint index, int size, cppgl::enumeration type, cppgl::sizei stride, const void * pointer)
{
	funs_->glVertexAttribIPointer(index, size, type, stride, pointer);
}

void QtGLES3::ActiveShaderProgram(cppgl::uint pipeline, cppgl::uint program)
{
	funs_->glActiveShaderProgram(pipeline, program);
}

void QtGLES3::BindImageTexture(cppgl::uint unit, cppgl::uint texture, int level, cppgl::boolean layered, int layer, cppgl::enumeration access, cppgl::enumeration format)
{
	funs_->glBindImageTexture(unit, texture, level, layered, layer, access, format);
}

void QtGLES3::BindProgramPipeline(cppgl::uint pipeline)
{
	funs_->glBindProgramPipeline(pipeline);
}

void QtGLES3::BindVertexBuffer(cppgl::uint bindingindex, cppgl::uint buffer, cppgl::intptr offset, cppgl::sizei stride)
{
	funs_->glBindVertexBuffer(bindingindex, buffer, offset, stride);
}

cppgl::uint QtGLES3::CreateShaderProgramv(cppgl::enumeration type, cppgl::sizei count, const char *const* strings)
{
	return funs_->glCreateShaderProgramv(type, count, strings);
}

void QtGLES3::DeleteProgramPipelines(cppgl::sizei n, const cppgl::uint * pipelines)
{
	funs_->glDeleteProgramPipelines(n, pipelines);
}

void QtGLES3::DispatchCompute(cppgl::uint num_groups_x, cppgl::uint num_groups_y, cppgl::uint num_groups_z)
{
	funs_->glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
}

void QtGLES3::DispatchComputeIndirect(cppgl::intptr indirect)
{
	funs_->glDispatchComputeIndirect(indirect);
}

void QtGLES3::DrawArraysIndirect(cppgl::enumeration mode, const void * indirect)
{
	funs_->glDrawArraysIndirect(mode, indirect);
}

void QtGLES3::DrawElementsIndirect(cppgl::enumeration mode, cppgl::enumeration type, const void * indirect)
{
	funs_->glDrawElementsIndirect(mode, type, indirect);
}

void QtGLES3::FramebufferParameteri(cppgl::enumeration target, cppgl::enumeration pname, int param)
{
	funs_->glFramebufferParameteri(target, pname, param);
}

void QtGLES3::GenProgramPipelines(cppgl::sizei n, cppgl::uint* pipelines)
{
	funs_->glGenProgramPipelines(n, pipelines);
}

void QtGLES3::GetBooleani_v(cppgl::enumeration target, cppgl::uint index, cppgl::boolean* data)
{
	funs_->glGetBooleani_v(target, index, data);
}

void QtGLES3::GetFramebufferParameteriv(cppgl::enumeration target, cppgl::enumeration pname, int* params)
{
	funs_->glGetFramebufferParameteriv(target, pname, params);
}

void QtGLES3::GetMultisamplefv(cppgl::enumeration pname, cppgl::uint index, float* val)
{
	funs_->glGetMultisamplefv(pname, index, val);
}

void QtGLES3::GetProgramInterfaceiv(cppgl::uint program, cppgl::enumeration programInterface, cppgl::enumeration pname, int* params)
{
	funs_->glGetProgramInterfaceiv(program, programInterface, pname, params);
}

void QtGLES3::GetProgramPipelineInfoLog(cppgl::uint pipeline, cppgl::sizei bufSize, cppgl::sizei* length, char* infoLog)
{
	funs_->glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
}

void QtGLES3::GetProgramPipelineiv(cppgl::uint pipeline, cppgl::enumeration pname, int* params)
{
	funs_->glGetProgramPipelineiv(pipeline, pname, params);
}

cppgl::uint QtGLES3::GetProgramResourceIndex(cppgl::uint program, cppgl::enumeration programInterface, const char * name)
{
	return funs_->glGetProgramResourceIndex(program, programInterface, name);
}

int QtGLES3::GetProgramResourceLocation(cppgl::uint program, cppgl::enumeration programInterface, const char * name)
{
	return funs_->glGetProgramResourceLocation(program, programInterface, name);
}

void QtGLES3::GetProgramResourceName(cppgl::uint program, cppgl::enumeration programInterface, cppgl::uint index, cppgl::sizei bufSize, cppgl::sizei* length, char* name)
{
	funs_->glGetProgramResourceName(program, programInterface, index, bufSize, length, name);
}

void QtGLES3::GetProgramResourceiv(cppgl::uint program, cppgl::enumeration programInterface, cppgl::uint index, cppgl::sizei propCount, const cppgl::enumeration * props, cppgl::sizei bufSize, cppgl::sizei* length, int* params)
{
	funs_->glGetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
}

void QtGLES3::GetTexLevelParameterfv(cppgl::enumeration target, int level, cppgl::enumeration pname, float* params)
{
	funs_->glGetTexLevelParameterfv(target, level, pname, params);
}

void QtGLES3::GetTexLevelParameteriv(cppgl::enumeration target, int level, cppgl::enumeration pname, int* params)
{
	funs_->glGetTexLevelParameteriv(target, level, pname, params);
}

cppgl::boolean QtGLES3::IsProgramPipeline(cppgl::uint pipeline)
{
	return funs_->glIsProgramPipeline(pipeline);
}

void QtGLES3::MemoryBarrierByRegion(cppgl::bitfield barriers)
{
	funs_->glMemoryBarrierByRegion(barriers);
}

void QtGLES3::ProgramUniform1f(cppgl::uint program, int location, float v0)
{
	funs_->glProgramUniform1f(program, location, v0);
}

void QtGLES3::ProgramUniform1fv(cppgl::uint program, int location, cppgl::sizei count, const float * value)
{
	funs_->glProgramUniform1fv(program, location, count, value);
}

void QtGLES3::ProgramUniform1i(cppgl::uint program, int location, int v0)
{
	funs_->glProgramUniform1i(program, location, v0);
}

void QtGLES3::ProgramUniform1iv(cppgl::uint program, int location, cppgl::sizei count, const int * value)
{
	funs_->glProgramUniform1iv(program, location, count, value);
}

void QtGLES3::ProgramUniform1ui(cppgl::uint program, int location, cppgl::uint v0)
{
	funs_->glProgramUniform1ui(program, location, v0);
}

void QtGLES3::ProgramUniform1uiv(cppgl::uint program, int location, cppgl::sizei count, const cppgl::uint * value)
{
	funs_->glProgramUniform1uiv(program, location, count, value);
}

void QtGLES3::ProgramUniform2f(cppgl::uint program, int location, float v0, float v1)
{
	funs_->glProgramUniform2f(program, location, v0, v1);
}

void QtGLES3::ProgramUniform2fv(cppgl::uint program, int location, cppgl::sizei count, const float * value)
{
	funs_->glProgramUniform2fv(program, location, count, value);
}

void QtGLES3::ProgramUniform2i(cppgl::uint program, int location, int v0, int v1)
{
	funs_->glProgramUniform2i(program, location, v0, v1);
}

void QtGLES3::ProgramUniform2iv(cppgl::uint program, int location, cppgl::sizei count, const int * value)
{
	funs_->glProgramUniform2iv(program, location, count, value);
}

void QtGLES3::ProgramUniform2ui(cppgl::uint program, int location, cppgl::uint v0, cppgl::uint v1)
{
	funs_->glProgramUniform2ui(program, location, v0, v1);
}

void QtGLES3::ProgramUniform2uiv(cppgl::uint program, int location, cppgl::sizei count, const cppgl::uint * value)
{
	funs_->glProgramUniform2uiv(program, location, count, value);
}

void QtGLES3::ProgramUniform3f(cppgl::uint program, int location, float v0, float v1, float v2)
{
	funs_->glProgramUniform3f(program, location, v0, v1, v2);
}

void QtGLES3::ProgramUniform3fv(cppgl::uint program, int location, cppgl::sizei count, const float * value)
{
	funs_->glProgramUniform3fv(program, location, count, value);
}

void QtGLES3::ProgramUniform3i(cppgl::uint program, int location, int v0, int v1, int v2)
{
	funs_->glProgramUniform3i(program, location, v0, v1, v2);
}

void QtGLES3::ProgramUniform3iv(cppgl::uint program, int location, cppgl::sizei count, const int * value)
{
	funs_->glProgramUniform3iv(program, location, count, value);
}

void QtGLES3::ProgramUniform3ui(cppgl::uint program, int location, cppgl::uint v0, cppgl::uint v1, cppgl::uint v2)
{
	funs_->glProgramUniform3ui(program, location, v0, v1, v2);
}

void QtGLES3::ProgramUniform3uiv(cppgl::uint program, int location, cppgl::sizei count, const cppgl::uint * value)
{
	funs_->glProgramUniform3uiv(program, location, count, value);
}

void QtGLES3::ProgramUniform4f(cppgl::uint program, int location, float v0, float v1, float v2, float v3)
{
	funs_->glProgramUniform4f(program, location, v0, v1, v2, v3);
}

void QtGLES3::ProgramUniform4fv(cppgl::uint program, int location, cppgl::sizei count, const float * value)
{
	funs_->glProgramUniform4fv(program, location, count, value);
}

void QtGLES3::ProgramUniform4i(cppgl::uint program, int location, int v0, int v1, int v2, int v3)
{
	funs_->glProgramUniform4i(program, location, v0, v1, v2, v3);
}

void QtGLES3::ProgramUniform4iv(cppgl::uint program, int location, cppgl::sizei count, const int * value)
{
	funs_->glProgramUniform4iv(program, location, count, value);
}

void QtGLES3::ProgramUniform4ui(cppgl::uint program, int location, cppgl::uint v0, cppgl::uint v1, cppgl::uint v2, cppgl::uint v3)
{
	funs_->glProgramUniform4ui(program, location, v0, v1, v2, v3);
}

void QtGLES3::ProgramUniform4uiv(cppgl::uint program, int location, cppgl::sizei count, const cppgl::uint * value)
{
	funs_->glProgramUniform4uiv(program, location, count, value);
}

void QtGLES3::ProgramUniformMatrix2fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glProgramUniformMatrix2fv(program, location, count, transpose, value);
}

void QtGLES3::ProgramUniformMatrix2x3fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glProgramUniformMatrix2x3fv(program, location, count, transpose, value);
}

void QtGLES3::ProgramUniformMatrix2x4fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glProgramUniformMatrix2x4fv(program, location, count, transpose, value);
}

void QtGLES3::ProgramUniformMatrix3fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glProgramUniformMatrix3fv(program, location, count, transpose, value);
}

void QtGLES3::ProgramUniformMatrix3x2fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glProgramUniformMatrix3x2fv(program, location, count, transpose, value);
}

void QtGLES3::ProgramUniformMatrix3x4fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glProgramUniformMatrix3x4fv(program, location, count, transpose, value);
}

void QtGLES3::ProgramUniformMatrix4fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glProgramUniformMatrix4fv(program, location, count, transpose, value);
}

void QtGLES3::ProgramUniformMatrix4x2fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glProgramUniformMatrix4x2fv(program, location, count, transpose, value);
}

void QtGLES3::ProgramUniformMatrix4x3fv(cppgl::uint program, int location, cppgl::sizei count, cppgl::boolean transpose, const float * value)
{
	funs_->glProgramUniformMatrix4x3fv(program, location, count, transpose, value);
}

void QtGLES3::SampleMaski(cppgl::uint maskNumber, cppgl::bitfield mask)
{
	funs_->glSampleMaski(maskNumber, mask);
}

void QtGLES3::TexStorage2DMultisample(cppgl::enumeration target, cppgl::sizei samples, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height, cppgl::boolean fixedsamplelocations)
{
	funs_->glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

void QtGLES3::UseProgramStages(cppgl::uint pipeline, cppgl::bitfield stages, cppgl::uint program)
{
	funs_->glUseProgramStages(pipeline, stages, program);
}

void QtGLES3::ValidateProgramPipeline(cppgl::uint pipeline)
{
	funs_->glValidateProgramPipeline(pipeline);
}

void QtGLES3::VertexAttribBinding(cppgl::uint attribindex, cppgl::uint bindingindex)
{
	funs_->glVertexAttribBinding(attribindex, bindingindex);
}

void QtGLES3::VertexAttribFormat(cppgl::uint attribindex, int size, cppgl::enumeration type, cppgl::boolean normalized, cppgl::uint relativeoffset)
{
	funs_->glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
}

void QtGLES3::VertexAttribIFormat(cppgl::uint attribindex, int size, cppgl::enumeration type, cppgl::uint relativeoffset)
{
	funs_->glVertexAttribIFormat(attribindex, size, type, relativeoffset);
}

void QtGLES3::VertexBindingDivisor(cppgl::uint bindingindex, cppgl::uint divisor)
{
	funs_->glVertexBindingDivisor(bindingindex, divisor);
}

void QtGLES3::BlendBarrier()
{
	funs_->glBlendBarrier();
}

void QtGLES3::BlendEquationSeparatei(cppgl::uint buf, cppgl::enumeration modeRGB, cppgl::enumeration modeAlpha)
{
	funs_->glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
}

void QtGLES3::BlendEquationi(cppgl::uint buf, cppgl::enumeration mode)
{
	funs_->glBlendEquationi(buf, mode);
}

void QtGLES3::BlendFuncSeparatei(cppgl::uint buf, cppgl::enumeration srcRGB, cppgl::enumeration dstRGB, cppgl::enumeration srcAlpha, cppgl::enumeration dstAlpha)
{
	funs_->glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void QtGLES3::BlendFunci(cppgl::uint buf, cppgl::enumeration src, cppgl::enumeration dst)
{
	funs_->glBlendFunci(buf, src, dst);
}

void QtGLES3::ColorMaski(cppgl::uint index, cppgl::boolean r, cppgl::boolean g, cppgl::boolean b, cppgl::boolean a)
{
	funs_->glColorMaski(index, r, g, b, a);
}

void QtGLES3::CopyImageSubData(cppgl::uint srcName, cppgl::enumeration srcTarget, int srcLevel, int srcX, int srcY, int srcZ, cppgl::uint dstName, cppgl::enumeration dstTarget, int dstLevel, int dstX, int dstY, int dstZ, cppgl::sizei srcWidth, cppgl::sizei srcHeight, cppgl::sizei srcDepth)
{
	funs_->glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}

void QtGLES3::DebugMessageCallback(cppgl::debugproc callback, const void * userParam)
{
	funs_->glDebugMessageCallback(callback, userParam);
}

void QtGLES3::DebugMessageControl(cppgl::enumeration source, cppgl::enumeration type, cppgl::enumeration severity, cppgl::sizei count, const cppgl::uint * ids, cppgl::boolean enabled)
{
	funs_->glDebugMessageControl(source, type, severity, count, ids, enabled);
}

void QtGLES3::DebugMessageInsert(cppgl::enumeration source, cppgl::enumeration type, cppgl::uint id, cppgl::enumeration severity, cppgl::sizei length, const char * buf)
{
	funs_->glDebugMessageInsert(source, type, id, severity, length, buf);
}

void QtGLES3::Disablei(cppgl::enumeration target, cppgl::uint index)
{
	funs_->glDisablei(target, index);
}

void QtGLES3::DrawElementsBaseVertex(cppgl::enumeration mode, cppgl::sizei count, cppgl::enumeration type, const void * indices, int basevertex)
{
	funs_->glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
}

void QtGLES3::DrawElementsInstancedBaseVertex(cppgl::enumeration mode, cppgl::sizei count, cppgl::enumeration type, const void * indices, cppgl::sizei instancecount, int basevertex)
{
	funs_->glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
}

void QtGLES3::DrawRangeElementsBaseVertex(cppgl::enumeration mode, cppgl::uint start, cppgl::uint end, cppgl::sizei count, cppgl::enumeration type, const void * indices, int basevertex)
{
	funs_->glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
}

void QtGLES3::Enablei(cppgl::enumeration target, cppgl::uint index)
{
	funs_->glEnablei(target, index);
}

void QtGLES3::FramebufferTexture(cppgl::enumeration target, cppgl::enumeration attachment, cppgl::uint texture, int level)
{
	funs_->glFramebufferTexture(target, attachment, texture, level);
}

cppgl::uint QtGLES3::GetDebugMessageLog(cppgl::uint count, cppgl::sizei bufSize, cppgl::enumeration* sources, cppgl::enumeration* types, cppgl::uint* ids, cppgl::enumeration* severities, cppgl::sizei* lengths, char* messageLog)
{
	return funs_->glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
}

cppgl::enumeration QtGLES3::GetGraphicsResetStatus()
{
	return funs_->glGetGraphicsResetStatus();
}

void QtGLES3::GetObjectLabel(cppgl::enumeration identifier, cppgl::uint name, cppgl::sizei bufSize, cppgl::sizei* length, char* label)
{
	funs_->glGetObjectLabel(identifier, name, bufSize, length, label);
}

void QtGLES3::GetObjectPtrLabel(const void * ptr, cppgl::sizei bufSize, cppgl::sizei* length, char* label)
{
	funs_->glGetObjectPtrLabel(ptr, bufSize, length, label);
}

void QtGLES3::GetPointerv(cppgl::enumeration pname, void ** params)
{
	funs_->glGetPointerv(pname, params);
}

void QtGLES3::GetSamplerParameterIiv(cppgl::uint sampler, cppgl::enumeration pname, int* params)
{
	funs_->glGetSamplerParameterIiv(sampler, pname, params);
}

void QtGLES3::GetSamplerParameterIuiv(cppgl::uint sampler, cppgl::enumeration pname, cppgl::uint* params)
{
	funs_->glGetSamplerParameterIuiv(sampler, pname, params);
}

void QtGLES3::GetTexParameterIiv(cppgl::enumeration target, cppgl::enumeration pname, int* params)
{
	funs_->glGetTexParameterIiv(target, pname, params);
}

void QtGLES3::GetTexParameterIuiv(cppgl::enumeration target, cppgl::enumeration pname, cppgl::uint* params)
{
	funs_->glGetTexParameterIuiv(target, pname, params);
}

void QtGLES3::GetnUniformfv(cppgl::uint program, int location, cppgl::sizei bufSize, float* params)
{
	funs_->glGetnUniformfv(program, location, bufSize, params);
}

void QtGLES3::GetnUniformiv(cppgl::uint program, int location, cppgl::sizei bufSize, int* params)
{
	funs_->glGetnUniformiv(program, location, bufSize, params);
}

void QtGLES3::GetnUniformuiv(cppgl::uint program, int location, cppgl::sizei bufSize, cppgl::uint* params)
{
	funs_->glGetnUniformuiv(program, location, bufSize, params);
}

cppgl::boolean QtGLES3::IsEnabledi(cppgl::enumeration target, cppgl::uint index)
{
	return funs_->glIsEnabledi(target, index);
}

void QtGLES3::MinSampleShading(float value)
{
	funs_->glMinSampleShading(value);
}

void QtGLES3::ObjectLabel(cppgl::enumeration identifier, cppgl::uint name, cppgl::sizei length, const char * label)
{
	funs_->glObjectLabel(identifier, name, length, label);
}

void QtGLES3::ObjectPtrLabel(const void * ptr, cppgl::sizei length, const char * label)
{
	funs_->glObjectPtrLabel(ptr, length, label);
}

void QtGLES3::PatchParameteri(cppgl::enumeration pname, int value)
{
	funs_->glPatchParameteri(pname, value);
}

void QtGLES3::PopDebugGroup()
{
	funs_->glPopDebugGroup();
}

void QtGLES3::PrimitiveBoundingBox(float minX, float minY, float minZ, float minW, float maxX, float maxY, float maxZ, float maxW)
{
	funs_->glPrimitiveBoundingBox(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
}

void QtGLES3::PushDebugGroup(cppgl::enumeration source, cppgl::uint id, cppgl::sizei length, const char * message)
{
	funs_->glPushDebugGroup(source, id, length, message);
}

void QtGLES3::ReadnPixels(int x, int y, cppgl::sizei width, cppgl::sizei height, cppgl::enumeration format, cppgl::enumeration type, cppgl::sizei bufSize, void * data)
{
	funs_->glReadnPixels(x, y, width, height, format, type, bufSize, data);
}

void QtGLES3::SamplerParameterIiv(cppgl::uint sampler, cppgl::enumeration pname, const int * param)
{
	funs_->glSamplerParameterIiv(sampler, pname, param);
}

void QtGLES3::SamplerParameterIuiv(cppgl::uint sampler, cppgl::enumeration pname, const cppgl::uint * param)
{
	funs_->glSamplerParameterIuiv(sampler, pname, param);
}

void QtGLES3::TexBuffer(cppgl::enumeration target, cppgl::enumeration internalformat, cppgl::uint buffer)
{
	funs_->glTexBuffer(target, internalformat, buffer);
}

void QtGLES3::TexBufferRange(cppgl::enumeration target, cppgl::enumeration internalformat, cppgl::uint buffer, cppgl::intptr offset, cppgl::sizeiptr size)
{
	funs_->glTexBufferRange(target, internalformat, buffer, offset, size);
}

void QtGLES3::TexParameterIiv(cppgl::enumeration target, cppgl::enumeration pname, const int * params)
{
	funs_->glTexParameterIiv(target, pname, params);
}

void QtGLES3::TexParameterIuiv(cppgl::enumeration target, cppgl::enumeration pname, const cppgl::uint * params)
{
	funs_->glTexParameterIuiv(target, pname, params);
}

void QtGLES3::TexStorage3DMultisample(cppgl::enumeration target, cppgl::sizei samples, cppgl::enumeration internalformat, cppgl::sizei width, cppgl::sizei height, cppgl::sizei depth, cppgl::boolean fixedsamplelocations)
{
	funs_->glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}
