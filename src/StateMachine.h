#pragma once

#include "States.h"

namespace xs {

struct StateMachine {
	const char *id;
	const char *initial;
	States states;

	const char *transition(const char *currentState, const char *event);
};

}; // namespace xs
