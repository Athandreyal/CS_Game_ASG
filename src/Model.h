#ifndef MODEL_H
#define MODEL_H
#define P1STARTX 320
#define P1STARTY 31
#define P2STARTX 320
#define P2STARTY 361
#define LIGHTPATHMAX 1000
#define PLAYERLIVES 3

struct typedef Model {
    bool active;  /*used to acknowledge if I should register keys or not*/
	Player user;
	Player program;/*its what they were called in Tron :P */
    /*vertical and horizontal lengths sepaated, it doesn't really matter, and saves computing which is which n redraw*/
    /*cannot do linked list easily, memory management is only a thing if we implement it, hence large arrays*/
}
#endif

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