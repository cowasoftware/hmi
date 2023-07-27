from tokenize import group
import jinja2
import os
import re
import utils
import json

from jinja2 import Template
from jinja2.loaders import FileSystemLoader
from jinja2 import Environment
import os
import utils


home = utils.get_dir(__file__, 2)
src_home = utils.join_path(home, 'src')
t_home = utils.join_path(home, 'scripts/res/template')
t_env = Environment(loader=FileSystemLoader(t_home))


shader_chunk_src_dir = utils.join_path(home, 'src', 'renderers', 'shaders')
shader_lib_src_dir = utils.join_path(home, 'src', 'renderers', 'shaders')
shader_chunk_glsl_dir = utils.join_path(home, 'scripts/res', 'glsl', 'shader_chunk')
shader_lib_glsl_dir = utils.join_path(home, 'scripts/res', 'glsl', 'shader_lib')


def get_name(file: str):
    name = os.path.basename(file)
    name = os.path.splitext(name)[0]
    return name


def get_shader_lib_name(file):
    name = get_name(file)
    name, group = os.path.splitext(name)
    return name, group[1:]


def to_class_name(name: str):
    return ''.join([item.capitalize() for item in name.split('_')])


def filter_line(str):
    if len(str) == 0:
        return True
    elif re.match('[\t ]*//', str):
        return True


def prehandle(str):
    return str.replace('"', '\\"')


def generate_shader_chunk(files, dst, test=True):
    class_name = 'ShaderChunk'
    class_h_name = 'shader_chunk'
    class_cpp_name = 'shader_chunk'
    class_h_file = utils.join_path(dst, class_h_name + '.h')
    class_cpp_file = utils.join_path(dst, class_cpp_name + '.cpp')
    class_h_template = t_env.get_template('shader_chunk.h')
    class_cpp_template = t_env.get_template('shader_chunk.cpp')

    class_h_params = {
        'class_name': class_name
    }

    class_cpp_params = {
        'test': test,
        'class_name': class_name,
        'class_h_name': class_h_name,
        'shader_chunk_blocks': {},
        'shader_chunk_files': {}
    }
    for file in files:
        shader_chunk_file = file
        shader_chunk_name = get_name(file)
        shader_chunk_lines = []

        if not test:
            with open(shader_chunk_file, 'r', encoding='utf-8') as fd:
                shader_chunk_lines = [line for line in fd.read().split(
                    '\n') if not filter_line(line)]
                shader_chunk_lines = [prehandle(line)
                                      for line in shader_chunk_lines]

        class_cpp_params['shader_chunk_blocks'][shader_chunk_name] = shader_chunk_lines
        class_cpp_params['shader_chunk_files'][shader_chunk_name] = file

    utils.makedirs(class_h_file)
    utils.makedirs(class_cpp_file)

    with open(class_h_file, 'w') as fd:
        # print(class_h_file)
        fd.write(class_h_template.render(**class_h_params))

    with open(class_cpp_file, 'w') as fd:
        # print(class_cpp_file)
        fd.write(class_cpp_template.render(**class_cpp_params))


def generate_shader_lib(files, dst, test=True):
    order = ['vertex', 'fragment']
    class_name = 'ShaderLib'
    class_h_name = 'shader_lib'
    class_cpp_name = 'shader_lib'
    class_h_file = utils.join_path(dst, class_h_name + '.h')
    class_cpp_file = utils.join_path(dst, class_cpp_name + '.cpp')
    class_h_template = t_env.get_template('shader_lib.h')
    class_cpp_template = t_env.get_template('shader_lib.cpp')

    class_h_params = {
        'class_name': class_name,
        'shader_lib_ids': [],
    }

    class_cpp_params = {
        'test': test,
        'class_name': class_name,
        'class_h_name': class_h_name,
        'shader_lib_ids': [],
        'shader_lib_files': {},
        'shader_lib_blocks': {}

    }
    for file in files:
        shader_lib_name, shader_lib_type = get_shader_lib_name(file)
        shader_lib_id = shader_lib_name.upper()
        if shader_lib_id not in class_cpp_params['shader_lib_ids']:
            class_cpp_params['shader_lib_ids'].append(shader_lib_id)
            class_h_params['shader_lib_ids'].append(shader_lib_id)
        shader_lib_file = file
        shader_lib_lines = []

        if not test:
            with open(shader_lib_file, 'r', encoding='utf-8') as fd:
                shader_lib_lines = [line for line in fd.read().split(
                    '\n') if not filter_line(line)]

        if shader_lib_id not in class_cpp_params['shader_lib_blocks']:
            class_cpp_params['shader_lib_blocks'][shader_lib_id] = []

        if shader_lib_id not in class_cpp_params['shader_lib_files']:
            class_cpp_params['shader_lib_files'][shader_lib_id] = []

        class_cpp_params['shader_lib_blocks'][shader_lib_id].append(
            (shader_lib_type, shader_lib_name, shader_lib_lines))
        class_cpp_params['shader_lib_files'][shader_lib_id].append(
            (shader_lib_type, shader_lib_name, shader_lib_file))
        #print(shader_lib_name, shader_lib_lines)

    class_cpp_params['shader_lib_blocks'] = {k: v for k, v in sorted(
        class_cpp_params['shader_lib_blocks'].items(), key=lambda item: item[0])}
    class_cpp_params['shader_lib_files'] = {k: v for k, v in sorted(
        class_cpp_params['shader_lib_files'].items(), key=lambda item: item[0])}

    for k, v in class_cpp_params['shader_lib_blocks'].items():
        v = sorted(v, key=lambda item: order.index(item[0]))
        class_cpp_params['shader_lib_blocks'][k] = v

    for k, v in class_cpp_params['shader_lib_files'].items():
        v = sorted(v, key=lambda item: order.index(item[0]))
        class_cpp_params['shader_lib_files'][k] = v

    class_cpp_params['shader_lib_ids'].sort()

    utils.makedirs(class_h_file)
    utils.makedirs(class_cpp_file)

    print(json.dumps(class_cpp_params, indent=4))
    with open(class_h_file, 'w') as fd:
        # print(class_h_file)
        fd.write(class_h_template.render(**class_h_params))

    with open(class_cpp_file, 'w') as fd:
        # print(class_cpp_file)
        fd.write(class_cpp_template.render(**class_cpp_params))


def generate_all(test=True):
    shader_chunk_files = [utils.join_path(
        shader_chunk_glsl_dir, name) for name in os.listdir(shader_chunk_glsl_dir)]
    generate_shader_chunk(shader_chunk_files, shader_chunk_src_dir, test=test)

    shader_lib_files = [utils.join_path(
        shader_lib_glsl_dir, name) for name in os.listdir(shader_lib_glsl_dir)]
    generate_shader_lib(shader_lib_files, shader_lib_src_dir, test=test)


generate_all(test=False)
