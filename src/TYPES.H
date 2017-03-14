#ifndef TYPES_H
#define TYPES_H

typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
typedef enum bool{ false, true } bool;
typedef enum velocity {slow=2, norm = 4, fast=4} velocity;
typedef enum accelerate {slower,faster} accelerate;
typedef enum Turn {left,right} Turn;
#endif
