/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil
*/
#ifndef RASTER_H
#define RASTER_H
#include "TYPES.H"



/* [TO DO] the functions below are examples. Replace them! */
int MIN(int x, int y);
void plot_pix(UINT8 *base, int x, int y);
void p_h_ln(UINT8 *base, int x, int y, int size);
void p_v_ln(UINT8 *base, int x, int y, int size);
void p_btmp_8(UINT8 *base, int x, int y, const UINT8 bitmap[]);
void clr_scrn(UINT8 *base);
void plotSplsh(UINT8 *base,UINT32 bitmap[]);

#endif
