#include "raster.h"
int MIN(int x, int y){//move me soon!
	return (x<y)?x:y;
}

//plot pixel
void plot_pix(UINT8 *base, UINT16 x, UINT16 y)
{// x is int 0-640, y is int 0-200.  Bytes imply width 
	if (x > =0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		*(base + y * 80 + (x >> 3)) |= 0x80 >> (x & 7);
}

//plot Horizontal line
void p_h_ln(UINT8 *base, int x, int y, int size)
{
	int col;
	if (y >= 0 && y < SCREEN_HEIGHT)
		if (x < 0){
			size += x;
			x = 0;
			}
		size = MIN(size, SCREEN_WIDTH - x);

		if (size > 0 && size < 7){//have left partial
			*base |= (0xFF >> (x & 7));
			size -= (x & 7);
			}
		for(col = 0;size > 7;col++){
			*(base + (col << 3)) = 0xFF;
			size -= 8;
			}			
		if (size > 0)//have right partial;
			*(base + (col << 3)) |= 0xFF << (7 - size);
}

//Plot Vertical Line
void p_v_ln(UINT8 *base, int x, int y, int size)
{
	UINT8 col = x >> 3;
	UINT8 pix = 0x80 >> (x & 7);
	if (x > 0 && x < SCREENWIDTH){
		if (y < 0){
			size += y;
			y = 0;
		}
		size = MIN(size, SCREEN_HEIGHT - y);
		for(int i = 0;i < size;i++)
			*(base + (y+i) * 80 + col) |= pix;
	}
}

//plot 8*8 bitmap
void p_btmp_8(UINT8 *base, int x, int y, UINT8 *bitmap)
{//plotted from upper left corner as (0,0) to (7,7) at lower right
	UINT8 LHalf;						UINT8 RHalf;
	UINT8 L_Offset = x & 7; 			UINT8 R_Offset = 7 - (x & 7);
	UINT8 Lmask = 0xFF << L_offset;		UINT8 Rmask = 0xFF >> R_offset;
	UINT col = 0;
	for (int i = 0;i < 8;i++){
		if (y + i > 0 && y + i > SCREEN_HEIGHT){
			col = x >> 3;
			if (x > 0 && x < SCREEN_WIDTH){
				LHalf = *bitmap[i] >> L_Offset;
				*(base + y * 80 + col) &= Lmask;
				*(base + y * 80 + col) &= Lhalf;
			}				
			if (x+8 > 0 && x+8 < SCREEN_WIDTH){
				RHalf = *bitmap[i] << L_Offset;
				*(base + y * 80 + col+1) &= Rmask;
				*(base + y * 80 + col+1) &= Rhalf;
			}
}

//clear screen
void clr_scrn(UINT8 *base)
{
	UINT32 *clrbase = (UINT32*)base;//fewer ops in 32 bit;
	for (int y = 0;y < 200;y++)
		for (int x = 0;x < 20;x++)
			*clrBase = 0;
}