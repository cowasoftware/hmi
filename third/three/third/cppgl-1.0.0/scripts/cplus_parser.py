'''
T 

T * 

T * const 

T const* 
const T * 


T const* const 
const T *  const 



T & t

T const& 
const T & 
'''

import math
import re
from turtle import st

class Type:
	def __init__(self,name = '', style = '', const = False, read = False) -> None:
		self.name = name
		self.style = style
		self.const = const
		self.read = read
	
	
def parse_type(s: str):
	match = None

	match = re.search('\s*(\w+)\s*',s)

	if match:
		return Type(match.group(1))
	
	match = re.search('\s*(\w+)\s*[\*]+\s*', s) 
	
	if match:
		return Type(match.group())
	





