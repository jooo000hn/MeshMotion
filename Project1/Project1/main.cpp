#include <iostream>
#include "ASFParser.h"
#include "GlobalVariables.h"

int main()
{
	auto gv = GlobalVariables::Instance();

	std::cout << "Let's work on mesh extraction and motion!\n";
	auto p = ASFParser::Instance();
	p->ParseASF(gv->dataDir + gv->testASF);

	system("pause");
}
