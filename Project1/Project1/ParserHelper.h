#pragma once
#include <regex>
#include <string>

// Is target in string s, ignore Upper and down
bool CheckKeyWord(std::string s, std::string target);
std::vector<unsigned int> GetKeyWordPositions(std::string& s, std::string& target);