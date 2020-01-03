// example.cpp

/**
 * Originally by Kipras Melnikovas (https://kipras.org) <kipras@kipras.org>
 * MIT Licensed
 *
 *
 * compile with:
 *
 * ```sh
g++ -std=c++17 ./example.cpp ./src/*.cpp -o example.out
 * ```
 *
*/

#include "./src/xstate.cpp"

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
				}
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
