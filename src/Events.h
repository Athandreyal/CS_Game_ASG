#ifndef EVENTS_H
#define EVENTS_H

#include "types.h"
#include "Model.h"

void chng_dir(Cycle *cycle, int *direction);
void chng_spd(Cycle *cycle, int speed);
int sub_life(Player *player);
int collide(UINT8 *base);
void lay_trl(Uint *base);