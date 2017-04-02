#ifndef PSG_H
#define PSG_H

#include "TYPES.H"
#include <stdio.h>

UINT8 readPsg(UINT16 reg);
void allmOn();
void writePsg(UINT8 reg, UINT8 val);
void setEnvlp(UINT8 shape, UINT16 period);
void chngVol(UINT8 channel, UINT8 volume);
void setMix(int channel, UINT8 device);
void stop_sound();
void setNote(UINT8,UINT32,UINT8);
void setNoise(UINT8 freq);
UINT16 getTDVal(UINT32);
void tstSound();

#endif