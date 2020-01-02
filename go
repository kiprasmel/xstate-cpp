#!/usr/bin/env sh

PROGNAME="${1:-"xstate"}"

g++ -std=c++11 ./"$PROGNAME".cpp -o "$PROGNAME".out && ./"$PROGNAME".out
