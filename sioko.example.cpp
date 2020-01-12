#include "./src/xstate.h"

int main() {
	/**
	 * TODO - padaryt visus states'us su `_SE` ir `_NO_SEE`
	*/

	xs::StateMachine robotoBusena = {
		id: "roboto-busena",
		state: { value: "pradine" },
		on: {},
		states: {
			{
				"pradine",
				{
					id: "",
					state: {},
					on: {
						{ "PAUSE", "pauze" },
						{ "LINE", "linija_locked" },
						{ "FORWARD", "pirmyn" },
						{ "LEFT", "kairen" },
						{ "RIGHT", "desinen" }
					},
					states: {}
				}
			},
			{
				"pauze",
				{
					id: "",
					state: {},
					on: {
						{ "UNPAUSE", "pirmyn" /** TODO - pasitikrinimo mini-strategija, kurioje apsižvalgai prieš lekiant pirmyn? */ }
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
						{ "PAUSE", "pauze" },
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
				/**
				 * šitą turėtų iškviesti `linija_locked` timer'is po N ms,
				 * kad būtų galima liniją nutraukti,
				 * ir dar po M ms turėtų pats išsikirsti
				*/
				"linija_nutraukiama",
				{
					id: "",
					state: {},
					on: {
						{ "PAUSE", "pauze" },
						{ "LINE", "linija_locked" }, /** TODO - ar šito reikia? */
						{ "FORWARD", "pirmyn" },
						{ "LEFT", "kairen" },
						{ "RIGHT", "desinen" }
					},
					states: {}
				}
			},
			{
				"pirmyn_mato",
				{
					id: "",
					state: {},
					on: {
						{ "PAUSE", "pauze" },
						{ "LINE", "linija_locked" },
						{ "FORWARD_NO_SEE", "pirmyn_nebemato" }
					},
					states: {}
				}
			},
			{
				/**
				 *
				*/
				"pirmyn_nebemato",
				{
					id: "",
					state: {},
					on: {
						{ "PAUSE", "pauze" },
						{ "LINE", "linija_locked" },
						{ "FORWARD_SEE", "pirmyn_mato" },
						{ "LEFT", "kairen" },
						{ "RIGHT", "desinen" }
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
						{ "PAUSE", "pauze" },
						{ "LINE", "linija_locked" },
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
						{ "PAUSE", "pauze" },
						{ "LINE", "linija_locked" },
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
			// self.logInfo();
			// self.send("LEFT");
		})
		.onTransition([](xs::Interpreter self) {
			self.logInfo();
		})
		// .onStop([](xs::Interpreter self) {
		// 	self.logInfo();
		// })
		.start()
	;

	// robotoValdymas.stateMachine.state.value = "69";

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

	robotoValdymas.send("FORWARD");
	/** reaguoti ir kartoti loop'ą iš naujo */

	robotoValdymas.send("UNLOCK");
	/** reaguoti ir kartoti loop'ą iš naujo */

	robotoValdymas.send("LEFT");
	/** reaguoti ir kartoti loop'ą iš naujo */


	// robotoValdymas.send("RIGHT");
	// // /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("LINE");
	// /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("LINE_UNLOCK");
	// /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("LEFT");
	// /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("PAUSE");
	// /** reaguoti ir kartoti loop'ą iš naujo */

	robotoValdymas.stop();

	return 0;
}
