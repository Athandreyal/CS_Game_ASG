#include <osbind.h>
#include "PSG.h"
#include <stdio.h>
/*Frequencies & volumes */

#define A 0
#define B 2
#define C 4
#define MID_C 261

int main()
{
   long old_ssp = Super(0);
   setNote(A,MID_C,5);
   
   while (!Cconis())		/* tone now playing, await key */
		;

   
   Cnecin();
	Super(old_ssp);
  /*   
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

	long old_ssp = Super(0);
   divide by 2 to go up an octave
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
    entirely accurate 

    /* TODO: Obtain confirmation of psg Clock speed    
    /* 478 as mid c potential(0xDE,0x01) checking + 13  491 (0xEB, 0x 01) c flat (or B) 
    *PSG_reg_select = 0;		/* set channel A fine tune = 248 
	*PSG_reg_write  = 0xEB;
    
	*PSG_reg_select = 1;		/* set channel A coarse tune = 0 
	*PSG_reg_write  = 0x01;


	/**PSG_reg_select = 7;		/* enable channel A on mixer 
	*PSG_reg_write  = 0x3E; 

	*PSG_reg_select = 8;		/* set channel A volume = 11 
	*PSG_reg_write  = 3;

	while (!Cconis())		/* tone now playing, await key 
		;

	*PSG_reg_select = 8;		/* set channel A volume = 0 
	*PSG_reg_write  = 0;

	Cnecin();
	Super(old_ssp);

    */
    	return 0;

}
