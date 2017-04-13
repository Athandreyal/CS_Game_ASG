#ifndef GLOBALS
#define GLOBALS
#include "Model.h"
#include "types.h"

extern volatile unsigned char tail;
extern volatile unsigned char head;
extern int mouse_x_old;
extern int mouse_y_old;
extern int mouse_x;
extern int mouse_y;
extern volatile unsigned char keyRegister;
extern volatile unsigned char buffer[256];
extern volatile unsigned char mouseState;
extern volatile unsigned char mouseKeys;
extern volatile bool keyWaiting;
extern volatile UINT8 *base;
extern Model model;



#endif