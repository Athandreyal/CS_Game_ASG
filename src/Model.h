#ifndef MODEL_H
#define MODEL_H
#include "TYPES.H"
#include "Objects.h"
#include "Constant.h"

void init(Model *model);
void reset(Model *model);
bool crashed(UINT8 *base, Model *model);
void matchStart(Model *model);
bool crashed2(UINT8 *base, int x, int y, const UINT8 bitmap[]);

#endif
