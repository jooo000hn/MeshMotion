#pragma once
#include <vector>
#include <string>
#include "MeshSkeleton.h"

enum class SectionName
{
	version,
	name,
	units,
	documentation,
	root,
	bonedata
};

enum class BoneName
{
	lhipjoint,     // left hip joint
	lfemur,
	ltibia,
	lfoot,
	ltoes,
	rhipjoint,
	rfemur,
	rtibia,
	rfoot,
	rtoes,
	lowerback,
	upperback,
	thorax,
	lowerneck,
	upperneck,
	head, 
	lclavicle,
	lhumerus,
	lradius,
	lwrist,
	lhand,
	lfingers,
	lthumnb,
	rclavicle,
	rhumerus,
	rradius,
	rwrist,
	rhand,
	rfingers,
	rthumb,
};

// ASF is the format of skeleton
class ASFParser
{
public:
	static ASFParser* Instance() { if (_instance == nullptr) _instance = new ASFParser();  return _instance; }

	MeshSkeleton ParseASF(std::string file);
private:
	ASFParser();
	~ASFParser();
	std::vector<std::string> GetTokens(std::string f);
	void ParseEachNode(SkeletonNode *n, std::vector<std::string> subTokens);
	ASFParser& operator=(ASFParser const&) const { return *_instance; };
	static ASFParser* _instance;
};

