import jinja2


header_template = '''
class ${1}
{
public:
	${1}();
	${1}(const ${1}&);
	${1}(${1}&&);
	virtual ~${1}();

public:
	${1}& operator=(const ${1}&);
	${1}& operator=(${1}&&);

private:

};
'''

source_template = '''
${1}::${1}()
{

}

${1}::${1}(const ${1}& obj)
{

}

${1}::${1}(${1}&&)
{

}

${1}::~${1}()
{

}


${1}& ${1}::operator=(const ${1}& rhs)
{
	return *this;
}

${1}& ${1}::operator=(${1}&& rhs)
{
	return *this;
}
'''
def make(template):
	result = ''
	lines = template.split('\n')
	for line in lines:
		if (lines.index(line) == 0 or lines.index(line) == (len(lines)-1)) and len(line) == 0:
			continue
		
		result += '"%s"%s\n' % (line, ',' if lines.index(line) != (len(lines)-2) else '')

	return result

print(make(source_template))

