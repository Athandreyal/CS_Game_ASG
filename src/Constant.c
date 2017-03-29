/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    Primary game constants
*/
#include "Constant.h"

/*    CURRENT UNITS      */
const UINT8  SCREEN_WIDTH = 80;
const UINT8  MSB = 0x80;
const UINT8  REMAINDER_MAX = 7;
const UINT8  BITS_PER = 8;
const UINT8  SHIFT = 3;
const UINT8  LINE_BODY = 0xFF;


/*     OTHER  UNITS      */
const UINT16 SCREEN_WIDTH_PIX = 640;
const UINT16 SCREEN_HEIGHT_PIX = 400;
const int    BMP_OFFSET = -4;
const UINT8  VBORDER_BITS = 20;
const UINT8  HBORDER_BITS = 80;
const UINT8  SCREEN_WIDTH_WORD = 40;
const UINT8  SCREEN_WIDTH_LONG = 20;
const UINT8  SHIFT_WORD = 4;
const UINT16 LINE_BODY_WORD = 0xFFFF;

int P1STARTX = 320;
int P1STARTY = 361;
int P2STARTX = 320;
int P2STARTY = 31;

int PLAYER_LIVES = 5;
