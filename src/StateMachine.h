#pragma once

#include <string>

#include "States.h"

namespace xs {

struct StateMachineState {
	std::string value;

	// StateMachineState(
	// 	std::string value
	// )
	// 	:
	// 	value(value)
	// {
	// }
};

class StateMachine {
	public:
	/**
	 * @note - these must be in order
	 * when you're creating the StateMachine
	 * via
	 */
	std::string id;
	StateMachineState state;
	std::string initial;
	std::map<std::string, StateMachine> states;
	std::map<std::string, std::string > on;

	// StateMachine(
	// 	std::string id = "",
	// 	std::string initial = "",
	// 	std::map<std::string, std::string > on = { { "foo", "BAR" } },
	// 	StateMachineState state = { .value = "" }
	// 	,
	// 	std::map<std::string, StateMachine> states = { }

	// 	// std::map<std::string, StateMachine> states = {
	// 	// 	{
	// 	// 		"green",
	// 	// 		{ .on = { { "TIMER", "yellow" } } },
	// 	// 	},
	// 	// 	{
	// 	// 		"yellow",
	// 	// 		{ .on = { { "TIMER", "red" } } }
	// 	// 	},
	// 	// 	{
	// 	// 		"red",
	// 	// 		{ .on = { { "TIMER", "green" } } }
	// 	// 	}
	// 	// }

	// )
	// 	:
	// 	id(id),
	// 	initial(initial),
	// 	on(on),
	// 	state(state)
	// 	,
	// 	states(states)
	// {
	// 	/** TODO */
	// 	this->state.value = this->initial;
	// }





	// StateMachine(std::initializer_list<StateMachine> self)
	// {
	// }


	StateMachineState transition(std::string currentState, std::string event);
};

}; // namespace xs
