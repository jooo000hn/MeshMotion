#pragma once
#include<vector>
#include"ParserHelper.h"
#include "Tool.h"

class unit_test
{
public:
	static unit_test* Instance() { if (_instance == nullptr) _instance = new unit_test(); return _instance; }

	bool TestCheckKeyword()
	{
		// check key word
		std::string s = "AAAA";
		std::string t = "B";

		std::string funcName = __func__;
		bool isT = CheckKeyWord(s, t);
		// DEBUG(funcName, isT);
		return false == isT;
	}

	bool TestGetKeyWordPosition()
	{
		std::string s = "AAaaAA";
		std::string t = "a";

		std::string funcName = __func__;
		auto ptr = GetKeyWordPositions(s, t);
		
		return s[ptr[0]] == t[0];
	}

private:
	unit_test();
	~unit_test();

	static unit_test* _instance;
};

