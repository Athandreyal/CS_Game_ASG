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
#include "globals.h"
#include "effects.h"

#define ESC_KEY   0x01
#define LARW_KEY  0x4B
#define RARW_KEY  0x4D
#define UARW_KEY  0x48
#define DARW_KEY  0x50
#define TRAP_70 70
#define TRAP_28 28

UINT8 framebuffer2[32255];

/*
///////////////////////////////////////////////////////////////////
// Function Name:  main
// Purpose:        core game code and loop
///////////////////////////////////////////////////////////////////
*/
void main(){
    UINT8 *base0, *base1;
    bool buffer, quit;
	Vector orig_vector70 = install_vector(TRAP_70,trap70_isr);  /*  kybd  */
	Vector orig_vector28 = install_vector(TRAP_28,trap28_isr);  /*  VBL  */
    rndrRqst = false;
    
    initKeyboard();
    buffer = quit = false;
    getScreen(&buffer, &base0, &base1);
    buffer = true;
    quit = false;
    srand(time(NULL));
    while(!quit){
        menuInit();
        quit = menuLoop(&buffer, base0, base1);
        if (!quit){
            init();
            gameLoop(&buffer, base0, base1);
        }
    }
    setBuffer(base0);
	install_vector(TRAP_70,orig_vector70);
	install_vector(TRAP_28,orig_vector28);
}

void gameLoop(bool *buffer, UINT8 *base0, UINT8 *base1){
    bool endMatch = false;
    bool crash = false;
    while (!endMatch && (model.user.life > 0 && model.program.life > 0)){
        doReset();
        render();
        toggleScreen(buffer, base0, base1);
        render();
        do{
            if (keyWaiting)
                endMatch = onKey();
            if (rndrRqst){
                toggleScreen(buffer, base0, base1);
                rndr_fld();/*render the field after the model changes, to reflect the move*/
                crash = (model.program.crashed || model.user.crashed);
                rndrRqst = false;
            }
        }while (!endMatch && !crash);
    }
    if (model.user.life > 0)
        success_music();
    else
        fail_music();
}

void getScreen(bool *buffer, UINT8 **base0, UINT8 **base1){
    long old_ssp = Super(0);
	*base0 = Physbase();
    myPhysBase(*base0);
    Super(old_ssp);
    *base1 = (UINT8*)((((long)(&framebuffer2)) + 255) & 0xffffff00);
    base = *base1;
    *buffer = true;
    setBuffer(base);
}

void setBuffer(UINT8 *baseX){
    long old_ssp = Super(0);
    mySetScreen(baseX);
    Super(old_ssp);
}

void toggleScreen(bool *buffer, UINT8 *base0, UINT8 *base1){
    long old_ssp = Super(0);
    if (*buffer){
        mySetScreen(base1);
        base = base0;
        }
    else{
        mySetScreen(base0);
        base = base1;
        }
    Super(old_ssp);
    *buffer = !(*buffer);
}

void doReset(Model *model){
    reset(model);
    matchStart(model);
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
bool onKey(){
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
            maneuver(key, &(model.user.cycle));
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
