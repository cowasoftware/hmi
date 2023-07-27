import jinja2

types = {
    "UNSIGNED_BYTE": "uint8_t",
    "BYTE": "int8_t",
    "SHORT": "short",
    "INT": "int",
    "FLOAT": "float",
    "DOUBLE": "double",
    "FLOAT_VEC2": "vec2",
    "FLOAT_VEC3": "vec3",
    "FLOAT_VEC4": "vec4",
    "FLOAT_MAT2": "mat2",
    "FLOAT_MAT3": "mat3",
    "FLOAT_MAT4": "mat4"
}


defaults = {
    "UNSIGNED_BYTE": "0",
    "BYTE": "0",
    "SHORT": "0",
    "INT": "0",
    "FLOAT": "0.0f",
    "DOUBLE": "0.0",
    "FLOAT_VEC2": "vec2(0.0f,0.0f)",
    "FLOAT_VEC3": "vec3(0.0f,0.0f,0.0f)",
    "FLOAT_VEC4": "vec4(0.0f,0.0f,0.0f,0.0f)",
    "FLOAT_MAT2": "mat2(1.0f)",
    "FLOAT_MAT3": "mat3(1.0f)",
    "FLOAT_MAT4": "mat4(1.0f)"
}


s = '''

static const std::map<uint32_t, std::pair<std::function<void *(CppGL &, std::string const &, int32_t)>, std::function<void(void *)>>> simple_uniform_makers = 
{
  {%-for gl_type,cpp_type,default_value in types%}
  {CppGL::{{gl_type}}, {[](CppGL &gl, std::string const &id, int32_t addr){ return MakeSimpleUniform<{{cpp_type}}>(gl, id, addr, {{default_value}}); },[](void *p){ delete static_cast<GLSimpleUniform<{{cpp_type}}>*>(p); }}}{%if not loop.last%},{%endif%}
  {%-endfor%}
};

'''

types = [(k,v,defaults[k]) for k,v in types.items()]

t = jinja2.Template(s)
s = t.render(types=types)
print(s)

