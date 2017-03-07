#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"

void render(Model *model, UINT8 *base);
void rndr_blk(UINT8 *base);
void rndr_fld(UINT8 *base);
void rndr_lif(Player *player, UINT8 *base);
void rndr_lw(lgt_walls *lw, UINT8 *base);
void rndr_cyc(Cycle cycle, UINT8 *base);
#endif