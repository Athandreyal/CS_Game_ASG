#include "isr.h"
#include "globals.h"
#include "Model.h"
#include "Events.h"
#include "isr_asm.h"

/*
///////////////////////////////////////////////////////////////////
// Function Name:  initKeyboard
// Purpose:        initialize keyBoard
///////////////////////////////////////////////////////////////////
*/
void initKeyboard(){
    tail = 0;
    head = 0;
    mouse_x = 0;
    mouse_y = 0;
    keyRegister = 0;
    buffer[256];
    mouseState = 0;
    mouseKeys = 0;
    keyWaiting = 0;
}
/*
///////////////////////////////////////////////////////////////////
// Function Name:  AIChoice
// Purpose:        installs vector 
// returns current vector to backup 
///////////////////////////////////////////////////////////////////
*/
Vector install_vector(int num, Vector vector){
	Vector orig;
	Vector *vectp = (Vector *)((long)num << 2);
	long old_ssp = Super(0);    
	orig = *vectp;
	*vectp = vector;
	Super(old_ssp);
	return orig;
}
/*
///////////////////////////////////////////////////////////////////
// Function Name:  AIChoice
// Purpose:       VBL interupt timer
///////////////////////////////////////////////////////////////////
*/
void VBL(){
    ticks++;
    if (!rndrRqst && (ticks & 1)){
        if (!model.menu){
            if (model.doCrash){
                if(!crashed());
                    doMove();
            }
            else{
                doMove();
                model.doCrash = true;
            }
        }
        rndrRqst = true;
    }
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  AIChoice
// Purpose:        actual guts of the keyboard isr input 
///////////////////////////////////////////////////////////////////
*/
void keyboard(){
    if      ((mouseState > 0) || (keyRegister >= 0xF8)){
        /*mouse in progress*/
        if      (mouseState == 0){
                mouseKeys = keyRegister & 3;
                mouseState=1;
        }
        else if (mouseState == 1){
                mouse_x += (int)((signed char)keyRegister);
                if (mouse_x > 636)
                    mouse_x = 636;
                else if (mouse_x < 4)
                    mouse_x = 4;
                mouseState=2;
        }
        else if (mouseState == 2){
                mouse_y += (int)((signed char)keyRegister);
                if (mouse_y > 396)
                    mouse_y = 396;
                else if (mouse_y < 4)
                    mouse_y = 4;
                mouseState=0;
        }
    }
    else if (mouseState == 0 && keyRegister < 0x80){
        /*keyboard*/
        tail++;
        buffer[tail] = keyRegister;
        keyWaiting = true;
    }
    else;
}