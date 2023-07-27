#pragma once

#include <string>
#include <vector>

namespace three
{
	class Object;

	class ObjectLoader
	{
	public:
		Object* Load(const std::string& file);
	};
}
