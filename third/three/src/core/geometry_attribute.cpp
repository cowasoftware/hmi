#include <iostream>

#include "./geometry_attribute.h"

namespace three
{

	static const std::string TYPE = "GeometryAttribute";

	UpdateRange::UpdateRange()
		: offset(0),
		count(-1)
	{
	}

	GeometryAttribute::GeometryAttribute()
		: normalized(false),
		size(0),
		usage(Usage::NONE),
		version(0),
		count(0)
	{
		type_ = TYPE;
	}

	GeometryAttribute::GeometryAttribute(GeometryAttribute const& attribute)
		: array(attribute.array),
		normalized(attribute.normalized),
		size(attribute.size),
		usage(attribute.usage),
		version(attribute.version),
		count(attribute.count),
		update_range(attribute.update_range)
	{
		type_ = TYPE;
	}

	GeometryAttribute::GeometryAttribute(GeometryAttribute&& attribute)
		: array(std::move(attribute.array)),
		normalized(attribute.normalized),
		size(attribute.size),
		usage(attribute.usage),
		version(attribute.version),
		count(attribute.count),
		update_range(attribute.update_range)
	{
		type_ = TYPE;
		attribute.normalized = false;
		attribute.size = 0;
		attribute.usage = Usage::NONE;
		attribute.version = 0;
		attribute.count = 0;
		update_range = UpdateRange();
	}

	GeometryAttribute::GeometryAttribute(Array const& array, size_t size, bool normalized, Usage _usage) : array(array),
		normalized(normalized),
		size(size),
		version(0)

	{
		type_ = TYPE;
		count = size != 0 ? array.size() / size : 0;
		usage = _usage;
	}

	GeometryAttribute::~GeometryAttribute()
	{
	}

	GeometryAttribute& GeometryAttribute::operator=(GeometryAttribute const& attribute)
	{
		array = attribute.array;
		normalized = attribute.normalized;
		size = attribute.size;
		usage = attribute.usage;
		version = attribute.version;
		count = attribute.count;
		update_range = attribute.update_range;
		return *this;
	}

	GeometryAttribute& GeometryAttribute::operator=(GeometryAttribute&& attribute)
	{
		array = std::move(attribute.array);
		normalized = attribute.normalized;
		size = attribute.size;
		usage = attribute.usage;
		version = attribute.version;
		count = attribute.count;
		update_range = attribute.update_range;

		attribute.normalized = false;
		attribute.size = 0;
		attribute.usage = Usage::NONE;
		attribute.version = 0;
		attribute.count = 0;
		attribute.update_range = UpdateRange();

		return *this;
	}

	GeometryAttribute::operator bool()
	{
		return size > 0 && usage != Usage::NONE;
	}

	void GeometryAttribute::NeedUpdate(bool update)
	{
		if (update)
		{
			version++;
		}
	}

}