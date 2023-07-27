#pragma once

#include <vector>
#include <string>

#include <QOpenGLExtraFunctions>
#include <cppgl.h>
#include <three.h>

namespace cppgl
{
    class CppGL;
};

namespace three
{
    class Scene;
    class Camera;
}

using namespace three;

class Skybox
{
public:
    Skybox(cppgl::CppGL& _gl);
    ~Skybox();

public:
    void Init(std::vector<std::string> const& files);
    void Render(mat4 const& view, mat4 const& projection);

private:
    uint32_t vao_ = 0;
    uint32_t vbo_ = 0;
    uint32_t index_ = 0;
    uint32_t program_ = 0;
    uint32_t texture_ = 0;
    uint32_t slot_ = 0;
    cppgl::CppGL& gl_;
    bool initalized_ = false;
};