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
#define G_4 392


#define C_5 523
int main()
{
    setNoise(0);
    setNote(CHAN_A,E_4,8);
    setNote(CHAN_B,F_4,5);
    setNote(CHAN_C,C_5,4);
    setNoise(5);
    while (!Cconis())		/* tone now playing, await key */
		;
        
    setNote(CHAN_A,E_4,0);
    setNote(CHAN_B,F_4,0); 
    setNote(CHAN_C,C_5,0);

    Cnecin();
 /*  Super(old_ssp); */
    /*getTDVal(261);
    tstSound();*/

    return 0;
}
