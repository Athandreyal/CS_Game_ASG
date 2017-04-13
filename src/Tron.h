/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil
*/
#ifndef TRON_H
#define TRON_H
#include "TYPES.H"
#include "Model.h"

extern unsigned char tail;
extern unsigned char head;
extern int mouse_x_old;
extern int mouse_y_old;
extern int mouse_x;
extern int mouse_y;
extern unsigned char keyRegister;
extern unsigned char buffer[256];
extern unsigned char mouseState;
extern unsigned char mouseKeys;
extern bool keyWaiting;
UINT32 getTime();

bool onKey(Model *model);
bool doMove(UINT8 *base, Model *model);
void getScreen(bool *buffer, UINT8 **base, UINT8 **base0, UINT8 **base1);
void setBuffer(UINT8 *base0);
void toggleScreen(bool *buffer, UINT8 **base, UINT8 *base0, UINT8 *base1);
void doReset(Model *model);
void getKey(UINT8 *key);
#endif
