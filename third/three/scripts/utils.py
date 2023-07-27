import os
import re


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