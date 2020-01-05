# [xstate](https://github.com/davidkpiano/xstate)-cpp

I needed [xstate](https://github.com/davidkpiano/xstate) in C++. Here we are

## Features

* Basic stuff (I dunno I'm new here I just wanted a state machine for myself ☃)
* Nested state machines just landed in by [#5](https://github.com/sarpik/xstate-cpp/pull/5) - see [./example.cpp](./example.cpp) for an example.
* Others coming in real soon. Actually, even sooner, if you wanna contribute:P

## Installation

* platformio

```sh
platformio lib install --save XState-cpp
```

For everything else, you need to compile all `.cpp` files - makefile [coming soon](https://github.com/sarpik/xstate-cpp/issues/7).

* git + submodules

```sh
git submodules add https://github.com/sarpik/xstate-cpp.git
# or:  git submodules add git@github.com/sarpik/xstate-cpp.git
git submodules update --init --recursive

g++ -std=c++11 ./xstate-cpp/src/*.cpp ./xstate-cpp/example.cpp -o example.out
./example.out
```

* git

```sh
git clone https://github.com/sarpik/xstate-cpp.git
# or:  git clone git@github.com:sarpik/xstate-cpp.git

g++ -std=c++11 ./xstate-cpp/src/*.cpp ./xstate-cpp/example.cpp -o example.out
./example.out
```

obviously, you subsitute the `example.cpp` with your own source files & get some spicy state machines.

## Usage

See also [./example.cpp](./example.cpp)

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
        "red"   ,
        { .on = { { "TIMER", "green"  } } }
      }
    }
  };

  Interpreter *toggleMachine = interpret(machine)
    ->logInfo()
    ->onStart([]() {
      printf("let's go!\n");
    })
    ->onTransition([](Interpreter *self) {
      self->logInfo();
    })
    ->onStop([]() {
      printf("oh no we stopped c:\n");
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
g++ -std=c++11 ./src/*.cpp ./example.cpp -o example.out
```

& run with

```sh
./example.out
```

I use [./src/go](./src/go)

## License

[MIT](./LICENSE) © [Kipras Melnikovas](https://github.com/sarpik)
