#ifndef MODEL_H
#define MODEL_H
#include "TYPES.H"
#include "Objects.h"
#include "Constant.h"
#include "globals.h"


void menuInit();
void init();
void reset();
bool crashed();
void matchStart();
bool crashed2(int x, int y, const UINT8 bitmap[]);

void doMove();

#endif
