#pragma once

#include <cstdint>

namespace cppgl
{
  class CppGL;
}

namespace three::gl
{

  class Extensions;
  class Capabilities;

  class State
  {
  public:
    State(cppgl::CppGL& gl, Extensions& extensions, Capabilities& capabilities);

  public:
    bool UseProgram(uint32_t program);

  private:
    cppgl::CppGL& gl;
    Extensions& extensions;
    Capabilities& capabilities;
    uint32_t current_program;
  };
}
