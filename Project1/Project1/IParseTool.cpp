#include "IParseTool.h"
#include "Tool.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

IParseTool::IParseTool()
{
}


IParseTool::~IParseTool()
{
}

std::vector<std::string> IParseTool::GetTokens(std::string f)
{
	std::ifstream ifs(f);
	std::string s;
	std::vector<std::string> tokens;
	int row = 0;
	if (ifs.is_open())
	{
		while (ifs >> s)
		{
			//DEBUG(row++, s);
			tokens.push_back(s);
		}
	}
	else
	{
		DEBUG(f, "Cannot open!");
	}
	return tokens;
}

std::vector<std::string> IParseTool::GetTokensByStr(std::string s)
{
	std::vector<std::string> tokens;
	std::istringstream iss(s);
	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(tokens));

	return tokens;
}

std::vector<std::vector<std::string>> IParseTool::GetTokensByLine(std::string f)
{
	std::ifstream ifs(f);
	std::string rString;  // row string
	std::vector<std::vector<std::string>> rowTokens;
	if(ifs.is_open())
	{
		while(std::getline(ifs,rString))
		{
			// rowTokens.push_back(GetTokens(rString));
			rowTokens.push_back(GetTokensByStr(rString));
		}
	}
	else
	{
		DEBUG(f, "Cannot open!");
	}
	return rowTokens;
}
