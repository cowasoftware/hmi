#pragma once

// #ifndef GLM_FORCE_XYZW_ONLY
// #define GLM_FORCE_XYZW_ONLY
// #endif


#include <glm/glm.hpp>
#include <iostream>

using mat2 = glm::mat2;
using mat3 = glm::mat3;
using mat4 = glm::mat4;


std::ostream& operator<<(std::ostream& lhs, const mat2& rhs);
std::ostream& operator<<(std::ostream& lhs, const mat3& rhs);
std::ostream& operator<<(std::ostream& lhs, const mat4& rhs);