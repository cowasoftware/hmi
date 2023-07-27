text  = '''
// OpenGL 1.0 core functions
  virtual void Viewport(int x, int y, sizei width, sizei height) = 0;
  virtual void DepthRange(double nearVal, double farVal) = 0;
  virtual bool IsEnabled(enumeration cap) = 0;
  virtual void GetTexLevelParameteriv(enumeration target, int level, enumeration pname, int *params) = 0;
  virtual void GetTexLevelParameterfv(enumeration target, int level, enumeration pname, float *params) = 0;
  virtual void GetTexParameteriv(enumeration target, enumeration pname, int *params) = 0;
  virtual void GetTexParameterfv(enumeration target, enumeration pname, float *params) = 0;
  virtual void GetTexImage(enumeration target, int level, enumeration format, enumeration type, void *pixels) = 0;
  virtual const ubyte *GetString(enumeration name) = 0;
  virtual void GetIntegerv(enumeration pname, int *params) = 0;
  virtual void GetFloatv(enumeration pname, float *params) = 0;
  virtual enumeration GetError() = 0;
  virtual void GetDoublev(enumeration pname, double *params) = 0;
  virtual void GetBooleanv(enumeration pname, bool *params) = 0;
  virtual void ReadPixels(int x, int y, sizei width, sizei height, enumeration format, enumeration type, void *pixels) = 0;
  virtual void ReadBuffer(enumeration mode) = 0;
  virtual void PixelStorei(enumeration pname, int param) = 0;
  virtual void PixelStoref(enumeration pname, float param) = 0;
  virtual void DepthFunc(enumeration func) = 0;
  virtual void StencilOp(enumeration fail, enumeration zfail, enumeration zpass) = 0;
  virtual void StencilFunc(enumeration func, int ref, uint mask) = 0;
  virtual void LogicOp(enumeration opcode) = 0;
  virtual void BlendFunc(enumeration sfactor, enumeration dfactor) = 0;
  virtual void Flush() = 0;
  virtual void Finish() = 0;
  virtual void Enable(enumeration cap) = 0;
  virtual void Disable(enumeration cap) = 0;
  virtual void DepthMask(bool flag) = 0;
  virtual void ColorMask(bool red, bool green, bool blue, bool alpha) = 0;
  virtual void StencilMask(uint mask) = 0;
  virtual void ClearDepth(double depth) = 0;
  virtual void ClearStencil(int s) = 0;
  virtual void ClearColor(float red, float green, float blue, float alpha) = 0;
  virtual void Clear(bitfield mask) = 0;
  virtual void DrawBuffer(enumeration mode) = 0;
  virtual void TexImage2D(enumeration target, int level, int internalformat, sizei width, sizei height, int border, enumeration format, enumeration type, const void *pixels) = 0;
  virtual void TexImage1D(enumeration target, int level, int internalformat, sizei width, int border, enumeration format, enumeration type, const void *pixels) = 0;
  virtual void TexParameteriv(enumeration target, enumeration pname, const int *params) = 0;
  virtual void TexParameteri(enumeration target, enumeration pname, int param) = 0;
  virtual void TexParameterfv(enumeration target, enumeration pname, const float *params) = 0;
  virtual void TexParameterf(enumeration target, enumeration pname, float param) = 0;
  virtual void Scissor(int x, int y, sizei width, sizei height) = 0;
  virtual void PolygonMode(enumeration face, enumeration mode) = 0;
  virtual void PointSize(float size) = 0;
  virtual void LineWidth(float width) = 0;
  virtual void Hint(enumeration target, enumeration mode) = 0;
  virtual void FrontFace(enumeration mode) = 0;
  virtual void CullFace(enumeration mode) = 0;

  // OpenGL 1.1 core functions
  virtual void Indexubv(const ubyte *c) = 0;
  virtual void Indexub(ubyte c) = 0;
  virtual bool IsTexture(uint texture) = 0;
  virtual void GenTextures(sizei n, uint *textures) = 0;
  virtual void DeleteTextures(sizei n, const uint *textures) = 0;
  virtual void BindTexture(enumeration target, uint texture) = 0;
  virtual void TexSubImage2D(enumeration target, int level, int xoffset, int yoffset, sizei width, sizei height, enumeration format, enumeration type, const void *pixels) = 0;
  virtual void TexSubImage1D(enumeration target, int level, int xoffset, sizei width, enumeration format, enumeration type, const void *pixels) = 0;
  virtual void CopyTexSubImage2D(enumeration target, int level, int xoffset, int yoffset, int x, int y, sizei width, sizei height) = 0;
  virtual void CopyTexSubImage1D(enumeration target, int level, int xoffset, int x, int y, sizei width) = 0;
  virtual void CopyTexImage2D(enumeration target, int level, enumeration internalformat, int x, int y, sizei width, sizei height, int border) = 0;
  virtual void CopyTexImage1D(enumeration target, int level, enumeration internalformat, int x, int y, sizei width, int border) = 0;
  virtual void PolygonOffset(float factor, float units) = 0;
  virtual void GetPointerv(enumeration pname, void **params) = 0;
  virtual void DrawElements(enumeration mode, sizei count, enumeration type, const void *indices) = 0;
  virtual void DrawArrays(enumeration mode, int first, sizei count) = 0;

  // OpenGL 1.2 core functions
  virtual void CopyTexSubImage3D(enumeration target, int level, int xoffset, int yoffset, int zoffset, int x, int y, sizei width, sizei height) = 0;
  virtual void TexSubImage3D(enumeration target, int level, int xoffset, int yoffset, int zoffset, sizei width, sizei height, sizei depth, enumeration format, enumeration type, const void *pixels) = 0;
  virtual void TexImage3D(enumeration target, int level, int internalformat, sizei width, sizei height, sizei depth, int border, enumeration format, enumeration type, const void *pixels) = 0;
  virtual void DrawRangeElements(enumeration mode, uint start, uint end, sizei count, enumeration type, const void *indices) = 0;
  virtual void BlendEquation(enumeration mode) = 0;
  virtual void BlendColor(float red, float green, float blue, float alpha) = 0;

  // OpenGL 1.3 core functions
  virtual void GetCompressedTexImage(enumeration target, int level, void *img) = 0;
  virtual void CompressedTexSubImage1D(enumeration target, int level, int xoffset, sizei width, enumeration format, sizei imageSize, const void *data) = 0;
  virtual void CompressedTexSubImage2D(enumeration target, int level, int xoffset, int yoffset, sizei width, sizei height, enumeration format, sizei imageSize, const void *data) = 0;
  virtual void CompressedTexSubImage3D(enumeration target, int level, int xoffset, int yoffset, int zoffset, sizei width, sizei height, sizei depth, enumeration format, sizei imageSize, const void *data) = 0;
  virtual void CompressedTexImage1D(enumeration target, int level, enumeration internalformat, sizei width, int border, sizei imageSize, const void *data) = 0;
  virtual void CompressedTexImage2D(enumeration target, int level, enumeration internalformat, sizei width, sizei height, int border, sizei imageSize, const void *data) = 0;
  virtual void CompressedTexImage3D(enumeration target, int level, enumeration internalformat, sizei width, sizei height, sizei depth, int border, sizei imageSize, const void *data) = 0;
  virtual void SampleCoverage(float value, bool invert) = 0;
  virtual void ActiveTexture(enumeration texture) = 0;

  // OpenGL 1.4 core functions
  virtual void PointParameteriv(enumeration pname, const int *params) = 0;
  virtual void PointParameteri(enumeration pname, int param) = 0;
  virtual void PointParameterfv(enumeration pname, const float *params) = 0;
  virtual void PointParameterf(enumeration pname, float param) = 0;
  virtual void MultiDrawElements(enumeration mode, const sizei *count, enumeration type, const void *const *indices, sizei drawcount) = 0;
  virtual void MultiDrawArrays(enumeration mode, const int *first, const sizei *count, sizei drawcount) = 0;
  virtual void BlendFuncSeparate(enumeration sfactorRGB, enumeration dfactorRGB, enumeration sfactorAlpha, enumeration dfactorAlpha) = 0;

  // OpenGL 1.5 core functions
  virtual void GetBufferPointerv(enumeration target, enumeration pname, void **params) = 0;
  virtual void GetBufferParameteriv(enumeration target, enumeration pname, int *params) = 0;
  virtual bool UnmapBuffer(enumeration target) = 0;
  virtual void *MapBuffer(enumeration target, enumeration access) = 0;
  virtual void GetBufferSubData(enumeration target, sizei offset, sizei size, void *data) = 0;
  virtual void BufferSubData(enumeration target, sizei offset, sizei size, const void *data) = 0;
  virtual void BufferData(enumeration target, sizei size, const void *data, enumeration usage) = 0;
  virtual bool IsBuffer(uint buffer) = 0;
  virtual void GenBuffers(sizei n, uint *buffers) = 0;
  virtual void DeleteBuffers(sizei n, const uint *buffers) = 0;
  virtual void BindBuffer(enumeration target, uint buffer) = 0;
  virtual void GetQueryObjectuiv(uint id, enumeration pname, uint *params) = 0;
  virtual void GetQueryObjectiv(uint id, enumeration pname, int *params) = 0;
  virtual void GetQueryiv(enumeration target, enumeration pname, int *params) = 0;
  virtual void EndQuery(enumeration target) = 0;
  virtual void BeginQuery(enumeration target, uint id) = 0;
  virtual bool IsQuery(uint id) = 0;
  virtual void DeleteQueries(sizei n, const uint *ids) = 0;
  virtual void GenQueries(sizei n, uint *ids) = 0;

  // OpenGL 2.0 core functions
  virtual void VertexAttribPointer(uint index, int size, enumeration type, bool normalized, sizei stride, const void *pointer) = 0;
  virtual void ValidateProgram(uint program) = 0;
  virtual void UniformMatrix4fv(int location, sizei count, bool transpose, const float *value) = 0;
  virtual void UniformMatrix3fv(int location, sizei count, bool transpose, const float *value) = 0;
  virtual void UniformMatrix2fv(int location, sizei count, bool transpose, const float *value) = 0;
  virtual void Uniform4iv(int location, sizei count, const int *value) = 0;
  virtual void Uniform3iv(int location, sizei count, const int *value) = 0;
  virtual void Uniform2iv(int location, sizei count, const int *value) = 0;
  virtual void Uniform1iv(int location, sizei count, const int *value) = 0;
  virtual void Uniform4fv(int location, sizei count, const float *value) = 0;
  virtual void Uniform3fv(int location, sizei count, const float *value) = 0;
  virtual void Uniform2fv(int location, sizei count, const float *value) = 0;
  virtual void Uniform1fv(int location, sizei count, const float *value) = 0;
  virtual void Uniform4i(int location, int v0, int v1, int v2, int v3) = 0;
  virtual void Uniform3i(int location, int v0, int v1, int v2) = 0;
  virtual void Uniform2i(int location, int v0, int v1) = 0;
  virtual void Uniform1i(int location, int v0) = 0;
  virtual void Uniform4f(int location, float v0, float v1, float v2, float v3) = 0;
  virtual void Uniform3f(int location, float v0, float v1, float v2) = 0;
  virtual void Uniform2f(int location, float v0, float v1) = 0;
  virtual void Uniform1f(int location, float v0) = 0;
  virtual void UseProgram(uint program) = 0;
  virtual void ShaderSource(uint shader, sizei count, const char *const *string, const int *length) = 0;
  virtual void LinkProgram(uint program) = 0;
  virtual bool IsShader(uint shader) = 0;
  virtual bool IsProgram(uint program) = 0;
  virtual void GetVertexAttribPointerv(uint index, enumeration pname, void **pointer) = 0;
  virtual void GetVertexAttribiv(uint index, enumeration pname, int *params) = 0;
  virtual void GetVertexAttribfv(uint index, enumeration pname, float *params) = 0;
  virtual void GetVertexAttribdv(uint index, enumeration pname, double *params) = 0;
  virtual void GetUniformiv(uint program, int location, int *params) = 0;
  virtual void GetUniformfv(uint program, int location, float *params) = 0;
  virtual int GetUniformLocation(uint program, const char *name) = 0;
  virtual void GetShaderSource(uint shader, sizei bufSize, sizei *length, char *source) = 0;
  virtual void GetShaderInfoLog(uint shader, sizei bufSize, sizei *length, char *infoLog) = 0;
  virtual void GetShaderiv(uint shader, enumeration pname, int *params) = 0;
  virtual void GetProgramInfoLog(uint program, sizei bufSize, sizei *length, char *infoLog) = 0;
  virtual void GetProgramiv(uint program, enumeration pname, int *params) = 0;
  virtual int GetAttribLocation(uint program, const char *name) = 0;
  virtual void GetAttachedShaders(uint program, sizei maxCount, sizei *count, uint *obj) = 0;
  virtual void GetActiveUniform(uint program, uint index, sizei bufSize, sizei *length, int *size, enumeration *type, char *name) = 0;
  virtual void GetActiveAttrib(uint program, uint index, sizei bufSize, sizei *length, int *size, enumeration *type, char *name) = 0;
  virtual void EnableVertexAttribArray(uint index) = 0;
  virtual void DisableVertexAttribArray(uint index) = 0;
  virtual void DetachShader(uint program, uint shader) = 0;
  virtual void DeleteShader(uint shader) = 0;
  virtual void DeleteProgram(uint program) = 0;
  virtual uint CreateShader(enumeration type) = 0;
  virtual uint CreateProgram() = 0;
  virtual void CompileShader(uint shader) = 0;
  virtual void BindAttribLocation(uint program, uint index, const char *name) = 0;
  virtual void AttachShader(uint program, uint shader) = 0;
  virtual void StencilMaskSeparate(enumeration face, uint mask) = 0;
  virtual void StencilFuncSeparate(enumeration face, enumeration func, int ref, uint mask) = 0;
  virtual void StencilOpSeparate(enumeration face, enumeration sfail, enumeration dpfail, enumeration dppass) = 0;
  virtual void DrawBuffers(sizei n, const enumeration *bufs) = 0;
  virtual void BlendEquationSeparate(enumeration modeRGB, enumeration modeAlpha) = 0;

  // OpenGL 2.1 core functions
  virtual void UniformMatrix4x3fv(int location, sizei count, bool transpose, const float *value) = 0;
  virtual void UniformMatrix3x4fv(int location, sizei count, bool transpose, const float *value) = 0;
  virtual void UniformMatrix4x2fv(int location, sizei count, bool transpose, const float *value) = 0;
  virtual void UniformMatrix2x4fv(int location, sizei count, bool transpose, const float *value) = 0;
  virtual void UniformMatrix3x2fv(int location, sizei count, bool transpose, const float *value) = 0;
  virtual void UniformMatrix2x3fv(int location, sizei count, bool transpose, const float *value) = 0;

  // OpenGL 3.0 core functions
  virtual bool IsVertexArray(uint array) = 0;
  virtual void GenVertexArrays(sizei n, uint *arrays) = 0;
  virtual void DeleteVertexArrays(sizei n, const uint *arrays) = 0;
  virtual void BindVertexArray(uint array) = 0;
  virtual void FlushMappedBufferRange(enumeration target, sizei offset, sizei length) = 0;
  virtual void *MapBufferRange(enumeration target, sizei offset, sizei length, bitfield access) = 0;
  virtual void FramebufferTextureLayer(enumeration target, enumeration attachment, uint texture, int level, int layer) = 0;
  virtual void RenderbufferStorageMultisample(enumeration target, sizei samples, enumeration internalformat, sizei width, sizei height) = 0;
  virtual void BlitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, bitfield mask, enumeration filter) = 0;
  virtual void GenerateMipmap(enumeration target) = 0;
  virtual void GetFramebufferAttachmentParameteriv(enumeration target, enumeration attachment, enumeration pname, int *params) = 0;
  virtual void FramebufferRenderbuffer(enumeration target, enumeration attachment, enumeration renderbuffertarget, uint renderbuffer) = 0;
  virtual void FramebufferTexture3D(enumeration target, enumeration attachment, enumeration textarget, uint texture, int level, int zoffset) = 0;
  virtual void FramebufferTexture2D(enumeration target, enumeration attachment, enumeration textarget, uint texture, int level) = 0;
  virtual void FramebufferTexture1D(enumeration target, enumeration attachment, enumeration textarget, uint texture, int level) = 0;
  virtual enumeration CheckFramebufferStatus(enumeration target) = 0;
  virtual void GenFramebuffers(sizei n, uint *framebuffers) = 0;
  virtual void DeleteFramebuffers(sizei n, const uint *framebuffers) = 0;
  virtual void BindFramebuffer(enumeration target, uint framebuffer) = 0;
  virtual bool IsFramebuffer(uint framebuffer) = 0;
  virtual void GetRenderbufferParameteriv(enumeration target, enumeration pname, int *params) = 0;
  virtual void RenderbufferStorage(enumeration target, enumeration internalformat, sizei width, sizei height) = 0;
  virtual void GenRenderbuffers(sizei n, uint *renderbuffers) = 0;
  virtual void DeleteRenderbuffers(sizei n, const uint *renderbuffers) = 0;
  virtual void BindRenderbuffer(enumeration target, uint renderbuffer) = 0;
  virtual bool IsRenderbuffer(uint renderbuffer) = 0;
  virtual const ubyte *GetStringi(enumeration name, uint index) = 0;
  virtual void ClearBufferfi(enumeration buffer, int drawbuffer, float depth, int stencil) = 0;
  virtual void ClearBufferfv(enumeration buffer, int drawbuffer, const float *value) = 0;
  virtual void ClearBufferuiv(enumeration buffer, int drawbuffer, const uint *value) = 0;
  virtual void ClearBufferiv(enumeration buffer, int drawbuffer, const int *value) = 0;
  virtual void GetTexParameterIuiv(enumeration target, enumeration pname, uint *params) = 0;
  virtual void GetTexParameterIiv(enumeration target, enumeration pname, int *params) = 0;
  virtual void TexParameterIuiv(enumeration target, enumeration pname, const uint *params) = 0;
  virtual void TexParameterIiv(enumeration target, enumeration pname, const int *params) = 0;
  virtual void Uniform4uiv(int location, sizei count, const uint *value) = 0;
  virtual void Uniform3uiv(int location, sizei count, const uint *value) = 0;
  virtual void Uniform2uiv(int location, sizei count, const uint *value) = 0;
  virtual void Uniform1uiv(int location, sizei count, const uint *value) = 0;
  virtual void Uniform4ui(int location, uint v0, uint v1, uint v2, uint v3) = 0;
  virtual void Uniform3ui(int location, uint v0, uint v1, uint v2) = 0;
  virtual void Uniform2ui(int location, uint v0, uint v1) = 0;
  virtual void Uniform1ui(int location, uint v0) = 0;
  virtual int GetFragDataLocation(uint program, const char *name) = 0;
  virtual void BindFragDataLocation(uint program, uint color, const char *name) = 0;
  virtual void GetUniformuiv(uint program, int location, uint *params) = 0;
  virtual void GetVertexAttribIuiv(uint index, enumeration pname, uint *params) = 0;
  virtual void GetVertexAttribIiv(uint index, enumeration pname, int *params) = 0;
  virtual void VertexAttribIPointer(uint index, int size, enumeration type, sizei stride, const void *pointer) = 0;
  virtual void EndConditionalRender() = 0;
  virtual void BeginConditionalRender(uint id, enumeration mode) = 0;
  virtual void ClampColor(enumeration target, enumeration clamp) = 0;
  virtual void GetTransformFeedbackVarying(uint program, uint index, sizei bufSize, sizei *length, sizei *size, enumeration *type, char *name) = 0;
  virtual void TransformFeedbackVaryings(uint program, sizei count, const char *const *varyings, enumeration bufferMode) = 0;
  virtual void BindBufferBase(enumeration target, uint index, uint buffer) = 0;
  virtual void BindBufferRange(enumeration target, uint index, uint buffer, sizei offset, sizei size) = 0;
  virtual void EndTransformFeedback() = 0;
  virtual void BeginTransformFeedback(enumeration primitiveMode) = 0;
  virtual bool IsEnabledi(enumeration target, uint index) = 0;
  virtual void Disablei(enumeration target, uint index) = 0;
  virtual void Enablei(enumeration target, uint index) = 0;
  virtual void GetIntegeri_v(enumeration target, uint index, int *data) = 0;
  virtual void GetBooleani_v(enumeration target, uint index, bool *data) = 0;
  virtual void ColorMaski(uint index, bool r, bool g, bool b, bool a) = 0;

  // OpenGL 3.1 core functions
  virtual void CopyBufferSubData(enumeration readTarget, enumeration writeTarget, sizei readOffset, sizei writeOffset, sizei size) = 0;
  virtual void UniformBlockBinding(uint program, uint uniformBlockIndex, uint uniformBlockBinding) = 0;
  virtual void GetActiveUniformBlockName(uint program, uint uniformBlockIndex, sizei bufSize, sizei *length, char *uniformBlockName) = 0;
  virtual void GetActiveUniformBlockiv(uint program, uint uniformBlockIndex, enumeration pname, int *params) = 0;
  virtual uint GetUniformBlockIndex(uint program, const char *uniformBlockName) = 0;
  virtual void GetActiveUniformName(uint program, uint uniformIndex, sizei bufSize, sizei *length, char *uniformName) = 0;
  virtual void GetActiveUniformsiv(uint program, sizei uniformCount, const uint *uniformIndices, enumeration pname, int *params) = 0;
  virtual void GetUniformIndices(uint program, sizei uniformCount, const char *const *uniformNames, uint *uniformIndices) = 0;
  virtual void PrimitiveRestartIndex(uint index) = 0;
  virtual void TexBuffer(enumeration target, enumeration internalformat, uint buffer) = 0;
  virtual void DrawElementsInstanced(enumeration mode, sizei count, enumeration type, const void *indices, sizei instancecount) = 0;
  virtual void DrawArraysInstanced(enumeration mode, int first, sizei count, sizei instancecount) = 0;

  // OpenGL 3.2 core functions
  virtual void SampleMaski(uint index, bitfield mask) = 0;
  virtual void GetMultisamplefv(enumeration pname, uint index, float *val) = 0;
  virtual void TexImage3DMultisample(enumeration target, sizei samples, int internalformat, sizei width, sizei height, sizei depth, bool fixedsamplelocations) = 0;
  virtual void TexImage2DMultisample(enumeration target, sizei samples, int internalformat, sizei width, sizei height, bool fixedsamplelocations) = 0;
  virtual void ProvokingVertex(enumeration mode) = 0;
  virtual void MultiDrawElementsBaseVertex(enumeration mode, const sizei *count, enumeration type, const void *const *indices, sizei drawcount, const int *basevertex) = 0;
  virtual void DrawElementsInstancedBaseVertex(enumeration mode, sizei count, enumeration type, const void *indices, sizei instancecount, int basevertex) = 0;
  virtual void DrawRangeElementsBaseVertex(enumeration mode, uint start, uint end, sizei count, enumeration type, const void *indices, int basevertex) = 0;
  virtual void DrawElementsBaseVertex(enumeration mode, sizei count, enumeration type, const void *indices, int basevertex) = 0;
  virtual void FramebufferTexture(enumeration target, enumeration attachment, uint texture, int level) = 0;

  // OpenGL 3.3 core functions
  virtual void VertexAttribP4uiv(uint index, enumeration type, bool normalized, const uint *value) = 0;
  virtual void VertexAttribP4ui(uint index, enumeration type, bool normalized, uint value) = 0;
  virtual void VertexAttribP3uiv(uint index, enumeration type, bool normalized, const uint *value) = 0;
  virtual void VertexAttribP3ui(uint index, enumeration type, bool normalized, uint value) = 0;
  virtual void VertexAttribP2uiv(uint index, enumeration type, bool normalized, const uint *value) = 0;
  virtual void VertexAttribP2ui(uint index, enumeration type, bool normalized, uint value) = 0;
  virtual void VertexAttribP1uiv(uint index, enumeration type, bool normalized, const uint *value) = 0;
  virtual void VertexAttribP1ui(uint index, enumeration type, bool normalized, uint value) = 0;
  virtual void SecondaryColorP3uiv(enumeration type, const uint *color) = 0;
  virtual void SecondaryColorP3ui(enumeration type, uint color) = 0;
  virtual void ColorP4uiv(enumeration type, const uint *color) = 0;
  virtual void ColorP4ui(enumeration type, uint color) = 0;
  virtual void ColorP3uiv(enumeration type, const uint *color) = 0;
  virtual void ColorP3ui(enumeration type, uint color) = 0;
  virtual void NormalP3uiv(enumeration type, const uint *coords) = 0;
  virtual void NormalP3ui(enumeration type, uint coords) = 0;
  virtual void MultiTexCoordP4uiv(enumeration texture, enumeration type, const uint *coords) = 0;
  virtual void MultiTexCoordP4ui(enumeration texture, enumeration type, uint coords) = 0;
  virtual void MultiTexCoordP3uiv(enumeration texture, enumeration type, const uint *coords) = 0;
  virtual void MultiTexCoordP3ui(enumeration texture, enumeration type, uint coords) = 0;
  virtual void MultiTexCoordP2uiv(enumeration texture, enumeration type, const uint *coords) = 0;
  virtual void MultiTexCoordP2ui(enumeration texture, enumeration type, uint coords) = 0;
  virtual void MultiTexCoordP1uiv(enumeration texture, enumeration type, const uint *coords) = 0;
  virtual void MultiTexCoordP1ui(enumeration texture, enumeration type, uint coords) = 0;
  virtual void TexCoordP4uiv(enumeration type, const uint *coords) = 0;
  virtual void TexCoordP4ui(enumeration type, uint coords) = 0;
  virtual void TexCoordP3uiv(enumeration type, const uint *coords) = 0;
  virtual void TexCoordP3ui(enumeration type, uint coords) = 0;
  virtual void TexCoordP2uiv(enumeration type, const uint *coords) = 0;
  virtual void TexCoordP2ui(enumeration type, uint coords) = 0;
  virtual void TexCoordP1uiv(enumeration type, const uint *coords) = 0;
  virtual void TexCoordP1ui(enumeration type, uint coords) = 0;
  virtual void VertexP4uiv(enumeration type, const uint *value) = 0;
  virtual void VertexP4ui(enumeration type, uint value) = 0;
  virtual void VertexP3uiv(enumeration type, const uint *value) = 0;
  virtual void VertexP3ui(enumeration type, uint value) = 0;
  virtual void VertexP2uiv(enumeration type, const uint *value) = 0;
  virtual void VertexP2ui(enumeration type, uint value) = 0;
  virtual void QueryCounter(uint id, enumeration target) = 0;
  virtual void GetSamplerParameterIuiv(uint sampler, enumeration pname, uint *params) = 0;
  virtual void GetSamplerParameterfv(uint sampler, enumeration pname, float *params) = 0;
  virtual void GetSamplerParameterIiv(uint sampler, enumeration pname, int *params) = 0;
  virtual void GetSamplerParameteriv(uint sampler, enumeration pname, int *params) = 0;
  virtual void SamplerParameterIuiv(uint sampler, enumeration pname, const uint *param) = 0;
  virtual void SamplerParameterIiv(uint sampler, enumeration pname, const int *param) = 0;
  virtual void SamplerParameterfv(uint sampler, enumeration pname, const float *param) = 0;
  virtual void SamplerParameterf(uint sampler, enumeration pname, float param) = 0;
  virtual void SamplerParameteriv(uint sampler, enumeration pname, const int *param) = 0;
  virtual void SamplerParameteri(uint sampler, enumeration pname, int param) = 0;
  virtual void BindSampler(uint unit, uint sampler) = 0;
  virtual bool IsSampler(uint sampler) = 0;
  virtual void DeleteSamplers(sizei count, const uint *samplers) = 0;
  virtual void GenSamplers(sizei count, uint *samplers) = 0;
  virtual void VertexAttribDivisor(uint index, uint divisor) = 0;
'''

