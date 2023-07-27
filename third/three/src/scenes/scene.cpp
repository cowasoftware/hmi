#include "./scene.h"

namespace three
{
	static const std::string TYPE("Scene");

	Scene::Scene()
	{
		type_ = TYPE;
	}

	Scene::~Scene()
	{
	}

	bool Scene::IsScene() const
	{
		return true;
	}

}