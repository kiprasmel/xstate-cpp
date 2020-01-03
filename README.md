# [xstate](https://github.com/davidkpiano/xstate)-cpp

I needed [xstate](https://github.com/davidkpiano/xstate) in C++. Here we are

## Features

* Basic stuff (I dunno I'm new here I just wanted a state machine for myself ☃)
* Nested state machines just landed in by #5 - see [./xstate.cpp](./xstate.cpp) for an example.
* Others coming in real soon. Actually, even sooner, if you wanna contribute:P

## Installation

You only need the [`xstate.h`](./xstate.h) header file - that's it.

* platformio

> SOON

* git + submodules

```sh
git submodules add https://github.com/sarpik/xstate-cpp.git
# or:  git submodules add git@github.com/sarpik/xstate-cpp.git
git submodules update --init --recursive
```

* git

```sh
git clone https://github.com/sarpik/xstate-cpp.git
# or:  git clone git@github.com:sarpik/xstate-cpp.git
```

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
g++ -std=c++17 
```

for example,

```sh
g++ -std=c++17 ./xstate.cpp -o xstate.out
```

## License

[MIT](./LICENSE) © [Kipras Melnikovas](https://github.com/sarpik)
