#pragma once

#include <string>
#include <vector>
#include <map>


class Shader
{
public:
	std::string vertex;
	std::string fragment;
};

class ShaderLib
{
public:
	enum ID
	{
		INVALID = 0,
		POINTS,
		DEFAULT,
		MESH_LAMBERT,
		MESH_PHONG,
		MESH_BASIC
	};
public:
	static Shader Get(ID id);
};