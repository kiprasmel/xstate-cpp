// xstate.cpp

/**
 * Originally by Kipras Melnikovas (https://kipras.org) <kipras@kipras.org>
 * MIT Licensed
 *
 *
 * This file (`.cpp`) is not actually needed - everything's inside `xstate.h`,
 * and this is just an example usage.
 *
 *
 * compile with:
 *
 * ```sh
 * g++ -std=c++17 ./xstate.cpp -o xstate.out
 * ```
 *
*/

#include "xstate.h"

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> splitStr(std::string str = "", const char delim = ' ') {
    std::string buf;                 // Have a buffer string
    std::stringstream ss(str);       // Insert the string into a stream

    std::vector<std::string> tokens; // Create vector to hold our words

    while (getline(ss, buf, delim)) {
        tokens.push_back(buf);
	}

	return tokens;
}

namespace xs {

const char *StateMachine::transition(const char *currentState, const char *event)
{
	std::vector<std::string> stateAccessTokens = splitStr(currentState, '.');

	// printf("num of tokens %d\n", stateAccessTokens.size());

	// for (auto &token : stateAccessTokens) {
	// 	printf("token %s\n", token.c_str());
	// }

	StateMachine *head = this;

	/** go deeper & traverse */
	for (size_t i = 0; i + 1 < stateAccessTokens.size(); ++i) {
		const char *stateToken = stateAccessTokens[i].c_str();
		head = &head->states[stateToken].nested;
	}

	const int lastIndex = stateAccessTokens.size() - 1;
	std::string lastStateAccessToken = stateAccessTokens[lastIndex];

	/**
	 * HALP FIXME
	 *
	 * lmfao I spent way too much time here
	 *
	 * don't use `const char *` for indexing for sure.
	 *
	*/
	const char *nextState = head->states[lastStateAccessToken].on[event];

	// printf("nextState %s\n", nextState);

	return nextState;
}

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

Interpreter *interpret(StateMachine  stateMachine) {
	Interpreter *interpreter = new Interpreter(new StateMachine(stateMachine));

	return interpreter;
}

Interpreter *interpret(StateMachine *stateMachine) {
	Interpreter *interpreter = new Interpreter(                 stateMachine );

	return interpreter;
}

} // namespace xs

int main() {
	xs::StateMachine machine = {
		.id = "light",
		.initial = "green",
		.states = {
			{
				"green" ,
				{ .on = { { "TIMER", "yellow" } } }
			},
			{
				"yellow",
				{ .on = { { "TIMER", "red"    } } }
			},
			{
				"red"  ,
				{
					.on = { { "TIMER", "red.red-100"  } },
					.nested = {
						.id = "red-brightness",
						.initial = "red-100",
						.states = {
							{
								"red-100",
								{ .on = { { "TIMER", "red.red-0" } } }
							},
							{
								"red-0",
								{ .on = { { "TIMER", "green" } } }
							}
						}
					}
				},
			}
		}
	};

	xs::Interpreter *toggleMachine = xs::interpret(machine)
		->logInfo()
		->onStart([]() {
			printf("let's go!\n");
		})
		->onTransition([](xs::Interpreter *self) {
			self->logInfo();
		})
		->onStop([]() {
			printf("oh no we stopped c:\n");
		})
		->start();

	toggleMachine->send("TIMER");

	toggleMachine->send("TIMER");

	toggleMachine->send("TIMER");

	toggleMachine->send("TIMER");

	toggleMachine->send("TIMER");

	toggleMachine->send("TIMER");

	toggleMachine->stop();

	delete toggleMachine;

	return 0;
}
