// xstate.cpp

/**
 * Originally by Kipras Melnikovas (https://kipras.org) <kipras@kipras.org>
 * MIT Licensed
 *
 *
 * compile with:
 *
 * ```sh
 * g++ -std=c++11 ./xstate.cpp -o xstate.out
 * ```
 *
*/

#include <cstdio>
#include <map>
#include <functional>
/**
 * {
 * 	.on = { { "EVENT", "nextState" } }
 * };
 *
 */
struct State {
	std::map<const char *, const char *> on;
};

/**
 * {
 *	{
 *		"green" ,
 *		{ .on = { { "TIMER", "yellow" } } }
 *	},
 *	{
 *		"yellow",
 *		{ .on = { { "TIMER", "red"    } } }
 *	},
 *	{
 *		"red"  ,
 *		{ .on = { { "TIMER", "green"  } } }
 *	}
 * };
 *
 */
typedef std::map<const char *, State> States;

/**
 * {
 *	.id = "light",
 *	.initial = "green",
 *	.states = {
 *		{
 *			"green" ,
 *			{ .on = { { "TIMER", "yellow" } } }
 *		},
 *		{
 *			"yellow",
 *			{ .on = { { "TIMER", "red"    } } }
 *		},
 *		{
 *			"red"  ,
 *			{ .on = { { "TIMER", "green"  } } }
 *		}
 *	}
 * };
 *
 */
struct StateMachine {
	const char *id;
	const char *initial;
	States states;

	const char *transition(const char *currentState, const char *event) {
		const char *nextState = this->states[currentState].on[event];
		return nextState;
	}
};

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

	InterpreterStatus status;

	InterpreterState *state;
	StateMachine *stateMachine;

	public:

	Interpreter(StateMachine *stateMachine)
		:
		stateMachine(stateMachine),
		state(new InterpreterState({ .value = stateMachine->initial})),
		status(notStarted)
	{
	}

	const char *getStatusStr() const {
		return InterpreterStatusStrings[this->status];
	}

	Interpreter *logInfo() {
		printf("status = %d (%s) | state = %s \n", this->status, this->getStatusStr(), this->state->value);
		return this;
	}

	Interpreter *send(const char *event) {
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



	// void onStart(std::function<void(const InterpreterState *state)> callback = [](const InterpreterState *state) {}) const {
	// 	callback(this->state);
	// }

	Interpreter *start() {
		this->status = started;
		this->handleOnStart();

		return this;
	}

	/** the one we call ourselves */
	private: std::function<const void()> handleOnStart = []() {};

	public:
	Interpreter *onStart(const std::function<const void(                 )> callback = [](                 ) {}) {
		this->handleOnStart = [&]() { callback(    ); };
		return this;
	}

	/** the one we expose to the consumer so he can inject the callback */
	Interpreter *onStart(const std::function<const void(Interpreter *self)> callback = [](Interpreter *self) {}) {
		this->handleOnStart = [&]() { callback(this); };
		return this;
	}



	// std::function<void(                             )> onTransition = [](                             ) {};
	// std::function<void(const InterpreterState *state)> onTransition = [](const InterpreterState *state) {};

	// void onTransition(std::function<void()> callback = []() {}) const {
	// 	callback();
	// }

	/** the one we call ourselves */
	private: std::function<const void()> handleOnTransition = []() {};

	/** the one we expose to the consumer so he can inject the callback */
	public:
	Interpreter *onTransition(const std::function<const void(                 )> callback = [](                 ) {}) {
		this->handleOnTransition = [&]() { callback(    ); };
		return this;
	}

	Interpreter *onTransition(const std::function<const void(Interpreter *self)> callback = [](Interpreter *self) {}) {
		this->handleOnTransition = [&]() { callback(this); };
		return this;
	}



	// std::function<void()> onStop = []() {};
	// void onStop(std::function<void(const InterpreterState *state)> callback = [](const InterpreterState *state) {}) const {
	// 	callback(this->state);
	// }

	Interpreter *stop() {
		this->status = stopped;
		this->handleOnStop();
		return this;
	}

	/** the one we call ourselves */
	private: std::function<const void()> handleOnStop = []() {};

	/** the one we expose to the consumer so he can inject the callback */
	public:
	Interpreter *onStop(const std::function<const void(                 )> callback = [](                 ) {}) {
		this->handleOnStop = [&]() { callback(    ); };
		return this;
	}

	Interpreter *onStop(const std::function<const void(Interpreter *self)> callback = [](Interpreter *self) {}) {
		this->handleOnStop = [&]() { callback(this); };
		return this;
	}
};
