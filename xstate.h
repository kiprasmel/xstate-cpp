#pragma once
// xstate.h

/**
 * Originally by Kipras Melnikovas (https://kipras.org) <kipras@kipras.org>
 * MIT Licensed
 *
 *
 * This file is pretty meh because you'd have to separate out
 * the implementation into the `.cpp` file & that's *meh*,
 * thus we don't currently use it, but maybe in the future.
 *
*/

#include <map>
#include <functional>

namespace xs {

struct State;

typedef std::map<std::string, State> States;
// typedef std::map<const char *, State *> States;

struct StateMachine {
	const char *id;
	const char *initial;
	States states;
	// States *states;

	const char *transition(const char *currentState, const char *event);
};

// struct State : public StateMachine {
struct State {
	std::map<const char *, const char *> on;
	StateMachine nested;
};

// struct StateMachine;
// // {
// // 	const char *id;
// // 	const char *initial;
// // 	States *states;

// // 	const char *transition(const char *currentState, const char *event);
// // };

// struct State;
// {
// 	std::map<const char *, const char *> on;
// };

enum InterpreterStatus {
	notStarted,
	started,
	stopped
};

const char *InterpreterStatusStrings[] = { "notStarted", "started", "stopped" };

struct InterpreterState {
	const char *value;
};

struct Interpreter {
	private:
	InterpreterStatus status      ;

	InterpreterState *state       ;
	StateMachine     *stateMachine;

	public:
	Interpreter(StateMachine *stateMachine);

	const char  *getStatusStr() const;
	Interpreter *logInfo     ()      ;

	/** handlers */
	Interpreter *start(                 );
	Interpreter *send (const char *event);
	Interpreter *stop (                 );

	private:
	std::function<const void()> handleOnStart     ;
	std::function<const void()> handleOnTransition;
	std::function<const void()> handleOnStop      ;

	public:
	Interpreter *onStart     (const std::function<const void(                 )> callback);
	Interpreter *onStart     (const std::function<const void(Interpreter *self)> callback);

	Interpreter *onTransition(const std::function<const void(                 )> callback);
	Interpreter *onTransition(const std::function<const void(Interpreter *self)> callback);

	Interpreter *onStop      (const std::function<const void(                 )> callback);
	Interpreter *onStop      (const std::function<const void(Interpreter *self)> callback);
};

Interpreter *interpret(StateMachine  stateMachine);
Interpreter *interpret(StateMachine *stateMachine);

} // namespace xs
