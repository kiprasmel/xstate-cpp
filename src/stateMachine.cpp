//#include <cstdio>

#include "xstate.h"
#include "SplitStr.h"

namespace xs {

const char *InterpreterStatusStrings[] = { "notStarted", "started", "stopped" };

const char *StateMachine::transition(const char *currentState, const char *event)
{
	std::vector<std::string> stateAccessTokens = splitStr(currentState, '.');

	// printf("num of tokens %d\n", stateAccessTokens.size());

	// for (auto &token : stateAccessTokens) {
	// 	printf("token %s\n", token.c_str());
	// }

	StateMachine *head = this;

	/** go deeper & traverse */
	for (size_t i = 0; i + 1 < stateAccessTokens.size(); ++i) {
		const char *stateToken = stateAccessTokens[i].c_str();
		head = &head->states[stateToken].nested;
	}

	const int lastIndex = stateAccessTokens.size() - 1;
	std::string lastStateAccessToken = stateAccessTokens[lastIndex];

	/**
	 * HALP FIXME
	 *
	 * lmfao I spent way too much time here
	 *
	 * don't use `const char *` for indexing for sure.
	 *
	*/
	const char *nextState = head->states[lastStateAccessToken].on[event];

	// printf("nextState %s\n", nextState);

	return nextState;
}

}; // namespace xs
