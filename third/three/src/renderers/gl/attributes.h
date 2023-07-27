#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include <cppgl.h>

namespace three::gl
{
  class Attribute
  {
  public:
    Attribute();
    Attribute(std::string const& name, uint32_t location, uint32_t type, uint32_t size);

  public:
    std::string name;
    uint32_t location;
    uint32_t type;
    uint32_t size;
  };

  class Attributes
  {
  public:
    Attributes(cppgl::CppGL& gl, uint32_t program);

  public:
    cppgl::CppGL& gl;
    uint32_t program;
    std::vector<Attribute> attributes;
  };

}
