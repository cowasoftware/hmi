import re


text = '''
#define name value \

'''


def prereplace(s: str):
	s = s.replace('  ', '\\s+')
	s = s.replace(' ', '\\s*')
	return s


def parse_define(s: str):
	reg = ' #define  (\w+)  (\w+)'
	reg = prereplace(reg)
	print(reg)
	ret = re.findall(reg, s)
	print(ret)

parse_define(text)