#pragma once

#include "../core/object.h"
#include "../math/matrix.h"

namespace three
{
	class Camera : public Object
	{
	public:
		Camera();
		virtual ~Camera();

	public:
		bool IsCamera() const override;

	public:
		void UpdateWorldMatrix();

	public:
		mat4 world_matrix_inverse;
		mat4 projection_matrix;
		mat4 projection_matrix_inverse;
	};
}