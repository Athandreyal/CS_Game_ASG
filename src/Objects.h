#ifndef OBJECTS_H
#define OBJECTS_H
#include "TYPES.H"
extern UINT8 STICKMAN[];
extern UINT8 CYCLE1[4][8];
extern UINT8 CYCLE2[4][8];
void drawBackground(UINT8* base);
void drawLives(UINT8* base, int lives, int player);
#define VBORDER 20;
#define HBORDER 80;
#define P1LIFEX 30
#define P1LIFEY 50
#define P2LIFEX 570
#define P2LIFEY 50
/*
#define BIKE_HEIGHT 	8
#define FIGURE_HEIGHT 	8
*/


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
}

struct typedef Cycle {
	int x;
	int y;
	int speed;
	int direction[2];
}Cycle;

struct typedef Player {
	Cycle cycle;
	int life;
    bool user; /*is user?*/
    int segments;/*to speed indexing of the path array, the index we're working on*/
    bool crashed;
    LGTPATH VPATH_ar[LIGHTPATHMAX];/*hoping 1000 is adequate - vertical lengths only*/
    LGTPATH HPATH_ar[LIGHTPATHMAX];/*hoping 1000 is adequate - horizontal lengths only*/    
}Player;

#endif