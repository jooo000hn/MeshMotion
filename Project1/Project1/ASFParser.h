#pragma once
#include <vector>
#include <string>
#include "MeshSkeleton.h"
#include "IParseTool.h"

enum class SectionName
{
	version,
	name,
	units,
	documentation,
	root,
	bonedata,
	hierarchy,
	undefined
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
	undefined
};

enum class BoneInfo
{
	id,
	name, // bone name
	direction,
	length,
	axis,
	dof,
	limits,
	undefined,
	begin,
	end
};

// ASF is the format of skeleton
class ASFParser:public IParseTool
{
public:
	static ASFParser* Instance() { if (_instance == nullptr) _instance = new ASFParser();  return _instance; }

	MeshSkeleton ParseASF(std::string file);
private:
	ASFParser();
	~ASFParser();
	static void ParseSection(MeshSkeleton& skeleton, std::vector<std::string> subTokens);
	static void ParseBone(std::vector<SkeletonNode*> &bonedata, std::vector<std::string> subTokens);
	
	static SectionName Str2Section(std::string s);
	static BoneInfo Str2BoneInfo(std::string s);
	static BoneName Str2BoneName(std::string s);
	static bool CheckSizeEqual(std::vector<std::string> &subTokens, unsigned size, std::string errorName);
	static bool CheckSizeGreater(std::vector<std::string> &subTokens, unsigned size, std::string errorName);
	// singleton style
	ASFParser& operator=(ASFParser const&) const { return *_instance; };
	static ASFParser* _instance;
};

