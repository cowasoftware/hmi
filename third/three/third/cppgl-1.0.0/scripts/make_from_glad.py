from dataclasses import replace
from email.policy import default
import os
import re
import json

from jinja2 import Template
from jinja2.loaders import FileSystemLoader
from jinja2 import Environment

import utils


home = utils.get_dir(__file__, 2)
res_dir = utils.join_path(home, 'scripts/res')
src_dir = utils.join_path(home, 'src')
t_dir = utils.join_path(home, 'scripts/res/templates')
t_env = Environment(loader=FileSystemLoader(t_dir))


text = utils.read_txt(utils.join_path(res_dir, 'glad.h'))

types = [('GLuint', 'uint32_t'),
         ('GLenum', 'enumeration'),
         ('GLchar', 'char'),
         ('GLsizeiptr', 'sizeiptr'),
         ('GLsizei', 'int32_t'),
         ('GLbyte', 'int8_t'),
         ('GLubyte', 'uint8_t'),
         ('GLbitfield', 'bitfield'),
         ('GLboolean', 'bool'),
         ('GLintptr', 'int64_t'),
         ('GLint', 'int32_t'),
         ('GLfloat', 'float'),
         ('GLshort', 'int16_t'),
         ('GLdouble', 'double'),
         ('GLushort', 'uint16_t')
         ]

default = [('GLuint', '0'),
         ('GLenum', '0'),
         ('GLchar', '\'\''),
         ('GLsizeiptr', '0'),
         ('GLsizei', '0'),
         ('GLbyte', '0'),
         ('GLubyte', '0'),
         ('GLbitfield', '0'),
         ('GLboolean', 'false'),
         ('GLintptr', '0'),
         ('GLint', '0'),
         ('GLfloat', '0.0f'),
         ('GLshort', '0'),
         ('GLdouble', '0.0'),
         ('GLushort', '0')
         ]


def replace_type(type):
    for t1, t2 in types:
        if t1 in type:
            return type.replace(t1, t2)
    return type


def find_enum(s: str):
    lines = s.split('\n')
    enums = []
    regex = '\s*#define\s+(GL_\w+)\s+([a-z0-9A-Z]+)'
    for line in lines:
        match = re.search(regex, line)
        if not match:
            continue

        enums.append(('CPP' + match.group(1), match.group(2)))
    return enums


def parse_arg(arg):
    regex_list = []
    # const type* const* name
    # regex_list.append('\s*(void)(\w*)\s*')  # void
    regex_list.append(
        '\s*(((const)*)\s*(\w+)\s*(\**)\s*((const)*)(\**))\s*(\w*)\s*')

    arg_type = None
    arg_name = None

    for regex in regex_list:
        match = re.search(regex, arg)
        if not match:
            continue

        arg_type = match.group(1)
        arg_type = replace_type(arg_type)
        arg_type = arg_type.strip()
        arg_name = match.groups()[-1]
        arg_name = arg_name.strip()
        break

    return (arg_type, arg_name)


def find_function(s: str):
    reg = '([\w\s\*\&]+) ([\*\s\w]+)\(([\w\*\&\s\,]*)\)'
    match = re.search(reg, s)
    if match is not None:
        return_type = match.groups()[0]
        if len(return_type) == 0:
            print(fun)
            pass
        fun_name = match.groups()[1]
        name = re.search('\w+', fun_name).group()
        return_type += fun_name.replace(name, '')
        # print(name)

        return_type = replace_type(return_type)
        fun_args = match.groups()[2]
        args = fun_args.split(',')
        args = [parse_arg(arg)
                for arg in args if len(re.sub('\s+', '', arg)) != 0]

        return (return_type, name, args)


def find_glad_api(s: str):
    lines = s.split('\n')
    apis = []
    regex = '\s*GLAPI\s+(\w+)\s+(glad_\w+)'
    for line in lines:
        match = re.search(regex, line)
        if not match:
            continue
        apis.append((match.group(1), match.group(2)))
    return apis


def find_glapi_extern(s: str):
    lines = s.split('\n')
    regex = '\s*typedef\s+([\w\*\s*]+)\s+\(\s*APIENTRYP (\w+)\s*\)\s*\(\s*(.*)\s*\)\s*'
    externs = []
    for line in lines:
        match = re.search(regex, line)
        if not match:
            continue
        line = '%s %s(%s)' % (match.group(1), match.group(2), match.group(3))
        extern = find_function(line)
        externs.append(extern)

    return externs


def find_api_define(s: str):
    lines = s.split('\n')
    regex = '\s*#define\s+(gl\w+)\s+(glad_\w+)'
    defines = []
    for line in lines:
        match = re.search(regex, line)
        if not match:
            continue
        defines.append((match.group(1), match.group(2)))
    return defines


def generate_function(text):
    externs = find_glapi_extern(text)
    apis = find_glad_api(text)
    defines = find_api_define(text)

    externs = {extern[1]: extern for extern in externs}
    apis = {glad: name for name, glad in apis}
    funs = []
    for gl, glad in defines:
        if glad not in apis:
            print(1, gl)
            continue
        elif apis[glad] not in externs:
            print(2, gl)
            continue
        extern = externs[apis[glad]]

        funs.append((extern[0], gl[2:], extern[2]))

    return funs


def generate():
    h_file = utils.join_path(src_dir, 'cppgl.h')
    cpp_file = utils.join_path(src_dir, 'cppgl.cpp')
    text = utils.read_txt(utils.join_path(res_dir, 'qt/.h'))

    enums = find_enum(text)
    funs = generate_function(text)

    t_h = t_env.get_template('cppgl.h')
    utils.write_txt(h_file, t_h.render(enums=enums, funs=funs))

    t_cpp = t_env.get_template('cppgl.cpp')
    utils.write_txt(cpp_file, t_cpp.render(enums=enums, funs=funs))


generate()
#regex = '\s*(((const)*)\s*(\w+)\s*(\**)\s*((const)*)(\**))\s*(\w*)\s*'
# print(re.search(regex,'void').groups())
