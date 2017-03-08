#ifndef MODEL_H
#define MODEL_H
#include "Objects.h"
#define P1STARTX 320
#define P1STARTY 31
#define P2STARTX 320
#define P2STARTY 361

/*const int PLAYERLIVES = 5;*/



void init(Model *model);
void reset(Model *model);
void release(Model *model);
bool collision(Model *model);
void crash(Model *model);

/*
    Init                initialise model data structures
    match start         place the cycles at their starts
    Release             activate the keyboard
    Collision           check for and apply collision
    Crash               
    Reset               initialise model data structures, ignore user bool and lives
*/
#endif
