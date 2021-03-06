/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    Primary game code, Main, doMode, getTime, onKey
*/

#include "PSG.h"
#include "effects.h"
#include <osbind.h>
#include "TYPES.H"
#include <stdio.h>
#include "globals.h"
#include "music.h"
#include "isr.h"
#include "isr_asm.h"


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
	Vector orig_vector28 = install_vector(TRAP_28,trap28_isr);  /*  VBL  */
    stop_sound();
    f = fopen("log.txt","w");
	fclose(f);
	f = fopen("log.txt","a");
	
	
   
       /* siren();*/
       /* fail_music();
		start_music();*/
	while (!Cconis())
	{
	update_game_music(2);
	/*update_music();*/
	}
	/*success_music();	*/
    install_vector(TRAP_28,orig_vector28);    
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
    fclose(f);
    stop_sound();

    return 0;
}
