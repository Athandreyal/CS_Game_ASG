/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil
*/
#ifndef CONSTANT_H
#define CONSTANT_H
#include "TYPES.H"

/*    CURRENT UNITS      */
extern UINT8 SCREEN_WIDTH;
extern UINT8 MSB;
extern UINT8 REMAINDER_MAX;
extern UINT8 BITS_PER;
extern UINT8 SHIFT;
extern UINT8 LINE_BODY;


/*     OTHER  UNITS      */
extern UINT16 SCREEN_WIDTH_PIX;
extern UINT16 SCREEN_HEIGHT_PIX;
extern int    BMP_OFFSET;
extern UINT8  VBORDER_BITS;
extern UINT8  HBORDER_BITS;
extern UINT8  SCREEN_WIDTH_WORD;
extern UINT8  SCREEN_WIDTH_LONG;
extern UINT8  SHIFT_WORD;
extern UINT16 LINE_BODY_WORD;

extern int P1STARTX;
extern int P1STARTY;
extern int P2STARTX;
extern int P2STARTY;

extern int PLAYER_LIVES;

#endif