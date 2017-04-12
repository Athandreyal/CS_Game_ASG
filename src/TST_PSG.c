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
#define OFF 1
#define ON 0

int main()
{
    stop_sound();
    setMix(CHAN_C,TONE,ON);
    setNote(CHAN_C,D_4,8);

    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_C,C_4,8);
        setNote(CHAN_C,E_4,8);
        setNote(CHAN_C,G_4,8);
    }
     Cnecin();
    setMix(CHAN_C,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_C,E_4,1);
        setNote(CHAN_C,F_4,2);
        setNote(CHAN_C,C_5,8);
    }
     Cnecin();
    setMix(CHAN_C,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_C,F_4,8);
        setNote(CHAN_C,G_4,5);
        setNote(CHAN_C,A_5,4);
    }
    Cnecin();

    setMix(CHAN_C,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_C,F_4,8);
        setNote(CHAN_C,G_4,5);
        setNote(CHAN_C,C_6,4);
    }
    Cnecin();

    setMix(CHAN_C,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_C,F_SHARP_4,8);
        setNote(CHAN_C,G_4,5);
        setNote(CHAN_C,C_SHARP_6,32);
    }
    Cnecin();

    setMix(CHAN_C,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_C,F_SHARP_4,8);
        setNote(CHAN_C,G_4,5);
        setNote(CHAN_C,A_FLAT_5,32);
    }
    Cnecin();

    setMix(CHAN_C,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_C,E_4,8);
        setNote(CHAN_C,F_4,8); 
        setNote(CHAN_C,C_5,8);
    }
    Cnecin();

    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_A,C_4,8);
        setNote(CHAN_B,E_4,8);
        setNote(CHAN_C,G_4,8);
    }
     Cnecin();
    setMix(CHAN_C,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_A,E_4,1);
        setNote(CHAN_B,F_4,2);
        setNote(CHAN_C,C_5,8);
    }
     Cnecin();
    setMix(CHAN_C,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_A,F_4,8);
        setNote(CHAN_B,G_4,5);
        setNote(CHAN_C,A_5,4);
    }
    Cnecin();

    setMix(CHAN_C,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_A,F_4,8);
        setNote(CHAN_B,G_4,5);
        setNote(CHAN_C,C_6,4);
    }
    Cnecin();

    setMix(CHAN_C,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_A,F_SHARP_4,8);
        setNote(CHAN_B,G_4,5);
        setNote(CHAN_C,C_SHARP_6,32);
    }
    Cnecin();

    setMix(CHAN_C,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_A,F_SHARP_4,8);
        setNote(CHAN_B,G_4,5);
        setNote(CHAN_C,A_FLAT_5,32);
    }
    Cnecin();

    setMix(CHAN_C,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    while (!Cconis())      /* tone now playing, await key */
    {
        setNote(CHAN_A,E_4,8);
        setNote(CHAN_B,F_4,8); 
        setNote(CHAN_C,C_5,8);
    }
    Cnecin();

    
    stop_sound();

    return 0;
}
