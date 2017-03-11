#include <osbind.h>
#include "raster.h"
#include "Objects.h"
#include "TYPES.H"
#include "Renderer.h"
#include "Model.h"
#include "Events.h"
        
/*#include <stdio.h>*/


int main()
{
    int x,y,i,j,k;
/*    struct Cycle2 cycle2;/* = {
                            1,
                            1,
                            1};
*/  Model model;
    Model* model_ptr = &model;
	UINT8 *base = Physbase();
/*    FILE *f = fopen("log.txt","w");
    fclose(f);*/
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
    for (k=0;k<5;k++){ /*ITERATE CYCLE SET
        /*DRAW CYCLE SET*/
        x = 196;
        y = 100;
        Vsync();
        for(j=1;j<5;j++){
            for(i = 0;i<8;i++){
                p_btmp_8(base, x+i,y+i*10,CYCLE1[(j+k)%4]);
                }
            x+=8;
            }
        for(j=1;j<5;j++){
            for(i = 0;i<8;i++){
                p_btmp_8(base, x+i,y+i*10,CYCLE2[(j+k)%4]);
                }
            x+=8;
            }
        Cnecin();
        /*UNDRAW CYCLE SET*/
        x = 196;
        y = 100;
        Vsync();
        for(j=1;j<5;j++){
            for(i = 0;i<8;i++){
                p_btmp_8(base, x+i,y+i*10,CYCLE1[(j+k)%4]);
                }
            x+=8;
            }
        for(j=1;j<5;j++){
            for(i = 0;i<8;i++){
                p_btmp_8(base, x+i,y+i*10,CYCLE2[(j+k)%4]);
                }
            x+=8;
            }    
        }

    /*player life stickman printouts*/
    x = 300;
    y = 240;
    for(i=0;i<5;i++){/*stickman*/
        p_btmp_8(base,x,y,STICKMAN);
        x+=8;
    }
    render(base, model_ptr);
    Cnecin();
    Vsync();
    clr_scrn(base); 
    
/*    f = fopen("log.txt", "a");
    fprintf(f,"87 clear screen\n");*/
    
    init(model_ptr);
    matchStart(model_ptr);
/*    fprintf(f,"user:%d    program:%d\n",model.user.isUser,model.program.isUser);
*/    render(base, model_ptr);/*why no new placement?*/
    Cnecin();
    
    for(i=0;i<50;i++){
/*        clr_scrn(base); */
/*        fprintf(f,"\n--");*/
        move(&(model_ptr->user.cycle));
        move(&(model_ptr->program.cycle));
        Vsync();
        rndr_fld(base, model_ptr);/*why no new placement?*/
        Vsync();
    }
/*    fclose(f);*/

    
	return 0;
}
