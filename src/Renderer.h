#ifndef RENDERER_H
#define RENDERER_H
#include "Model.h"
#include "TYPES.H"
#include "Objects.h"

void render(UINT8 *base, Model *model);
void rndr_bak(UINT8 *base, Model *model);
void rndr_fld(UINT8 *base, Model *model);
void rndr_lif(UINT8 *base, Player *player);
void rndr_lw(UINT8 *base, Cycle *cycle, int index);
void rndr_cyc(UINT8 *base, Player *player, int index);
void setLPos(Cycle* cycle);
void uRndrCyc(UINT8 *base, Player *player);
#endif
