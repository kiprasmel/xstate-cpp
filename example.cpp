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
#include "./src/xstate.h"
// #include "./src/StateMachine.h"

int main() {
	try {
	// // parallel
	// xs::StateMachine machine = xs::StateMachine({
	// 	.id = "light",
	// 	// .type = "parallel", /** TODO implement lol */
	// 	.states = {
	// 		{
	// 			"bold"   ,
	// 			{
	// 				.state = { .value = "off" },
	// 				.states = {
	// 					{
	// 						"on",
	// 						{ .on = { { "TOGGLE_BOLD", "off" } } }
	// 					},
	// 					{
	// 						"off",
	// 						{ .on = { { "TOGGLE_BOLD", "on" } } }
	// 					}
	// 				}
	// 			}
	// 		},
	// 		{
	// 			"underline",
	// 			{
	// 				.state = { .value = "off" },
	// 				.states = {
	// 					{
	// 						"on",
	// 						{ .on = { { "TOGGLE_UNDERLINE", "off" } } }
	// 					},
	// 					{
	// 						"off",
	// 						{ .on = { { "TOGGLE_UNDERLINE", "on" } } }
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// });

	// // xs::Interpreter* tm = xs::interpret(machine);

	// // std::cout << "\n";

	// machine.transition("bold.off", "TOGGLE_BOLD");

	// machine.transition("underline.off", "TOGGLE_UNDERLINE");
	// machine.transition("underline.on", "TOGGLE_UNDERLINE");

	// std::cout << "parallel - m.state.val = " << machine.state.value
	// 	<< "\n" << "states = " << machine.states["bold"].state.value << " ; " <<  machine.states["underline"].state.value
	// 	<< "\n";


	/** --- */

	// xs::StateMachine basic {
	// 	.id = "basic",
	// 	.state = { .value = "yellow" }, /** the initial value */
	// 	.states = {
	// 		{
	// 			"green",
	// 			{ .on = { { "TIMER", "yellow" } } },
	// 		},
	// 		{
	// 			"yellow",
	// 			{ .on = { { "TIMER", "red" } } }
	// 		},
	// 		{
	// 			"red",
	// 			{ .on = { { "TIMER", "green" } } }
	// 		}
	// 	}
	// };

	xs::StateMachine basic = {
		.id = "light",
		.state = { .value = "green" },
		.states = {
			{
				"green" ,
				{ .on = { { "TIMER", "yellow" } } }
			},
			{
				"yellow",
				{ .on = { { "TIMER", "red"    }, { "FOOBAR", "yellow" } } }
			},
			{
				"red"  ,
				{
					.id = "red-brightness",
					.state = { .value = "red-100" },
					.on = { { "TIMER", "red.red-100"  } },
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
	};

	// xs::StateMachine basic = {
	// 	"basic",
	// 	"green",
	// 	{
	// 		{
	// 			"green",
	// 			{ .on = { { "TIMER", "yellow" } } },
	// 		},
	// 		{
	// 			"yellow",
	// 			{ .on = { { "TIMER", "red" } } }
	// 		},
	// 		{
	// 			"red",
	// 			{ .on = { { "TIMER", "green" } } }
	// 		}
	// 	},
	// 	{},
	// 	""
	// };

	basic.transition("green", "TIMER");
	basic.transition("yellow", "TIMER");
	basic.transition("red", "TIMER");

	// std::cout << "\nbasic - state.val = " << basic.state.value
		// << "\n";

	std::cout << basic.stringify(0, false) << "\n";

	// basic.transition("yellow_DECOY_BISH", "TIMER"); // red

	std::cout << "\nbasic - state.val after TIMER = " << basic.state.value << "\n"; // red

	/** --- */

	// xs::Interpreter basicToggle = xs::interpret(basic)
	// 	.onTransition([](xs::Interpreter* self) {
	// 		std::cout << "\nlogging info: ";
	// 		self->logInfo();
	// 	})
	// 	.start()
	// ;

	// // xs::Interpreter* tm = new xs::Interpreter(basic);
	// // tm->

	// basicToggle.send("TIMER"); // green
	// basicToggle.send("TIMER"); // yellow

	// std::cout << "\nvalue = " << basicToggle.stateMachine.state.value << "\n";

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
