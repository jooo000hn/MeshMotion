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

//	std::cout << "Let's work on mesh extraction and motion!\n";
//	auto p = ASFParser::Instance();
//	p->ParseASF(gv->dataDir + gv->testASF);
//
//	
//	uni_test();


	std::string s("this subject has a submarine as a subsequence");
	std::smatch m;
	std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

	std::cout << "Target sequence: " << s << std::endl;
	std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
	std::cout << "The following matches and submatches were found:" << std::endl;

	while (std::regex_search(s, m, e)) {
		for (auto x : m) std::cout << x << " ";
		std::cout << std::endl;
		s = m.suffix().str();
	}

	system("pause");
}

void uni_test()
{
	auto ut = unit_test::Instance();
	
	if (
		ut->TestCheckKeyword() &&
		ut->TestGetKeyWordPosition())
		DEBUG("All true!", "");

}