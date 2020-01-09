#include <iostream>
#include <vector>
#include <string>

#include "xstate.h"
#include "stringUtils.h"

namespace xs {

std::string InterpreterStatusStrings[] = { "notStarted", "started", "stopped" };

/**
 * @note this might return an empty string ("")
 * IF the next state during the event was not defined.
 */
StateMachineState StateMachine::transition(std::string currentState, std::string event) {
	std::vector<std::string> stateAccessTokens = splitStr(currentState, '.');

	StateMachine *head = this;

	/** go deeper & traverse */
	for (size_t i = 0; i + 1 < stateAccessTokens.size(); ++i) {
		std::string stateToken = stateAccessTokens[i];
		head = &head->states[stateToken];
	}

	const int lastIndex = stateAccessTokens.size() - 1;
	std::string lastStateAccessToken = stateAccessTokens[lastIndex];

	/**
	 *
	*/
	std::map<std::string, std::string>::iterator
	    nextStateIt =  head->states[lastStateAccessToken].on.find(event);

	if (nextStateIt == head->states[lastStateAccessToken].on.end()) {
		std::cout << "\nreached error\n";
		/** NOT found */
		// std::string strified = this->stringify(*this);
		// std::cerr << "NICE " << strified << "\n\n";

		std::cerr << "\nERR state machine tried to `transition`, but the provided `event`"
	            << "\n    did not have a handler for transitioning to the next state."
							<< "\n"
							<< "\ninfo:"
								<< "\n1. `this` inside `transition`: \n"
								<< (this->stringify(*this))
								// << "\nid: " << this->id
								// << "\nstate.value: " << this->state.value
								<< "\n"
								<< "\n2. deepest state machine we accessed,"
								<< "\n   the one we tried to transition to the next state: \n"
								<< (head->stringify(*head))
								// << (*head).lshift(std::cerr, 0)
								// << (*head)
 								// << "\nid: " << head->id
								// << "\nstate.value: " << head->state.value
								<< "\n"
								<< "\n3. args to the `transition` function:"
								<< "\nprovided `currentState`: " << currentState
								<< "\nprovided `event`: " << event
								<< "\n"
							<< "\n";


		#ifdef PLATFORMIO
			/** skip */
		#else
			std::cerr << "\nexiting\n";
			throw;
		#endif
	}

	std::string nextState = nextStateIt->second;

	/** update the targeted state */
	head->state.value = nextState;

	return head->state;
}


/** TODO no `self` */
std::string StateMachineState::stringify(StateMachineState& self, size_t depth, const bool firstOnNewline) const {
	std::string strBody = "";

	const std::string& value = self.value;
	if (value.length()) { strBody += "\n.value = " + value; }



	if (!strBody.length()) {
		return "";
	}

	/**
	 * deepify by 2, but we'll deepify again below, so only by 1
	*/
	std::string deepifiedBody = deepifyRStr(strBody, depth + 2 - 1);

	std::string str
		= std::string(firstOnNewline ? "\n" : "")
		+ "{"
		+ deepifiedBody
		+ "\n}";

	// str = deepifyRStr(str, depth + 1);

	return str;
};




std::string StateMachine::stringifyId(const size_t depth) const {
	if (!this->id.length()) {
		return "";
	}

	std::string deepifiedId = deepifyStr(this->id, depth);
	return deepifiedId;
};

/**
 * TODO abstract into
 *
 * ```cpp
 * stringifyMap
 * 	const size_t depth,
 * 	const bool firstOnNewline,
 * 	std::function<...> keyStringifier = []() { return value },
 * 	std::function<...> valueStringifier = []() { return value }
 * )
 * ```
 *
 */
std::string StateMachine::stringifyOn(const size_t depth, const bool firstOnNewline) const {
	if (!this->on.size())	{
		return "";
	}

	std::string strBody = "";

	for (const auto& keyValue : this->on) {
		const std::string& key = keyValue.first;
		const std::string& value = keyValue.second;

		if (!key.length() || !value.length()) {
			return "";
		}

		strBody
			+= key
			+ ", "
			+ value
			+ " }";

		/** if not last element */
		strBody += ",\n";
	}

	strBody = deepifyRStr(strBody, depth + 1);

	std::string str
		= std::string(firstOnNewline ? "\n" : "")
		+ "{"
		+ strBody
		+ "\n}";

	str = deepifyRStr(str, depth + 1);

	return str;
}

std::string StateMachine::stringifyStates(const size_t depth, const bool firstOnNewline) const {
	if (!this->states.size()) {
		return "";
	}

	std::string strBody = "";

	const auto& lastKey = this->states.rbegin()->first;

	for (std::map<std::string, StateMachine>::value_type keyValue : this->states) {

		const std::string& key = keyValue.first;
		const std::string& value = this->stringify(keyValue.second, depth + 1, firstOnNewline);

		/** TODO early return if not */
		if (!key.length() || !value.length()) {
			return "";
		}

		strBody
			// += "{\n"
			+= key
			+ ","
			+ "\n"
			+ value
			// + " }"
		;

		strBody = deepifyRStr(strBody, depth + 1);

		strBody
			= std::string("{")
			+ "\n"
			+ strBody
			+ "\n"
			+ "}"
		;

		// strBody
		// 	+= "{ "
		// 	+ keyValue.first
		// 	+ ", "
		// 	+ this->stringify(keyValue.second, depth + 1, firstOnNewline)
		// 	+ " }"
		// ;

		// if (keyValue.first != lastKey) {
			// strBody += "\n";
		// }
	}

	strBody = deepifyRStr(strBody, depth + 1);

	strBody
		= std::string("{")
		+ "\n"
		+ strBody
		+ "\n"
		+ "}"
	;

// std::string str
// 		= std::string(firstOnNewline ? "\n" : "")
// 		+ "{\n"
// 		+ strBody
// 		+ "\n}";


	return strBody;
};

std::string StateMachine::stringify(StateMachine& self, size_t depth, const bool firstOnNewline) const {
	std::string strBody = "";

	std::string id = self.stringifyId(depth);
	if (id.length()) { strBody += "\n.id = " + id; }

	std::string state = self.state.stringify(self.state, depth, firstOnNewline);
	if (state.length()) { strBody += "\n.state = " + state; };

	std::string on = self.stringifyOn(depth, firstOnNewline);
	if (on.length()) { strBody += "\n.on = " + on; }

	std::string states = self.stringifyStates(depth, firstOnNewline);
	if (states.length()) { strBody += "\n.states = " + states; }

	if (!strBody.length()) {
		return "";
	}

	// std::string state = self.stringifyState(depth);
	// if (state.length) { strBody += ".state = " + state; }

	// std::string on = self.stringifyOn(depth);
	// if (on.length) { strBody += ".on = " + state; }

	/**
	 * deepify by 2, but we'll deepify again below, so only by 1
	*/
	std::string deepifiedBody = deepifyRStr(strBody, depth + 2 - 1);

	std::string str
		= std::string(firstOnNewline ? "\n" : "")
		+ "{"
		+ deepifiedBody
		+ "\n}";

	// str = deepifyRStr(str, depth + 1);

	return str;
};

// std::ostream& StateMachine::lshift(std::ostream& stream, size_t iterationCount = 0) const {
// 	stream << "{"
// 		<< "\n  .id = " << this->id
// 		<< "\n  .state = " << this->state
// 		// << "\n.states = " << this->states
// 		// << "\n  .on = " << this->on
// 	<< "\n}";

// 	return stream;
// }

// /** lshift `StateMachine` */
// std::ostream& operator<< (std::ostream& stream, const StateMachine& self) {
// 	return self.lshift(stream, 0);
// };

}; // namespace xs
