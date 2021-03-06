/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    new game types and enums.
*/

#ifndef TYPES_H
#define TYPES_H

typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
typedef enum bool{ false, true } bool;
/*typedef enum velocity {slow=2, norm = 4, fast=6} velocity;*/
typedef enum velocity {norm = 4, fast=6} velocity;
typedef enum accelerate {slower,faster} accelerate;
typedef enum Turn {left,right} Turn;
typedef enum menuPosition {ONE=0, TWO=40, ESCAPE=80} menuPosition;
typedef void (*Vector)();  /* a vector is a function start address */
#endif
