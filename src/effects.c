#include "effects.h"
#include "PSG.h"
#include <osbind.h>
#include "TYPES.H"
#include <stdio.h>

#define CHAN_A 0
#define CHAN_B 2
#define CHAN_C 4
#define A_LEVEL 8  /* lower 4 bits to control */
#define B_LEVEL 9  /* lower 4 bits to control */
#define C_LEVEL 10 /* lower 4 bits to control */
#define F_3 175
#define C_4 261
#define D_4 294
#define E_4 330
#define F_4 349
#define F_SHARP_4 370
#define G_4 392
#define G_SHARP_4 415
#define C_5 523
#define E_5 659
#define G_5 784
#define A_FLAT_5 831
#define A_5 880
#define B_5 988
#define C_6 1046
#define E_6 1319
#define B_6 1976
#define C_SHARP_6 1109

#define MIXER 7
#define NOISE 2
#define TONE 1
#define OFF 1
#define ON 0

/*
	siren for testing
	coinup for title screen menu selection
	derez for death

*/

void derez()
{
	UINT32 start = F_3;
	UINT32 end = B_6;
	UINT32 x = F_3;
	stop_sound();

	setEnvSt(C_LEVEL,1);
    setEnvlp(0x08, 500);
    setMix(CHAN_C,TONE,ON);


	while (x < end)
	{
		setEnvlp(0x08, 500);
		setNote(CHAN_C,x);
		setEnvlp(0x0A, 500);
   	 	setNote(CHAN_C,x);
   	 	
   	 	if(x>=1976)
   	 		break;

   	 	x++;
	}

	stop_sound();
}

void fail_music()
{

}

void success_music()
{
	stop_sound();

	setEnvSt(C_LEVEL,1);
    
    setMix(CHAN_C,TONE,ON);
   
  	setEnvlp(0x0A, 2500);
    setNote(CHAN_C,C_5);
    wait(1);

    setEnvlp(0x08, 10);
    setNote(CHAN_C,C_5);
    wait(1);
    
    setEnvlp(0x0A, 10);
 	setNote(CHAN_C,C_5);
    wait(1);

    setEnvlp(0x08, 10);
 	setNote(CHAN_C,C_5);
    wait(1);
	
	setEnvlp(0x0A, 10);
	/*setEnvlp(0x08, 10);*/
	setNote(CHAN_C,G_5);
    wait(1);
	
	setEnvlp(0x0C, 2500);

	setNote(CHAN_C,C_6);
    wait(1);

    setNote(CHAN_C,C_SHARP_6);
    wait(1);

    setNote(CHAN_C,A_FLAT_5);
    wait(1);
    
    setNote(CHAN_C,B_5);
    wait(1);
    setNote(CHAN_C,A_5);
    wait(1);
    setNote(CHAN_C,B_5);
    wait(1);
	
    setNote(CHAN_C,E_6);
    wait(3);
}

void siren()
{
	/*read & save psg state then initilize all to off */
	/*stretch goal above for now just play effects on channel c */
	stop_sound();
	setEnvSt(A_LEVEL,1);
    setEnvlp(0x00, 30000);
	setMix(CHAN_A,TONE,ON);

	setNote(CHAN_A,E_5);
	wait(3);

	setNote(CHAN_A,C_5);
	wait(3);
}