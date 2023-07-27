import utils
import math
import re
import os
import shutil

home = utils.get_dir(__file__,2)
src_home = utils.join_path(home,'src')



def filter_header_file(header_file):
    regexs = [
        'renderers[\\\/]+gl',
        'renderers[\\\/]+shaders'
    ]
    for regex in regexs:
        match = re.search(regex, header_file)
        if match:
            return True
    # if regex in regexs:
    #     match = re.search(regex,header_file)
    #     if match:
    #         print(header_file)

def generate_lib_include(name, src):
    src = utils.join_path(os.path.abspath(src))
    header_files = []
    for root, dirs, files in os.walk(src):
        for file in files:
            suffix = os.path.splitext(file)[1]
            header_file_src = utils.join_path(root, file)
            if suffix in ['.inl', '.h']:
                header_files.append(header_file_src)

    export_header_files = []

    for header_file_src in header_files:
        if filter_header_file(header_file_src):
            continue  
        export_header_files.append(header_file_src)

    total_include_file = utils.join_path(src ,name + '.h')
    total_include_lines = []
    for header_file_src in export_header_files:
        if os.path.basename(header_file_src) == name + '.h':
            continue
        if os.path.splitext(header_file_src)[1] == '.inl':
            continue
        header_line = header_file_src.replace(src,'.')
        total_include_lines.append('#include "%s"' % header_line)
    total_include_lines.sort()
    with open(total_include_file, 'wb') as fd:
        fd.write('\n'.join(total_include_lines).encode())
        print('ok')

def install_include(name, src, dst):
    src = utils.join_path(os.path.abspath(src))
    dst = utils.join_path(os.path.abspath(dst))
    header_files = []
    for root, dirs, files in os.walk(src):
        for file in files:
            suffix = os.path.splitext(file)[1]
            header_file_src = utils.join_path(root, file)
            header_file_dst = header_file_src.replace(src, dst)
            if suffix in ['.inl', '.h']:
                header_files.append((header_file_src, header_file_dst))

    export_header_files = []

    for header_file_src, header_file_dst in header_files:
        if filter_header_file(header_file_src):
            continue  
        export_header_files.append((header_file_src, header_file_dst))

    for header_file_src, header_file_dst in export_header_files:
        dir = os.path.dirname(header_file_dst)
        if not os.path.exists(dir):
            os.makedirs(dir)
        shutil.copy(header_file_src, header_file_dst)

    # total_include_file = utils.join_path(dst,name + '.h')
    # total_include_lines = []
    # for header_file_src, header_file_dst in export_header_files:
    #     if os.path.basename(header_file_src) == name + '.h':
    #         continue
    #     if os.path.splitext(header_file_src)[1] == '.inl':
    #         continue
    #     header_line = header_file_src.replace(src,'.')
    #     print(header_line)
    #     total_include_lines.append('#include "%s"' % header_line)
    # total_include_lines.sort()
    # #print(total_include_file)
    # with open(total_include_file, 'wb') as fd:
    #     fd.write('\n'.join(total_include_lines).encode())


def install_lib(src, dst):
    src = utils.join_path(os.path.abspath(src))
    dst = utils.join_path(os.path.abspath(dst))
    print(src)
    lib_files = []
    for root, dirs, files in os.walk(src):
        for file in files:   
            suffix = os.path.splitext(file)[1]
            lib_file_src = utils.join_path(root, file)
            lib_file_dst = utils.join_path(dst, os.path.basename(lib_file_src))
            if suffix in ['.so', '.a', '.lib']:
                lib_files.append((lib_file_src, lib_file_dst))

    export_lib_files = []
    print(export_lib_files)

    for lib_file_src, lib_file_dst in lib_files:
        export_lib_files.append((lib_file_src, lib_file_dst))

    for lib_file_src, lib_file_dst in export_lib_files:
        print(lib_file_dst)
        dir = os.path.dirname(lib_file_dst)
        if not os.path.exists(dir):
            os.makedirs(dir)
        shutil.copy(lib_file_src, lib_file_dst)



generate_lib_include('three', src_home)
install_include('three',src_home, utils.join_path(home,'install/include'))
install_lib(utils.join_path(home,'build'),utils.join_path(home,'install/lib'))

cmds = '''
cd ./install
conan new three/1.0.0 -b
conan export-pkg -f conanfile.py
cd ..
'''
os.system(cmds)
