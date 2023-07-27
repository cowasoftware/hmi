#pragma once

#include "./camera.h"

namespace three
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera();
		virtual ~PerspectiveCamera();

	public:
		void UpdateProjectionMatrix();

	public:
		static bool IsInstance(Camera const &camera);
		static bool IsInstance(Object const &object);

	public:
		float znear;
		float zfar;
		float fov;
		float aspect;
	};
}