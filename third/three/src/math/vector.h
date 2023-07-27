#pragma once

// #ifndef GLM_FORCE_XYZW_ONLY
// #define GLM_FORCE_XYZW_ONLY
// #endif

#include <iostream>

#include <glm/glm.hpp>
#include <iostream>

using vec1 = glm::vec1;
using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;

std::ostream& operator<<(std::ostream& lhs, const vec1& rhs);
std::ostream& operator<<(std::ostream& lhs, const vec2& rhs);
std::ostream& operator<<(std::ostream& lhs, const vec3& rhs);
std::ostream& operator<<(std::ostream& lhs, const vec4& rhs);
