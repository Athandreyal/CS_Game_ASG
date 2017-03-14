#include "Tron.h"
#include <osbind.h>
#include <stdio.h>
#include "Model.h"
#include "Events.h"
#include "Renderer.h"

#define ESC_KEY   0x0001001B
#define LARW_KEY  0x004B0000
#define RARW_KEY  0x004D0000
#define UARW_KEY  0x00480000
#define DARW_KEY  0x00500000

void main(){
    Model model;
	UINT8 *base = Physbase();
    bool quit = false;
    long timeNow, timeThen, timeElapsed;    
    timeNow = timeThen = timeElapsed = 0;
    init(&model);
    render(base, &model);
    Cnecin();
    matchStart(&model);
    do{
        timeNow = getTime();
        timeElapsed = timeNow - timeThen;
        if (Cconis())
            quit = onKey(Cnecin(), &(model));
        if (timeElapsed > 1){
            if(doMove(base, &model,timeNow)){
                Vsync();
                rndr_fld(base, &model);
                timeThen = timeNow;
                }
            }
    }while (!quit && model.user.life > 0 && model.program.life > 0);
    /*call cleanup once necessary*/
}

UINT32 getTime(){
    long *timer = (long*)0x462;
    long old_ssp = Super(0);
    UINT32 timeNow;
    timeNow = (UINT32)*timer;
    Super(old_ssp);
    return timeNow;
}

bool doMove(UINT8 *base, Model *model, long timeNow){
    bool noCrash = true;
    FILE *f = fopen("log.txt","a");
    move(&(model->user.cycle));
    move(&(model->ghost.cycle));
    AIChoice(model, timeNow);
    move(&(model->program.cycle));
    setGhost(model);
    if(crashed(base, model)){
        fprintf(f,"crashed\n");
        reset(model);
        matchStart(model);
        Vsync();
        render(base, model);
        noCrash = false;
    }
    fclose(f);
    return noCrash;
}

bool onKey(UINT32 key, Model *model){
    bool quit = false;
    switch(key){ 
        case ESC_KEY:
            quit = true;
            break;
        case LARW_KEY:/*left turn*/
        case RARW_KEY:/*right turn*/
        case UARW_KEY:/*accelerate*/
        case DARW_KEY:/*decelerate*/
            maneuver(key, &(model->user.cycle));
    }
    return quit;
}