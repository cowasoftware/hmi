#include <cassert>

#include "./properties.h"

namespace three::gl
{

	MaterialProperty::MaterialProperty() : uniforms(nullptr),
		current_program(nullptr)
	{
	}

	Properties::Properties()
	{
	}

	Properties::~Properties()
	{
		// asert(material_properties_.empty());
	}

	MaterialProperty& Properties::Get(Material& material)
	{
		auto property_iter = material_properties_.find(&material);

		if (property_iter == material_properties_.end())
		{
			auto property = new MaterialProperty();
			material_properties_[&material] = property;
			return *property;
		}

		return *(property_iter->second);
	}

	void Properties::Remove(Material& material)
	{
		auto property_iter = material_properties_.find(&material);

		if (property_iter != material_properties_.end())
		{
			delete property_iter->second;
			material_properties_.erase(&material);
		}
	}
}
