#include <stdexcept>
#include <iostream>

#include "./geometry.h"
#include "./geometry_attribute.h"

static size_t id = 0;
static const Event dispose_event("dispose");
static const std::string TYPE("Geometry");

Geometry::Geometry()
	: index_(nullptr)
{
	type_ = TYPE;
	id_ = ++id;
}

Geometry::~Geometry()
{
	DispatchEvent(dispose_event);
}

GeometryAttribute* Geometry::GetAttribute(const std::string& name)
{
	auto iter = attributes_.find(name);

	if (iter == attributes_.end())
	{
		return nullptr;
	}

	return iter->second;
}


GeometryAttribute const* Geometry::GetAttribute(const std::string& name) const
{
	auto iter = attributes_.find(name);

	if (iter == attributes_.end())
	{
		return nullptr;
	}

	return iter->second;
}

void Geometry::SetAttribute(const std::string& name, GeometryAttribute& attribute)
{
	auto iter = attributes_.find(name);
	if (iter != attributes_.end())
	{
		iter->second = &attribute;
	}
	else
	{
		attributes_[name] = &attribute;
	}
}

bool Geometry::HasAttribute(const std::string& name)
{
	return attributes_.find(name) != attributes_.end();
}

void Geometry::DeleteAttribute(const std::string& name)
{
	auto iter = attributes_.find(name);
	attributes_.erase(iter);
}

void Geometry::SetIndex(GeometryAttribute& index)
{
	index_ = &index;
}

GeometryAttribute* Geometry::GetIndex()
{
	return index_;
}

GeometryAttribute const* Geometry::GetIndex() const
{
	return index_;
}
