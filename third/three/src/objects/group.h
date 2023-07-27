#pragma once

#include "../core/object.h"

namespace three
{
	class Group : public Object
	{
	public:
		Group();
		virtual ~Group();

	public:
		bool IsGroup() const override;
	};
}