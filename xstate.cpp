// xstate.cpp

/**
 * Originally by Kipras Melnikovas (https://kipras.org) <kipras@kipras.org>
 * MIT Licensed
 *
 *
 * compile with:
 *
 * ```sh
 * g++ -std=c++11 ./xstate.cpp -o xstate.out
 * ```
 *
*/

/**
 * {
 * 	.on = { { "EVENT", "nextState" } }
 * };
 *
 */
struct State {
	std::map<const char *, const char *> on;
};
