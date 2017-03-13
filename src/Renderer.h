#ifndef RENDERER_H
#define RENDERER_H
#include "Model.h"
#include "TYPES.H"
#include "Objects.h"

void render(UINT8 *base, Model *model);
void rndr_blk(UINT8 *base, Model *model);
void rndr_fld(UINT8 *base, Model *model);
void rndr_lif(UINT8 *base, Player *player);
void rndr_lw(UINT8 *base, Cycle *cycle);
void rndr_cyc(UINT8 *base, Player *player);
#endif