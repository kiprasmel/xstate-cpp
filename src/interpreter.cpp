#include <cstdio>

#include "Interpreter.h"

namespace xs {

Interpreter::Interpreter(StateMachine *stateMachine)
	:
	stateMachine(stateMachine),
	state(new InterpreterState({ .value = stateMachine->initial})),
	status(notStarted)
{
}

const char *Interpreter::getStatusStr() const {
	return InterpreterStatusStrings[this->status];
}

Interpreter *Interpreter::logInfo() {
	printf("status = %d (%s) | state = %s \n", this->status, this->getStatusStr(), this->state->value);
	return this;
}

Interpreter *Interpreter::send(const char *event) {
	if (this->status != started) {
		fprintf(
			stderr,
			"\nERR interpreter.send was called when it was not started / stopped (%s).\n",
			this->getStatusStr()
		);

		throw;
	}

	const char *nextState = this->stateMachine->transition(this->state->value, event);
	// printf("nextState %s\n", nextState);

	/**
		* An event might've been fired at the wrong time /
		* when the state didn't have any handlers for that specific event,
		* thus we just skip it, since that's allowed.
		*/
	if (nextState != NULL) {
		this->state->value = nextState;
	}

	this->handleOnTransition();

	return this;
}

/** handlers (identical) */


Interpreter *Interpreter::start() {
	this->status = started;
	this->handleOnStart();

	return this;
}

Interpreter *Interpreter::onStart(const std::function<const void(                 )> callback = [](                 ) {}) {
	this->handleOnStart = [&]() { callback(    ); };
	return this;
}

/** the one we expose to the consumer so he can inject the callback */
Interpreter *Interpreter::onStart(const std::function<const void(Interpreter *self)> callback = [](Interpreter *self) {}) {
	this->handleOnStart = [&]() { callback(this); };
	return this;
}


Interpreter *Interpreter::onTransition(const std::function<const void(                 )> callback = [](                 ) {}) {
	this->handleOnTransition = [&]() { callback(    ); };
	return this;
}

Interpreter *Interpreter::onTransition(const std::function<const void(Interpreter *self)> callback = [](Interpreter *self) {}) {
	this->handleOnTransition = [&]() { callback(this); };
	return this;
}


Interpreter *Interpreter::stop() {
	this->status = stopped;
	this->handleOnStop();
	return this;
}

Interpreter *Interpreter::onStop(const std::function<const void(                 )> callback = [](                 ) {}) {
	this->handleOnStop = [&]() { callback(    ); };
	return this;
}

Interpreter *Interpreter::onStop(const std::function<const void(Interpreter *self)> callback = [](Interpreter *self) {}) {
	this->handleOnStop = [&]() { callback(this); };
	return this;
}


Interpreter *interpret(StateMachine  stateMachine) {
	Interpreter *interpreter = new Interpreter(new StateMachine(stateMachine));

	return interpreter;
}

Interpreter *interpret(StateMachine *stateMachine) {
	Interpreter *interpreter = new Interpreter(                 stateMachine );

	return interpreter;
}

}; // namespace xs
