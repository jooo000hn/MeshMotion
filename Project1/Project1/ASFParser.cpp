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

void ASFParser::ParseSection(MeshSkeleton& skeleton, std::vector<std::string> subTokens)
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
	switch (Str2Section(s))
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
		std::for_each(subTokens.begin() + 1, subTokens.end(), [&](std::string& s)
		{
			documentation.append(s);
			documentation.append(" ");
		});
		skeleton.SetDocumentation(documentation);
		break;
	case SectionName::root:
		if (!CheckSizeGreater(subTokens, 12, "root"))
			return;
		id = 2;
		// root order
		while (subTokens[id] != "axis")
		{
			rootOrder.push_back(subTokens[id++]);
		}
		id++;
		// root axis
		while (subTokens[id] != "position")
		{
			rootAxis.push_back(subTokens[id++]);
		}
		id++;
		// root position
		while (subTokens[id] != "orientation")
		{
			rootPosition = glm::vec3(
				atof(subTokens[id++].c_str()),
				atof(subTokens[id++].c_str()),
				atof(subTokens[id++].c_str()));
		}
		id++;
		// root orientation
		while (id < subTokens.size())
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
		ParseBone(bonedata, subTokens);
		skeleton.SetBonedata(bonedata);
		break;

	case SectionName::undefined:
		break;
	}
}

void ASFParser::ParseBone(std::vector<SkeletonNode*>& bonedata, std::vector<std::string> subTokens)
{
	SkeletonNode* currentNode;
	for (unsigned i = 0; i < subTokens.size(); ++i)
	{
		if (subTokens[i] == "begin")
		{
			currentNode = new SkeletonNode();
			while (subTokens[i] != "end")
			{
				int count, pair;
				switch (Str2BoneInfo(subTokens[i]))
				{
				case BoneInfo::id:
					currentNode->SetId(stoi(subTokens[++i]));
					break;
				case BoneInfo::name:
					currentNode->SetName(subTokens[++i]);
					break;
				case BoneInfo::direction:
					currentNode->SetDirection(glm::vec3(stof(subTokens[i + 1]), stof(subTokens[i + 2]), stof(subTokens[i + 3])));
					i += 3;
					break;
				case BoneInfo::length:
					currentNode->SetLength(stof(subTokens[++i]));
					break;
				case BoneInfo::axis:
					currentNode->SetAxis(std::vector<std::string>{subTokens[++i], subTokens[++i], subTokens[++i], subTokens[++i]});
					break;
				case BoneInfo::dof:
					count = 1;
					while (subTokens[i + count] != "limits")
					{
						count++;
					}
					for (int j = 0; j < count - 1; j++)
					{
						currentNode->AddDof(subTokens[i + j + 1]);
					}
					i += count - 1;
					break;
				case BoneInfo::limits:
					count = 1;
					while (subTokens[i + count] != "end")
					{
						count++;
					}
					pair = (count - 1) / 2; // (,xxx,xxx,)
					for (int j = 0; j < pair; j++)
					{
						int index = i + j * 2 + 1;
						subTokens[index] = subTokens[index].substr(subTokens[index].find('(') + 1);
						subTokens[index + 1] = subTokens[index + 1].substr(0, subTokens[index + 1].find(')'));
						currentNode->AddLimits(glm::vec2(stof(subTokens[index]), stof(subTokens[index + 1])));
					}
					i += count - 1;
					break;
				case BoneInfo::undefined:
					break;
				}
				i++;
			}
			bonedata.push_back(currentNode);
		}
	}
}

void ASFParser::ParseHierarchy(std::vector<SkeletonNode*>& bonedata, std::vector<std::vector<std::string>> subTokens)
{
	if (subTokens.size() <= 2)
		return;

	unsigned int i = 0;
	while (subTokens[i++][0] != "begin");

	// Add a root to bonedata
	SkeletonNode* root = new SkeletonNode();
	root->SetName("root");
	bonedata.push_back(root);

	// Initialize a tmp map to quickly access the skeleton node
	std::unordered_map<std::string, SkeletonNode*> name2bonedata;
	std::for_each(bonedata.begin(), bonedata.end(), [&](SkeletonNode* n)
	{
		name2bonedata[n->Name()] = n;
	});


	while (i < subTokens.size()-1)
	{
		// parse a row, which is a hiarchy
		auto rootName = subTokens[i][0];

		SkeletonNode* rootNode = nullptr;
		rootNode = name2bonedata.at(rootName);

		for (auto iter = subTokens[i].begin() + 1; iter != subTokens[i].end(); ++iter)
		{
			auto node = name2bonedata.at(*iter);
			if (node != nullptr)
			{
				rootNode->AddChildren(node);
				node->SetParent(rootNode);
			}
		}

		i++;
	}
}

