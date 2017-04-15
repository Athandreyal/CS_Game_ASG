/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    Primary game code, Main, doMode, getTime, onKey
*/

#include <osbind.h>
#include "music.h"
#include "isr.h"
#include "isr_asm.h"
#include "globals.h"
#include "psg.h"

#define CHAN_A 0
#define CHAN_B 2
#define CHAN_C 4
#define A_LEVEL 8  /* lower 4 bits to control */
#define B_LEVEL 9  /* lower 4 bits to control */
#define C_LEVEL 10 /* lower 4 bits to control */

#define D_2	73L
#define G_2	98L
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



void start_music()
{
	/*start opening song*/
}

void update_title_music(UINT32 time_elapsed)
{
	static UINT32 runningTime = 0;

}

void update_game_music(UINT32 time_elapsed)
{
	static UINT32 runningTime = 0;
	static prevTime = 0
	
	setEnvSt(A_LEVEL,1);
	setEnvSt(B_LEVEL,1);
	setMix(CHAN_A,TONE,ON);
	setMix(CHAN_B,TONE,ON);
	
	 setEnvlp(0x00, 5000);
		
	
	if(ticks % 210 == 0)
	{
	/*setEnvlp(0x00, 5000);*/
	setNote(CHAN_A,C_3);
	}
	else if (ticks % 200 == 0)
	{
	/* setEnvlp(0x0A, 10000);*/
	 setNote(CHAN_A,E_3);
	}
	else if (ticks % 280 == 0)
	{
	/*	setEnvlp(0x0D,30000);*/
	 setNote(CHAN_B,G_2);
	}
	else if (ticks == 350)
	{
	/*setEnvlp(0x00, 5000);*/
	setNote(CHAN_A,D_2);
	}
	
}

void update_music()
{
	UINT8 channels[350];
	UINT32 freq[350];
	UINT8 shape[350];
	UINT16 period[350];
	UINT32 currentTick = ticks;
	
	fprintf(f,"line 88 music ticks: %5ld\n",ticks);
	fflush(f);
	
	channels[0] = CHAN_A;
	freq[0] = C_4;
	shape[0] = 0x00;
	period[0] = 15000;
	/*
	fprintf(f,"line 96 music ticks: %5ld\n",ticks);
	fflush(f);
	
	channels[69] = CHAN_A;
	freq[69] = C_4;
	shape[69] = 0x00;
	period[69] = 15000;
	
	fprintf(f,"line 104 music ticks: %5ld\n",ticks);
	fflush(f);
	
	channels[209] = CHAN_A;
	freq[209] = C_4;
	shape[209] = 0x00;
	period[209] = 15000;
	*/
	fprintf(f,"line 112 music: %5ld\n",ticks);
	fflush(f);
	
	fprintf(f,"line 115 music channels: %5ld\n",channels[ticks]);
	fprintf(f,"line 116 music freq: %5ld\n",freq[ticks]);
	fprintf(f,"line 117 music shape: %5ld\n",shape[ticks]);
	fprintf(f,"line 118 music period: %5ld\n",period[ticks]);
	
	
	setEnvSt(A_LEVEL,1);
	setEnvSt(B_LEVEL,1);
	setMix(CHAN_A,TONE,ON);
	setMix(CHAN_B,TONE,ON);
    
	setEnvlp(shape[currentTick], period[currentTick]);
	setNote(channels[currentTick],freq[currentTick]);
}

void update_close_music(UINT32 time_elapsed)
{
	static UINT32 runningTime = 0;

}