#pragma once

#include <map>

#include "StateMachine.h"

namespace xs {

struct State {
	std::map<std::string , std::string > on;
	StateMachine nested;
};

}; // namespace xs
