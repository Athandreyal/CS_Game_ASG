/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    Primary game code, Main, doMode, getTime, onKey
*/

#include "Tron.h"
#include <osbind.h>
#include "Model.h"
#include "Events.h"
#include "Renderer.h"
#include "mSetScrn.h"

#define ESC_KEY   0x0001001B
#define LARW_KEY  0x004B0000
#define RARW_KEY  0x004D0000
#define UARW_KEY  0x00480000
#define DARW_KEY  0x00500000

UINT8 framebuffer2[32255];

/*
///////////////////////////////////////////////////////////////////
// Function Name:  main
// Purpose:        core game code and loop
///////////////////////////////////////////////////////////////////
*/
void main(){
    Model model;
    UINT8 *base, *base0, *base1;
    bool buffer, crash, quit;
    long timeNow, timeThen, timeElapsed;
    buffer = crash = quit = false;
    getScreen(&buffer, &base, &base0, &base1);
    buffer = true;
    init(&model);
    timeNow = timeThen = timeElapsed = 0;
    Cnecin();
    do{/*render twice to catch both buffers for a full screen draw*/
        doReset(&model);
        render(base, &model);  /*full frame render*/
        toggleScreen(&buffer, &base, base0, base1);
        render(base, &model);  /*full frame render*/
        do{
            timeNow = getTime();
            timeElapsed = timeNow - timeThen;
            if (Cconis())
                quit = onKey(Cnecin(), &(model));
            if (timeElapsed > 1){
                toggleScreen(&buffer, &base, base0, base1);
                doMove(base, &model,timeNow);
                rndr_fld(base, &model);/*render the field after the model changes, to reflect the move*/
                crash = crashed(base, &model);
                timeThen = timeNow;
                }
        }while (!quit && !crash);
        Cnecin();
    }while (!quit && model.user.life > 0 && model.program.life > 0);
    setBuffer(base0);
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  getTime
// Purpose:        access the system timer to onbtaint and return the current time
// Outputs:        lont timeNow:  the current timer value;
///////////////////////////////////////////////////////////////////
*/
UINT32 getTime(){
    long *timer = (long*)0x462;
    long old_ssp = Super(0);
    UINT32 timeNow;
    timeNow = (UINT32)*timer;
    Super(old_ssp);
    return timeNow;
}

void getScreen(bool *buffer, UINT8 **base, UINT8 **base0, UINT8 **base1){
    long old_ssp = Super(0);
	*base0 = Physbase();
    myPhysBase(*base0);
    Super(old_ssp);
    *base1 = (UINT8*)((((long)(&framebuffer2)) + 255) & 0xffffff00);
    *base = *base1;
    *buffer = true;
    setBuffer(*base);
}

void setBuffer(UINT8 *base){
    long old_ssp = Super(0);
    mySetScreen(base);
    Super(old_ssp);
}

void toggleScreen(bool *buffer, UINT8 **base, UINT8 *base0, UINT8 *base1){
    long old_ssp = Super(0);
    if (*buffer){
        mySetScreen(base1);
        *base = base0;
        }
    else{
        mySetScreen(base0);
        *base = base1;
        }
    Super(old_ssp);
    *buffer = !(*buffer);
    Vsync();
}

void doReset(Model *model){
    reset(model);
    matchStart(model);
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  doMove
// Purpose:        top level move driver: initiates moves, detects crashes, triggers reset when necessary.
// Inputs:         UINT8 *base :    the frame buffer
//                 Model *model:    the current game model for manipulation and updating
//                 long timeNow:    the current timer value, used here for random seeding in AIChoice
// Outputs:        Model *model:    the updated game model.
///////////////////////////////////////////////////////////////////
*/
bool doMove(UINT8 *base, Model *model, long timeNow){
    bool noCrash = true;
    move(&(model->user.cycle));
    setGhost(model);
    move(&(model->ghost.cycle));
    AIChoice(base, model, timeNow);
    move(&(model->program.cycle));
    return noCrash;
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  onKey
// Purpose:        top level key driver: initiates key detection, access, and triggers quit and move events.
// Inputs:         UINT32 key:      the key that was read
//                 Model *model:    the current game model for manipulation and updating
// Outputs:        Model *model:    the updated game model.
///////////////////////////////////////////////////////////////////
*/
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

