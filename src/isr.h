#ifndef ISR_H
#define ISR_H
#include "types.h"
#include <osbind.h>
#include <stdio.h>

#define TRAP_0 32
#define TRAP_28 28
#define TRAP_70 70
#include "globals.h"

void keyboard();
Vector install_vector(int num, Vector vector);
void initKeyboard();
void VBL();

#endif