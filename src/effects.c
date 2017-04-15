/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    Primary game code, Main, doMode, getTime, onKey
*/

#include "effects.h"
#include "PSG.h"
#include <osbind.h>
#include "TYPES.H"
#include <stdio.h>
#include "globals.h"

#define CHAN_A 0
#define CHAN_B 2
#define CHAN_C 4
#define A_LEVEL 8  /* lower 4 bits to control */
#define B_LEVEL 9  /* lower 4 bits to control */
#define C_LEVEL 10 /* lower 4 bits to control */

#define D_2	73L

#define C_3	131L
#define D_3	147L
#define E_3	164L
#define F_3 175L
#define G_FLAT_3 185L
#define G_3	196L
#define G_SHARP_3 208l
#define A_3	220L
#define B_3 247L

#define C_4 261L
#define D_4 294L
#define E_4 330L
#define F_4 349L
#define F_SHARP_4 370L
#define G_FLAT_4 370L
#define G_4 392L
#define G_SHARP_4 415L
#define A_FLAT_4 415L
#define A_4	440L
#define B_FLAT_4 466L
#define B_4	494L

#define C_5 523L
#define C_SHARP_5 523L
#define D_FLAT_5 554L
#define D_5	587L
#define E_FLAT_5 622L
#define E_5 659L
#define G_5 784L
#define A_FLAT_5 831L
#define A_5 880L
#define B_5 988L

#define C_6 1046L
#define C_SHARP_6 1109L
#define E_6 1319L
#define B_6 1976L


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
/*
///////////////////////////////////////////////////////////////////
// Function Name:  derez
// Purpose:       derez sound for player or ai death
///////////////////////////////////////////////////////////////////
*/

