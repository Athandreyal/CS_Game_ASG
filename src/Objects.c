#include "Objects.h"
#include "raster.h"
#include "types.h"

UINT8 STICKMAN[] = {0xEF, 0xEF, 0x93, 0x6D, 0xEF, 0xD7, 0xBB, 0xBB};

/*bike orientations: N,E,S,W, ie, W = bike1[3], with third row being bike1[3][2], etc*/
UINT8 CYCLE1[4][8] = {	    {0x18, 0x18, 0x24, 0x24, 0x24, 0x5A, 0x42, 0x66},
							{0x00, 0xE0, 0x9C, 0x23, 0x23, 0x9C, 0xE0, 0x00},
							{0x66, 0x42, 0x5A, 0x24, 0x24, 0x24, 0x18, 0x18},
							{0x00, 0x07, 0x39, 0xC4, 0xC4, 0x39, 0x07, 0x00}
							};
						
UINT8 CYCLE2[4][8] =  {	    {0x18, 0x18, 0x24, 0x3C, 0x24, 0x5A, 0x5A, 0x66},
							{0x00, 0xE0, 0x9C, 0x6B, 0x6B, 0x9C, 0xE0, 0x00}, 
							{0x66, 0x5A, 0x5A, 0x24, 0x3C, 0x24, 0x18, 0x18},
							{0x00, 0x07, 0x39, 0xD6, 0xD6, 0x39, 0x07, 0x00}
							};

void drawBackground(UINT8* base){/*square corners, overwrites whatever it finds along border!*/
	UINT16* rebase = (UINT16*)base;
	int Vmin = 20;/*why can't I use #define values here??*/
	int Vmax = SCREEN_HEIGHT - 20;
	int Hmin = 80>>4;
	int Hmax = (SCREEN_WIDTH - 80) >> 4;
    int x,y;
	for(x = 0;x < 40;x++){
		for (y = 0;y < 400;y++){
            if (y < Vmin || y >= Vmax || x < Hmin || x >= Hmax)
                *(rebase + y * 40 + x) = 0xFFFF;
            }
        }
}
				
void drawLives(UINT8* base, int lives, int player){
    int i;
	for (i = 0;i < lives;i++){
        if (player)
            p_btmp_8(base, P2LIFEX + (i<<3),P2LIFEY, STICKMAN);
        else
            p_btmp_8(base, P1LIFEX + (i<<3),P1LIFEY, STICKMAN);
	}
}