#include <glm/gtc/matrix_inverse.hpp>

#include "./camera.h"

namespace three
{
	static const std::string TYPE = "Camera";

	Camera::Camera()
		: world_matrix_inverse(1.0f),
		  projection_matrix(1.0f),
		  projection_matrix_inverse(1.0f)

	{
		type_ = TYPE;
	}

	Camera::~Camera()
	{
	}

	bool Camera::IsCamera() const
	{
		return true;
	}

	void Camera::UpdateWorldMatrix()
	{
		Object::UpdateWorldMatrix();
		world_matrix_inverse = glm::inverse(world_matrix);
	}
}