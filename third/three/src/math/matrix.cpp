#include "./matrix.h"
#include <glm/gtx/string_cast.hpp>

std::ostream& operator<<(std::ostream& lhs, const mat2& rhs)
{
	lhs << glm::to_string(rhs);
	return lhs;
}
std::ostream& operator<<(std::ostream& lhs, const mat3& rhs)
{
	lhs << glm::to_string(rhs);
	return lhs;
}
std::ostream& operator<<(std::ostream& lhs, const mat4& rhs)
{
	lhs << glm::to_string(rhs);
	return lhs;
}