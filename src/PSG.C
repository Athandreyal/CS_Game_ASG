#include <osbind.h>
#include <stdio.h>
#include "PSG.h"

#define A_FINE 0
#define A_COURSE 1 /* lower 4 bits to control */
#define A_LEVEL 8  /* lower 4 bits to control */

#define B_FINE 2
#define B_COURSE 3 /* lower 4 bits to control */
#define B_LEVEL 9  /* lower 4 bits to control */

#define C_FINE 4
#define C_COURSE 5 /* lower 4 bits to control */
#define C_LEVEL 10 /* lower 4 bits to control */

#define NOISE_FREQ 6 /* lower 5 bits to control */

#define ENV_FREQ_FINE 11
#define ENV_FREQ_COURSE 12

/* lower 4 bits to control */
#define ENV_SHAPE 13

#define IO_PORTA 14
#define IO_PORTB 15


void testSound()
{
    volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

	long old_ssp = Super(0);
 
    *PSG_reg_select = 0;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 0xEB;
    
	*PSG_reg_select = 1;		/* set channel A coarse tune = 0 */
	*PSG_reg_write  = 0x01;


	/*PSG_reg_select = 7;		/* enable channel A on mixer 
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


void setNote(UINT8 channel, UINT32 freq, UINT8 volume)
{
    UINT16 TD = getTDVal(freq);
    UINT8 course;
    UINT8 cChannel;
    UINT8 vChannel;
    UINT8 fine;
    
    volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;
    FILE *f = fopen("log.txt", "w");
 
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
    
    fprintf(f,"TD %i\n",TD); 
    
    fine = TD;
    course = (TD >> 8) & 0x0F;
    
    fprintf(f,"Course: %i\n",course );
    fprintf(f,"Fine: %i\n", fine);  
    
    /* fine tune (take lower 8 bits)*/
    *PSG_reg_select = channel;
    *PSG_reg_write  = fine;
    
    /* course tune (take lower 4 bits)*/
    *PSG_reg_select = cChannel;
    *PSG_reg_write  = course;
    
    /* Volume (take lower 4 bits)*/
    *PSG_reg_select = vChannel;
    *PSG_reg_write  = (volume & 0x0F);   
    fclose(f);
}

UINT16 getTDVal(UINT32 freq)
{
   /* assumption that clock speed is 2 MHz */
   UINT32 clckSpd = 2000000;
   UINT16 TD = 0;
   TD = (clckSpd / (16*freq));

   FILE *f = fopen("log.txt", "a");
   fprintf(f,"GetTDVal output: %X\n", TD);
   fclose(f);
  
   return TD;
}

