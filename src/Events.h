#ifndef EVENTS_H
#define EVENTS_H

#include "types.h"
#include "Model.h"

void setSpd2(Cycle *cycle, accelerate accel);
void setSpd(Cycle *cycle, UINT32 key);
void setTurn(Cycle *cycle,UINT32 key);
/*void setTurn(Cycle *cycle,Turn dir);*/
void chng_dir(Cycle *cycle, int *direction);
void chng_spd(Cycle *cycle, int speed);
void sub_life(Player *player);
/*bool collide(UINT8 *base, Cycle *cycle);
/*void lay_trl(UINT8 *base), Cycle *cycle;*/
void maneuver(UINT32 key, Cycle* cycle);
void move(Cycle* cycle);
UINT32 collide(UINT8 *base, Cycle *cycle);
void AITurn(Cycle *cycle,Turn dir);
void AIChoice(Model *model, long time);
void setGhost(Model *model);
#endif
