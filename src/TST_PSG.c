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
#define OFF 0
#define ON 1

int main()
{
    /*
    long old_ssp = Super(0);
    volatile char *PSG_reg_select = 0xFF8800;
    volatile char *PSG_reg_write  = 0xFF8802;
   ;
    */
     int x = 0;
  /*  
    setMix(CHAN_A, TONE);
    setMix(CHAN_B, TONE);
    setMix(CHAN_B, TONE);
 */ 
       
        while (!Cconis())       /* tone now playing, await key */
        {

           /* 

            *PSG_reg_select = MIXER;
            *PSG_reg_write = 0x07;

 noise channel
            *PSG_reg_select = 6;
            *PSG_reg_write = 0x00; */

            setNoise(0);
            setMix(CHAN_A,TONE,OFF);
            setMix(CHAN_B,TONE,OFF);
            setMix(CHAN_C,TONE,ON);
            setMix(CHAN_A,NOISE,OFF);
            setMix(CHAN_B,NOISE,OFF);
            setMix(CHAN_C,NOISE,OFF);
  
            setNote(CHAN_A,C_4,8);
  
            for(x = 0; x < 200000; x++)
            {
            }
            setNote(CHAN_A,C_4,0);

            setNote(CHAN_B,D_4,8);
            for(x = 0; x < 200000; x++)
            {
            }
            setNote(CHAN_B,D_4,0);

            setNote(CHAN_C,E_4,8);
            for(x = 0; x < 200000; x++)
            {
            }
            setNote(CHAN_C,E_4,0);
            
            /* Super(old_ssp);*/
        }


        /* stop_sound();*/



/*
   /* allmOn();*/
    setNoise(0); 
    setMix(CHAN_A,NOISE,OFF);
    setMix(CHAN_B,NOISE,OFF);
    setMix(CHAN_C,NOISE,OFF);

    setMix(CHAN_A,TONE,OFF);
    setMix(CHAN_B,TONE,OFF);
    setMix(CHAN_C,TONE,ON);
    
    setEnvlp(0x0A,15625);
    while (!Cconis())		/* tone now playing, await key */
		;
          
    setNote(CHAN_A,E_4,1);
    setNote(CHAN_B,F_4,2);

    setNote(CHAN_C,C_5,8);
    Cnecin();
    while (!Cconis())		/* tone now playing, await key */
		;
        
        /*  
    setNote(CHAN_A,F_4,8);
    setNote(CHAN_B,G_4,5);
     */ 
    setNote(CHAN_C,A_5,4);
    Cnecin();
    
    while (!Cconis())		/* tone now playing, await key */
		;
        /*  
    setNote(CHAN_A,E_4,0);
    setNote(CHAN_B,F_4,0);
     */  
    setNote(CHAN_C,C_5,0);
    for(x = 0; x < 500; x++)
    {
    }
    /*  
    setNote(CHAN_A,F_4,8);
    setNote(CHAN_B,G_4,5);
     */ 
    setNote(CHAN_C,A_5,4);
    Cnecin();

    while (!Cconis())		/* tone now playing, await key */
		;
        /*  
    setNote(CHAN_A,F_4,8);
    setNote(CHAN_B,G_4,5);
     */ 
    setNote(CHAN_C,C_6,4);
    Cnecin();    

    while (!Cconis())		/* tone now playing, await key */
		;
        /*  
    setNote(CHAN_A,F_SHARP_4,8);
    setNote(CHAN_B,G_4,5);
     */ 
    setNote(CHAN_C,C_SHARP_6,32);
    Cnecin(); 

    while (!Cconis())		/* tone now playing, await key */
		;
        /*  
    setNote(CHAN_A,F_SHARP_4,8);
    setNote(CHAN_B,G_4,5);
     */ 
    setNote(CHAN_C,A_FLAT_5,32);
    Cnecin();     

    while (!Cconis())		/* tone now playing, await key */
		;
    stop_sound();
 /*
    setNote(CHAN_A,E_4,0);
    setNote(CHAN_B,F_4,0); 
     */ 
    setNote(CHAN_C,C_5,0);

    Cnecin();
 /*  Super(old_ssp); */
    /*getTDVal(261);
    tstSound();*/

    return 0;
}
