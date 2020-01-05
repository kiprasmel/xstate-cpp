#!/usr/bin/env sh

PROGNAME="${1:-"example"}"

g++ -std=c++11 ./src/*.cpp ./"$PROGNAME".cpp -o "$PROGNAME".out && ./"$PROGNAME".out
