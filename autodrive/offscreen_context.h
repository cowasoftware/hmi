#pragma once

#include <cstdint>
#include <functional>
#include <cppgl.h>

using cppgl::CppGL;

class OffscreenContext
{
public:
    using Render = std::function<void(CppGL &)>;

    OffscreenContext(CppGL &gl, uint32_t width, uint32_t height);
    virtual ~OffscreenContext();

    void Viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    virtual uint32_t With(Render render);

protected:
    CppGL &_gl;
    uint32_t _width = 0;
    uint32_t _height = 0;
    uint32_t _view_x = 0;
    uint32_t _view_y = 0;
    uint32_t _view_width = 0;
    uint32_t _view_height = 0;
    uint32_t _fbo = 0;
    uint32_t _cbo = 0;
    uint32_t _rbo = 0;
};

class MSAAOffscreenContext : public OffscreenContext
{
public:
    MSAAOffscreenContext(CppGL &gl, uint32_t width, uint32_t height, uint32_t sample);
    virtual ~MSAAOffscreenContext();
    uint32_t With(Render render) override;

protected:
    uint32_t _sample = 0;
    uint32_t _f_fbo = 0;
    uint32_t _f_cbo = 0;
};