SectionName ASFParser::Str2Section(std::string s)
{
	if (s == "version")
	{
		return SectionName::version;
	}
	if (s == "name")
	{
		return SectionName::name;
	}
	if (s == "units")
	{
		return SectionName::units;
	}
	if (s == "documentation")
	{
		return SectionName::documentation;
	}
	if (s == "root")
	{
		return SectionName::root;
	}
	if (s == "bonedata")
	{
		return SectionName::bonedata;
	}
	if (s == "hierarchy")
	{
		return SectionName::hierarchy;
	}
	DEBUG("Find an undefined section!", "");
	return SectionName::undefined;
}

BoneInfo ASFParser::Str2BoneInfo(std::string s)
{
	if (s == "id")
	{
		return BoneInfo::id;
	}
	if (s == "name")
	{
		return BoneInfo::name;
	}
	if (s == "direction")
	{
		return BoneInfo::direction;
	}
	if (s == "length")
	{
		return BoneInfo::length;
	}
	if (s == "axis")
	{
		return BoneInfo::axis;
	}
	if (s == "dof")
	{
		return BoneInfo::dof;
	}
	if (s == "limits")
	{
		return BoneInfo::limits;
	}
	if (s == "begin")
	{
		return BoneInfo::begin;
	}
	if (s == "end")
	{
		return BoneInfo::end;
	}
	DEBUG("Find an undefined bone information!", "");
	return BoneInfo::undefined;
}

BoneName ASFParser::Str2BoneName(std::string s)
{
	if (s == "lhipjoint")
	{
		return BoneName::lhipjoint;
	}
	if (s == "lfemur")
	{
		return BoneName::lfemur;
	}
	if (s == "ltibia")
	{
		return BoneName::ltibia;
	}
	if (s == "lfoot")
	{
		return BoneName::lfoot;
	}
	if (s == "ltoes")
	{
		return BoneName::ltoes;
	}
	if (s == "rhipjoint")
	{
		return BoneName::rhipjoint;
	}
	if (s == "rfemur")
	{
		return BoneName::rfemur;
	}
	if (s == "rtibia")
	{
		return BoneName::rtibia;
	}
	if (s == "rfoot")
	{
		return BoneName::rfoot;
	}
	if (s == "rtoes")
	{
		return BoneName::rtoes;
	}
	if (s == "lowerback")
	{
		return BoneName::lowerback;
	}
	if (s == "upperback")
	{
		return BoneName::upperback;
	}
	if (s == "thorax")
	{
		return BoneName::thorax;
	}
	if (s == "lowerneck")
	{
		return BoneName::lowerneck;
	}
	if (s == "upperneck")
	{
		return BoneName::upperneck;
	}
	if (s == "head")
	{
		return BoneName::head;
	}
	if (s == "lclavicle")
	{
		return BoneName::lclavicle;
	}
	if (s == "lhumerus")
	{
		return BoneName::lhumerus;
	}
	if (s == "lradius")
	{
		return BoneName::lradius;
	}
	else
	{
		if (s == "lwrist")
		{
			return BoneName::lwrist;
		}
		if (s == "lhand")
		{
			return BoneName::lhand;
		}
		if (s == "lfingers")
		{
			return BoneName::lfingers;
		}
		else
		{
			if (s == "lthumnb")
			{
				return BoneName::lthumnb;
			}
			if (s == "rclavicle")
			{
				return BoneName::rclavicle;
			}
			else
			{
				if (s == "rhumerus")
				{
					return BoneName::rhumerus;
				}
				if (s == "rradius")
				{
					return BoneName::rradius;
				}
				if (s == "rwrist")
				{
					return BoneName::rwrist;
				}
				if (s == "rhand")
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
					DEBUG("Find an undefined bone name!", "");
					return BoneName::undefined;
				}
			}
		}
	}
}

bool ASFParser::CheckSizeEqual(std::vector<std::string>& subTokens, unsigned size, std::string errorName)
{
	if (subTokens.size() != size)
	{
		DEBUG(errorName, "token size error!");
		return false;
	}
	return true;
}

bool ASFParser::CheckSizeGreater(std::vector<std::string>& subTokens, unsigned size, std::string errorName)
{
	if (subTokens.size() < size)
	{
		DEBUG(errorName, "token size error!");
		return false;
	}
	return true;
}

MeshSkeleton ASFParser::ParseASF(std::string file)
{
	MeshSkeleton skeleton;
	DEBUG("We try to parse ", file);

	// Initialize tokens
	auto tokens = GetTokens(file);
	auto rowTokens = GetTokensByLine(file);
	std::vector<int> positions;
	int p = 0;
	std::for_each(tokens.begin(), tokens.end(), [&](std::string s)
	{
		if (s.find(":") != std::string::npos)
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
		else // deal with hiearchy
		{
			unsigned int row = 0;
			while (rowTokens[row++][0] != ":hierarchy");
			std::vector<SkeletonNode*> bonedata = skeleton.Bonedata();
			// parse in the hierarchy information
			ParseHierarchy(bonedata, std::vector<std::vector<std::string>>(rowTokens.begin() + row, rowTokens.end()));
			skeleton.SetBonedata(bonedata);
		}
	}

	return skeleton;
}

