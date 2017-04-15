#include "globals.h"

/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    Primary game code, Main, doMode, getTime, onKey
*/

volatile unsigned char tail;
volatile unsigned char head;
int mouse_x_old;
int mouse_y_old;
int mouse_x;
int mouse_y;
unsigned char keyRegister;
unsigned char buffer[256];
unsigned char mouseState;
unsigned char mouseKeys;
bool keyWaiting;
bool rndrRqst=true;
FILE *f;
UINT32 ticks=0;


UINT8 *base;
Model model;

