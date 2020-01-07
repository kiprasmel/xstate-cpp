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
	 * @note this will be an empty string ("") if next state does not exist.
	*/
	std::string nextState = head->states[lastStateAccessToken].on[event];

	// this->state.value = nextState;
	head->state.value = nextState;
	// return this->state;
	return head->state;
}

}; // namespace xs
