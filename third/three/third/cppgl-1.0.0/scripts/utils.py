from email import utils
import os
import re
import json


def join_path(*args):
    return os.path.join(*args).replace('\\', '/')


def get_dir(file, level=1, abs=True):
    ret = file if not abs else os.path.abspath(file)
    for i in range(0, level):
        ret = os.path.dirname(ret)
    return ret


def makedirs(file):
    dir = get_dir(file)
    if not os.path.exists(dir):
        os.makedirs(dir)


def read_txt(file, encoding='utf-8'):
    with open(file, 'r', encoding=encoding) as fd:
        return fd.read()

def write_txt(file,text,encoding='utf-8'):
    with open(file, 'w', encoding=encoding) as fd:
        fd.write(text)

def read_json(file, encoding='utf-8'):
    with open(file, 'r', encoding=encoding) as fd:
        return json.load(fd)



