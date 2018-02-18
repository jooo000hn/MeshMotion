#include "ASFParser.h"
#include <iostream>
#include <fstream>
#include <stack>
#include "Tool.h"
#include "GlobalVariables.h"
#include "ParserHelper.h"

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

void ASFParser::ParseEachNode(SkeletonNode* n, std::vector<std::string> subTokens)
{
	if (subTokens.size() == 0)
		return;


}

MeshSkeleton ASFParser::ParseASF(std::string file)
{
	MeshSkeleton skeleton;
	DEBUG("We try to parse ", file);

	// Initialize tokens
	auto tokens = GetTokens(file);
	std::vector<int> positions;
	int p = 0;
	std::for_each(tokens.begin(), tokens.end(),[&](std::string s)
	{
		if (s.find(":")!=std::string::npos)
		{
			positions.push_back(p);
		}
		p++;
	});

	// Root node
	skeleton.SetTreeRoot(new SkeletonNode());
	for (unsigned i = 0; i < positions.size(); ++i)
	{
		unsigned pos = positions[i];
		DEBUG("Find yo ~~~", tokens[pos]);
		SkeletonNode* n = new SkeletonNode();
		// process one 
		if (i != positions.size() - 1)
		{
			ParseEachNode(n, std::vector<std::string>(tokens.begin() + pos, tokens.begin() + positions[i + 1] - 1));
		}
		else // deal with the last one
		{
			ParseEachNode(n, std::vector<std::string>(tokens.begin() + pos, tokens.end()));
		}
		skeleton.TreeRoot()->AddChildrenNode(n);
	};

	return skeleton;
}

