#include "CalcString.h"

CalcString::CalcString()
{

}

CalcString::CalcString(const std::string& str, int32_t index, int32_t subIndex)
{
	m_str = str + indexString(index, subIndex);
}

void CalcString::init(const std::string& str, int32_t index, int32_t subIndex)
{
	m_str = str + indexString(index, subIndex);
}

CalcString& CalcString::initDefine(const std::string& type, const std::string& name, int32_t index, int32_t subIndex)
{
	m_str = type + " " + name + indexString(index, subIndex) + " = ";
	return *this;
}

CalcString& CalcString::append(const std::string& str, int32_t index, int32_t subIndex)
{
	m_str += (str + indexString(index, subIndex));
	return *this;
}

CalcString& CalcString::ands(const std::string& str, int32_t index, int32_t subIndex, bool emptyNoSignal)
{
	if (emptyNoSignal && str.empty())
	{
		return *this;
	}
	if (emptyNoSignal && !m_str.empty())
	{
		m_str.append(", ");
	}
	m_str += (str + indexString(index, subIndex));
	return *this;
}

CalcString& CalcString::add(const std::string& str, int32_t index, int32_t subIndex, bool emptyNoSignal)
{
	if (emptyNoSignal && str.empty())
	{
		return *this;
	}
	if (emptyNoSignal && !m_str.empty())
	{
		m_str.append(" + ");
	}
	m_str += (str + indexString(index, subIndex));
	return *this;
}

CalcString& CalcString::minus(const std::string& str, int32_t index, int32_t subIndex, bool emptyNoSignal)
{
	if (emptyNoSignal && str.empty())
	{
		return *this;
	}
	if (emptyNoSignal && !m_str.empty())
	{
		m_str.append(" - ");
	}
	m_str += (str + indexString(index, subIndex));
	return *this;
}

CalcString& CalcString::multi(const std::string& str, int32_t index, int32_t subIndex, bool emptyNoSignal)
{
	if (emptyNoSignal && str.empty())
	{
		return *this;
	}
	if (emptyNoSignal && !m_str.empty())
	{
		m_str.append(" * ");
	}
	m_str += (str + indexString(index, subIndex));
	return *this;
}

CalcString& CalcString::div(const std::string& str, int32_t index, int32_t subIndex, bool emptyNoSignal)
{
	if (emptyNoSignal && str.empty())
	{
		return *this;
	}
	if (emptyNoSignal && !m_str.empty())
	{
		m_str.append(" / ");
	}
	m_str += (str + indexString(index, subIndex));
	return *this;
}

CalcString& CalcString::function(const std::string& str)
{
	m_str = str + m_str;
	return *this;
}

CalcString& CalcString::parentheses()
{
	if (!m_str.empty())
	{
		m_str = "(" + m_str + ")";
	}
	return *this;
}

std::string CalcString::toString()
{
	return m_str;
}

CalcString::operator std::string()
{
	return m_str;
}

std::string CalcString::indexString(int32_t index, int32_t subIndex)
{
	return index != -1 ? "_" + std::to_string(index) + (subIndex != -1 ? "_" + std::to_string(subIndex) : "") : "";
}