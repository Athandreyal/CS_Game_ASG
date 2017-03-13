#ifndef EVENTS_H
#define EVENTS_H

#include "types.h"
#include "Model.h"

void chng_dir(Cycle *cycle, int *direction);
void chng_spd(Cycle *cycle, int speed);
void sub_life(Player *player);
bool collide(UINT8 *base, Model *model);
/*void lay_trl(UINT8 *base), Cycle *cycle;*/
void move(Cycle* cycle);
#endif