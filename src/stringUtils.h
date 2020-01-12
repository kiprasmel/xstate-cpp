#pragma once

#include <vector>
#include <string>

std::vector<std::string> splitStr(std::string str = "", const char delim = ' ');
std::string joinStr(std::vector<std::string> tokens, const char delim = ' ');
