from email.mime import base
import re
import os
import json
from tokenize import group
import shutil

from jinja2 import Template
from jinja2.loaders import FileSystemLoader
from jinja2 import Environment

import utils


home = utils.get_dir(__file__, 2)
res_dir = utils.join_path(home, 'scripts/res')
inc_dir = utils.join_path(home, 'include')
src_dir = utils.join_path(home, 'src')
t_dir = utils.join_path(home, 'scripts/res/templates')
t_env = Environment(loader=FileSystemLoader(t_dir))


types = [
    ('GLboolean', 'boolean'),
    ('GLuint', 'uint'),
    ('GLenum', 'enumeration'),
    ('GLchar', 'char'),
    ('GLsizeiptr', 'sizeiptr'),
    ('GLsizei', 'sizei'),
    ('GLbyte', 'byte'),
    ('GLubyte', 'ubyte'),
    ('GLbitfield', 'bitfield'),
    ('GLboolean', 'bool'),
    ('GLintptr', 'intptr'),
    ('GLint', 'int'),
    ('GLfloat', 'float'),
    ('GLshort', 'short'),
    ('GLdouble', 'double'),
    ('GLushort', 'ushort'),
    ('qopengl_GLsizeiptr', 'sizeiptr'),
    ('qopengl_GLintptr', 'intptr'),
    ('GLclampf', 'clampf'),
    ('GLuint64', 'uint64'),
    ('GLint64', 'int64'),
    ('GLsync', 'sync'),
    ('GLvoid', 'void'),
    ('GLDEBUGPROC', 'debugproc')
]

default = [
    ('GLboolean', 'false'),
    ('GLuint', '0'),
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
    ('GLushort', '0'),
    ('GLsync', 'nullptr')
]


def replace_type(type):
    match = None
    try:
        spans = re.findall('\w+', type)
        # print(spans)
        for span in spans:
            for t1, t2 in types:
                if t1 == span:
                    type = type.replace(t1, t2)
        return type

    except Exception as e:
        print('not find', type, e)
        exit()


def get_default_value(type):
    match = None
    try:
        if '*' in type:
            return 'nullptr'

        spans = re.findall('\w+', type)
        for span in spans:
            for t1, t2 in default:
                if t1 == span:
                    if t1 == span:
                        return t2
        return ''
    except Exception as e:
        print('not find default value', type, e)
        exit()


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


def find_function(s: str):
    regex = '\s*inline\s+(.+)'
    lines = s.splitlines()
    externs = []
    for line in lines:
        match = re.search(regex, line)
        if not match:
            continue
        extern = match.group(1)
        extern = re.sub('\w+\:\:', '', extern)
        externs.append(extern)
    return externs


def parse_function(s: str):
    reg = '([\w\s\*\&]+)\s+([\*\s\w]+)\(([\w\*\&\s\,]*)\)'
    match = re.search(reg, s)
    if match is not None:
        return_type = match.groups()[0]
        if len(return_type) == 0:
            print(fun)
            pass
        fun_name = match.groups()[1]
        name = re.search('\w+', fun_name).group()
        return_type += fun_name.replace(name, '')
        default_value = get_default_value(return_type)
        return_type = replace_type(return_type)
        fun_args = match.groups()[2]
        args = fun_args.split(',')
        args = [parse_arg(arg)
                for arg in args if len(re.sub('\s+', '', arg)) != 0]

        return ((return_type, default_value), name[2:], args)


def generate(s: str):
    # inline GLboolean QOpenGLFunctions::glIsEnabled(GLenum cap)
    externs = find_function(s)
    externs = [parse_function(extern)
               for extern in externs if 'sync' not in extern]
    #[print(extern) for extern in externs]
    return externs


def render():
    s1 = utils.read_txt(utils.join_path(res_dir, 'qt/qopenglfunctions.h'))
    externs1 = generate(s1)
    s2 = utils.read_txt(utils.join_path(res_dir, 'qt/qopenglextrafunctions.h'))
    externs2 = generate(s2)
    externs = externs1 + externs2

    s3 = utils.read_txt(utils.join_path(res_dir, 'gl/glad.h'))
    enums1 = find_enum(s3)

    s4 = utils.read_txt(utils.join_path(res_dir, 'gl/glext.h'))
    enums2 = find_enum(s4)

    enums = enums1

    enums1_keys = [k for k,v in enums1]
    for k,v in enums2:
        if k not in enums1_keys:
            enums.append((k,v))

    h_file = utils.join_path(inc_dir, 'cppgl.h')

    t_h = t_env.get_template('cppgl.h')
    utils.write_txt(h_file, t_h.render(enums=enums, funs=externs))

    cpp_file = utils.join_path(src_dir, 'cppgl.cpp')
    t_cpp = t_env.get_template('cppgl.cpp')
    utils.write_txt(cpp_file, t_cpp.render(enums=enums, funs=externs))

    #shutil.copy(h_file, inc_dir)

def add_ns(type,ns=''):
    if len(ns) == 0:
        return type

    base_type = ['void', 'bool','char','short','int','float','double']
    spans = re.findall('\w+',type)
    for span in spans:
        if span in base_type:
            #print(span)
            return type
        elif span in [v for k,v in types]:
            type = type.replace(span,'%s::%s' % (ns,span))
    return type

def render_qt():
    s1 = utils.read_txt(utils.join_path(res_dir, 'qt/qopenglfunctions.h'))
    externs1 = generate(s1)
    s2 = utils.read_txt(utils.join_path(res_dir, 'qt/qopenglextrafunctions.h'))
    externs2 = generate(s2)
    externs = []
   

    for return_type, name, args in externs1 + externs2:
        externs.append(((add_ns(return_type[0],ns='cppgl'), return_type[1]),name,[(add_ns(type,ns='cppgl'),name) for type,name in args]))
    


    h_file = utils.join_path(src_dir, 'qtgles3.h')

    t_h = t_env.get_template('qtgles3.h')
    utils.write_txt(h_file, t_h.render(funs=externs))

    cpp_file = utils.join_path(src_dir, 'qtgles3.cpp')
    t_cpp = t_env.get_template('qtgles3.cpp')
    utils.write_txt(cpp_file, t_cpp.render(funs=externs))


render()
render_qt()
