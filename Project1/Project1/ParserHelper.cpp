#include "ParserHelper.h"
#include <algorithm>
#include "Tool.h"

bool checkKeyword(std::string s, std::string target)
{
	std::transform(s.begin(), s.end(),s.begin(), ::tolower);
	std::transform(target.begin(), target.end(), target.begin(), ::tolower);

	std::regex e(target);

	return std::regex_search(s,e);
}
