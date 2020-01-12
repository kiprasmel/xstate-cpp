#pragma once

#include <vector>
#include <string>

std::vector<std::string> splitStr(std::string str = "", const char delim = ' ');
std::string joinStr(std::vector<std::string> tokens, const char delim = ' ');

std::string deepifyStr(std::string str = "", size_t depth = 1, const char deepening_str = ' ', size_t single_amount = 2);
std::string deepifyRStr(std::string rstr = "", size_t depth = 1, const char delim = '\n');
