/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    Primary game code, Main, doMode, getTime, onKey
*/

#include "Tron.h"
#include <osbind.h>
#include <stdlib.h>
#include "Model.h"
#include "Events.h"
#include "Renderer.h"
#include "mSetScrn.h"
#include "raster.h"
#include "Menu.h"
#include <time.h>
#include "isr.h"
#include "isr_asm.h"

#define ESC_KEY   0x01
#define LARW_KEY  0x4B
#define RARW_KEY  0x4D
#define UARW_KEY  0x48
#define DARW_KEY  0x50
#define TRAP_70 70

unsigned char tail;
unsigned char head;
int mouse_x_old;
int mouse_y_old;
int mouse_x;
int mouse_y;
unsigned char keyRegister;
unsigned char buffer[256];
unsigned char mouseState;
unsigned char mouseKeys;
bool keyWaiting;

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
    bool buffer, crash, quit, endMatch;
    long timeNow, timeThen, timeElapsed;
	Vector orig_vector70 = install_vector(TRAP_70,trap70_isr);  /*  kybd  */
    initKeyboard();
    buffer = crash = quit = endMatch = false;
    getScreen(&buffer, &base, &base0, &base1);
    buffer = true;
    timeNow = timeThen = timeElapsed = 0;
    srand(time(NULL));
    while(!quit){
        menuInit(&model);
        quit = menuLoop(&buffer, &base, base0, base1, &model);
        init(&model);
        while (!endMatch && (!quit && model.user.life > 0 && model.program.life > 0)){
            doReset(&model);
            render(base, &model);
            toggleScreen(&buffer, &base, base0, base1);
            render(base, &model);
            do{
                timeNow = getTime();
                timeElapsed = timeNow - timeThen;
                if (keyWaiting)
                    endMatch = onKey(&model);
                if (timeElapsed > 1){
                    toggleScreen(&buffer, &base, base0, base1);
                    doMove(base, &model);
                    rndr_fld(base, &model);/*render the field after the model changes, to reflect the move*/
                    crash = crashed(base, &model);
                    timeThen = timeNow;
                    }
            }while (!endMatch && !crash);
        }
    }
    setBuffer(base0);
	install_vector(TRAP_70,orig_vector70);
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
bool doMove(UINT8 *base, Model *model){
    bool noCrash = true;
    move(&(model->user.cycle));
    setGhost(model);
    move(&(model->ghost.cycle));
    AIChoice(base, model);
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
bool onKey(Model *model){
    int origSsp;
    int origIpl;
    bool quit = false;
    UINT8 key;
    getKey(&key);
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

void getKey(UINT8 *key){
    int origSsp;
    int origIpl;
    while(!keyWaiting);
    
    origSsp = Super(0);
    origIpl = set_ipl(7);
    *key = buffer[tail];
    keyWaiting = head == tail;
    head++;
    set_ipl(origIpl);
    Super(origSsp);
}
