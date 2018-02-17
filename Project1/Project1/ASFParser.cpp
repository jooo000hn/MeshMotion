#include "ASFParser.h"
#include <iostream>
#include <fstream>
#include <stack>
#include "Tool.h"
#include "GlobalVariables.h"


ASFParser* ASFParser::_instance = nullptr;

ASFParser::ASFParser()
{
}


ASFParser::~ASFParser()
{
}

std::vector<std::string> ASFParser::GetTokens(std::string f)
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

MeshSkeleton ASFParser::ParseASF(std::string file)
{
	MeshSkeleton skeleton;
	DEBUG("We try to parse ", file);

	// Initialize tokens
	auto tokens = GetTokens(file);

	return skeleton;
}
