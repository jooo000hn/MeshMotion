#include "ParserHelper.h"
#include <algorithm>
#include "Tool.h"

bool CheckKeyWord(std::string s, std::string target)
{
	std::transform(s.begin(), s.end(),s.begin(), ::tolower);
	std::transform(target.begin(), target.end(), target.begin(), ::tolower);

	std::regex e(target);

	return std::regex_search(s,e);
}

std::vector<unsigned int> GetKeyWordPositions(std::string s, std::string target)
{
	std::smatch m;
	std::regex e(target);

	std::regex_search(s, m, e);

	std::vector<unsigned int> result(m.size());
	for(unsigned i = 0; i < m.size();++i)
	{
		result[i] = m.position(i);
	}
	return result;
}
