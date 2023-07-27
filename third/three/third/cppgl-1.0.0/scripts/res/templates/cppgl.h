#pragma once

#include <cstdint>

namespace cppgl
{
	using boolean = unsigned char;
	using byte = signed char;
	using ubyte = unsigned char;
	using ushort = unsigned short;
	using uint = unsigned int;
	using sizei = int;
	using sizeiptr = signed long int;
	using intptr = signed long int;
	using enumeration = unsigned int;
	using bitfield = unsigned int;
	using uint64 = uint64_t;
	using int64 = int64_t;
	using clampf = float;
	using sync = void*;
	using debugproc = void(enumeration source,enumeration type,uint id,enumeration severity,sizei length,const char *message,const void *userParam);
	enum
	{
		{%-for name,value in enums %}
		{{name}} = {{value}}{%if not loop.last %},{%endif%}
		{%-endfor%}
	};

	class CppGL
	{
	public:
		CppGL() = default;
		virtual ~CppGL() = default;
		
	public:
		{%-for ret,name,args in funs%}
		virtual {{ret[0]}} {{name}}({%for arg_type,arg_name in args%}{{arg_type}} {{arg_name}}{%if not loop.last %}, {%endif%}{%endfor%});
		{%-endfor%}
	};
}