import os
import shutil

home = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

print('home:',home)

def run():
	inc_str = ''
	src_str = ''

	target = os.path.join(home, 'src')
	print('target:',target)
	for root, dirs, files in os.walk(target):

		for dir in dirs:
			dir = os.path.join(root, dir).replace(target, '')
			dir = dir.replace('\\', '/')
			inc_str += 'file(GLOB PROJECT_HEADERS "${PROJECT_SOURCE_DIR}/src%s/*.h")\n' % dir
			src_str += 'aux_source_directory(${PROJECT_SOURCE_DIR}/src%s PROJECT_SOURCES)\n' % dir

	print(inc_str + src_str)


def make_include():
	target = os.path.join(home, 'third/cppgl/src')
	include_dir = os.path.join(home, 'inc/cppgl')

	for root, dirs, files in os.walk(target):
		for file in files:
			if os.path.splitext(file)[1] in ['.h']:
				file_path = os.path.join(root, file).replace(target, include_dir)
				print(file_path)

				file_dir = os.path.dirname(file_path)
				if not os.path.exists(file_dir):
					os.makedirs(file_dir)
				shutil.copy(os.path.join(root, file), file_path)


