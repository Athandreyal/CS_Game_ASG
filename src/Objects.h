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
void drawBackground(UINT8* base);
void drawLives(UINT8* base, int lives, int player);



/*used to keep track of current segment, so we need not have many little segements unlessfrantic maneuvering*/
typedef struct Cycle {
    int x;
    int y;
    int speed;
    int direction[2];
    int lastPos1[4];/* xy coords, direction[x,y] -- where were we*/
    int lastPos2[4];/* xy coords, direction[x,y] -- where were we*/
    int player;/*0 for player, 1 for AI, 2 for ghost*/
    UINT8 *bmp;
}Cycle;

typedef struct Player {
    Cycle cycle;
    int life;
    bool isUser; /*is user?*/
    bool crashed;
}Player;

typedef struct Model{
    int active;  /*used to acknowledge if I should register keys or not*/
    Player user;
    Player ghost;/*used to predict of 'program' will crash afte next move*/
    Player program;/*its what they were called in Tron :P */
}Model;

#endif