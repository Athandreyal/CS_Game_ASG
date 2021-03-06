/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    Primary game code, Main, doMode, getTime, onKey
*/

#include <osbind.h>
#include "PSG.h"
#include "TYPES.H"
#include "globals.h"
#include <stdio.h>
#include "isr.h"
#include "isr_asm.h"

/*Frequencies & volumes */
#define A_FINE 0
#define A_COURSE 1 /* lower 4 bits to control */
#define A_LEVEL 8  /* lower 4 bits to control */

#define B_FINE 2
#define B_COURSE 3 /* lower 4 bits to control */
#define B_LEVEL 9  /* lower 4 bits to control */

#define C_FINE 4
#define C_COURSE 5  /* lower 4 bits to control */
#define C_LEVEL 10 /* lower 4 bits to control */

#define NOISE_CHANNEL 6 /* lower 5 bits to control */
#define MIXER 7

#define ENV_PERIOD_FINE 11
#define ENV_PERIOD_COURSE 12

/* lower 4 bits to control */
#define ENV_SHAPE 13

#define IO_PORTA 14
#define IO_PORTB 15

#define TONE 1
#define NOISE 2

#define CHAN_A 0
#define CHAN_B 2
#define CHAN_C 4

#define OFF 0
#define ON 1

/*sketch out use in tron update cycle
UINT32 prevTime = 0;
UINT32 now;
UINT32 timeElapsed;
    
    
    
    new = getTime();
    timeElapsed = (now - prevTime);
    prev = now;
    updtMusc(timeElapsed);

*/
/*
///////////////////////////////////////////////////////////////////
// Function Name:  wait
// Purpose:        wait for x time using divisor a measure of accuracy
///////////////////////////////////////////////////////////////////
*/
void wait(UINT32 time,UINT32 divisor)
{
    UINT32 originalTime = 0;
    UINT32 elapsedTime = 0;
	Vector orig_vector28 = install_vector(TRAP_28,trap28_isr);  /*  VBL  */
    originalTime = ticks;

    while(ticks <= (originalTime + (divisor*time))){
		fprintf(f,"ticks: %5d  originalTime:  %5d  divisor: %2d  time: %5d   result: %5d\n",ticks,originalTime,divisor,time,(originalTime + (divisor*time)));
		fflush(f);
	}
	install_vector(TRAP_28,orig_vector28);
}
/*
///////////////////////////////////////////////////////////////////
// Function Name:  writePsg 
// Purpose:  write given value to given register
///////////////////////////////////////////////////////////////////
*/
void writePsg(UINT8 reg, UINT8 val)
{
    long old_ssp;
    volatile char *PSG_reg_select = 0xFF8800;
    volatile char *PSG_reg_write  = 0xFF8802;
	
    old_ssp = Super(0);
    *PSG_reg_select = reg;
    *PSG_reg_write  = val;
    
	Super(old_ssp);

}
/*
///////////////////////////////////////////////////////////////////
// Function Name:  AIChoice
// Purpose:  to read value from selected psg register
///////////////////////////////////////////////////////////////////
*/

UINT8 readPsg(UINT16 reg)
{
    long old_ssp = Super(0);
    volatile UINT16 *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_read  = 0xFF8802;
    UINT8 psgVal;
    
    
    *PSG_reg_select = (reg | 0x0300);
    
    if(reg == MIXER)
    {
        *PSG_reg_read  = 0xFF8800;
        psgVal = *PSG_reg_read;
    }
    else
    {
        psgVal = *PSG_reg_read;
    }

     Super(old_ssp);
     
    return psgVal;
}

/*
///////////////////////////////////////////////////////////////////
// Function Name: setNote
// Purpose:       takes channel and freq to set the a b or c channels to the given td vals to 
					produce the related sound.
///////////////////////////////////////////////////////////////////
*/

