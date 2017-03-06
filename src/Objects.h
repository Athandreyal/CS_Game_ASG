#ifndef OBJECTS_H
#define OBJECTS_H
#include "TYPES.H"
extern UINT8 STICKMAN[];
extern UINT8 CYCLE1[4][8];
extern UINT8 CYCLE2[4][8];
void drawBackground(UINT8* base);
void drawLives(UINT8* base, int lives, int player);
#define BIKE_HEIGHT 	8
#define FIGURE_HEIGHT 	8
#define VBORDER 20;
#define HBORDER 80;
#define P1LIFEX 30
#define P1LIFEY 50
#define P2LIFEX 570
#define P2LIFEY 50
#endif