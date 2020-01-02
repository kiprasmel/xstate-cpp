# [xstate](https://github.com/davidkpiano/xstate)-cpp

I needed [xstate](https://github.com/davidkpiano/xstate) in C++. Here we are

## Usage

```cpp
#include "xstate.h"

using namespace xs;

int main() {
	StateMachine machine = {
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

	Interpreter *toggleMachine = interpret(machine)
		->logInfo()
		->onStart([]() {
			printf("let's go!\n");
		})
		->onTransition([]() {
			printf("yay we transitioned!\n");
		})
		->onStop([](Interpreter *self) {
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
```

compile with:

```sh
g++ -std=c++11 
```

for example,

```sh
g++ -std=c++11 ./xstate.cpp -o xstate.out
```

## License

[MIT](./LICENSE) © [Kipras Melnikovas](https://github.com/sarpik)
