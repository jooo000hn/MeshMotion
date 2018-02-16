#include "ASFParser.h"
#include <iostream>
#include <fstream>
#include "Tool.h"
#include "GlobalVariables.h"

ASFParser* ASFParser::_instance = nullptr;

ASFParser::ASFParser()
{
}


ASFParser::~ASFParser()
{
}

MeshSkeleton ASFParser::ParseASF(std::string file)
{
	MeshSkeleton skeleton;
	DEBUG("We try to parse ", file);

	std::ifstream ifs(file);
	std::string s;
	int row = 0;
	if (ifs.is_open())
	{
		while (ifs >> s)
		{
			DEBUG(row++, s);
		}
	}
	else
	{
		DEBUG(file, "Cannot open!");
	}

	return skeleton;
}
