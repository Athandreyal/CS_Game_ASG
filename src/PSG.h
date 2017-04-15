#ifndef PSG_H
#define PSG_H

#include "TYPES.H"
#include <stdio.h>

void wait(UINT32 time,UINT32 divisor);
UINT8 readPsg(UINT16 reg);
void allmOn();
void writePsg(UINT8 reg, UINT8 val);
void setEnvlp(UINT8 shape, UINT16 period);
void setEnvSt(UINT8 levelChannel,UINT8 envState);
void chngVol(UINT8 channel, UINT8 volume);
void setMix(int channel, UINT8 device, UINT8 onOFF);
void stop_sound();
void setNote(UINT8,UINT32);
void setNoise(UINT8 freq);
UINT16 getTDVal(UINT32);
void tstSound();

typedef struct RegState {
	UINT32 currentTime;

    UINT8 chanAfine;
    UINT8 chanAcourse;

    UINT8 chanBfine;
    UINT8 chanBcourse;

    UINT8 chanCfine;
    UINT8 chanCcourse;

    UINT8 noise;

    UINT8 mixer;

    UINT8 chanAlevel;
    UINT8 chanBlevel;
    UINT8 chanClevel;

    UINT8 envFreq;
    UINT8 envShape;

}RegState;

#endif