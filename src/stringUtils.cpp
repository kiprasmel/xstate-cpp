#include "stringUtils.h"

#include <vector>
#include <string>
#include <sstream>

/**
 * split a single string into an array of string tokens
 * opposite of `joinStr`
 *
 * TODO format
 */
std::vector<std::string> splitStr(std::string str, const char delim) {
    std::string buf;                 // Have a buffer string
    std::stringstream ss(str);       // Insert the string into a stream

    std::vector<std::string> tokens; // Create vector to hold our words

    while (getline(ss, buf, delim)) {
        tokens.push_back(buf);
	}

	return tokens;
}

/**
 * join an array of string tokens into a single string
 * opposite of `splitStr`
 */
std::string joinStr(std::vector<std::string> tokens, const char delim) {
	std::string str = "";

	for (size_t i = 0; i < tokens.size(); ++i) {
		const std::string& buf = tokens[i];

		str += buf;

		if (i < tokens.size() - 1) {
			str += delim;
		}
	}

	return str;
}

std::string deepifyStr(std::string str, const size_t depth, const char deepening_str, const size_t single_amount) {
	// return std::string(depth * single_amount, deepening_str) + str;
	size_t depthAmount = depth * single_amount;
	std::string prefix = std::string(depthAmount, deepening_str);
	std::string deepifiedStr = prefix + str;

	return deepifiedStr;
}

/**
 * string with newlines
 *
 * TODO rename to a better name
 * TODO allow passing all parameters to `deepifyStr` to allow customization instead of the default ones
*/
std::string deepifyRStr(std::string rstr, size_t depth, const char delim) {
	std::vector<std::string> strs = splitStr(rstr, delim);

	for (std::string& str : strs) {
		str = deepifyStr(str, depth);
	}

	std::string deepifiedStr = joinStr(strs, delim);

	return deepifiedStr;
}
