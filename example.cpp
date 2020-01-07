// example.cpp

/**
 * Originally by Kipras Melnikovas (https://kipras.org) <kipras@kipras.org>
 * MIT Licensed
 *
 *
 * compile with:
 *
 * ```sh
g++ -std=c++11 ./example.cpp ./src/*.cpp -o example.out
 * ```
 *
*/

#include <iostream> // std::cout
#include "./src/xstate.cpp"

int main() {
	try {
	xs::StateMachine machine = {
		.id = "light",
		// .type = "parallel", /** TODO implement lol */
		.initial = "bold",
		.states = {
			{
				"bold"   ,
				{
					.initial = "off",
					.states = {
						{
							"on",
							{ .on = { { "TOGGLE_BOLD", "off" } } }
						},
						{
							"off",
							{ .on = { { "TOGGLE_BOLD", "on" } } }
						}
					}
				}
			}
		}
	};

	xs::Interpreter *toggleMachine = xs::interpret(machine)
		->logInfo()
		->onStart([]() {
			std::cout << "let's go!\n";
		})
		->onTransition([](xs::Interpreter *self) {
			self->logInfo();
		})
		->onStop([]() {
			std::cout << "oh no we stopped c:\n";
		})
		->start();

	toggleMachine->send("bold.TOGGLE_BOLD"); // ??

	toggleMachine->send("TOGGLE_BOLD");

	toggleMachine->send("TOGGLE_BOLD");

	// toggleMachine->send("TIMER");

	// toggleMachine->send("TIMER");

	// toggleMachine->send("TIMER");

	// toggleMachine->stop();

	delete toggleMachine;
	}
	catch (const char* message) {
		std::cerr << "\nERR: " << message;
	}

	return 0;
}
