#include <osbind.h>
#include "raster.h"
#include "Objects.h"
#include "TYPES.H"
#include "Renderer.h"
#include "Model.h"
#include <stdio.h>

int main()
{
    int x,y,i,j;
    Model model;
    Model* model_ptr = &model;
	UINT8 *base = Physbase();
    FILE *f = fopen("log.txt","w");
    
    
    if (f == NULL)
        exit(1);

    fprinf(f,"Address of model struct: %s",&model);
    fclose(f);

    
    clr_scrn(base);

    /*diagonal line */
    x = 80;
    y = 20;
    while( x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
        plot_pix(base, x++, y++);

    /*diagonal using p_h_ln*/
    x = 80;
    y = 20;
    while (x < 640){
        p_h_ln(base, x, y, 6);
        x += 5;
        y++;
    }    

    /*diagonal using p_v_ln*/
    x = 80;
    y = 20;
    while(y < 400){
        p_v_ln(base, x, y, 6);
        y += 5;
        x++;
    }
    
    /*slanted triangle using p_h_ln*/
    x = 110;
    y = 130;
    i = j = 0;
    for(;i < 80;i++){
        p_h_ln(base,x+i,y+i,1+j);/*over one, down one, one longer every other i*/
        j += i & 1;
        }

    /*player cycle printouts*/
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
    

    /*player life stickman printouts*/
    i = j = 0;
    x = 300;
    y = 240;
    while (j++<8)  /*black background*/
        p_h_ln(base,x,y+j,40);
    while(i<5)  /*stickman*/
        p_btmp_8(base,x+i++*8,y,STICKMAN);
        
    model.user.life = 5;
    model.program.life = 5;
    
/*    init(model_ptr);
/*    rndr_blk(base, &model);
/*    rndr_lif(base, 5, 0);
    rndr_lif(base, 5, 1);*/
	return 0;
}
