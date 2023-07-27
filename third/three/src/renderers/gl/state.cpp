#include <cppgl.h>

#include "./extensions.h"
#include "./capabilities.h"
#include "./state.h"

namespace three::gl
{

  State::State(cppgl::CppGL &_gl, Extensions &_extensions, Capabilities &_capabilities)
      : gl(_gl),
        extensions(_extensions),
        capabilities(_capabilities),
        current_program(0)
  {
  }

  bool State::UseProgram(uint32_t program)
  {
    // zinfo("program(%d) used", program);
    gl.UseProgram(program);

    if (current_program != program)
    {
      // zinfo("program(%d) used", program);
      current_program = program;
      return true;
    }

    return false;
  }

}