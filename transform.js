
const input = `
{  
  .id = roboto-busena,
  state : {  
    value : pirmyn_nebemato
  },
  .states = {  
    {
      desinen_mato,
      {  
        .on = {  
          { FORWARD_SEE, pirmyn_mato },
          { LINE_LOCK, linija_uzrakinta },
          { PAUSE, pauze },
          { RIGHT_NO_SEE, desinen_nebemato }
        }
      }
    },
    {
      desinen_nebemato,
      {  
        .on = {  
          { FORWARD_SEE, pirmyn_mato },
          { LEFT_SEE, kairen_mato },
          { LINE_LOCK, linija_uzrakinta },
          { PAUSE, pauze },
          { RIGHT_SEE, desinen_mato }
        }
      }
    },
    {
      kairen_mato,
      {  
        .on = {  
          { FORWARD_SEE, pirmyn_mato },
          { LEFT_NO_SEE, kairen_nebemato },
          { LINE_LOCK, linija_uzrakinta },
          { PAUSE, pauze }
        }
      }
    },
    {
      kairen_nebemato,
      {  
        .on = {  
          { FORWARD_SEE, pirmyn_mato },
          { LEFT_SEE, kairen_mato },
          { LINE_LOCK, linija_uzrakinta },
          { PAUSE, pauze },
          { RIGHT_SEE, desinen_mato }
        }
      }
    },
    {
      linija_atrakinta,
      {  
        .on = {  
          { FORWARD_SEE, pirmyn_mato },
          { LEFT_SEE, kairen_mato },
          { LINE_LOCK, linija_uzrakinta },
          { PAUSE, pauze },
          { RIGHT_SEE, desinen_mato }
        }
      }
    },
    {
      linija_uzrakinta,
      {  
        .on = {  
          { LINE_UNLOCK, linija_atrakinta },
          { PAUSE, pauze }
        }
      }
    },
    {
      pauze,
      {  
        .on = {  
          { UNPAUSE, pirmyn_nebemato }
        }
      }
    },
    {
      pirmyn_mato,
      {  
        .on = {  
          { FORWARD_NO_SEE, pirmyn_nebemato },
          { LINE_LOCK, linija_uzrakinta },
          { PAUSE, pauze }
        }
      }
    },
    {
      pirmyn_nebemato,
      {  
        .on = {  
          { FORWARD_SEE, pirmyn_mato },
          { LEFT_SEE, kairen_mato },
          { LINE_LOCK, linija_uzrakinta },
          { PAUSE, pauze },
          { RIGHT_SEE, desinen_mato }
        }
      }
    },
    {
      pradine,
      {  
        .on = {  
          { FORWARD_SEE, pirmyn_mato },
          { LEFT_SEE, kairen_mato },
          { LINE_LOCK, linija_uzrakinta },
          { PAUSE, pauze },
          { RIGHT_SEE, desinen_mato }
        }
      }
    }
  }
}
`;

const sp = "[\s\t\n]*";

const parsed = input
		.replace(/\s\./g, "  ")
		.replace(/=/g, ":")
		// .replace(/\{(?<key>([^,:{}]|\w)+),(?<value>[^,:{}]+)\},?/g, "$<key>: $<value>,")
		.replace(/\{(?<key>([^,:{}]|\w)+),(?<value>[^,:{}]+)[\s\t\n]*\},?/g, "\"$<key>\": \"$<value>\",")
		.replace(/\{(?<key>([^,:{}]|\w)+),(?<value>[^,:{}]+)[\s\t\n]*,?[\s\t\n]*\{/g, "{\n,$<key>: {\n$<value>")
		.replace(/[\s\t\n]*state[\s\t\n]*:[\s\t\n]*\{[\s\t\n]*value[\s\t\n]*:[\s\t\n]*(?<value>([^,:{}\n]|\w)+)[\s\t\n]*\}[\s\t\n]*,?/g, "\ninitial: $<value>,")
		.replace(/\}[\s\t\n]*,[\s\t\n]*{/g, "")
		// .replace(/\{(?<key>([^,:{}]|\w)+),(?<value>[^,:{}]+)\},?/g, "$<key>: $<value>,")
		.replace(/\"\s?([\w|_]+)\s?\"/g, '"$1"')
;

/**
 * TODO remove `{` and `}` @ `states:`
 * TODO just do it properly in the C++ code
 */

let output = parsed;

console.log(output);
