/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    primary game test code. Has numerous stages of testing and rendering built in.
*/

#include <osbind.h>
#include "raster.h"
#include "Objects.h"
#include "TYPES.H"
#include "Renderer.h"
#include "Model.h"
#include "Events.h"
#include "Constant.h"        
#include <stdio.h>


/*
///////////////////////////////////////////////////////////////////
// Function Name:  main
// Purpose:        primary game test code. Has numerous stages of testing and rendering built in.
///////////////////////////////////////////////////////////////////
*/
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
    int direction[2] = {0,0};
    clr_scrn(base);

    /*diagonal line */
    x = 80;
    y = 20;
    while( x < SCREEN_WIDTH_PIX && y < SCREEN_HEIGHT_PIX)
        plot_pix(base, x++, y++);

    /*diagonal using p_h_ln*/
    x = 80;
    y = 20;
    while (x < SCREEN_WIDTH_PIX){
        p_h_ln(base, x, y, 6);
        x += 5;
        y++;
    }    

    /*diagonal using p_v_ln*/
    x = 80;
    y = 20;
    while(y < SCREEN_HEIGHT_PIX){
        p_v_ln(base, x, y, 6);
        y += 5;
        x++;
    }
    
    /*slanted triangle using p_h_ln*/
    x = 110;
    y = 130;
    i = j = 0;
    for(;i < SCREEN_WIDTH;i++){
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
    init(model_ptr);
    render(base, model_ptr);
    Cnecin();
    Vsync();
    clr_scrn(base); 

    init(model_ptr);
    matchStart(model_ptr);
    render(base, model_ptr);/*why no new placement?*/
    Cnecin();

    /*run to meeting at center*/
    for(i=0;i<40;i++){
        move(&(model_ptr->user.cycle));
        move(&(model_ptr->program.cycle));
        Vsync();
        rndr_fld(base, model_ptr);
        Vsync();
    }
    /*turn away */
    direction[0] = -1;
    chng_dir(&(model.user.cycle),   direction);
    chng_dir(&(model.program.cycle),direction);
    /*run a little*/
    chng_spd(&(model_ptr->user.cycle),   slow);
    chng_spd(&(model_ptr->program.cycle),fast);
    for(i=0;i<25;i++){
        move(&(model_ptr->user.cycle));
        move(&(model_ptr->program.cycle));
        Vsync();
        rndr_fld(base, model_ptr);
        Vsync();
    }
    chng_spd(&(model_ptr->user.cycle),   fast);
    chng_spd(&(model_ptr->program.cycle),slow);
    for(i=0;i<25;i++){
        move(&(model_ptr->user.cycle));
        move(&(model_ptr->program.cycle));
        Vsync();
        rndr_fld(base, model_ptr);
        Vsync();
    }
    chng_spd(&(model_ptr->user.cycle),   norm);
    chng_spd(&(model_ptr->program.cycle),norm);
    for(i=0;i<8;i++){
        move(&(model_ptr->user.cycle));
        move(&(model_ptr->program.cycle));
        Vsync();
        rndr_fld(base, model_ptr);
        Vsync();
    }
    direction[0] = 0;
    direction[1] = -1;
    chng_dir(&(model.user.cycle),   direction);
    direction[1] = 1;
    chng_dir(&(model.program.cycle),direction);
    for(i=0;i<20;i++){
        move(&(model_ptr->user.cycle));
        move(&(model_ptr->program.cycle));
        Vsync();
        rndr_fld(base, model_ptr);
        Vsync();
    }
    
    direction[0] = 1;
    direction[1] = 0;
    chng_dir(&(model.user.cycle),   direction);
    chng_dir(&(model.program.cycle),direction);
    for(i=0;i<20;i++){
        move(&(model_ptr->user.cycle));
        move(&(model_ptr->program.cycle));
        Vsync();
        rndr_fld(base, model_ptr);
        Vsync();
    }
    
    
	return 0;
}
