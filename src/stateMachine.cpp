#include <iostream>
#include <vector>
#include <string>

#include "xstate.h"
#include "stringUtils.h"

namespace xs {

std::string InterpreterStatusStrings[] = { "notStarted", "started", "stopped" };

const std::map<std::string, std::function<std::string(const StateMachine* self, size_t depth, bool firstOnNewline)>> StateMachine::fieldStringifiers = {
	{ "id",     [](const StateMachine* self, size_t depth, bool firstOnNewline) { return self->stringifyId(depth);                     } },
	{ "state",  [](const StateMachine* self, size_t depth, bool firstOnNewline) { return self->state.stringify(depth, firstOnNewline); } },
	{ "on",     [](const StateMachine* self, size_t depth, bool firstOnNewline) { return self->stringifyOn(depth, firstOnNewline);     } },
	{ "states", [](const StateMachine* self, size_t depth, bool firstOnNewline) { return self->stringifyStates(depth, firstOnNewline); } },
};

/**
 * @note this might return an empty string ("")
 * IF the next state during the event was not defined.
 */
StateMachineState StateMachine::transition(std::string currentState, std::string event) {
	std::vector<std::string> stateAccessTokens = splitStr(currentState, '.');

	StateMachine* head;

	/** avoid modifying `this` */
	if (stateAccessTokens.size() <= 1) {
		head = this;
	} else {
		/** go deeper & traverse */
		for (size_t i = 0; i + 1 < stateAccessTokens.size(); ++i) {
			std::string stateToken = stateAccessTokens[i];
			head = &head->states[stateToken];
		}

		// head = &this->states[stateAccessTokens[0]];

		// /** go deeper & traverse */
		// for (size_t i = 1; i + 1 < stateAccessTokens.size(); ++i) {
		// 	std::string stateToken = stateAccessTokens[i];
		// 	head = &head->states[stateToken];
		// }
	}




	// StateMachine *head = this;

	// /** go deeper & traverse */
	// for (size_t i = 0; i + 1 < stateAccessTokens.size(); ++i) {
	// 	std::string stateToken = stateAccessTokens[i];
	// 	head = &head->states[stateToken];
	// }

	const int lastIndex = stateAccessTokens.size() - 1;
	std::string lastStateAccessToken = stateAccessTokens[lastIndex];

	/**
	 *
	*/
	std::map<std::string, std::string>::iterator
	    nextStateIt =  head->states[lastStateAccessToken].on.find(event);

	if (nextStateIt == head->states[lastStateAccessToken].on.end()) {
		// std::cout << "\nreached error\n";
		/** NOT found */
		// std::string strified = this->stringify(*this);
		// std::cerr << "NICE " << strified << "\n\n";

		std::cout << "\n does this == head? " << (this == head); // << " ; equals original? " << (head == original);

		std::cerr << "\nERR state machine tried to `transition`, but the provided `event`"
	            << "\n    did not have a handler for transitioning to the next state."
							<< "\n"
							<< "\ninfo:"
								<< "\n1. `this` inside `transition`: \n"
								<< this->stringify()
								// << "\nid: " << this->id
								// << "\nstate.value: " << this->state.value
								<< "\n"
								<< "\n2. deepest state machine we accessed,"
								<< "\n   the one we tried to transition to the next state: \n"
								<< head->stringify()
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
std::string StateMachineState::stringify(size_t depth, const bool firstOnNewline) const {
	std::string strBody = "";

	const std::string& value = this->value;
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

	const auto& lastKey = this->on.rbegin()->first;

	for (const auto& keyValue : this->on) {
		const std::string& key = keyValue.first;
		const std::string& value = keyValue.second;

		if (!key.length() || !value.length()) {
			return "";
		}

		strBody
			// += "{\n"
			+= std::string("\n")
			+ "{ "
			+ key
			+ ", "
			+ value
			+ " }"
		;

		/** TODO if not last element */
		if (key != lastKey) {
			strBody += ",";
		}
	}

	strBody = deepifyRStr(strBody, depth + 1);

	std::string str
		= std::string(firstOnNewline ? "\n" : "")
		+ "{"
		+ strBody
		+ "\n"
		+ "}"
	;

	return str;
}

std::string StateMachine::stringifyStates(const size_t depth, const bool firstOnNewline) const {
	if (!this->states.size()) {
		return "";
	}

	std::string str = "";

	const auto& lastKey = this->states.rbegin()->first;

	for (auto keyValue : this->states) {

		const std::string& key = keyValue.first;
		const std::string& value = keyValue.second.stringify(depth, firstOnNewline);

		/** TODO early return if not */
		if (!key.length() || !value.length()) {
			return "";
		}

		/** reset */
		std::string strBody
			// = "{\n"
			= key
			+ ","
			+ "\n"
			+ value
			// + " }"
		;

		strBody = deepifyRStr(strBody, depth + 1);

		strBody
			= std::string("\n")
			+ "{"
			+ "\n"
			+ strBody
			+ "\n"
			+ "}"
		;

		if (key != lastKey) {
			strBody += ",";
		}

		str += strBody;
	}

	str = deepifyRStr(str, depth + 1);

	str
		= std::string(firstOnNewline ? "\n" : "")
		+ "{"
		+ str
		+ "\n}"
	;

	// strBody
	// 	= std::string("{")
	// 	+ "\n"
	// 	+ strBody
	// 	+ "\n"
	// 	+ "}"
	// ;

// std::string str
// 		= std::string(firstOnNewline ? "\n" : "")
// 		+ "{\n"
// 		+ strBody
// 		+ "\n}";


	return str;
};

std::string StateMachine::stringifyField(std::string fieldName, size_t depth, const bool firstOnNewline) const {
	// const std::vector<std::string> allowedFields = { "id", "state", "on", "states" };

	// const std::vector<std::function<std::string(size_t depth, bool firstOnNewline)>> stringifiers = {
	// 	[&](size_t depth, bool firstOnNewline) { return this->stringifyId(depth); },
	// 	[&](size_t depth, bool firstOnNewline) { return this->state.stringify(depth, firstOnNewline); },
	// 	[&](size_t depth, bool firstOnNewline) { return this->stringifyOn(depth, firstOnNewline); },
	// 	[&](size_t depth, bool firstOnNewline) { return this->stringifyStates(depth, firstOnNewline); },
	// };

	// std::map<std::string, std::function<std::string(size_t depth, bool firstOnNewline)>> fieldStringifiers = {
	// 	{ "id",     [&](size_t depth, bool firstOnNewline) { return this->stringifyId(depth);                     } },
	// 	{ "state",  [&](size_t depth, bool firstOnNewline) { return this->state.stringify(depth, firstOnNewline); } },
	// 	{ "on",     [&](size_t depth, bool firstOnNewline) { return this->stringifyOn(depth, firstOnNewline);     } },
	// 	{ "states", [&](size_t depth, bool firstOnNewline) { return this->stringifyStates(depth, firstOnNewline); } },

	if (this->fieldStringifiers.find(fieldName) == this->fieldStringifiers.end()) {
		/** invalid field */

		std::cerr
			<< "\nERR cannot stringify field `"
			<< fieldName
			<< "` - it does not have a stringify function for it yet.\n"
		;

		#ifdef PLATFORMIO
			/** skip */
		#else
			throw;
		#endif
	}

	return StateMachine::fieldStringifiers.at(fieldName)(this, depth, firstOnNewline);
	                          /** [fieldName](depth, firstOnNewline); */
};

/**
 * DFS
 */
std::string StateMachine::stringify(size_t depth, const bool firstOnNewline) const {
	std::string strBody = "";

	// struct Field {
	// 	std::string name;
	// 	std::string value;
	// 	// std::function<std::string(size_t depth, bool firstOnNewline)> stringify;
	// };

	// std::vector<Field> fields = {
	// 	{
	// 		"id",
	// 		this->stringifyId(depth)
	// 		// this->id,
	// 		// [&](size_t depth, bool firstOnNewline) { return this->stringifyId(depth); }
	// 	},
	// 	{
	// 		"state",
	// 		this->state.stringify(depth, firstOnNewline)
	// 		// this->state,
	// 		// [&](size_t depth, bool firstOnNewline) { return this->stringifyState(depth); }
	// 	},
	// 	{ "on",
	// 		this->stringifyOn(depth, firstOnNewline)
	// 		// this->on,
	// 		// [&](size_t depth, bool firstOnNewline) { return this->stringifyOn(depth, firstOnNewline); }
	// 	},
	// 	{
	// 		"states",
	// 		this->stringifyStates(depth, firstOnNewline)
	// 		// this->states,
	// 		// [&](size_t depth, bool firstOnNewline) { return this->stringifyStates(depth, firstOnNewline); }
	// 	}
	// };

	// std::vector<std::string> fields = for_each(this->fieldStringifiers.begin(), this->fieldStringifiers.end(),
	// 	[](const auto& fieldStringifier) {
	// 		return fieldStringifier.second(depth, firstOnNewline);
	// 	}
	// );

	for (const auto& fieldStringifier : this->fieldStringifiers) {
		const std::string& key   = fieldStringifier.first;
		const std::string& value = fieldStringifier.second(this, depth, firstOnNewline);

		if (!value.length()) {
			continue;
		}

		const bool needsComma = (strBody.length() > 0);
		const std::string prefix = needsComma ? "," : "";

		strBody
			+= prefix
			+ std::string("\n")
			+ "." + key + " = " + value
			// + field.stringify(depth, firstOnNewline)
		;
	}

	// const std::vector<std::string> fieldNames = { "id", "state", "on", "states" };
	// const std::vector<std::string>& fields = { id, state, on, states };
	// // std::vector<std::function<std::string(size_t depth, bool firstOnNewline)>>
	// std::vector<std::string (*)(size_t depth, bool firstOnNewline)>
	// 	// fieldStringifiers = { this->stringifyId, this->state.stringify, this->stringifyOn, this->stringifyStates };
	// 	fieldStringifiers = { [&](size_t depth, bool firstOnNewline) { return this->stringifyId(depth, firstOnNewline); } };


	// for (size_t i = 0; i < fields.size(); ++i) {
	// 	const auto& fieldName = fieldNames[i];
	// 	const auto& field = fields[i];
	// 	const auto& fieldStringifier = fieldStringifiers[i];

	// 	// std::string test = fieldStringifiers[0](depth, firstOnNewline);

	// 	if (field.length()) {
	// 		const bool needsComma = strBody.length() > 0;
	// 		const std::string prefix = needsComma ? "," : "";

	// 		strBody
	// 			+= prefix
	// 			+ std::string("\n")
	// 			+ "." + fieldName + " = "
	// 			+ fieldStringifier(depth, firstOnNewline)
	// 		;
	// 	}
	// }



	// std::string id = this->stringifyId(depth);
	// if (id.length()) { strBody += "\n.id = " + id; }

	// std::string state = this->state.stringify(depth, firstOnNewline);
	// if (state.length()) { strBody += "\n.state = " + state; };

	// std::string on = this->stringifyOn(depth, firstOnNewline);
	// if (on.length()) { strBody += "\n.on = " + on; }

	// std::string states = this->stringifyStates(depth, firstOnNewline);
	// if (states.length()) { strBody += "\n.states = " + states; }



	if (!strBody.length()) {
		return "";
	}

	// std::string state = this->stringifyState(depth);
	// if (state.length) { strBody += ".state = " + state; }

	// std::string on = this->stringifyOn(depth);
	// if (on.length) { strBody += ".on = " + state; }

	/**
	 * deepify by 2, but we'll deepify again below, so only by 1
	*/
	strBody = deepifyRStr(strBody, depth + 2 - 1);

	std::string str
		= std::string(firstOnNewline ? "\n" : "")
		+ "{"
		+ strBody
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