void setNote(UINT8 channel, UINT32 freq)/*, UINT8 volume)*/
{
    UINT16 TD = 0;
    UINT8 course;
    UINT8 cChannel;
    UINT8 vChannel;
    UINT8 fine;
	fprintf(f,"line 138 TD: %d\n",TD);
	fprintf(f,"line 139 freq: %ld\n",freq);    	fflush(f);
	TD = getTDVal(freq);
	fprintf(f,"line 141 set note: %5ld\n",freq);
    	fflush(f);
	fprintf(f,"line 143 set note hex: %4x\n",TD);
	fprintf(f,"line 144 set note dec: %d\n",TD);
	fflush(f);
  
    switch(channel){ 
        case A_FINE: cChannel = A_COURSE;
                     vChannel = A_LEVEL;
                     break;
        case B_FINE: cChannel = B_COURSE;
                     vChannel = B_LEVEL;
                     break;
        case C_FINE: cChannel = C_COURSE;
                     vChannel = C_LEVEL;
                     break;
    }
    
    fprintf(f,"cChannel: %i\n", cChannel);
    fprintf(f,"vChannel: %i\n", vChannel);
    
    fine = (TD & 0x00ff);
    course = (TD >> 8) & 0x0F;
    
    fprintf(f,"Course: %x\n",course );
    fprintf(f,"Fine: %x\n", fine);  
    
    /* fine tune (take lower 8 bits)*/
    writePsg(channel,fine);
    
    /* course tune (take lower 4 bits)*/
    writePsg(cChannel,course);
    
    /* Volume (take lower 4 bits)
    writePsg(vChannel,(volume & 0x0F));
    */
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  setEnvSt
// Purpose:       toggles the level control state in 5th bit of a b or c levels
///////////////////////////////////////////////////////////////////
*/

void setEnvSt(UINT8 levelChannel,UINT8 envState)
{
    UINT8 oldData = 0;
    UINT8 newState = 0;
    oldData = readPsg(levelChannel);
    /*newState= oldData & (~(1 << 4) | (envState << 4));
     writePsg(levelChannel, newState);*/
    writePsg(levelChannel, ((oldData & 0x00) | 0x10));
}


/*
///////////////////////////////////////////////////////////////////
// Function Name:  chngVol
// Purpose:     	changes or sets the volume to the given channel
///////////////////////////////////////////////////////////////////
*/
/* 
Change Volume 
0-1
1-3
2-5
3-7
4-9
5-11
6-13
7-15
8-17
9-19
10-21
11-23
12-25
13-27
14-29
15-31
*/
void chngVol(UINT8 channel, UINT8 volume)
{
        writePsg(channel, (volume & 0x0F));
}

/*
///////////////////////////////////////////////////////////////////
// Function Name: setMix
// Purpose:      Used to set and manipulated the mixer onOFF is the requested position for device 
// NOISE or TONE in any given channel a b or c.
///////////////////////////////////////////////////////////////////
*/
void setMix(int channel, UINT8 device, UINT8 onOFF) /*, UINT8 switch)*/
{
    UINT8 Setting = 0;
    UINT8 offset = 0;
    UINT8 psgVal = 0;
    UINT8 newPsgVal = 0;
    
    switch(device){ 
        case TONE: offset += 0;
                     break;
        case NOISE: offset += 3;
                     break;
    }
    switch(channel){ 
        case CHAN_A: offset += 0;
                     break;
        case CHAN_B: offset += 1;
                     break;
        /* channel c not turning noise off ?? why? */
        case CHAN_C: offset += 2;
                     break;
    }
    
    psgVal = readPsg(MIXER);

    newPsgVal = psgVal & (~(1 << offset) | (onOFF << offset));
    /*
    if(onOFF == ON)
         newPsgVal = psgVal & (0x01 << offset);
    else if(onOFF == OFF)
         newPsgVal = psgVal | (0x01 << offset);
*/
    writePsg(MIXER, newPsgVal);
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  AIChoice
// Purpose:        sets all registers to initial inactive values.
///////////////////////////////////////////////////////////////////
*/

void stop_sound()
{
    UINT8 blackout = 0x00;
    UINT8 whiteout = 0xFF;

    chngVol(CHAN_A,0);
    chngVol(CHAN_B,0);
    chngVol(CHAN_C,0);
 
    writePsg(A_FINE,blackout);
    writePsg(A_FINE,blackout);
    
    writePsg(B_FINE,blackout);
    writePsg(B_FINE,blackout);
    
    writePsg(C_FINE,blackout);
    writePsg(C_FINE,blackout);
    
    writePsg(NOISE_CHANNEL,blackout);
    
    writePsg(MIXER,whiteout);
    
    writePsg(A_LEVEL,blackout);
    writePsg(B_LEVEL,blackout);
    writePsg(B_LEVEL,blackout);
    
    writePsg(ENV_PERIOD_FINE,blackout);
    writePsg(ENV_PERIOD_COURSE,blackout);
    writePsg(ENV_SHAPE,blackout);
}
/*
///////////////////////////////////////////////////////////////////
// Function Name:  setNoise
// Purpose:        sets the noise to a given level within its range
///////////////////////////////////////////////////////////////////
*/
/*range 1 - 31*/
void setNoise(UINT8 freq)
{
    long old_ssp = Super(0);
    volatile char *PSG_reg_select = 0xFF8800;
    volatile char *PSG_reg_write  = 0xFF8802;

    *PSG_reg_select = NOISE_CHANNEL;
    *PSG_reg_write = (freq & 0x1F);
     Super(old_ssp);
}

/* max period 65535 min 1 

-0x0? (00xx) -Descent
-0x04 (01xx) -hitwDropoff
-0x08        -downSawtooth
-0x09        -Descent
-0x0A        -downSine
-0x0B        -dropdownTomax
-0x0C        -upsawtooth
-0x0D        -ascent
-0x0E        -upSine
-0x0F        -hitwDropoff
*/

/*
///////////////////////////////////////////////////////////////////
// Function Name:  setEnvlp
// Purpose:       sets the shape and period for the psg envelope generator.
///////////////////////////////////////////////////////////////////
*/
void setEnvlp(UINT8 shape, UINT16 period)
{
    UINT8 fine = 0;
    UINT8 course = 0;

    fine = period;
    course = (period >> 8);
    writePsg(ENV_PERIOD_FINE, fine);
    writePsg(ENV_PERIOD_COURSE, course);
    
    writePsg(ENV_SHAPE, (shape & 0x0F));    
}
/*
///////////////////////////////////////////////////////////////////
// Function Name:  getTDVal
// Purpose:     helper to calculate the td value (in the psg docs) from the requested frequency in setNote
///////////////////////////////////////////////////////////////////
*/
UINT16 getTDVal(UINT32 freq)
{
   /* assumption that clock speed is 2 MHz */
   UINT32 clckSpd = 125000;
   UINT16 TD = 0;
   TD = (UINT16)(clckSpd / freq);
   fprintf(f,"\n");
   
   
   fprintf(f,"GetTDVal output in DEC: %d\n", TD);
   fprintf(f,"GetTDVal output in HEX: %X\n", TD);
  
   return TD;
}

void tstSound()
{
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

    long old_ssp = Super(0);
    FILE *f = fopen("log.txt", "a");
    fprintf(f,"Test the fuck out of this shit\n");
    fclose(f);
    /*divide by 2 to go up an octave
multiply by 2 to go down
 Note      Period

  c        478 (c actual)
	27
  C        451
	25
  d        426
	24
  D        402
	23
  e        379
	21
  f        358
	20
  F        338
	19
  g        319
	18
  G        301
	17
  a        284
	16
  A        268
	15
  b        253
/*  Middle C (supposedly sounds rather sharp to me (this is using 488 input
    as provided by the TP =(f Master)/16fr) formula
    I did assume that clocke speed was 2MHz (2* 10^6) but that may not be
    entirely accurate */

    /* TODO: Obtain confirmation of psg Clock speed */    
    /* 478 as mid c potential(0xDE,0x01) checking + 13  491 (0xEB, 0x 01) c flat (or B) */
    *PSG_reg_select = 0;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 0xEB;
    
	*PSG_reg_select = 1;		/* set channel A coarse tune = 0 */
	*PSG_reg_write  = 0x01;


	/**PSG_reg_select = 7;		/* enable channel A on mixer 
	*PSG_reg_write  = 0x3E; */

	*PSG_reg_select = 8;		/* set channel A volume = 11 */
	*PSG_reg_write  = 3;

	while (!Cconis())		/* tone now playing, await key */
		;

	*PSG_reg_select = 8;		/* set channel A volume = 0 */
	*PSG_reg_write  = 0;

	Cnecin();
	Super(old_ssp);
}


