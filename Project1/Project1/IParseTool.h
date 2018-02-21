#pragma once
#include <string>
#include <vector>

class IParseTool
{
public:
	IParseTool();
	~IParseTool();

	std::vector<std::string> GetTokens(std::string f);
	std::vector<std::string> GetTokensByStr(std::string s);
	std::vector<std::vector<std::string>> GetTokensByLine(std::string f);
};

