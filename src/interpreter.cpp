#include <iostream>
#include <string>

#include "Interpreter.h"
#include "stringUtils.h"

namespace xs {

Interpreter::Interpreter(StateMachine stateMachine)
	:
	stateMachine(stateMachine),
	// state(new InterpreterState({ .value = stateMachine->initial})),
	status(notStarted)
{
}

// // Interpreter::Interpreter(StateMachine *stateMachine)
// // 	:
// // 	stateMachine(stateMachine),
// // 	// state(new InterpreterState({ .value = stateMachine->initial})),
// // 	status(notStarted)
// // {
// // }

std::string Interpreter::getStatusStr() const {
	return InterpreterStatusStrings[this->status];
}

Interpreter Interpreter::logInfo() {
	std::cout << "status = " << this->status
		<< " (" << this->getStatusStr() << ")"
		<< " | state = " << this->stateMachine.state.value
		<< "\n";

	return (*this);
}

Interpreter Interpreter::send(std::string event) {
	if (this->status != started) {
		std::cerr << "\nERR interpreter.send was called when it was not started / stopped"
			<< " (" << this->getStatusStr() << ")."
			<< "\n";

		/**
		 * platformio isn't happy about error handling somehow
		 *
		 * also, I did not find any official statement that this flag gets set -
		 * it just works 🤷‍♀️
		 *
		 * To check yourself, compile with `-D PLATFORMIO`
		 */
		#ifdef PLATFORMIO
			/** skip */
		#else
			throw;
		#endif
	}

	std::string nextState = this->stateMachine.transition(this->stateMachine.state.value, event).value;
	// printf("nextState %s\n", nextState);

	/**
		* An event might've been fired at the wrong time /
		* when the state didn't have any handlers for that specific event,
		* thus we just skip it, since that's allowed.
		*/
	if (nextState != "") {
		this->stateMachine.state.value = nextState;
	} else {
		std::cout << "got empty state\n";
	}

	this->handleOnTransition(this);

	return (*this);
}

/** handlers (identical) */


Interpreter Interpreter::start() {
	this->status = started;
	this->handleOnStart();

	return (*this);
}

Interpreter Interpreter::onStart(const std::function<const void(                 )> callback = [](                 ) {}) {
	this->handleOnStart = [&]() { callback(    ); };
	return (*this);
}

/** the one we expose to the consumer so he can inject the callback */
Interpreter Interpreter::onStart(const std::function<const void(Interpreter self)> callback = [](Interpreter self) {}) {
	this->handleOnStart = [&]() { callback((*this)); };
	return (*this);
}


Interpreter& Interpreter::onTransition(const std::function<const void(                 )> callback = [](                 ) {}) {
	this->handleOnTransition = [=](Interpreter* self) { callback(    ); };
	return (*this);
}

Interpreter& Interpreter::onTransition(const std::function<const void(Interpreter* self)> callback = [](Interpreter* self) {}) {
	this->handleOnTransition = [=](Interpreter* self) { callback(self); };

	return (*this);
}


Interpreter Interpreter::stop() {
	this->status = stopped;
	this->handleOnStop();
	return (*this);
}

Interpreter Interpreter::onStop(const std::function<const void(                 )> callback = [](                 ) {}) {
	this->handleOnStop = [&]() { callback(    ); };
	return (*this);
}

Interpreter Interpreter::onStop(const std::function<const void(Interpreter self)> callback = [](Interpreter self) {}) {
	this->handleOnStop = [&]() { callback((*this)); };
	return (*this);
}


Interpreter interpret(StateMachine stateMachine) {
	Interpreter interpreter = Interpreter(stateMachine);

	return interpreter;
}


Interpreter* interpret(StateMachine stateMachine) {
	Interpreter* interpreter = new Interpreter(stateMachine);

	return interpreter;
}

}; // namespace xs