import math
import re
import jinja2





def parse_arg(arg):
	match = re.search('([\w\*\&\s]+) ([\*\&\w]+)', arg)
	arg_type = match.groups()[0]
	arg_name = match.groups()[1]
	
	name = re.search('\w+',arg_name).group()
	type = arg_type + arg_name.replace(name,'')
	return (type,name)
	


def parse_fun(fun):
	reg = '(\w+) ([\*\w]+)\(([\w\*\s\&])\)'
	reg = '([\w\s\*\&]+) ([\*\s\w]+)\(([\w\*\&\s\,]*)\)'
	match = re.search(reg,fun)
	if match is not None:
		return_type = match.groups()[0]
		if len(return_type) == 0:
			print(fun)
		fun_name = match.groups()[1]
		name = re.search('\w+',fun_name).group()
		return_type += fun_name.replace(name,'')
		fun_args = match.groups()[2]
		args = fun_args.split(',')
		args = [parse_arg(arg) for arg in args if len(re.sub('\s+','',arg)) != 0]
		return (return_type, name, args)
		

template_str = '''
{%for fun in funs%}
{{fun[0]}} {{class}}::{{fun[1]}}({%for arg in fun[2]%}{{arg[0]}} {{arg[1]}}{%if not loop.last%},{%endif%}{%endfor%})
{
	{%if fun[0] != 'void'%}return{%endif%} funs_->gl{{fun[1]}}({%for arg in fun[2]%}{{arg[1]}}{%if not loop.last%}, {%endif%}{%endfor%});
}
{%endfor%}

'''

def make(name,text):
	metas = []
	lines = text.split('\n')
	for line in lines:
		meta = parse_fun(line)
	
		if meta is None:
			continue
		metas.append(meta)


	template = jinja2.Template(template_str)
	return template.render({'class': name,'funs':metas})


res = make('QtGLContext', text)

# with open('funs.cpp','w',encoding='utf-8') as fd:
# 	fd.write(res)