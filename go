#!/usr/bin/env sh
# go

#
# usage:
# ./go [args to g++]
#

PROGNAME="${PROGNAME:-sioko.example}"

# -Wall -Wextra -Wpedantic
g++ -std=c++2a -g ./src/*.cpp ./"$PROGNAME".cpp -o "$PROGNAME".out $* && ./"$PROGNAME".out
