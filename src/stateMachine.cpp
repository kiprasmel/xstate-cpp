#include <iostream>
#include <vector>
#include <string>

#include "xstate.h"
#include "stringUtils.h"

namespace xs {

std::string InterpreterStatusStrings[] = { "notStarted", "started", "stopped" };

/**
 * @note this might return an empty string ("")
 * IF the next state during the event was not defined.
 */
StateMachineState StateMachine::transition(std::string currentState, std::string event) {
	std::vector<std::string> stateAccessTokens = splitStr(currentState, '.');

	StateMachine *head = this;

	/** go deeper & traverse */
	for (size_t i = 0; i + 1 < stateAccessTokens.size(); ++i) {
		std::string stateToken = stateAccessTokens[i];
		head = &head->states[stateToken];
	}

	const int lastIndex = stateAccessTokens.size() - 1;
	std::string lastStateAccessToken = stateAccessTokens[lastIndex];

	/**
	 *
	*/
	std::map<std::string, std::string>::iterator
	    nextStateIt =  head->states[lastStateAccessToken].on.find(event);

	if (nextStateIt == head->states[lastStateAccessToken].on.end()) {
		/** NOT found */
		std::string strified = this->stringify(*this);
		std::cerr << "NICE " << strified << "\n\n";

		// std::cerr << "\nERR state machine tried to `transition`, but the provided `event`"
	  //           << "\n    did not have a handler for transitioning to the next state."
		// 					<< "\n"
		// 					<< "\ninfo:"
		// 						<< "\n1. `this` inside `transition`: \n"
		// 						<< (this->stringify(*this))
		// 						// << "\nid: " << this->id
		// 						// << "\nstate.value: " << this->state.value
		// 						<< "\n"
		// 						<< "\n2. deepest state machine we accessed,"
		// 						<< "\n   the one we tried to transition to the next state: \n"
		// 						<< (head->stringify(*head))
		// 						// << (*head).lshift(std::cerr, 0)
		// 						// << (*head)
 		// 						// << "\nid: " << head->id
		// 						// << "\nstate.value: " << head->state.value
		// 						<< "\n"
		// 						<< "\n3. args to the `transition` function:"
		// 						<< "\nprovided `currentState`: " << currentState
		// 						<< "\nprovided `event`: " << event
		// 						<< "\n"
		// 					<< "\n";


		#ifdef PLATFORMIO
			/** skip */
		#else
			std::cerr << "\nexiting\n";
			throw;
		#endif
	}

	std::string nextState = nextStateIt->second;

	/** update the targeted state */
	head->state.value = nextState;

	return head->state;
}

std::string StateMachine::stringifyId(const size_t depth) const {
	return deepifyStr(this->id, depth);
};

std::string StateMachine::stringifyStates(const size_t depth, const bool firstOnNewline) const {
	std::string str = "{";

	const auto& lastKey = this->states.rbegin()->first;

	for (std::map<std::string, StateMachine>::value_type keyValue : this->states) {
		str
			+= "{ "
			+ keyValue.first
			+ ", "
			+ this->stringify(keyValue.second, firstOnNewline)
			+ " }"
		;

		if (keyValue.first != lastKey) {
			str += "\n";
		}
	}

	std::string str
		= std::string(firstOnNewline ? "\n" : "")
		+ "{"
		+ strBody
		+ "\n}";


	return str;
};

std::string StateMachine::stringify(StateMachine& self, size_t depth, const bool firstOnNewline) const {
	std::string strBody
		= "\n.id = " + self.stringifyId(depth)
		+ "\n.state = " + self.stringifyStates(depth, firstOnNewline)
		// + "\n.states = " + self->states
		// + "\n.on = " + self.on
	;

	/**
	 * deepify by 2, but we'll deepify again below, so only by 1
	*/
	strBody = deepifyStr(strBody, depth + 2 - 1);

	std::string str
		= std::string(firstOnNewline ? "\n" : "")
		+ "{"
		+ strBody
		+ "\n}";

	str = deepifyStr(str, depth + 1);

	return str;
};

// std::ostream& StateMachine::lshift(std::ostream& stream, size_t iterationCount = 0) const {
// 	stream << "{"
// 		<< "\n  .id = " << this->id
// 		<< "\n  .state = " << this->state
// 		// << "\n.states = " << this->states
// 		// << "\n  .on = " << this->on
// 	<< "\n}";

// 	return stream;
// }

// /** lshift `StateMachine` */
// std::ostream& operator<< (std::ostream& stream, const StateMachine& self) {
// 	return self.lshift(stream, 0);
// };

}; // namespace xs
