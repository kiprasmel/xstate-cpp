#pragma once

#include <map>
#include <string>

// #include "State.h"
// #include "xstate.h"

namespace xs {

struct State;

typedef std::map<std::string, State> States;

}; // namespace xs
