#include "PSG.h"
#include <osbind.h>
#include "TYPES.H"
#include <stdio.h>

#define CHAN_A 0
#define CHAN_B 2
#define CHAN_C 4
#define C_4 261
#define D_4 294
#define E_4 330
#define F_4 349
#define F_SHARP_4 370
#define G_4 392
#define G_SHARP_4 415
#define C_5 523
#define G_5 784
#define A_FLAT_5 831
#define A_5 880
#define C_6 1046
#define C_SHARP_6 1109

#define MIXER 7
#define NOISE 2
#define TONE 1


int main()
{
  /*  
    setMix(CHAN_A, TONE);
    setMix(CHAN_B, TONE);
    setMix(CHAN_B, TONE);
 */ 
    UINT32 x;
   /* allmOn();*/
    setNoise(0); 
    setEnvlp(0x0F,15625);
    while (!Cconis())		/* tone now playing, await key */
		;
    setNote(CHAN_A,E_4,8);
    setNote(CHAN_B,F_4,5);
    setNote(CHAN_C,C_5,4);
    Cnecin();
    while (!Cconis())		/* tone now playing, await key */
		;
    setNote(CHAN_A,F_4,8);
    setNote(CHAN_B,G_4,5);
    setNote(CHAN_C,A_5,4);
    Cnecin();
    
    while (!Cconis())		/* tone now playing, await key */
		;
    setNote(CHAN_A,E_4,0);
    setNote(CHAN_B,F_4,0); 
    setNote(CHAN_C,C_5,0);
    for(x = 0; x < 500; x++)
    {
    }
    setNote(CHAN_A,F_4,8);
    setNote(CHAN_B,G_4,5);
    setNote(CHAN_C,A_5,4);
    Cnecin();

    while (!Cconis())		/* tone now playing, await key */
		;
    setNote(CHAN_A,F_4,8);
    setNote(CHAN_B,G_4,5);
    setNote(CHAN_C,C_6,4);
    Cnecin();    

    while (!Cconis())		/* tone now playing, await key */
		;
    setNote(CHAN_A,F_SHARP_4,8);
    setNote(CHAN_B,G_4,5);
    setNote(CHAN_C,C_SHARP_6,4);
    Cnecin(); 

    while (!Cconis())		/* tone now playing, await key */
		;
    setNote(CHAN_A,F_SHARP_4,8);
    setNote(CHAN_B,G_4,5);
    setNote(CHAN_C,A_FLAT_5,4);
    Cnecin();     

    while (!Cconis())		/* tone now playing, await key */
		;
    
    stop_sound();
 /*
    setNote(CHAN_A,E_4,0);
    setNote(CHAN_B,F_4,0); 
    setNote(CHAN_C,C_5,0);
*/
    Cnecin();
 /*  Super(old_ssp); */
    /*getTDVal(261);
    tstSound();*/

    return 0;
}
