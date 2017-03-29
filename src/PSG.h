#ifndef PSG_H
#define PSG_H

#include "TYPES.H"
#include <stdio.h>

void setNote(UINT8,UINT32,UINT8);
void setNoise(UINT8 freq);
UINT16 getTDVal(UINT32);
void tstSound();

#endif