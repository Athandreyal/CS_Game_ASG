#ifndef OBJECTS_H
#define OBJECTS_H
extern const UINT8 STICKMAN[];
extern const UINT8 BIKE1[];
extern const UINT8 BIKE2[];
void drawBackground(void* base);
void drawLives(UINT8* base, int lives, int player);
#define BIKE_HEIGHT 	8
#define FIGURE_HEIGHT 	8
#define VBORDER = 20;
#define HBORDER = 80;
#define P1LIFEX = 30
#define P1LIFEY = 50
#define P2LIFEX = 346
#define P2LIFEY = 50
#endif