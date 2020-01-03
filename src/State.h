#pragma once

#include <map>

#include "StateMachine.h"
// #include "xstate.h"

namespace xs {

struct State {
	std::map<const char *, const char *> on;
	StateMachine nested;
};

}; // namespace xs
