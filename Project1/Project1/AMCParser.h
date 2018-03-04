#pragma once
#include "MeshMotionFlow.h"
#include "IParseTool.h"

// AMC is the format of animation
class AMCParser : public IParseTool
{
public:
	static AMCParser* Instance() { if (_instance == nullptr) _instance = new AMCParser();  return _instance; }

	MeshMotionFlow ParsAMC(std::string file);
private:
	AMCParser();
	~AMCParser();

	static AMCParser* _instance;
};

