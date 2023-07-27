#include "cppgl.h"
#include <string>
#include <stdexcept>

namespace cppgl
{
	{%-for ret,name,args in funs%}
	{{ret[0]}} CppGL::{{name}}({%for arg_type,arg_name in args%}{{arg_type}} {{arg_name}}{%if not loop.last %}, {%endif%}{%endfor%})
	{
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " +  "the function[{{name}}] is unimplemented, please implement it.");
		{%-if ret[0] != 'void'%}return {{ret[1]}};{%endif%} 
	}
	{%endfor%}
}