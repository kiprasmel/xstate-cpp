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
	xs::StateMachine machine = {
		id: "light",
		state: { value: "green" },
		on: {},
		states: {
			{
				"green" ,
				{ on: { { "TIMER", "yellow" } } }
			},
			{
				"yellow",
				{ on: { { "TIMER", "red"    } } }
			},
			{
				"red.red-100"  ,
				{
					// on: { { "TIMER", "red.red-100"  } },
					on: { { "TIMER", "green"  } },
					states: {
						// {
						// id: "red-brightness",
						// state: { value: "red-100" },
						// states: {
							{
								"red-100",
								{ on: { { "TIMER", "red.red-0" } } }
							},
							{
								"red-0",
								{ on: { { "TIMER", "green" } } }
							}
						// }
						// }
					}
				}
			}
		}
	};

	xs::Interpreter toggleMachine = xs::interpret(machine)
		.logInfo()
		.onStart([]() {
			std::cout << "let's go!\n";
		})
		.onTransition([](xs::Interpreter self) {
			self.logInfo();
		})
		.onStop([]() {
			std::cout << "oh no we stopped c:\n";
		})
		.start();

	toggleMachine.send("TIMER");

	toggleMachine.send("TIMER");

	toggleMachine.send("TIMER");

	toggleMachine.send("TIMER");

	toggleMachine.send("TIMER");

	toggleMachine.send("TIMER");

	toggleMachine.stop();

	return 0;
}
