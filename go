#!/usr/bin/env sh

PROGNAME="${1:-"example"}"

g++ -std=c++2a ./src/*.cpp ./"$PROGNAME".cpp -o "$PROGNAME".out && ./"$PROGNAME".out
