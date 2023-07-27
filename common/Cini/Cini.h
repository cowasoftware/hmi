#pragma once
#include <string>
#include <vector>
#include <stdint.h>
#include "CiniMacro.h"

class Cini
{
public:
	Cini(const std::string& iniPath, bool useSimpleIni = false);

	~Cini();

public:
	void setMaxLength(int32_t length);

	void setMaxSection(int32_t sectionNum);

	std::string readIni(const std::string& key, const std::string& section = "Section") const;

	void writeIni(const std::string& key, const std::string& value, const std::string& section = "Section") const;

	std::vector<std::string> getAllSection() const;

	std::vector<std::string> getAllKey(const std::string& section = "Section") const;

	std::string getFirstKey(const std::string& section = "Section") const;

	void deleteKey(const std::string& key, const std::string& section = "Section") const;

	void deleteSection(const std::string& section = "Section") const;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	std::string m_iniPath;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	int32_t m_length;
	int32_t m_sectionNum;
	bool m_useSimpleIni;
	void* m_simpleIni;
	bool m_loadSuccess;
};