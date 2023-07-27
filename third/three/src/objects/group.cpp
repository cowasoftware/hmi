#include "./group.h"

namespace three
{
	static const std::string TYPE("Group");
	
	Group::Group()
	{
		type_ = TYPE;
	}

	Group::~Group()
	{
	}

	bool Group::IsGroup() const
	{
		return true;
	}
}