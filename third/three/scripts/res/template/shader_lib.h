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
		{%-for id in shader_lib_ids%}
		{{id}}{%if not loop.last%},{%endif%}
		{%-endfor%}
	};
public:
	static Shader Get(ID id);
};