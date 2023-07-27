#include "./material.h"

namespace three
{
	static size_t s_id = 1;
	static const Event dispose_event("dispose");
	static const std::string TYPE = "Material";

	Material::Material()
		: wireframe(false),
		vertex_colors(false),
		transparent(false),
		opacity(1.0),
		version(0)
	{
		type_ = TYPE;
		id_ = s_id++;
	}

	Material::~Material()
	{
		DispatchEvent(dispose_event);
	}

	void Material::OnBeforeRender()
	{
	}

	void Material::NeedUpdate(bool update)
	{
		if (update)
		{
			version++;
		}
	}
}