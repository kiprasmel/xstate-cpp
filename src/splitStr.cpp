#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> splitStr(std::string str = "", const char delim = ' ') {
    std::string buf;                 // Have a buffer string
    std::stringstream ss(str);       // Insert the string into a stream

    std::vector<std::string> tokens; // Create vector to hold our words

    while (getline(ss, buf, delim)) {
        tokens.push_back(buf);
	}

	return tokens;
}
