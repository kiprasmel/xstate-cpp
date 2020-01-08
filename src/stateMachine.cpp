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
		std::cerr << "\nERR state machine tried to `transition`, but the provided `event`"
	            << "\n    did not have a handler for transitioning to the next state."
							<< "\n"
							<< "\ninfo:"
								<< "\n1. `this` inside `transition`: \n"
								<< (*this)
								// << "\nid: " << this->id
								// << "\nstate.value: " << this->state.value
								<< "\n"
								<< "\n2. deepest state machine we accessed,"
								<< "\n   the one we tried to transition to the next state: \n"
								<< (*head).lshift(std::cerr, 0)
								// << (*head)
 								// << "\nid: " << head->id
								// << "\nstate.value: " << head->state.value
								<< "\n"
								<< "\n3. args to the `transition` function:"
								<< "\nprovided `currentState`: " << currentState
								<< "\nprovided `event`: " << event
								<< "\n"
							<< "\n";

		#ifdef PLATFORMIO
			/** skip */
		#else
			throw;
		#endif
	}

	std::string nextState = nextStateIt->second;

	/** update the targeted state */
	head->state.value = nextState;

	return head->state;
}

std::string stringifyId(size_t depth = 0) const {
	std::string
};

std::string StateMachine::stringify(size_t depth = 0) const {
	std::string str = std::string("{")
		+ "\n  .id = " + this->id
		+ "\n  .state = " + this->state
		// + "\n.states = " + this->states
		+ "\n  .on = " + this->on
	+ "\n}";

	return str;
};

std::ostream& StateMachine::lshift(std::ostream& stream, size_t iterationCount = 0) const {
	stream << "{"
		<< "\n  .id = " << this->id
		<< "\n  .state = " << this->state
		// << "\n.states = " << this->states
		<< "\n  .on = " << this->on
	<< "\n}";

	return stream;
}

/** lshift `StateMachine` */
std::ostream& operator<< (std::ostream& stream, const StateMachine& self) {
	return self.lshift(stream, 0);
};

}; // namespace xs
