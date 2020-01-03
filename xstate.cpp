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
