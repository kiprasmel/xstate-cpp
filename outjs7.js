
{  
   id : roboto-busena,
initial: pirmyn_nebemato,
   states : {  
    {

      desinen_mato: {

      ,  
         on : {  
           FORWARD_SEE:  pirmyn_mato ,
           LINE_LOCK:  linija_uzrakinta ,
           PAUSE:  pauze ,
           RIGHT_NO_SEE:  desinen_nebemato ,
        }
      }
    

      desinen_nebemato: {

      ,  
         on : {  
           FORWARD_SEE:  pirmyn_mato ,
           LEFT_SEE:  kairen_mato ,
           LINE_LOCK:  linija_uzrakinta ,
           PAUSE:  pauze ,
           RIGHT_SEE:  desinen_mato ,
        }
      }
    

      kairen_mato: {

      ,  
         on : {  
           FORWARD_SEE:  pirmyn_mato ,
           LEFT_NO_SEE:  kairen_nebemato ,
           LINE_LOCK:  linija_uzrakinta ,
           PAUSE:  pauze ,
        }
      }
    

      kairen_nebemato: {

      ,  
         on : {  
           FORWARD_SEE:  pirmyn_mato ,
           LEFT_SEE:  kairen_mato ,
           LINE_LOCK:  linija_uzrakinta ,
           PAUSE:  pauze ,
           RIGHT_SEE:  desinen_mato ,
        }
      }
    

      linija_atrakinta: {

      ,  
         on : {  
           FORWARD_SEE:  pirmyn_mato ,
           LEFT_SEE:  kairen_mato ,
           LINE_LOCK:  linija_uzrakinta ,
           PAUSE:  pauze ,
           RIGHT_SEE:  desinen_mato ,
        }
      }
    

      linija_uzrakinta: {

      ,  
         on : {  
           LINE_UNLOCK:  linija_atrakinta ,
           PAUSE:  pauze ,
        }
      }
    

      pauze: {

      ,  
         on : {  
           UNPAUSE:  pirmyn_nebemato ,
        }
      }
    

      pirmyn_mato: {

      ,  
         on : {  
           FORWARD_NO_SEE:  pirmyn_nebemato ,
           LINE_LOCK:  linija_uzrakinta ,
           PAUSE:  pauze ,
        }
      }
    

      pirmyn_nebemato: {

      ,  
         on : {  
           FORWARD_SEE:  pirmyn_mato ,
           LEFT_SEE:  kairen_mato ,
           LINE_LOCK:  linija_uzrakinta ,
           PAUSE:  pauze ,
           RIGHT_SEE:  desinen_mato ,
        }
      }
    

      pradine: {

      ,  
         on : {  
           FORWARD_SEE:  pirmyn_mato ,
           LEFT_SEE:  kairen_mato ,
           LINE_LOCK:  linija_uzrakinta ,
           PAUSE:  pauze ,
           RIGHT_SEE:  desinen_mato ,
        }
      }
    }
  }
}

