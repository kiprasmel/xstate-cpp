#pragma once

#include <string>
#include <functional>

#include "xstate.h"

namespace xs {

enum InterpreterStatus {
	notStarted,
	started,
	stopped
};

extern std::string InterpreterStatusStrings[];

struct Interpreter {
	InterpreterStatus status      ;

	StateMachine     *stateMachine;

	Interpreter(StateMachine *stateMachine);

	std::string  getStatusStr() const;
	Interpreter *logInfo     ()      ;

	/** handlers */
	Interpreter *start(                 );
	Interpreter *send (std::string event);
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
