#ifndef ISR_H
#define ISR_H
#include "types.h"
#include <osbind.h>
#include <stdio.h>

#define TRAP_0 32
#define TRAP_28 28
#define TRAP_70 70
#include "Model.h"

extern unsigned char tail;
extern unsigned char head;
extern int mouse_x;
extern int mouse_y;
extern unsigned char keyRegister;
extern unsigned char buffer[256];
extern unsigned char mouseState;
extern unsigned char mouseKeys;
extern bool keyWaiting;
UINT32 getTime();
typedef void (*Vector)();  /* a vector is a function start address */

void keyboard();
Vector install_vector(int num, Vector vector);
void initKeyboard();

#endif