#include "./src/xstate.h"

int main() {
	printf("hi\n");

	xs::StateMachine machine = {
		.id = "sensoriu-off-on-off-check",
		.initial =  "nemato",
		.states = {
			{"nemato", { .on = { {"PAMATE", "mato"} } }},
			{"mato", { .on = { {"NEBEMATO", "vel_nemato"} } }},
			{"vel_nemato", {  } },
		}
	};

	xs::Interpreter *toggleMachine = xs::interpret(machine)
		->logInfo()
		->onStart([](xs::Interpreter *self) {
			self->logInfo();
		})
		->onTransition([](xs::Interpreter *self) {
			self->logInfo();
		})
		->onStop([](xs::Interpreter *self) {
			self->logInfo();
			printf("We've been stopped!\n");
		})
		->start();

	// toggleMachine->send("NEBEMATO"); /** nothing */

	// toggleMachine->send("PAMATE");

	// toggleMachine->send("NEBEMATO");

	// toggleMachine->stop();
	// // toggleMachine->send("PAMATE");

	return 0;
}
