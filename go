#!/usr/bin/env sh

PROGNAME="${1:-"xstate"}"

g++ -std=c++17 ./"$PROGNAME".cpp -o "$PROGNAME".out && ./"$PROGNAME".out
