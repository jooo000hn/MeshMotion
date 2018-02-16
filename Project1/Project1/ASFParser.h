#pragma once
#include <vector>
#include <string>
#include "MeshSkeleton.h"

// ASF is the format of skeleton
class ASFParser
{
public:
	static ASFParser* Instance() { if (_instance == nullptr) _instance = new ASFParser();  return _instance; }

	MeshSkeleton ParseASF(std::string file);
private:
	ASFParser();
	~ASFParser();
	ASFParser& operator=(ASFParser const&) const { return *_instance; };
	static ASFParser* _instance;
};

