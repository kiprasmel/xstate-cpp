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

extern std::string InterpreterStatusStrings[]; /** defined @ `./interpreter.cpp` */
// inline std::string InterpreterStatusStrings[] = { "notStarted", "started", "stopped" }; /** -std=c++17 */

struct Interpreter {
	StateMachine      stateMachine;

	InterpreterStatus       status;

	Interpreter(StateMachine stateMachine);

	std::string getStatusStr() const;
	Interpreter logInfo     () const;

	/** handlers */
	Interpreter start();
	Interpreter send (std::string event);
	Interpreter stop ();

	/**
	 * These `handleOnXyz` functions are private & with a default value
	 * since we inject them through `onXyz`
	 * and then use them inside `xyz`.
	 *
	 * for example,
	 * we inject `handleOnStart` (`handleOnStart = []() { ... }`) from `onStart`
	 * and then call it inside `start`.
	 *
	 */
	private:
	std::function<void(Interpreter self)> handleOnStart      = [](Interpreter self) {};
	std::function<void(Interpreter self)> handleOnTransition = [](Interpreter self) {};
	std::function<void(Interpreter self)> handleOnStop       = [](Interpreter self) {};

	public:
	Interpreter onStart     (const std::function<void()> callback = []() {});
	Interpreter onStart     (const std::function<void(Interpreter self)> callback = [](Interpreter self) {});

	Interpreter onTransition(const std::function<void()> callback = []() {});
	Interpreter onTransition(const std::function<void(Interpreter self)> callback = [](Interpreter self) {});

	Interpreter onStop      (const std::function<void()> callback = []() {});
	Interpreter onStop      (const std::function<void(Interpreter self)> callback = [](Interpreter self) {});
};

Interpreter interpret(StateMachine stateMachine);

} // namespace xs
