#include "isr.h"

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

Vector install_vector(int num, Vector vector){
	Vector orig;
	Vector *vectp = (Vector *)((long)num << 2);
	long old_ssp = Super(0);    
	orig = *vectp;
	*vectp = vector;
	Super(old_ssp);
	return orig;
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
                if (mouse_x > 640)
                    mouse_x = 640;
                else if (mouse_x < 0)
                    mouse_x = 0;
                mouseState=2;
                break;
            case 2:/*y*/
                mouse_y += (int)((signed char)keyRegister);
                if (mouse_y > 400)
                    mouse_y = 400;
                else if (mouse_y < 0)
                    mouse_y = 0;
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