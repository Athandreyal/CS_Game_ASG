#include "Tron.h"
#include <osbind.h>
#include <stdio.h>
#include "Model.h"
#include "Events.h"
#include "Renderer.h"
#define ESC_KEY 27

FILE *f;

void main(){
    Model model;
	UINT8 *base = Physbase();
    bool quit = false;
    long timeNow, timeThen, timeElapsed;    
    f = fopen("log.txt","w");
    fclose(f);
    timeNow = timeThen = timeElapsed = 0;
    init(&model);
    render(base, &model);
    Cnecin();
    matchStart(&model);
    do{
        timeNow = getTime();
        timeElapsed = timeNow - timeThen;
        if (Cconis())
            quit = onKey((char)Cnecin(), &model);
        if (timeElapsed > 2){
/*            process_synchronous;*/
            move(&(model.user.cycle));
            move(&(model.program.cycle));
            Vsync();
            rndr_fld(base, &model);
            timeThen = timeNow;
            }
    }while (!quit);
    /*call cleanup once necessary*/
    fclose(f);
}

UINT32 getTime(){
    long *timer = (long*)0x462;
    long old_ssp = Super(0);
    UINT32 timeNow;
    timeNow = (UINT32)*timer;
    Super(old_ssp);
    return timeNow;
}

bool onKey(char key, Model *model){
    bool quit = false;
    f = fopen("log.txt","a");
    fprintf(f, "key captured: %d", (int)key);
    switch(key){ 
        case ESC_KEY:
            quit = true;
            break;
        case 'j':/*left turn*/
            setTurn(&(model->user.cycle),left);
            break;
        case 'l':/*right turn*/
            setTurn(&(model->user.cycle),right);
            break;
        case 'i':/*accelerate*/
            setSpd(&(model->user.cycle),faster);
            break;
        case 'k':/*decelerate*/
            setSpd(&(model->user.cycle),slower);
    }
    fclose(f);
    return quit;
}