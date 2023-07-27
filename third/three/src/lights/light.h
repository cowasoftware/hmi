#pragma once

#include "../core/object.h"
#include "../math/vector.h"

namespace three
{
	class Light : public Object
	{
	public:
		Light();
		virtual ~Light();

	public:
		bool IsLight() const override;

	public:
		void SetColor(uint32_t c) { color = vec3(((c >> 16) & 0xFF) / 255.0f, ((c >> 8) & 0xFF) / 255.0f, (c & 0xFF) / 255.0f); };

	public:
		vec3 color;
		float intensity;
	};
}