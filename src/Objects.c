#include "Objects.h"
#include "raster.h"


/*UINT8 STICKMAN[] = {0xEF, 0xEF, 0x93, 0x6D, 0xEF, 0xD7, 0xBB, 0xBB};*/
UINT8 STICKMAN[] = {0x10, 0x10, 0x6C, 0x92, 0x10, 0x28, 0x44, 0x44};


/*bike orientations: N,E,S,W, ie, W = bike1[3], with third row being bike1[3][2], etc*/
UINT8 CYCLE1[4][8] =  {     {0x00, 0x08, 0x1C, 0x14, 0x2A, 0x6B, 0x77, 0x77},
                            {0x00, 0x70, 0x78, 0x66, 0x1B, 0x66, 0x78, 0x70}, 
                            {0x00, 0x77, 0x77, 0x6B, 0x2A, 0x14, 0x1C, 0x08},
                            {0x00, 0x07, 0x0F, 0x33, 0x6C, 0x33, 0x0F, 0x07} 
                            };
UINT8 CYCLE2[4][8] = {      {0x00, 0x08, 0x14, 0x14, 0x22, 0x41, 0x49, 0x77},
                            {0x00, 0x70, 0x48, 0x46, 0x21, 0x46, 0x48, 0x70},
                            {0x00, 0x77, 0x49, 0x41, 0x22, 0x14, 0x14, 0x08},
                            {0x00, 0x07, 0x09, 0x31, 0x42, 0x31, 0x09, 0x07} 
                            };
                        