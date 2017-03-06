#include <osbind.h>
#include "raster.h"
#include "Objects.h"
#include "TYPES.H"

int main()
{
    int x,y,i,j;
	UINT8 *base = Physbase();
    clr_scrn(base);
    x = 80;
    y = 20;
    while( x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
        plot_pix(base, x++, y++);

    x = 80;
    y = 20;
    while (x < 640){
        p_h_ln(base, x, y, 6);
        x += 5;
        y++;
    }    
    x = 80;
    y = 20;
    while(y < 400){
        p_v_ln(base, x, y, 6);
        y += 5;
        x++;
    }
    x = 196;
    y = 100;
    for(j=0;j<4;j++){
        for(i = 0;i<8;i++){
            p_btmp_8(base, x+i,y+i*10,CYCLE1[j]);
            }
        x+=8;
        }
    for(j=0;j<4;j++){
        for(i = 0;i<8;i++){
            p_btmp_8(base, x+i,y+i*10,CYCLE2[j]);
            }
        x+=8;
        }
    
    i = j = 0;
    x = 300;
    y = 240;
    while (j++<8)
        p_h_ln(base,x,y+j,40);
    while(i<5){
        p_btmp_8(base,x+i++*8,y,STICKMAN);
        
    }
    
    drawBackground(base);
    drawLives(base, 5, 0);
    drawLives(base, 5, 1);
	return 0;
}
