#pragma once

#include "../core/object.h"

namespace three
{
	class Scene : public Object
	{
	public:
		Scene();
		virtual ~Scene();

	public:
		bool IsScene() const override;
	};
}
