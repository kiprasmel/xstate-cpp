/* eslint-disable @typescript-eslint/camelcase */

import { Machine } from "xstate";

// xs::StateMachine robotoBusena = {
const machine = Machine({
	id: "roboto-busena",
	// state: { value: "pradine" },
	initial: "pradine",
	on: {},
	states: {
		/**
		 * remove brackets
		 * replace in-between `,` with `:`
		 */
		// {
		// "pradine",
		pradine: {
			id: "",
			// state: {},
			on: {
				/**
				 * remove brackets
				 * replace the in-between comma `,` with column `:`
				 * (same as above :O)
				 */
				// { "PAUSE", "pauze" },
				PAUSE: "pauze",
				LINE_LOCK: "linija_uzrakinta",
				FORWARD_SEE: "pirmyn_mato",
				LEFT: "kairen_mato",
				RIGHT: "desinen_mato",
			},
			states: {},
		},
		// },
		// 	,
		// // {
		pauze: {
			id: "",
			// state: {},
			on: {
				UNPAUSE:
					"pirmyn_nebemato" /** TODO - pasitikrinimo mini-strategija, kurioje apsižvalgai prieš lekiant pirmyn? */,
			},
			states: {},
		},
		// },
		// {
		linija_uzrakinta: {
			id: "",
			// state: {},
			on: {
				PAUSE: "pauze",
				LINE_UNLOCK: "linija_atrakinta",
			},
			states: {},
		},
		// },
		// 	/**
		// 	 * TODO - galbūt čia reiktų `žvalgytis` būsenos,
		// 	 * kai apsisukęs sukinėjiesi kairėn dešinėn,
		// 	 * iki kol ką nors pamatai?
		// 	*/
		// 	// {
		// 		/**
		// 		 * šitą turėtų iškviesti `linija_uzrakinta` timer'is po N ms,
		// 		 * kad būtų galima liniją nutraukti,
		// 		 * ir dar po M ms turėtų pats išsikirsti
		// 		*/
		linija_atrakinta: {
			id: "",
			// state: {},
			on: {
				PAUSE: "pauze",
				LINE_LOCK: "linija_uzrakinta" /** TODO - ar šito reikia? */,
				FORWARD_SEE: "pirmyn_mato",
				LEFT_SEE: "kairen_mato",
				RIGHT_SEE: "desinen_mato",
			},
			states: {},
		},
		// },
		// 	// {
		// 	// 	"pirmyn",
		// 	// 	{
		// 	// 		id: "",
		// 	// 		state: { value: "mato" },
		// 	// 		on: {
		// 	// 		},
		// 	// 		states: {
		// 	// 			{
		// 	// 				"mato",
		// 	// 				{
		// 	// 					id: "",
		// 	// 					state: {},
		// 	// 					on: {
		// 	// 						{ "PAUSE", "pauze" },
		// 	// 						{ "LINE_LOCK", "linija_uzrakinta" },
		// 	// 						{ "FORWARD_NO_SEE", "pirmyn.nebemato" }
		// 	// 					},
		// 	// 					states: {}
		// 	// 				}
		// 	// 			},
		// 	// 			{
		// 	// 				"nebemato",
		// 	// 				{
		// 	// 					id: "",
		// 	// 					state: {},
		// 	// 					on: {
		// 	// 						{ "PAUSE", "pauze" },
		// 	// 						{ "LINE_LOCK", "linija_uzrakinta" },
		// 	// 						{ "FORWARD_SEE", "pirmyn.mato" },
		// 	// 						{ "LEFT", "kairen" },
		// 	// 						{ "RIGHT", "desinen" }
		// 	// 					},
		// 	// 					states: {}
		// 	// 				}
		// 	// 			},
		// 	// 		}
		// 	// 	}
		// 	// },
		// 	/** --- */
		// 	// {
		pirmyn_mato: {
			id: "",
			// state: {},
			on: {
				PAUSE: "pauze",
				LINE_LOCK: "linija_uzrakinta",
				FORWARD_NO_SEE: "pirmyn_nebemato",
			},
			states: {},
		},
		// },
		// 	// {
		// 		/**
		// 		 *
		// 		*/
		pirmyn_nebemato: {
			id: "",
			// state: {},
			on: {
				PAUSE: "pauze",
				LINE_LOCK: "linija_uzrakinta",
				FORWARD_SEE: "pirmyn_mato",
				LEFT_SEE: "kairen_mato",
				RIGHT_SEE: "desinen_mato",
			},
			states: {},
		},
		// 	// },
		// 	,
		// 	// {
		kairen_mato: {
			id: "",
			// state: {},
			on: {
				PAUSE: "pauze",
				LINE_LOCK: "linija_uzrakinta",
				FORWARD_SEE: "pirmyn_mato",
				LEFT_NO_SEE: "kairen_nebemato",
			},
			states: {},
		},
		// },
		// 	,
		// 	// {
		kairen_nebemato: {
			id: "",
			// state: {},
			on: {
				PAUSE: "pauze",
				LINE_LOCK: "linija_uzrakinta",
				FORWARD: "pirmyn_mato",
				LEFT_SEE: "kairen_mato",
				RIGHT_SEE: "desinen_mato",
			},
			states: {},
		},
		// },
		// 	,
		// {
		desinen_mato: {
			id: "",
			// state: {},
			on: {
				PAUSE: "pauze",
				LINE_LOCK: "linija_uzrakinta",
				FORWARD_SEE: "pirmyn_mato",
				RIGHT_NO_SEE: "desinen_nebemato",
			},
			states: {},
		},
		// },
		// {
		desinen_nebemato: {
			id: "",
			// state: {},
			on: {
				PAUSE: "pauze",
				LINE_LOCK: "linija_uzrakinta",
				FORWARD_SEE: "pirmyn_mato",
				RIGHT_SEE: "desinen_mato",
				LEFT_SEE: "kairen_mato" /** TODO - ar šitą naudojam? */,
			},
			states: {},
		},
		// }
		// }
	},
});
