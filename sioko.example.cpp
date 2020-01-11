#include "./src/xstate.h"

int main() {
	xs::StateMachine robotoBusena = {
		id: "roboto-busena",
		state: { value: "stop" },
		on: {},
		states: {
			{
				"stop",
				{
					id: "",
					state: {},
					on: {
						{ "LINE", "linija" },
						{ "FORWARD", "pirmyn" },
						{ "LEFT", "kairen" },
						{ "RIGHT", "desinen" }
					},
					states: {}
				}
			},
			{
				"linija_locked",
				{
					id: "",
					state: {},
					on: {
						{ "STOP", "stop" },
						{ "LINE_UNLOCK", "linija_nutraukiama" }
					},
					states: {}
				}
			},
			/**
			 * TODO - galbūt čia reiktų `žvalgytis` būsenos,
			 * kai apsisukęs sukinėjiesi kairėn dešinėn,
			 * iki kol ką nors pamatai?
			*/
			{
				"linija_nutraukiama",
				{
					id: "",
					state: {},
					on: {
						{ "STOP", "stop" },
						// { "LINE_TIMER", "pirmyn" }, /** bad, nes iškart baigtųsi */
						{ "FORWARD", "pirmyn" },
						{ "LEFT", "kairen" },
						{ "RIGHT", "desinen" }
					},
					states: {}
				}
			},
			{
				"pirmyn",
				{
					id: "",
					state: {},
					on: {
						{ "STOP", "stop" },
						{ "LINE", "linija" }
					},
					states: {}
				}
			},
			{
				"kairen",
				{
					id: "",
					state: {},
					on: {
						{ "STOP", "stop" },
						{ "LINE", "linija" },
						{ "FORWARD", "pirmyn" },
						// { "RIGHT", "desinen" } /** TODO - ar šitą naudojam? */
					},
					states: {}
				}
			},
			{
				"desinen",
				{
					id: "",
					state: {},
					on: {
						{ "STOP", "stop" },
						{ "LINE", "linija" },
						{ "FORWARD", "pirmyn" },
						// { "LEFT", "kairen" } /** TODO - ar šitą naudojam? */
					},
					states: {}
				}
			}
		}
	};

	xs::Interpreter robotoValdymas = xs::interpret(robotoBusena)
		.onStart([](xs::Interpreter self) {
			self.logInfo();
			self.send("LEFT");
		})
		// .onTransition([](const xs::Interpreter& self) {
		// 	self.logInfo();
		// })
		// .onStop([](xs::Interpreter self) {
		// 	self.logInfo();
		// })
		// .start()
	;

	robotoValdymas.stateMachine.state.value = "69";

	std::cout << " val = " << robotoValdymas.stateMachine.state.value << "\n";

	// /** TODO BEGIN config */
	// unsigned long kiekLaikoVykdytLinijaMs = 200; // TODO TEST
	// /** END config */

	// unsigned long latestLinijosPamatymoLaikasMs;

	/** važiuoti */
	// while (true) {
	// 	if (kiekMatoLinija() > 0) {
	// 		latestLinijosPamatymoLaikasMs = millis(); /** atsinaujins, jeigu ir pamatys iš naujo */
	// 		robotoValdymas.send("LINE");
	// 	}

	// 	if (arPraejoLaikas(latestLinijosPamatymoLaikasMs, kiekLaikoVykdytLinijaMs)) {
	// 		robotoValdymas.send("LINE_UNLOCK");
	// 	}

	// 	if (arVidurysKaNorsMato()) { robotoValdymas.send("FORWARD"); }

	// 	/**
	// 	 * TODO - čia negerai, nes vienas arba kitas šonas įgauna pirmumą
	// 	 * (šiuo atveju kairė).
	// 	 *
	// 	 * Reiktų galbūt tikrinimo abiejų kartu pirmiausia,
	// 	 * kad tokiu atveju tiesiog rautų pirmyn :D
	// 	*/
	// 	if (arKaireKaNorsMato() && arDesineKaNorsMato()) {
	// 		/**
	// 		 * TODO
	// 		 *
	// 		 * keista, kažkas tikriausiai ne taip.
	// 		 * Reiktų atsižvelgti į tai, KIEK kuri pusė mato,
	// 		 * ir tada pagal pasirinkti pusę
	// 		 *
	// 		*/
	// 		// robotoValdymas.send(o ką dabar?);
	// 	}
	// 	if (arKaireKaNorsMato())   { robotoValdymas.send("LEFT"); }
	// 	if (arDesineKaNorsMato())  { robotoValdymas.send("RIGHT"); }

	// }

	// robotoValdymas.send("FORWARD");
	// /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("LEFT");
	// /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("RIGHT");
	// /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("LINE");
	// /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("LINE_UNLOCK");
	// /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("LINE_UNLOCK");
	// /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("STOP");
	// /** reaguoti ir kartoti loop'ą iš naujo */

	robotoValdymas.stop();

	return 0;
}
