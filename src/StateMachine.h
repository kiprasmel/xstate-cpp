#pragma once

#include <string>

#include "States.h"

namespace xs {

struct StateMachine {
	std::string id;
	std::string initial;
	States states;

	std::string transition(std::string currentState, std::string event);
};

}; // namespace xs
