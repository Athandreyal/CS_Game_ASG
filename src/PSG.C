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

/*sketch out use in tron update cycle
UINT32 prevTime = 0;
UINT32 now;
UINT32 timeElapsed;
    
    
    
    new = getTime();
    timeElapsed = (now - prevTime);
    prev = now;
    updtMusc(timeElapsed);

*/
UINT8 readPsg(UINT16 reg)
{
    long old_ssp = Super(0);
    volatile UINT16 *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_read  = 0xFF8802;
    UINT8 psgVal;
    
    
    *PSG_reg_select = (reg | 0x0300);
     psgVal = *PSG_reg_read;
    
     Super(old_ssp);
     
    return psgVal;
}

/* max period 65535 min 1 */
void setEnvlp(UINT8 shape, UINT16 period)
{
    UINT8 fine = period;
    UINT8 course = (period >> 8);
    writePsg(ENV_PERIOD_FINE, fine);
    writePsg(ENV_PERIOD_COURSE, course);
    
    writePsg(ENV_SHAPE, (shape & 0x0F));
    
}
/* Change Volume */
void chngVol(UINT8 channel, UINT8 volume)
{
    writePsg(vChannel, (volume & 0x0F));
}

void allmOn()
{
    
     writePsg(MIXER, 0xC0 );
}
void setMix(int channel, UINT8 device)
{
    UINT8 Setting;
    UINT8 offset;
    UINT8 psgVal;
    UINT8 newPsgVal;
    
    switch(device){ 
        case TONE: offset += 0;
                     break;
        case NOISE: offset += 3;
                     break;
    }
    switch(channel){ 
        case A_FINE: offset += 0;
                     break;
        case B_FINE: offset += 1;
                     break;
        case C_FINE: offset += 2;
                     break;
    }
    
    psgVal = readPsg(MIXER);
    newPsgVal = psgVal | (0x01 << offset);
    writePsg(MIXER, newPsgVal);
}

void stop_sound()
{
    UINT8 blackout = 0x00;
    chngVol(CHAN_A,0);
    chngVol(CHAN_B,0);
    chngVol(CHAN_C,0);
  /*
    writePsg(A_FINE,blackout);
    writePsg(A_FINE,blackout);
    
    writePsg(B_FINE,blackout);
    writePsg(B_FINE,blackout);
    
    writePsg(C_FINE,blackout);
    writePsg(C_FINE,blackout);
    
    writePsg(NOISE_CHANNEL,blackout);
    
    writePsg(MIXER,blackout);
    
    writePsg(A_LEVEL,blackout);
    writePsg(B_LEVEL,blackout);
    writePsg(B_LEVEL,blackout);
    
    writePsg(ENV_PERIOD_FINE,blackout);
    writePsg(ENV_PERIOD_COURSE,blackout);
    writePsg(ENV_SHAPE,blackout);
    */
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

void setNoise(UINT8 freq)
{
    long old_ssp = Super(0);
    volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;
    
    /* need to change to xor 0 is out put 1 is off */
    *PSG_reg_select = NOISE_CHANNEL;
    *PSG_reg_write = (freq & 0x1F);
     Super(old_ssp);
}

void setNote(UINT8 channel, UINT32 freq, UINT8 volume)
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
    
    /* Volume (take lower 4 bits)*/
    writePsg(vChannel,(volume & 0x0F));
   /* fprintf(f,readPsg(cChannel));*/
    
    fclose(f);
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
*/


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


