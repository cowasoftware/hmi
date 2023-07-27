#include "./shader_chunk.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <map>

{%-if not test%}
{%-for shader_chunk_name, shader_chunk_lines in shader_chunk_blocks.items()%}
static const char *{{shader_chunk_name.upper()}} = {%if shader_chunk_lines | length == 0%}"";{%else%}
    {%- for line in shader_chunk_lines-%}
    "{{line}}{%if not loop.last -%}\n{%endif%}"{%if loop.last -%};{%endif%}
    {%endfor%}{%endif%}
{%-endfor%}
static const std::map<std::string,const char*> shader_chunk_map = {
	{%-for name in shader_chunk_blocks.keys()%}
	{ "{{name}}",{{name.upper()}} }{%if not loop.last%},{%endif%}
	{%-endfor%}
};
{%-else%}
static const std::map<std::string,const char*> shader_chunk_map = {
	{%-for name,file in shader_chunk_files.items()%}
	{ "{{name}}","{{file}}" }{%if not loop.last%},{%endif%}
	{%-endfor%}
};
{%-endif%}


std::string {{class_name}}::Get(std::string const& name)
{
{%-if not test%}
	auto iter = shader_chunk_map.find(name);
	
	if(iter == shader_chunk_map.end())
	{
		std::stringstream ss;
        ss << __FILE__ << ":" << __LINE__ << " - ERROR - " << "not eixst shader chunk: " << name << std::endl;
		return "";
	}

	return iter->second;
{%-else%}
    static std::map<std::string,std::string> codes;
	auto file_iter = shader_chunk_map.find(name);
	if(file_iter == shader_chunk_map.end())
	{
		std::stringstream ss;
		ss << __FILE__ << ":" << __LINE__ << " - ERROR - " << "not eixst shader chunk: " << name << std::endl;
		throw ss.str();
	}
	std::string file = file_iter->second;
	auto code_iter = codes.find(name);
	
	if(code_iter != codes.end())
	{
		return code_iter->second;
	}
	std::string code;

	std::ifstream chunk(file, std::ios::in);
	if(chunk.is_open())
	{
		std::stringstream ss;
		ss << chunk.rdbuf();
		code = ss.str();
		codes[name] = code;
	}
	else
	{
		std::cerr << __FILE__ << ":" << __LINE__ << " - DEBUG - " << "not exist file: " << file << std::endl;
	}

    return code;
{%-endif%}
}

