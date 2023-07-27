#include "./quaternion.h"
#include <glm/gtx/string_cast.hpp>

std::ostream& operator<<(std::ostream& lhs, const quat& rhs)
{
	lhs << glm::to_string(rhs);
	return lhs;
}
