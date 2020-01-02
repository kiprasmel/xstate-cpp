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

#include <map>
/**
 * {
 * 	.on = { { "EVENT", "nextState" } }
 * };
 *
 */
struct State {
	std::map<const char *, const char *> on;
};

/**
 * {
 *	{
 *		"green" ,
 *		{ .on = { { "TIMER", "yellow" } } }
 *	},
 *	{
 *		"yellow",
 *		{ .on = { { "TIMER", "red"    } } }
 *	},
 *	{
 *		"red"  ,
 *		{ .on = { { "TIMER", "green"  } } }
 *	}
 * };
 *
 */
typedef std::map<const char *, State> States;
