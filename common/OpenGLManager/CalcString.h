#pragma once
#include <string>

/** 计算式字符串
*/
class CalcString
{
public:
	/** 构造函数
	*/
	CalcString();

	/** 构造函数
	@param [in] str 字符串
	@param [in] index 索引值
	*/
	CalcString(const std::string& str, int32_t index = -1, int32_t subIndex = -1);

public:
	void init(const std::string& str, int32_t index = -1, int32_t subIndex = -1);

	CalcString& initDefine(const std::string& type, const std::string& name, int32_t index = -1, int32_t subIndex = -1);

	CalcString& append(const std::string& str, int32_t index = -1, int32_t subIndex = -1);

	CalcString& ands(const std::string& str, int32_t index = -1, int32_t subIndex = -1, bool emptyNoSignal = true);

	CalcString& add(const std::string& str, int32_t index = -1, int32_t subIndex = -1, bool emptyNoSignal = true);

	CalcString& minus(const std::string& str, int32_t index = -1, int32_t subIndex = -1, bool emptyNoSignal = true);

	CalcString& multi(const std::string& str, int32_t index = -1, int32_t subIndex = -1, bool emptyNoSignal = true);

	CalcString& div(const std::string& str, int32_t index = -1, int32_t subIndex = -1, bool emptyNoSignal = true);

	CalcString& function(const std::string& str);

	CalcString& parentheses();

	std::string toString();

	operator std::string();

private:
	std::string indexString(int32_t index, int32_t subIndex);

private:
	std::string m_str;
};