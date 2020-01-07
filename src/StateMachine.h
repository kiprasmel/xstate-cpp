#pragma once

#include <string>

#include "States.h"

namespace xs {

struct StateMachineState {
	std::string value;
};

struct StateMachine {
	/**
	 * @note - these must be in order
	 * when you're creating the StateMachine
	 * via
	 */
	std::string id;
	std::string initial;
	std::map<std::string, StateMachine> states;
	std::map<std::string, std::string > on;

	StateMachineState state;

	std::string transition(std::string currentState, std::string event);
};

}; // namespace xs
