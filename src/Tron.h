#ifndef TRON_H
#define TRON_H
#include "TYPES.H"
#include "Model.h"

const char ESC_KEY = (char)27;
UINT32 getTime();
bool onKey(char key, Model *model);
#endif