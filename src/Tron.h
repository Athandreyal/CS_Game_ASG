#ifndef TRON_H
#define TRON_H
#include "TYPES.H"
#include "Model.h"

UINT32 getTime();
bool onKey(UINT32 key, Model *model);
bool doMove(UINT8 *base, Model *model, long timeNow);
#endif