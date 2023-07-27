#include <cassert>
#include <cstring>
#include <cppgl.h>

#include "./attributes.h"


namespace three::gl
{
  Attribute::Attribute()
    : location(0),
    type(0),
    size(0)
  {
  }

  Attribute::Attribute(std::string const& name, uint32_t location, uint32_t type, uint32_t size)
    : name(name),
    location(location),
    type(type),
    size(size)
  {
  }

  Attributes::Attributes(cppgl::CppGL& _gl, uint32_t _program)
    : gl(_gl),
    program(_program)
  {
    int32_t n;
    gl.GetProgramiv(program, cppgl::CPPGL_ACTIVE_ATTRIBUTES, &n);

    // zdebug("attributes count: %d", n);
    char name[1024];
    int32_t length;
    int32_t size;
    uint32_t type;

    for (int i = 0; i < n; i++)
    {
      memset(name, 0, sizeof(name));
      gl.GetActiveAttrib(program, i, sizeof(name), &length, &size, &type, name);
      int32_t location = gl.GetAttribLocation(program, name);
      uint32_t location_size = 1;

      if (type == cppgl::CPPGL_FLOAT_MAT2)
        location_size = 2;
      else if (type == cppgl::CPPGL_FLOAT_MAT3)
        location_size = 3;
      else if (type == cppgl::CPPGL_FLOAT_MAT4)
        location_size = 4;

      // zdebug("parse attribute[%d] : %s, %d", location, name, type);
      attributes.emplace_back(Attribute{ name, static_cast<uint32_t>(location), type, location_size });
    }
  }
}
