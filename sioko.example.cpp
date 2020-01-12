#include "./src/xstate.h"

int main() {
	/**
	 * TODO - padaryt visus states'us su `_SE` ir `_NO_SEE`
	 * TODO patikrint, ar viskas ok:D
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
						{ "LINE_LOCK", "linija_uzrakinta" },
						{ "FORWARD_SEE", "pirmyn_mato" },
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
				"linija_uzrakinta",
				{
					id: "",
					state: {},
					on: {
						{ "PAUSE", "pauze" },
						{ "LINE_UNLOCK", "linija_atrakinta" }
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
				 * šitą turėtų iškviesti `linija_uzrakinta` timer'is po N ms,
				 * kad būtų galima liniją nutraukti,
				 * ir dar po M ms turėtų pats išsikirsti
				*/
				"linija_atrakinta",
				{
					id: "",
					state: {},
					on: {
						{ "PAUSE", "pauze" },
						{ "LINE_LOCK", "linija_uzrakinta" }, /** TODO - ar šito reikia? */
						{ "FORWARD_SEE", "pirmyn_mato" },
						{ "LEFT_SEE", "kairen_mato" },
						{ "RIGHT_SEE", "desinen_mato" }
					},
					states: {}
				}
			},
			// {
			// 	"pirmyn",
			// 	{
			// 		id: "",
			// 		state: { value: "mato" },
			// 		on: {
			// 		},
			// 		states: {
			// 			{
			// 				"mato",
			// 				{
			// 					id: "",
			// 					state: {},
			// 					on: {
			// 						{ "PAUSE", "pauze" },
			// 						{ "LINE_LOCK", "linija_uzrakinta" },
			// 						{ "FORWARD_NO_SEE", "pirmyn.nebemato" }
			// 					},
			// 					states: {}
			// 				}
			// 			},
			// 			{
			// 				"nebemato",
			// 				{
			// 					id: "",
			// 					state: {},
			// 					on: {
			// 						{ "PAUSE", "pauze" },
			// 						{ "LINE_LOCK", "linija_uzrakinta" },
			// 						{ "FORWARD_SEE", "pirmyn.mato" },
			// 						{ "LEFT", "kairen" },
			// 						{ "RIGHT", "desinen" }
			// 					},
			// 					states: {}
			// 				}
			// 			},
			// 		}
			// 	}
			// },
			/** --- */
			{
				"pirmyn_mato",
				{
					id: "",
					state: {},
					on: {
						{ "PAUSE", "pauze" },
						{ "LINE_LOCK", "linija_uzrakinta" },
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
						{ "LINE_LOCK", "linija_uzrakinta" },
						{ "FORWARD_SEE", "pirmyn_mato" },
						{ "LEFT_SEE", "kairen_mato" },
						{ "RIGHT_SEE", "desinen_mato" }
					},
					states: {}
				}
			},
			{
				"kairen_mato",
				{
					id: "",
					state: {},
					on: {
						{ "PAUSE", "pauze" },
						{ "LINE_LOCK", "linija_uzrakinta" },
						{ "FORWARD_SEE", "pirmyn_mato" },
						{ "LEFT_NO_SEE", "kairen_nebemato" }
					},
					states: {}
				}
			},
			{
				"kairen_nebemato",
				{
					id: "",
					state: {},
					on: {
						{ "PAUSE", "pauze" },
						{ "LINE_LOCK", "linija_uzrakinta" },
						{ "FORWARD", "pirmyn_mato" },
						{ "LEFT_SEE", "kairen_mato" },
						{ "RIGHT_SEE", "desinen_mato" }
					},
					states: {}
				}
			},
			{
				"desinen_mato",
				{
					id: "",
					state: {},
					on: {
						{ "PAUSE", "pauze" },
						{ "LINE_LOCK", "linija_uzrakinta" },
						{ "FORWARD_SEE", "pirmyn_mato" },
						{ "RIGHT_NO_SEE", "desinen_nebemato" }
					},
					states: {}
				}
			},
			{
				"desinen_nemato",
				{
					id: "",
					state: {},
					on: {
						{ "PAUSE", "pauze" },
						{ "LINE_LOCK", "linija_uzrakinta" },
						{ "FORWARD_SEE", "pirmyn_mato" },
						{ "RIGHT_SEE", "desinen_mato" },
						{ "LEFT_SEE", "kairen_mato" } /** TODO - ar šitą naudojam? */
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


	robotoValdymas.send("FORWARD_SEE"); // send forward
	robotoValdymas.send("LEFT_SEE"); // ignore
	robotoValdymas.send("FORWARD_NO_SEE"); // make cancellable
	robotoValdymas.send("LEFT_SEE"); // send left
	robotoValdymas.send("RIGHT_SEE"); // ignore
	robotoValdymas.send("LEFT_NO_SEE"); // send left
	robotoValdymas.send("RIGHT_SEE"); // send right
	robotoValdymas.send("FORWARD_SEE"); // forward
	robotoValdymas.send("LINE_LOCK"); // line
	robotoValdymas.send("FORWARD_SEE"); // ignore
	robotoValdymas.send("LINE_UNLOCK"); // unlock line
	robotoValdymas.send("FORWARD_SEE"); // send forward


	// robotoValdymas.send("RIGHT");
	// // /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("LINE_LOCK");
	// /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("LINE_UNLOCK");
	// /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("LEFT");
	// /** reaguoti ir kartoti loop'ą iš naujo */
	// robotoValdymas.send("PAUSE");
	// /** reaguoti ir kartoti loop'ą iš naujo */



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

	robotoValdymas.stop();

	return 0;
}
