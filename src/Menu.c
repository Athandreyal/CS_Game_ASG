#include "menu.h"
#include "types.h"
#include "Objects.h"
#include "constant.h"
#include "raster.h"
#include "mSetScrn.h"
#include <OSBind.h>
#include "model.h"
#include <stdio.h>
#include "tron.h"
#include "isr_asm.h"
#include "globals.h"

#define UARW_KEY  0x48
#define DARW_KEY  0x50
#define Q_KEY     0x01
#define ESC_KEY   0x01
#define ONE_KEY   0x02
#define TWO_KEY   0x03
#define ENT_KEY   0x1C

bool menuLoop(bool *buffer, UINT8 *base0, UINT8 *base1){
    bool quit = false;
    UINT8 key;
    bool LRMouse = false;
    do{
        key = 0;
        if(keyWaiting || mouseKeys)
        {
            if (keyWaiting){
                getKey(&key);
                quit = ((key == ESC_KEY) || (key == ENT_KEY)) && (model.mode == 0);
                }
            else{
                LRMouse = mouseKeys & 3;
                if (LRMouse){
                    quit = false;
                    if      (mouse_x > 240 && mouse_x < 515 && mouse_y > 208 && mouse_y < 240)
                    {
                        setMenuChoice(ONE_KEY);
                        key = ENT_KEY;
                    }
                    else if (mouse_x > 240 && mouse_x < 535 && mouse_y > 248 && mouse_y < 275)
                    {
                        setMenuChoice(TWO_KEY);
                        key = ENT_KEY;
                    }
                    else if (mouse_x > 240 && mouse_x < 420 && mouse_y > 285 && mouse_y < 315)
                    {
                        setMenuChoice(ESC_KEY);
                        key = ENT_KEY;
                        quit = true;
                    }
                }
            }
            if (!quit){
                setMenuChoice(key);
            }
        }
        if(rndrRqst)
        {
            fst_blk(base);
            plotSplsh(SPLASH);
            renderMouse();
            renderSplashChoice();/*render to current, mode 1, mode2 1*/
            toggleScreen(buffer, base0, base1);/*switch to buffer 0*/
            rndrRqst = false;
        }            
    }while(!quit && !(key == ENT_KEY));
    return quit;
}

void renderSplashChoice(){
    switch(model.mode){
        case 0:/*            180      -4        240     64      -4    is 180,300*/
            p_btmp_8(CHOICE_X+BMP_OFFSET,CHOICE_Y+ESCAPE+BMP_OFFSET,CYCLE2[1]);
            break;
        case 1:/*            180      -4        240      0      -4    is 180,236*/
            p_btmp_8(CHOICE_X+BMP_OFFSET,CHOICE_Y+ONE+BMP_OFFSET,CYCLE2[1]);
            break;
        case 2:/*            180      -4        240     32      -4    is 180,272*/
            p_btmp_8(CHOICE_X+BMP_OFFSET,CHOICE_Y+TWO+BMP_OFFSET,CYCLE2[1]);
            break;
    }
    model.mode2=model.mode;
}

void setMenuChoice(UINT8 key){
    model.mode2=model.mode;
    if      (key == ONE_KEY){
        model.mode = 1;
        }
    else if (key == TWO_KEY){
        model.mode = 2;
        }
    else if (key == ESC_KEY){
        model.mode = 0;
        }
    else if (key == UARW_KEY){
        if      (model.mode == 1)
            model.mode = 0;
        else if (model.mode == 2)
            model.mode = 1;
        else if (model.mode == 0)
            model.mode = 2;
    }
    else if (key == DARW_KEY){
        if      (model.mode == 2)
            model.mode = 0;
        else if (model.mode == 1)
            model.mode = 2;
        else if (model.mode == 0)
            model.mode = 1;
    }
}

void renderMouse(){
    int origSsp = Super(0);
    int origIpl = set_ipl(7);
/*    if (mouse_x_old > -1 && mouse_y_old > -1)
        p_btmp_8(mouse_x_old+BMP_OFFSET,mouse_y_old+BMP_OFFSET,CYCLE1[0]);*/
    mouse_x_old = mouse_x;
    mouse_y_old = mouse_y;
    p_btmp_8(mouse_x+BMP_OFFSET,mouse_y+BMP_OFFSET,CYCLE1[0]);
    set_ipl(origIpl);
    Super(origSsp);
}