#include "./qtgles3.h"

QtGLES3::QtGLES3()
{
	funs_ = new QOpenGLExtraFunctions();
	funs_->initializeOpenGLFunctions();
}

QtGLES3::~QtGLES3()
{
	delete funs_;
}

{%-for ret,name,args in funs%}
{{ret[0]}} QtGLES3::{{name}}({%for arg_type,arg_name in args%}{{arg_type}} {{arg_name}}{%if not loop.last %}, {%endif%}{%endfor%})
{
	{%if ret[0] != 'void'%}return {%endif%}funs_->gl{{name}}({%for arg_type,arg_name in args%}{{arg_name}}{%if not loop.last %}, {%endif%}{%endfor%});
}
{%endfor%}