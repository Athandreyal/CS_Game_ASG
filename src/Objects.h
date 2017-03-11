#ifndef OBJECTS_H
#define OBJECTS_H
#include "TYPES.H"

#define VBORDER 20;
#define HBORDER 80;
#define P1LIFEX 30
#define P1LIFEY 50
#define P2LIFEX 570
#define P2LIFEY 50
/*#define LIGHTPATHMAX 1000

/*
#define BIKE_HEIGHT     8
#define FIGURE_HEIGHT     8
*/

extern UINT8 STICKMAN[];
extern UINT8 CYCLE1[4][8];
extern UINT8 CYCLE2[4][8];
void drawBackground(UINT8* base);
void drawLives(UINT8* base, int lives, int player);



/*used to keep track of current segment, so we need not have many little segements unlessfrantic maneuvering*/
typedef struct LGTPATH{
    /* linked list catalouging lightwalls
    Update the wall pixel by pixel per movement at direction
    change save segment for later render calls*/
    /*cannot do linked list so easily, memory management is only a thing if we implement it*/
    int x;
    int y;
    int length;
    bool vertical;
}LGTPATH;

typedef struct Cycle {
    int x;
    int y;
    int speed;
    int direction[2];
    int lastPos[4];/* xy coords, direction[x,y] -- where we were so we can xor ourself*/
}Cycle;

typedef struct Player {
    Cycle cycle;
    int life;
    bool isUser; /*is user?*/
    int segments;/*to speed indexing of the path array, the index we're working on*/
    bool crashed;
}Player;

typedef struct Model{
    int active;  /*used to acknowledge if I should register keys or not*/
    Player user;
    Player program;/*its what they were called in Tron :P */
/*    UINT8 grid[320][200];
    /*vertical and horizontal lengths sepaated, it doesn't really matter, and saves computing which is which n redraw*/
    /*cannot do linked list easily, memory management is only a thing if we implement it, hence large arrays*/
}Model;

#endif