#pragma once

#include <iostream>
#include <string>
#include <functional>

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

	std::string stringify(size_t depth = 0, const bool firstOnNewline = false) const;
};

inline std::ostream& operator<< (std::ostream& stream, const StateMachineState& self) {
	stream << "{"
		<< "\n  .value = " << self.value
	<< "\n}";

	return stream;
};

struct StateMachine {
	public:
	/**
	 * @note - these must be in order
	 * when you're creating the StateMachine
	 * via
	 */
	std::string                         id    ;
	StateMachineState                   state ;
	std::map<std::string, std::string > on    ;
	std::map<std::string, StateMachine> states;

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

	std::string stringifyId(const size_t depth = 0) const;
	// // std::string stringifyState(const size_t depth = 0) const;
	std::string stringifyOn(const size_t depth = 0, const bool firstOnNewline = false) const;
	std::string stringifyStates(const size_t depth = 0, const bool firstOnNewline = false) const;
	// std::string stringifyOn(const size_t depth = 0) const;
	// std::string stringifyStates(const size_t depth = 0) const;


	static const std::map<std::string, std::function<std::string(const StateMachine* self, size_t depth, bool firstOnNewline)>> fieldStringifiers;
	//  = {
	// 	{ "id",     [&](StateMachine* self, size_t depth, bool firstOnNewline) { return self->stringifyId(depth);                     } },
	// 	{ "state",  [&](StateMachine* self, size_t depth, bool firstOnNewline) { return self->state.stringify(depth, firstOnNewline); } },
	// 	{ "on",     [&](StateMachine* self, size_t depth, bool firstOnNewline) { return self->stringifyOn(depth, firstOnNewline);     } },
	// 	{ "states", [&](StateMachine* self, size_t depth, bool firstOnNewline) { return self->stringifyStates(depth, firstOnNewline); } },
	// };

	std::string stringifyField(std::string fieldName = "", size_t depth = 0, const bool firstOnNewline = false) const;

	// std::string stringify(const size_t depth = 0, bool firstOnNewline = false) const;
	std::string stringify(size_t depth = 0, const bool firstOnNewline = false) const;

	std::ostream& lshift(std::ostream& stream, size_t iterationCount) const;
};

// /** lshift `std::map<std::string, std::string>` (`StateMachine::on`) */
// inline std::ostream& operator<< (std::ostream& stream, const std::map<std::string, std::string>& selfMap) {
// 	stream << "{";

// 	for (const auto& keyValue : selfMap) {
// 		stream << "\n{ " << keyValue.first << ", " << keyValue.second << " }";
// 	}

// 	stream << "}";

// 	return stream;
// };

// /** lshift `StateMachine` */
// inline std::ostream& operator<< (std::ostream& stream, const StateMachine& self);

// /** lshift `std::map<std::string, StateMachine>` (`StateMachine::states`) */
// inline std::ostream& operator<< (std::ostream& stream, const std::map<std::string, StateMachine>& selfMap) {
// 	bool first = true;

// 	for (const auto& keyValue : selfMap) {
// 		if (first) {
// 			first = false;
// 		} else {
// 			stream << "\n";
// 		}

// 		stream << keyValue.second; // value
// 	}

// 	return stream;
// };

}; // namespace xs
