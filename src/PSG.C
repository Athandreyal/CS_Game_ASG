#include <osbind.h>
#include "PSG.h"
#include "TYPES.H"

/*Frequencies & volumes */
#define A_FINE 0
#define A_COURSE 1 /* lower 4 bits to control */
#define A_LEVEL 8  /* lower 4 bits to control */

#define B_FINE 2
#define B_COURSE 3 /* lower 4 bits to control */
#define B_LEVEL 9  /* lower 4 bits to control */

#define C_FINE 4
#define C_COURSE   /* lower 4 bits to control */
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



void playSound(UINT8 Channel, UINT8 envOnOFF, UINT8 noiseOnOff, UINT32 noteFreq, UINT8 envShape, UINT16 envPeriod, UINT8 volume, UINT32 time)
{

}
*/

/*
///////////////////////////////////////////////////////////////////
// Function Name:  getTime
// Purpose:        access the system timer to onbtaint and return the current time
// Outputs:        lont timeNow:  the current timer value;
///////////////////////////////////////////////////////////////////
*/
UINT32 getTime(){
    long *timer = (long*)0x462;
    long old_ssp = Super(0);
    UINT32 timeNow;
    timeNow = (UINT32)*timer;
    Super(old_ssp);
    return timeNow;
}

void wait(UINT32 time)
{
    UINT32 originalTime = 0;
    UINT32 divisor = 17;
    UINT32 elapsedTime = 0;

    originalTime = getTime();

    while(getTime() <= (originalTime + (divisor*time)))
        ;
}

void writePsg(UINT8 reg, UINT8 val)
{
    long old_ssp = Super(0);
    volatile char *PSG_reg_select = 0xFF8800;
    volatile char *PSG_reg_write  = 0xFF8802;
    
    *PSG_reg_select = reg;
    *PSG_reg_write  = val;
    
     Super(old_ssp);
}

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

void setNote(UINT8 channel, UINT32 freq)/*, UINT8 volume)*/
{
    UINT16 TD = getTDVal(freq);
    UINT8 course;
    UINT8 cChannel;
    UINT8 vChannel;
    UINT8 fine;
    
 
    FILE *f = fopen("log.txt", "a");
     fprintf(f,"Set note TD Val: %i\n",TD); 
     fprintf(f,"Channel before switch: %i\n",channel); 
 
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
    
    fine = TD;
    course = (TD >> 8) & 0x0F;
    
    fprintf(f,"Course: %i\n",course );
    fprintf(f,"Fine: %i\n", fine);  
    
    /* fine tune (take lower 8 bits)*/
    writePsg(channel,fine);
    
    /* course tune (take lower 4 bits)*/
    writePsg(cChannel,course);
    
    /* Volume (take lower 4 bits)
    writePsg(vChannel,(volume & 0x0F));
    */
    fclose(f);
}

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

void allmOn()
{
    
     writePsg(MIXER, 0xC0 );
}

UINT16 getTDVal(UINT32 freq)
{
   /* assumption that clock speed is 2 MHz */
   UINT32 clckSpd = 2000000;
   UINT16 TD = 0;
   FILE *f = fopen("log.txt", "a");
   TD = (clckSpd / (16*freq));
   fprintf(f,"\n");
   
   fprintf(f,"GetTDVal output in DEC: %i\n", TD);
   fprintf(f,"GetTDVal output in HEX: %X\n", TD);
   fclose(f);
  
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


