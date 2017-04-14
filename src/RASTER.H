/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil
*/
#ifndef RASTER_H
#define RASTER_H
#include "TYPES.H"
#include "globals.h"


/* [TO DO] the functions below are examples. Replace them! */
int MIN(int x, int y);
void plot_pix(int x, int y);
void p_h_ln(int x, int y, int size);
void p_v_ln(int x, int y, int size);
void p_btmp_8(int x, int y, const UINT8 bitmap[]);
void clr_scrn();
void plotSplsh(UINT32 bitmap[]);

#endif
