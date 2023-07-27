#pragma once

// #ifndef GLM_FORCE_QUAT_DATA_XYZW
// #define GLM_FORCE_QUAT_DATA_XYZW
// #endif

#include <glm/gtc/quaternion.hpp>
#include <iostream>

using quat = glm::quat;

std::ostream &operator<<(std::ostream &lhs, const quat &rhs);