void derez()
{
	UINT32 start = F_3;
	UINT32 end = B_6;
	UINT32 x = F_3;
/*	stop_sound();*/
	setEnvSt(C_LEVEL,1);
    setEnvlp(0x08, 500);
    setMix(CHAN_C,TONE,ON);

	while (x < end)
	{
		setEnvlp(0x08, 500);
		setNote(CHAN_C,x);
		
		setEnvlp(0x0A, 500);
   	 	setNote(CHAN_C,x);
   	 	
   	 	x += 50;
	}

	stop_sound();
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  fail_music
// Purpose:        fail music to play upon losing all hearts ai or player
///////////////////////////////////////////////////////////////////
*/

void fail_music()
{
	stop_sound();
	setEnvSt(C_LEVEL,1);
	setMix(CHAN_C,TONE,ON);
	
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(2,4);
	
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(2,4);
	
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(2,4);
	
	setEnvlp(0x00, 3500);
	setNote(CHAN_C,E_5);
	wait(5,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,B_4);
	wait(2,4);
	
	setEnvlp(0x00, 3500);
	setNote(CHAN_C,E_FLAT_5);
	wait(5,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,B_4);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,B_4);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_5);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_FLAT_5);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,C_5);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,B_4);
	wait(9,4);
	
	
	
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_5);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_FLAT_5);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,C_5);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,B_4);
	wait(4,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,C_5);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,C_SHARP_5);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,C_5);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,B_4);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,B_FLAT_4);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,A_4);
	wait(2,4);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,A_FLAT_4);
	wait(2,4);
	
	setEnvlp(0x00, 8000);
	setNote(CHAN_C,G_4);
	wait(7,8);
	
	/*
	fprintf(f,"fail_music 125\n");fflush(f);
	setEnvlp(0x00, 3500);
	setNote(CHAN_C,E_5);
	wait(1,8);
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_5);
	wait(3,4);
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 7000);
	setNote(CHAN_C,C_5);
	wait(4,4);
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,E_4);
	wait(3,4);
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_4);
	wait(3,4);
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 7000);
	setNote(CHAN_C,C_4);
	wait(4,4);
	
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,B_4);
	wait(3,8);
	
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,E_4);
	wait(3,4);
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_4);
	wait(3,4);
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,C_4);
	wait(3,4);
	/*	
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,B_4);
	wait(3,8);
	
	fprintf(f,"fail_music 135\n");fflush(f);
	setEnvlp(0x00, 3500);
	setNote(CHAN_C,E_FLAT_5);
	wait(1,8);
	
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(2,8);
	
	setEnvlp(0x00, 3500);
	setNote(CHAN_C,E_FLAT_5);
	wait(2,8);
	
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,A_4);
	wait(1,8);
	
	setEnvlp(0x00, 3500);
	setNote(CHAN_C,E_FLAT_5);
	wait(2,8);
	
	fprintf(f,"fail_music 152\n");fflush(f);
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(2,8);
	
	fprintf(f,"fail_music 157\n");fflush(f);
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(1,8);
	
	fprintf(f,"fail_music 162\n");fflush(f);
	setEnvlp(0x00, 4000);
	setNote(CHAN_C,F_3);
	wait(3,8);
	
	fprintf(f,"fail_music 167\n");fflush(f);
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(1,8);
	
	fprintf(f,"fail_music 172\n");fflush(f);
	setEnvlp(0x00, 4000);
	setNote(CHAN_C,F_3);
	wait(1,8);
	
	fprintf(f,"fail_music 177\n");fflush(f);
	setEnvlp(0x00, 4000);
	setNote(CHAN_C,E_3);
	wait(1,8);
	
	fprintf(f,"fail_music 182\n");fflush(f);
	setEnvlp(0x00, 4000);
	setNote(CHAN_C,D_2);
	wait(2,8);	
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,E_4);
	wait(3,4);
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_4);
	wait(3,4);
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 7000);
	setNote(CHAN_C,C_4);
	wait(4,4);
	
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,B_4);
	wait(3,8);
	
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,E_4);
	wait(3,4);
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_4);
	wait(3,4);
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,C_4);
	wait(3,4);
	
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,E_4);
	wait(3,4);
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_4);
	wait(3,4);
	
	
	fprintf(f,"fail_music 177\n");fflush(f);
	setEnvlp(0x00, 4000);
	setNote(CHAN_C,E_3);
	wait(1,8);
	fprintf(f,"fail_music 187\n");fflush(f);
	fprintf(f,"line 173 in effects setNote for D_3 : %ld\n", D_3);fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_3);
	wait(4,8);	
	
	fprintf(f,"fail_music 130\n");fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,B_4);
	wait(3,8);
	
	fprintf(f,"fail_music 135\n");fflush(f);
	setEnvlp(0x00, 3500);
	setNote(CHAN_C,E_FLAT_5);
	wait(1,8);
	
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(2,8);
	
	setEnvlp(0x00, 3500);
	setNote(CHAN_C,E_FLAT_5);
	wait(2,8);
	
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,A_4);
	wait(1,8);
	
	setEnvlp(0x00, 3500);
	setNote(CHAN_C,E_FLAT_5);
	wait(2,8);
	
	fprintf(f,"fail_music 152\n");fflush(f);
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(2,8);
	
	fprintf(f,"fail_music 157\n");fflush(f);
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(1,8);
	
	fprintf(f,"fail_music 162\n");fflush(f);
	setEnvlp(0x00, 4000);
	setNote(CHAN_C,F_3);
	wait(3,8);
	
	fprintf(f,"fail_music 167\n");fflush(f);
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(1,8);
	
	fprintf(f,"fail_music 172\n");fflush(f);
	setEnvlp(0x00, 4000);
	setNote(CHAN_C,F_3);
	wait(1,8);
	
	fprintf(f,"fail_music 177\n");fflush(f);
	setEnvlp(0x00, 4000);
	setNote(CHAN_C,E_3);
	wait(1,8);
	
	fprintf(f,"fail_music 182\n");fflush(f);
	setEnvlp(0x00, 4000);
	setNote(CHAN_C,D_2);
	wait(2,8);
	
	/*fprintf(f,"fail_music 187\n");fflush(f);
	fprintf(f,"line 173 in effects setNote for D_3 : %ld\n", D_3);fflush(f);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_3);
	wait(4,8);
	/*
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,B_4);
	wait(8,8);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,A_4);
	wait(8,8);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,E_3);
	wait(4,8);
	
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,D_3);
	wait(4,8);
	setEnvlp(0x00, 5000);
	setNote(CHAN_C,C_3);
	wait(4,8);
	*/
	
	/*
	Cnecin();
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,G_3);
	wait(1,8);
	Cnecin();
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(1,8);
	Cnecin();
	setEnvlp(0x00, 4000);
	setNote(CHAN_C,F_3);
	wait(3,8);
	*/

	/*	
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(1,8);
	
	setEnvlp(0x00, 3000);
	setNote(CHAN_C,A_4);
	wait(8,8);
	
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(1,8);
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(1,8);
	setEnvlp(0x00, 2500);
	setNote(CHAN_C,B_4);
	wait(1,8);
*/	
	stop_sound();
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  success_music
// Purpose:        play during player win
///////////////////////////////////////////////////////////////////
*/
void success_music()
{
	

	stop_sound();

	setEnvSt(C_LEVEL,1);
    
    setMix(CHAN_C,TONE,ON);
   
  	setEnvlp(0x0A, 2500);
    setNote(CHAN_C,C_5);
	
    wait(1,17);

    setEnvlp(0x08, 10);
    setNote(CHAN_C,C_5);
    wait(1,17);
    
    setEnvlp(0x0A, 10);
 	setNote(CHAN_C,C_5);
    wait(1,17);

    setEnvlp(0x08, 10);
 	setNote(CHAN_C,C_5);
    wait(1,17);
	
	setEnvlp(0x0A, 10);
	/*setEnvlp(0x08, 10);*/
	setNote(CHAN_C,G_5);
    wait(1,17);
	
	setEnvlp(0x0C, 2500);

	setNote(CHAN_C,C_6);
    wait(1,17);

    setNote(CHAN_C,C_SHARP_6);
    wait(1,17);

    setNote(CHAN_C,A_FLAT_5);
    wait(1,17);
    
    setNote(CHAN_C,B_5);
    wait(1,17);
    setNote(CHAN_C,A_5);
    wait(1,17);
    setNote(CHAN_C,B_5);
    wait(1,17);
	
    setNote(CHAN_C,E_6);
    wait(3,17);
	stop_sound();
 }

void siren()
{
	/*read & save psg state then initilize all to off */
	/*stretch goal above for now just play effects on channel c */
	stop_sound();
	setEnvSt(C_LEVEL,1);
    setEnvlp(0x00, 30000);
	setMix(CHAN_C,TONE,ON);

	setNote(CHAN_C,E_5);
	wait(3,17);

	setNote(CHAN_C,C_5);
	wait(3,17);
}