#pragma once
#include<vector>
#include"ParserHelper.h"
#include "Tool.h"

class unit_test
{
public:
	static unit_test* Instance() { if (_instance == nullptr) _instance = new unit_test(); return _instance; }

	bool test_checkKeyword()
	{
		// check key word
		std::string s = "AAAA";
		std::string t = "B";

		std::string funcName = __func__;
		bool isT = checkKeyword(s, t);
		DEBUG(funcName, isT);
		return	isT;
	}

private:
	unit_test();
	~unit_test();

	static unit_test* _instance;
};

