#pragma once

#include <iostream>
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

inline std::ostream& operator<< (std::ostream& stream, const StateMachineState& self) {
	stream << "{"
		<< "\n  .value = " << self.value
	<< "\n}";

	return stream;
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

	std::string stringifyId(size_t depth = 0) const;
	std::string stringify(size_t depth = 0) const;

	std::ostream& lshift(std::ostream& stream, size_t iterationCount = 0) const;
};

/** lshift `std::map<std::string, std::string>` (`StateMachine::on`) */
inline std::ostream& operator<< (std::ostream& stream, const std::map<std::string, std::string>& selfMap) {
	stream << "{";

	for (const auto& keyValue : selfMap) {
		stream << "\n{ " << keyValue.first << ", " << keyValue.second << " }";
	}

	stream << "}";

	return stream;
};

/** lshift `StateMachine` */
// inline std::ostream& operator<< (std::ostream& stream, const StateMachine& self);

/** lshift `std::map<std::string, StateMachine>` (`StateMachine::states`) */
inline std::ostream& operator<< (std::ostream& stream, const std::map<std::string, StateMachine>& selfMap) {
	bool first = true;

	for (const auto& keyValue : selfMap) {
		if (first) {
			first = false;
		} else {
			stream << "\n";
		}

		stream << keyValue.second; // value
	}

	return stream;
};

}; // namespace xs
