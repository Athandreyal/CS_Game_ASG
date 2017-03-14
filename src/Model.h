#ifndef MODEL_H
#define MODEL_H
#include "TYPES.H"
#include "Objects.h"
#define P1STARTX 320
#define P1STARTY 361
#define P2STARTX 320
#define P2STARTY 31


void init(Model *model);
void reset(Model *model);
void release(Model *model);
bool crashed(UINT8 *base, Model *model);
void matchStart(Model *model);

#endif
