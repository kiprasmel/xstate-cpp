#!/usr/bin/env sh
# go

#
# usage:
# ./go [args to g++]
#

#PROGNAME="${1:-"example"}"
PROGNAME="sioko.example"

# -Wall -Wextra -Wpedantic
g++ -std=c++11 -g ./src/*.cpp ./"$PROGNAME".cpp -o "$PROGNAME".out $* && ./"$PROGNAME".out
