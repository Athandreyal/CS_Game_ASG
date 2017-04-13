/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    Game object struct definitions
*/

#ifndef OBJECTS_H
#define OBJECTS_H
#include "TYPES.H"

#define VBORDER 20;
#define HBORDER 80;
#define P1LIFEX 30
#define P1LIFEY 50
#define P2LIFEX 570
#define P2LIFEY 50

extern UINT8 STICKMAN[];
extern UINT8 CYCLE1[4][8];
extern UINT8 CYCLE2[4][8];
extern UINT32 SPLASH[];
void drawBackground(UINT8* base);
void drawLives(UINT8* base, int lives, int player);


/*
    Collision expects the current frame to be up to date, double buffering means the current frame is one update out of date.
    
    double buffering messes with pos and lastPos.
    double buffering results in pos, and lastPos2 being local, and lastPos being on the other buffer
        -this means the LW and collision will be out of step
    I am expecting unrender to undo lastPos, unrender must undo lastPos2 now

    
    I am expecting the LW to be drawn between LP2 and LP1, but these are not on the same buffer, problems result;
        -LW expected to be one step behing the player.
        -LW should draw last TWO wall segments on each call.
        -LP3 is now required.
    
    the above ~should~ correct for double buffering.
    
/*used to keep track of current segment, so we need not have many little segements unlessfrantic maneuvering*/
typedef struct Cycle {
    int x;
    int y;
    int speed;
    int direction[2];
    int last[3][4];/* xy coords, direction[x,y] -- where were we*/
    int player;/*0 for player, 1 for AI, 2 for ghost*/
    UINT8 *bmp;
    UINT8 *lastbmp[3];
}Cycle;

typedef struct Player {
    Cycle cycle;
    int life;
    bool isUser; /*is user?*/
    bool crashed;
}Player;

typedef struct Model{
    int mode;  
    int mode2;  
    Player user;
    Player ghost;/*used to predict of 'program' will crash afte next move*/
    Player program;/*its what they were called in Tron :P */
}Model;

#endif