#pragma once
#include <string>

class GlobalVariables
{
public:
	static GlobalVariables* Instance() { if (_instance == nullptr) _instance = new GlobalVariables(); return _instance; }
	
	// global variables
	std::string dataDir;
	std::string testASF;
	std::string testAMC;

private:
	GlobalVariables();
	~GlobalVariables() {};
	GlobalVariables& operator=(GlobalVariables const&) const { return *_instance; };
	static GlobalVariables* _instance;
};

