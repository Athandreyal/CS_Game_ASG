#include "PSG.h"
#include "effects.h"
#include <osbind.h>
#include "TYPES.H"
#include <stdio.h>

#define CHAN_A 0
#define CHAN_B 2
#define CHAN_C 4
#define A_LEVEL 8  /* lower 4 bits to control */
#define B_LEVEL 9  /* lower 4 bits to control */
#define C_LEVEL 10 /* lower 4 bits to control */
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
#define OFF 1
#define ON 0

int main()
{
    stop_sound();
    
   
       /* siren();*/
        /*success_music();*/
        derez();
 
        
    /* 
    setEnvSt(C_LEVEL,1);
    setEnvlp(0x00, 15625);
    setNote(CHAN_C,D_4);
    setMix(CHAN_C,TONE,ON);
   
    
    while (!Cconis())      /* tone now playing, await key 
        ;
     setNote(CHAN_C,D_4);
    setEnvlp(0x04, 15625);
    Cnecin();

    while (!Cconis())      /* tone now playing, await key 
        ;
     setNote(CHAN_C,D_4);
    setEnvlp(0x08, 15625);
    Cnecin();

    while (!Cconis())      /* tone now playing, await key 
        ;
     setNote(CHAN_C,D_4);
    setEnvlp(0x09, 15625);

    Cnecin();

    while (!Cconis())      /* tone now playing, await key 
        ;
     setNote(CHAN_C,D_4);
    setEnvlp(0x0A, 15625);
    Cnecin();

    while (!Cconis())      /* tone now playing, await key 
        ; 
    setNote(CHAN_C,D_4);
    setEnvlp(0x0B,15625);

    Cnecin();

    while (!Cconis())      /* tone now playing, await key 
        ; 
    setNote(CHAN_C,D_4);
    setEnvlp(0x0C,15625);

    Cnecin();

    while (!Cconis())      /* tone now playing, await key 
        ;
    setNote(CHAN_C,D_4);
    setEnvlp(0x0D,15625);

    Cnecin();

    while (!Cconis())      /* tone now playing, await key 
        ;
    setNote(CHAN_C,D_4);
    setEnvlp(0x0E,15625);

    Cnecin();

    while (!Cconis())      /* tone now playing, await key 
        ;
    setNote(CHAN_C,D_4);
    setEnvlp(0x0F,15625);
*
    Cnecin();
    while (!Cconis())      /* tone now playing, await key */
        ;

    Cnecin();
    
    stop_sound();

    return 0;
}
