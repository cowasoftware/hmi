#include <iostream>
#include <fstream>
#include <sstream>

#include "./shader_lib.h"


{%if test -%}
static std::string GetShaderLibCodeFromFile(std::string const &file)
{
	static std::map<std::string, std::string> codes;
	auto code_iter = codes.find(file);
	
	if(code_iter != codes.end())
	{
		return code_iter->second;
	}
	std::string code;

	std::ifstream lib(file, std::ios::in);
	if(lib.is_open())
	{
		std::stringstream ss;
		ss << lib.rdbuf();
		code = ss.str();
		codes[file] = code;
	}
	else
	{
		std::cerr << __FILE__ << ":" << __LINE__ << " - DEBUG - " << "not exist file: " << file << std::endl;
	}

    return code;
}
{%-endif%}

{%-if not test%}
{%-for id,block in shader_lib_blocks.items()%}
{%-for type,name,lines in block%}
static const char *{{id.upper()}}_{{type.upper()}} = {%if lines | length == 0%}"";{%else%}
    {% for line in lines-%}
    "{{line}}{%if not loop.last -%}\n{%endif%}"{%if loop.last -%};{%endif%}
    {% endfor%}{%endif%}
{%-endfor%}
{%-endfor%}

static const std::map<ShaderLib::ID,Shader> shader_lib_map = {
	{%-for id,block in shader_lib_blocks.items()%}
	{ {{class_name}}::{{id}}, Shader{ {%for type,name,lines in block%}{{id.upper()}}_{{type.upper()}}{%if not loop.last%} ,{%endif%}{%endfor%}} }{%if not loop.last%} ,{%endif%}
	{%-endfor%}
};
{%else%}

static const std::map<ShaderLib::ID,Shader> shader_lib_map = {
	{%-for id,file in shader_lib_files.items()%}
	{ {{class_name}}::{{id}}, Shader{ {%for type,name, path in file%}GetShaderLibCodeFromFile("{{path}}"){%if not loop.last%} ,{%endif%}{%endfor%}} }{%if not loop.last%} ,{%endif%}
	{%-endfor%}
};

{%-endif%}



Shader ShaderLib::Get(ID id)
{
	auto iter = shader_lib_map.find(id);

	if(iter != shader_lib_map.end())
	{
		return iter->second;
	}
	else
	{	
		std::cerr << __FILE__ << ":" << __LINE__ << "invalid shader id: " << id << std::endl;
		return Shader();
	}
	
}
