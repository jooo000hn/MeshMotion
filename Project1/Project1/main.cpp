#include <iostream>
#include "ASFParser.h"
#include "GlobalVariables.h"
#include "unit_test.h"
#include "Tool.h"

// for unit test
void uni_test();

int main()
{
	auto gv = GlobalVariables::Instance();

	std::cout << "Let's work on mesh extraction and motion!\n";
	auto p = ASFParser::Instance();
	p->ParseASF(gv->dataDir + gv->testASF);

	
	uni_test();

	system("pause");
}

void uni_test()
{
	auto ut = unit_test::Instance();
	
	ut->test_checkKeyword();
}