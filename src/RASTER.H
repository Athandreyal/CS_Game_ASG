#ifndef RASTER_H
#define RASTER_H

#include "types.h"

/* [TO DO] the functions below are examples. Replace them! */
int MIN(int x, int y);
void plot_pix(UINT8 *base, int x, int y);
void p_h_ln(UINT8 *base, int x, int y, int size);
void p_v_ln(UINT8 *base, int x, int y, int size);
void p_btmp_8(UINT8 *base, int x, int y, const UINT8 *bitmap);
void clr_scrn(void *base);

#endif
