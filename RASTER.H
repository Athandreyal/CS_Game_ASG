#ifndef RASTER_H
#define RASTER_H

#include "types.h"

/* [TO DO] the functions below are examples. Replace them! */

void plot_pix(UINT16 *base, int x, int y);
void p_h_ln(UINT16 *base, int x, int y, int size);
void p_v_ln(UINT16 *base, int x, int y, int size);
void p_btmp_8(UINT16 *base, int x, int y, UINT8 *bitmap);
void clr_scrn(UINT16 *base);

#endif
