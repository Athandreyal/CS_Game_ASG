#ifndef PSG_H
#define PSG_H

#include "TYPES.H"
#include <stdio.h>

UINT8 readPsg(UINT8 register);
void writePsg(UINT8 reg, UINT8 val);
void setEnvlp(UINT8 shape, UINT32 period);
void chngVol(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();
void setNote(UINT8,UINT32,UINT8);
void setNoise(UINT8 freq);
UINT16 getTDVal(UINT32);
void tstSound();

#endif