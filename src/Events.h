/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil
*/
#ifndef EVENTS_H
#define EVENTS_H

#include "types.h"
#include "Model.h"
#include "Constant.h"

void setSpd2(Cycle *cycle, accelerate accel);
void setSpd(Cycle *cycle, UINT8 key);
void setTurn(Cycle *cycle,UINT8 key);
void chng_dir(Cycle *cycle, int *direction);
void chng_spd(Cycle *cycle, int speed);
void sub_life(Player *player);
void maneuver(UINT8 key, Cycle* cycle);
void move(Cycle* cycle);
/*UINT32 collide(UINT8 *base, Cycle *cycle);*/
bool collide(Cycle *cycle);
int readGrid(int x, int y,int length);
void AITurn(Cycle *cycle,Turn dir);
void AIChoice();
void setGhost();
bool doMove();
bool crashed();
bool crashed2(int x, int y, const UINT8 bitmap[]);
#endif
