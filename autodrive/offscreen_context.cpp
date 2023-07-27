#include <iostream>
#include <stdexcept>
#include "offscreen_context.h"

using namespace cppgl;

OffscreenContext::OffscreenContext(CppGL &gl, uint32_t width, uint32_t height)
    : _gl(gl), _width(width), _height(height)
{
    Viewport(0, 0, _width, _height);
}

OffscreenContext::~OffscreenContext()
{
    if (0 != _fbo)
    {
        _gl.DeleteFramebuffers(1, &_fbo);
        _gl.DeleteTextures(1, &_cbo);
        _gl.DeleteRenderbuffers(1, &_rbo);
    }
}

void OffscreenContext::Viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    _view_x = x < _width ? x : _width;
    _view_y = y < _height ? y : _height;
    _view_width = _view_x + width < _width ? width : width - _view_x;
    _view_height = _view_y + height < _height ? height : height - _view_y;
}

uint32_t OffscreenContext::With(OffscreenContext::Render render)
{
    auto &gl = _gl;

    if (0 == _fbo)
    {
        gl.GenFramebuffers(1, &_fbo);
        gl.BindFramebuffer(CPPGL_FRAMEBUFFER, _fbo);

        gl.GenTextures(1, &_cbo);
        gl.BindTexture(CPPGL_TEXTURE_2D, _cbo);
        gl.TexImage2D(CPPGL_TEXTURE_2D, 0, CPPGL_RGB, _width, _height, 0, CPPGL_RGB, CPPGL_UNSIGNED_BYTE, NULL);
        gl.TexParameteri(CPPGL_TEXTURE_2D, CPPGL_TEXTURE_MIN_FILTER, CPPGL_LINEAR);
        gl.TexParameteri(CPPGL_TEXTURE_2D, CPPGL_TEXTURE_MAG_FILTER, CPPGL_LINEAR);
        gl.BindTexture(CPPGL_TEXTURE_2D, 0);
        gl.FramebufferTexture2D(CPPGL_FRAMEBUFFER, CPPGL_COLOR_ATTACHMENT0, CPPGL_TEXTURE_2D, _cbo, 0);

        gl.GenRenderbuffers(1, &_rbo);
        gl.BindRenderbuffer(CPPGL_RENDERBUFFER, _rbo);
        gl.RenderbufferStorage(CPPGL_RENDERBUFFER, CPPGL_DEPTH24_STENCIL8, _width, _height);
        gl.BindRenderbuffer(CPPGL_RENDERBUFFER, 0);

        gl.FramebufferRenderbuffer(CPPGL_FRAMEBUFFER, CPPGL_DEPTH_STENCIL_ATTACHMENT, CPPGL_RENDERBUFFER, _rbo);
        if (gl.CheckFramebufferStatus(CPPGL_FRAMEBUFFER) != CPPGL_FRAMEBUFFER_COMPLETE)
        {
            throw std::logic_error("ERROR: Framebuffer is not complete!");
        }

        gl.BindFramebuffer(CPPGL_FRAMEBUFFER, 0);
    }

    gl.BindFramebuffer(CPPGL_FRAMEBUFFER, _fbo);
    gl.Viewport(_view_x, _view_y, _view_width, _view_height);

    if (render)
    {
        render(gl);
    }

    gl.BindFramebuffer(CPPGL_FRAMEBUFFER, 0);
    return _cbo;
}

MSAAOffscreenContext::MSAAOffscreenContext(CppGL &gl, uint32_t width, uint32_t height, uint32_t sample)
    : OffscreenContext(gl, width, height),
      _sample(sample)
{
    _sample = sample;
}

MSAAOffscreenContext::~MSAAOffscreenContext()
{
    if (_f_fbo)
    {
        _gl.DeleteFramebuffers(1, &_f_fbo);
        _gl.DeleteTextures(1, &_f_cbo);
    }
}

