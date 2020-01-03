#pragma once

// #include "State.h"
// #include "States.h"
#include "States.h"
// #include "xstate.h"

namespace xs {

struct StateMachine {
	const char *id;
	const char *initial;
	States states;

	const char *transition(const char *currentState, const char *event);
};

}; // namespace xs
