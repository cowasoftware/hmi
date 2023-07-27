#pragma once

#include <cstdint>
#include <cppgl.h>

#include <QOpenGLExtraFunctions>

class QtGLES3 : public cppgl::CppGL
{
public:
	QtGLES3();
	~QtGLES3();
	
public:
	{%-for ret,name,args in funs%}
	{{ret[0]}} {{name}}({%for arg_type,arg_name in args%}{{arg_type}} {{arg_name}}{%if not loop.last %}, {%endif%}{%endfor%}) override;
	{%-endfor%}	
private:
	QOpenGLExtraFunctions *funs_;
};