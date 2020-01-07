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
	xs::StateMachine* machine = new xs::StateMachine({
		.id = "light",
		// .type = "parallel", /** TODO implement lol */
		// .initial = "bold",
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
			},
			{
				"underline",
				{
					.initial = "off",
					.states = {
						{
							"on",
							{ .on = { { "TOGGLE_UNDERLINE", "off" } } }
						},
						{
							"off",
							{ .on = { { "TOGGLE_UNDERLINE", "on" } } }
						}
					}
				}
			}
		}
	});

	xs::Interpreter* tm = xs::interpret(machine);

	std::cout << "test\n";

	// machine->transition("bold.off", "TOGGLE_BOLD");

	// machine->transition("underline.off", "TOGGLE_UNDERLINE");

	// std::cout << "\nvalue: " << machine->state.value << "\n";

	// xs::Interpreter *tm = xs::interpret(machine)
	// 	->onTransition([](xs::Interpreter *self) {
	// 		self->logInfo();
	// 	});

	// tm->transition("bold.off", "TOGGLE_BOLD");

	// tm->transition("underline.off", "TOGGLE_UNDERLINE");

	/** */

	// xs::Interpreter *toggleMachine = xs::interpret(machine) ->logInfo()
	//  ->onStart([]() {std::cout << "let's go!\n";
	//  })
	//  ->onTransition([](xs::Interpreter *self) {self->logInfo();
	//  })
	//  ->onStop([]() {std::cout << "oh no we stopped c:\n";
	//  })
	//  ->start();

	// toggleMachine->send("bold.TOGGLE_BOLD"); // ??

	// toggleMachine->send("TOGGLE_BOLD");

	// toggleMachine->send("TOGGLE_BOLD");

	// toggleMachine->send("TIMER");

	// toggleMachine->send("TIMER");

	// toggleMachine->send("TIMER");

	// toggleMachine->stop();

	// delete toggleMachine;
	}
	catch (const char* message) {
		std::cerr << "\nERR: " << message;
	}

	std::cout << "\ndone\n";

	return 0;
}
