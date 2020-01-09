#!/usr/bin/env sh

PROGNAME="${1:-"example"}"

# -Wall -Wextra -Wpedantic
g++ -std=c++2a -g ./src/*.cpp ./"$PROGNAME".cpp -o "$PROGNAME".out && ./"$PROGNAME".out
