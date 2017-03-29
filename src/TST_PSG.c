#include "PSG.h"
#include <osbind.h>
#include "TYPES.H"
#include <stdio.h>

#define CHAN_A 0
#define C_NOTE
int main()
{
    setNote(CHAN_A,C_NOTE,5);
    while (!Cconis())		/* tone now playing, await key */
		;

    Cnecin();
    
    /*getTDVal(261);
    tstSound();*/

    return 0;
}