uint32_t MSAAOffscreenContext::With(Render render)
{
    auto &gl = _gl;

    if (0 == _fbo)
    {
        // 离屏
        gl.GenFramebuffers(1, &_fbo);
        gl.BindFramebuffer(CPPGL_FRAMEBUFFER, _fbo);
        gl.GenTextures(1, &_cbo);

        gl.BindTexture(CPPGL_TEXTURE_2D_MULTISAMPLE, _cbo);
        gl.TexImage2DMultisample(CPPGL_TEXTURE_2D_MULTISAMPLE, _sample, CPPGL_RGB, _width, _height, true);
        gl.TexParameteri(CPPGL_TEXTURE_2D_MULTISAMPLE, CPPGL_TEXTURE_MIN_FILTER, CPPGL_LINEAR);
        gl.TexParameteri(CPPGL_TEXTURE_2D_MULTISAMPLE, CPPGL_TEXTURE_MAG_FILTER, CPPGL_LINEAR);
        gl.BindTexture(CPPGL_TEXTURE_2D_MULTISAMPLE, 0);
        gl.FramebufferTexture2D(CPPGL_FRAMEBUFFER, CPPGL_COLOR_ATTACHMENT0, CPPGL_TEXTURE_2D_MULTISAMPLE, _cbo, 0);

        gl.GenRenderbuffers(1, &_rbo);
        gl.BindRenderbuffer(CPPGL_RENDERBUFFER, _rbo);
        gl.RenderbufferStorageMultisample(CPPGL_RENDERBUFFER, _sample, CPPGL_DEPTH24_STENCIL8, _width, _height);
        gl.BindRenderbuffer(CPPGL_RENDERBUFFER, 0);
        gl.FramebufferRenderbuffer(CPPGL_FRAMEBUFFER, CPPGL_DEPTH_STENCIL_ATTACHMENT, CPPGL_RENDERBUFFER, _rbo);

        if (gl.CheckFramebufferStatus(CPPGL_FRAMEBUFFER) != CPPGL_FRAMEBUFFER_COMPLETE)
        {
            throw std::logic_error("ERROR: Framebuffer is not complete!");
        }

        gl.BindFramebuffer(CPPGL_FRAMEBUFFER, 0);

        // 输出
        gl.GenFramebuffers(1, &_f_fbo);
        gl.BindFramebuffer(CPPGL_FRAMEBUFFER, _f_fbo);

        gl.GenTextures(1, &_f_cbo);
        gl.BindTexture(CPPGL_TEXTURE_2D, _f_cbo);
        gl.TexImage2D(CPPGL_TEXTURE_2D, 0, CPPGL_RGB, _width, _height, 0, CPPGL_RGB, CPPGL_UNSIGNED_BYTE, NULL);
        gl.TexParameteri(CPPGL_TEXTURE_2D, CPPGL_TEXTURE_MIN_FILTER, CPPGL_LINEAR);
        gl.TexParameteri(CPPGL_TEXTURE_2D, CPPGL_TEXTURE_MAG_FILTER, CPPGL_LINEAR);
        gl.BindTexture(CPPGL_TEXTURE_2D, 0);
        gl.FramebufferTexture2D(CPPGL_FRAMEBUFFER, CPPGL_COLOR_ATTACHMENT0, CPPGL_TEXTURE_2D, _f_cbo, 0);

        if (gl.CheckFramebufferStatus(CPPGL_FRAMEBUFFER) != CPPGL_FRAMEBUFFER_COMPLETE)
        {
            throw std::logic_error("ERROR: Framebuffer is not complete!");
        }

        gl.BindFramebuffer(CPPGL_FRAMEBUFFER, 0);
    }

    gl.Enable(CPPGL_MULTISAMPLE);
    gl.BindFramebuffer(CPPGL_FRAMEBUFFER, _fbo);
    gl.Viewport(_view_x, _view_y, _view_width, _view_height);

    if (render)
    {
        render(gl);
    }
    gl.BindFramebuffer(CPPGL_READ_FRAMEBUFFER, _fbo);
    gl.BindFramebuffer(CPPGL_DRAW_FRAMEBUFFER, _f_fbo);
    gl.BlitFramebuffer(0, 0,
                       _width, _height,
                       0, 0,
                       _width, _height,
                       cppgl::CPPGL_COLOR_BUFFER_BIT, cppgl::CPPGL_NEAREST);

    gl.BindFramebuffer(CPPGL_FRAMEBUFFER, 0);
    return _f_cbo;
}