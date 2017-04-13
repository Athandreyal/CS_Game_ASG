#include "menu.h"
#include "types.h"
#include "Objects.h"
#include "splash.h"
#include "constant.h"
#include "raster.h"
#include "mSetScrn.h"
#include <OSBind.h>
#include "model.h"
#include <stdio.h>
#include "tron.h"

#define UARW_KEY  0x48
#define DARW_KEY  0x50
#define Q_KEY     0x01
#define ESC_KEY   0x01
#define ONE_KEY   0x02
#define TWO_KEY   0x03
#define ENT_KEY   0x1C

bool menuLoop(bool *buffer, UINT8 **base,UINT8 *base0,UINT8 *base1, Model *model){
    bool quit = false;
    UINT8 key;
    key = 0;
    fst_blk(*base);
    plotSplsh(*base,SPLASH);/*should be buffer 1 */
    toggleScreen(buffer, base, base0, base1);/*switch to buffer 0*/
    if(*base != base1)
        renderSplashChoice(base1, model);/*render to current, mode 1, mode2 1*/
    else
        renderSplashChoice(base0, model);/*render to current, mode 1, mode2 1*/
    do{
        Vsync();
        if(*base != base1)
            renderMouse(base1);
        else
            renderMouse(base0);
            
        if(keyWaiting)
        {
            getKey(&key);
            quit = ((key == ESC_KEY) || (key == ENT_KEY)) && (model->mode == 0);
            if (!quit){
                setMenuChoice(key,model);
            }
            if(*base != base1)
                renderSplashChoice(base1, model);/*render to current, mode 1, mode2 1*/
            else
                renderSplashChoice(base0, model);/*render to current, mode 1, mode2 1*/
        }
    }while(!quit && !(key == ENT_KEY));
    return quit;
}

void renderSplashChoice(UINT8 *base, Model *model){
    if(model->mode2 != -1){
        switch(model->mode2){
            case 0:/*            180      -4        240     64      -4    is 180,300*/
                p_btmp_8(base, CHOICE_X+BMP_OFFSET,CHOICE_Y+ESCAPE+BMP_OFFSET,CYCLE2[1]);
                break;
            case 1:/*            180      -4        240      0      -4    is 180,236*/
                p_btmp_8(base, CHOICE_X+BMP_OFFSET,CHOICE_Y+ONE+BMP_OFFSET,CYCLE2[1]);
                break;
            case 2:/*            180      -4        240     32      -4    is 180,272*/
                p_btmp_8(base, CHOICE_X+BMP_OFFSET,CHOICE_Y+TWO+BMP_OFFSET,CYCLE2[1]);
                break;
        }
    }
    switch(model->mode){
        case 0:/*            180      -4        240     64      -4    is 180,300*/
            p_btmp_8(base, CHOICE_X+BMP_OFFSET,CHOICE_Y+ESCAPE+BMP_OFFSET,CYCLE2[1]);
            break;
        case 1:/*            180      -4        240      0      -4    is 180,236*/
            p_btmp_8(base, CHOICE_X+BMP_OFFSET,CHOICE_Y+ONE+BMP_OFFSET,CYCLE2[1]);
            break;
        case 2:/*            180      -4        240     32      -4    is 180,272*/
            p_btmp_8(base, CHOICE_X+BMP_OFFSET,CHOICE_Y+TWO+BMP_OFFSET,CYCLE2[1]);
            break;
    }
    model->mode2=model->mode;
}

void setMenuChoice(UINT8 key, Model *model){
    model->mode2=model->mode;
    if      (key == ONE_KEY){
        model->mode = 1;
        }
    else if (key == TWO_KEY){
        model->mode = 2;
        }
    else if (key == ESC_KEY){
        model->mode = 0;
        }
    else if (key == UARW_KEY){
        if      (model->mode == 1)
            model->mode = 0;
        else if (model->mode == 2)
            model->mode = 1;
        else if (model->mode == 0)
            model->mode = 2;
    }
    else if (key == DARW_KEY){
        if      (model->mode == 2)
            model->mode = 0;
        else if (model->mode == 1)
            model->mode = 2;
        else if (model->mode == 0)
            model->mode = 1;
    }
}

void renderMouse(UINT8 *base){
    if (mouse_x > -1 && mouse_y > -1)
        p_btmp_8(base, mouse_x_old+BMP_OFFSET,mouse_y_old+BMP_OFFSET,CYCLE1[0]);
    p_btmp_8(base, mouse_x+BMP_OFFSET,mouse_y+BMP_OFFSET,CYCLE1[0]);
    mouse_x_old = mouse_x;
    mouse_y_old = mouse_y;
}