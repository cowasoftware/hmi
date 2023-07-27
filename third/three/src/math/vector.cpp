#include "./vector.h"
#include <glm/gtx/string_cast.hpp>

std::ostream& operator<<(std::ostream& lhs, const vec1& rhs)
{
	lhs << glm::to_string(rhs).substr(4);
	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const vec2& rhs)
{
	lhs << glm::to_string(rhs).substr(4);
	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const vec3& rhs)
{
	lhs << glm::to_string(rhs).substr(4);
	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const vec4& rhs)
{
	lhs << glm::to_string(rhs).substr(4);
	return lhs;
}
