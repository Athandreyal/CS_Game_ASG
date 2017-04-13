#ifndef ISR_H
#define ISR_H
#include "types.h"
#include <osbind.h>
#include <stdio.h>

#define TRAP_0 32
#define TRAP_28 28
#define TRAP_70 70
#include "Model.h"
#include "globals.h"

UINT32 getTime();
typedef void (*Vector)();  /* a vector is a function start address */

void keyboard();
Vector install_vector(int num, Vector vector);
void initKeyboard();

#endif