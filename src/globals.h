#ifndef GLOBALSH
#define GLOBALSH
#include "Model.h"
#include "types.h"
#include <stdio.h>

extern volatile unsigned char tail;
extern volatile unsigned char head;
extern int mouse_x_old;
extern int mouse_y_old;
extern int mouse_x;
extern int mouse_y;
extern  unsigned char keyRegister;
extern  unsigned char buffer[256];
extern  unsigned char mouseState;
extern  unsigned char mouseKeys;
extern  bool keyWaiting;
extern  bool rndrRqst;
extern UINT8 *base;
extern Model model;
extern FILE *f;
extern UINT32 ticks;



#endif