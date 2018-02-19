#include "ASFParser.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <stdlib.h>
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

void ASFParser::ParseSection(MeshSkeleton &skeleton, std::vector<std::string> subTokens)
{
	if (subTokens.size() == 0)
		return;

	// std::for_each(subTokens.begin(), subTokens.end(), [](std::string s) {DEBUG("current token: ", s); });

	// first one is :xxx
	auto s = subTokens[0].substr(1);
	std::unordered_map<std::string, std::string> unit;
	std::string documentation;
	std::vector<std::string> rootOrder;
	std::vector<std::string> rootAxis;
	glm::vec3 rootPosition;
	glm::vec3 rootOrientation;
	std::vector<SkeletonNode*> bonedata;
	unsigned int id = 0;
	switch (ASFParser::Str2Section(s))
	{
	case SectionName::version:
		if (!CheckSizeEqual(subTokens, 2, s))
			return;
		skeleton.SetVersion(subTokens[1]);
		break;
	case SectionName::name:
		if (!CheckSizeEqual(subTokens, 2, s))
			return;
		skeleton.SetName(subTokens[1]);
		break;
	case SectionName::units:
		if (!CheckSizeEqual(subTokens, 7, s))
			return;
		unit[subTokens[1]] = subTokens[2];
		unit[subTokens[3]] = subTokens[4];
		unit[subTokens[5]] = subTokens[6];
		skeleton.SetUnits(unit);
		break;
	case SectionName::documentation:
		if (!CheckSizeGreater(subTokens, 2, s))
			return;
		std::for_each(subTokens.begin() + 1, subTokens.end(), [&](std::string& s) {documentation.append(s); documentation.append(" "); });
		skeleton.SetDocumentation(documentation);
		break;
	case SectionName::root:
		if (!CheckSizeGreater(subTokens, 12, "root"))
			return;
		id = 2;
		// root order
		while(subTokens[id]!="axis")
		{
			rootOrder.push_back(subTokens[id++]);
		}
		id++;
		// root axis
		while(subTokens[id]!="position")
		{
			rootAxis.push_back(subTokens[id++]);
		}
		id++;
		// root position
		while(subTokens[id]!="orientation")
		{
			rootPosition = glm::vec3(
				atof(subTokens[id++].c_str()), 
				atof(subTokens[id++].c_str()), 
				atof(subTokens[id++].c_str()));
		}
		id++;
		// root orientation
		while(id < subTokens.size())
		{
			rootOrientation = glm::vec3(
				atof(subTokens[id++].c_str()),
				atof(subTokens[id++].c_str()),
				atof(subTokens[id++].c_str()));
		}

		skeleton.SetRootOrder(rootOrder);
		skeleton.SetRootAxis(rootAxis);
		skeleton.SetRootPosition(rootPosition);
		skeleton.SetRootOrientation(rootOrientation);
		break;
	case SectionName::bonedata:
		// ParseBone(bonedata, subTokens);
		skeleton.SetBonedata(bonedata);
		break;
	case SectionName::hierarchy:
		// ParseHierarchy()
		break;
	case SectionName::undefined:

		break;
	}
}

SectionName ASFParser::Str2Section(std::string s)
{
	if(s == "version")
	{
		return SectionName::version;
	}
	else if(s == "name")
	{
		return SectionName::name;
	}
	else if(s == "units")
	{
		return SectionName::units;
	}
	else if(s == "documentation")
	{
		return SectionName::documentation;
	}
	else if(s == "root")
	{
		return SectionName::root;
	}
	else if(s == "bonedata")
	{
		return SectionName::bonedata;
	}
	else if(s == "hierarchy")
	{
		return SectionName::hierarchy;
	}
	else
	{
		DEBUG("Find an undefined section!", "");
		return SectionName::undefined;
	}
}

BoneName ASFParser::Str2Bone(std::string s)
{
	if (s == "lhipjoint")
	{
		return BoneName::lhipjoint;
	}
	else if (s == "lfemur")
	{
		return BoneName::lfemur;
	}
	else if (s == "ltibia")
	{
		return BoneName::ltibia;
	}
	else if (s == "lfoot")
	{
		return BoneName::lfoot;
	}
	else if (s == "ltoes")
	{
		return BoneName::ltoes;
	}
	else if (s == "rhipjoint")
	{
		return BoneName::rhipjoint;
	}
	else if (s == "rfemur")
	{
		return BoneName::rfemur;
	}
	else if (s == "rtibia")
	{
		return BoneName::rtibia;
	}
	else if (s == "rfoot")
	{
		return BoneName::rfoot;
	}
	else if (s == "rtoes")
	{
		return BoneName::rtoes;
	}
	else if (s == "lowerback")
	{
		return BoneName::lowerback;
	}
	else if (s == "upperback")
	{
		return BoneName::upperback;
	}
	else if (s == "thorax")
	{
		return BoneName::thorax;
	}
	else if (s == "lowerneck")
	{
		return BoneName::lowerneck;
	}
	else if (s == "upperneck")
	{
		return BoneName::upperneck;
	}
	else if (s == "head")
	{
		return BoneName::head;
	}
	else if (s == "lclavicle")
	{
		return BoneName::lclavicle;
	}
	else if (s == "lhumerus")
	{
		return BoneName::lhumerus;
	}
	else if (s == "lradius")
	{
		return BoneName::lradius;
	}
	else if (s == "lwrist")
	{
		return BoneName::lwrist;
	}
	else if (s == "lhand")
	{
		return BoneName::lhand;
	}
	else if (s == "lfingers")
	{
		return BoneName::lfingers;
	}
	else if (s == "lthumnb")
	{
		return BoneName::lthumnb;
	}
	else if (s == "rclavicle")
	{
		return BoneName::rclavicle;
	}
	else if (s == "rhumerus")
	{
		return BoneName::rhumerus;
	}
	else if (s == "rradius")
	{
		return BoneName::rradius;
	}
	else if (s == "rwrist")
	{
		return BoneName::rwrist;
	}
	else if (s == "rhand")
	{
		return BoneName::rhand;
	}
	else if (s == "rfingers")
	{
		return BoneName::rfingers;
	}
	else if (s == "rthumb")
	{
		return BoneName::rthumb;
	}
	else
	{
		DEBUG("Find an undefined section!", "");
		return BoneName::undefined;
	}  
}

bool ASFParser::CheckSizeEqual(std::vector<std::string>& subTokens, unsigned size, std::string errorName)
{
	if(subTokens.size() != size)
	{
		DEBUG(errorName, "token size error!");
		return false;
	}
	else
	{
		return true;
	}
}

bool ASFParser::CheckSizeGreater(std::vector<std::string>& subTokens, unsigned size, std::string errorName)
{
	if (subTokens.size() < size)
	{
		DEBUG(errorName, "token size error!");
		return false;
	}
	else
	{
		return true;
	}
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

	// read the skeleton information
	
	for (unsigned i = 0; i < positions.size(); ++i)
	{
		unsigned pos = positions[i];
		DEBUG("Find yo ~~~", tokens[pos]);
		// process one 
		if (i != positions.size() - 1)
		{
			ParseSection(skeleton, std::vector<std::string>(tokens.begin() + pos, tokens.begin() + positions[i + 1]));
		}
		else // deal with the last one
		{
			ParseSection(skeleton, std::vector<std::string>(tokens.begin() + pos, tokens.end()));
		}
	};

	return skeleton;
}

