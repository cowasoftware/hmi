#include "./perspective_camera.h"

namespace three
{
	static const std::string TYPE("PerspectiveCamera");

	PerspectiveCamera::PerspectiveCamera()
		: znear(0.01f),
		  zfar(500.0f),
		  fov(glm::radians(45.0f)),
		  aspect(1.0f)
	{
		type_ = TYPE;
		UpdateProjectionMatrix();
	}

	PerspectiveCamera::~PerspectiveCamera()
	{
	}

	void PerspectiveCamera::UpdateProjectionMatrix()
	{
		projection_matrix = glm::perspective(fov, aspect, znear, zfar);
	}

	bool PerspectiveCamera::IsInstance(Camera const &camera)
	{
		return camera.get_type() == TYPE;
	}

	bool PerspectiveCamera::IsInstance(Object const &object)
	{
		return object.IsCamera() && IsInstance(static_cast<Camera const &>(object));
	}
}