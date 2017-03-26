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

UINT32 getTime();
bool onKey(UINT32 key, Model *model);
bool doMove(UINT8 *base, Model *model, long timeNow);
void getScreen(bool *buffer, UINT8 **base, UINT8 **base0, UINT8 **base1);
void setBuffer(UINT8 *base0);
void toggleScreen(bool *buffer, UINT8 **base, UINT8 *base0, UINT8 *base1);
void doReset(Model *model);
#endif