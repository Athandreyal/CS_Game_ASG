#ifndef RENDERER_H
#define RENDERER_H
#include "Model.h"
#include "TYPES.H"
#include "Objects.h"

void render();
void rndr_bak();
void rndr_fld();
void rndr_lif(Player *player);
void rndr_lw(Cycle *cycle, int index);
void rndr_cyc(Player *player, int index);
void setLPos(Cycle* cycle);
void uRndrCyc(Player *player);
#endif
