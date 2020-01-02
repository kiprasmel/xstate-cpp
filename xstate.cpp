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
 * g++ -std=c++11 ./xstate.cpp -o xstate.out
 * ```
 *
*/

#include "xstate.h"

// using namespace xs;

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
				{ .on = { { "TIMER", "green"  } } }
			}
		}
	};

	xs::Interpreter *toggleMachine = xs::interpret(machine)
		->logInfo()
		->onStart([]() {
			printf("let's go!\n");
		})
		->onTransition([]() {
			printf("yay we transitioned!\n");
		})
		->onStop([](xs::Interpreter *self) {
			printf("oh no we stopped c:\n");
			self->logInfo();
		})
		->start();

	toggleMachine->send("TIMER");

	toggleMachine->send("TIMER");

	toggleMachine->send("TIMER");

	toggleMachine->stop();

	delete toggleMachine;

	return 0;
}
