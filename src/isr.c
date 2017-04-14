#include "isr.h"
#include "globals.h"
#include "Model.h"

void initKeyboard(){
    tail = 0;
    head = 0;
    mouse_x_old = 0;
    mouse_y_old = 0;
    mouse_x = 0;
    mouse_y = 0;
    keyRegister = 0;
    buffer[256];
    mouseState = 0;
    mouseKeys = 0;
    keyWaiting = 0;
}

Vector install_vector(int num, Vector vector){
	Vector orig;
	Vector *vectp = (Vector *)((long)num << 2);
	long old_ssp = Super(0);    
	orig = *vectp;
	*vectp = vector;
	Super(old_ssp);
	return orig;
}

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

void keyboard(){
    if      ((keyRegister >= 0xF8) || mouseState > 0){
        /*mouse in progress*/
        switch(mouseState){
            case 0:/*header*/
                mouseKeys = keyRegister & 3;
                mouseState=1;
                break;
            case 1:/*x*/
                mouse_x += (int)((signed char)keyRegister);
                if (mouse_x > 636)
                    mouse_x = 636;
                else if (mouse_x < 4)
                    mouse_x = 4;
                mouseState=2;
                break;
            case 2:/*y*/
                mouse_y += (int)((signed char)keyRegister);
                if (mouse_y > 396)
                    mouse_y = 396;
                else if (mouse_y < 4)
                    mouse_y = 4;
                mouseState=0;
        }
    }
    else if (keyRegister < 0x80){
        /*keyboard*/
        tail++;
        *(buffer+tail) = keyRegister;
        keyWaiting = true;
    }
}