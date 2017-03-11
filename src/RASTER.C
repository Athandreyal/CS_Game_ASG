#include "raster.h"

/*#include <stdio.h>*/


int MIN(int x, int y){/*move me soon!*/
    int ans = (x<y)?x:y;
    return ans;
}

/*plot pixel*/
void plot_pix(UINT8 *base, int x, int y)
{/* x is int 0-640, y is int 0-200.  Bytes imply width*/ 
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
        *(base + y * 80 + (x >> 3)) |= 0x80 >> (x & 7);
}

/*plot Horizontal line*/
void p_h_ln(UINT8 *base, int x, int y, int size)
{
    int col=0;
    UINT8 head = 0xFF;
    UINT8 body = 0xFF;
    UINT8 tail = 0xFF;
    if (size > 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT){
        if (x < 0){
            size += x;
            x = 0;
            }
        size = MIN(size, SCREEN_WIDTH - x);
        if (size > 0){/*work to do*/
            head = head >> (x & 7);
            tail = tail << (8 - ((x + size) & 7));
            col = x >> 3;
            if ((size + x) >> 3 == col){/*then we start and end in same block, special case, mask both ends*/
                body = head & tail;
                *(base + y * 80 + col) |= body; 
            }
            else {/*start mask, body, end mask*/
                *(base + y * 80 + col) |= head;
                size -= MIN(size,8-(x & 7));
                while(size > 7){
                    col++;
                    *(base + (y * 80 + col)) |= body;
                    size -= 8;
                }
                col++;
                *(base + y * 80 + col) |= tail;
            }
        }
     }
}

/*Plot Vertical Line*/
void p_v_ln(UINT8 *base, int x, int y, int size)
{
    int i;
    UINT8 col = x >> 3;
    UINT8 pix = 0x80 >> (x & 7);
    if (x >= 0 && x < SCREEN_WIDTH){
        if (y < 0){
            size += y;
            y = 0;
        }
        size = MIN(size, SCREEN_HEIGHT - y);
        for(i = 0;i < size;i++)
            *(base + (y+i) * 80 + col) |= pix;
    }
}

/*plot 8*8 bitmap*/
void p_btmp_8(UINT8 *base, int x, int y, const UINT8 bitmap[])
{/*plotted from upper left corner as (0,0) to (7,7) at lower right*/
    int i;
/*    FILE *f = fopen("log.txt", "a");*/
    UINT8 LHalf;                        UINT8 RHalf;
    UINT8 L_Offset = x & 7;             UINT8 R_Offset = 8 - (x & 7);
    UINT8 Lmask = 0xFF << R_Offset;     UINT8 Rmask = 0xFF >> L_Offset;
    UINT8 col = x >> 3;
/*    fprintf(f,"p_btmp_8 %d %d\n",x,y);*/
    for (i = 0;i < 8;i++){
        if (y + i > 0 && y + i < SCREEN_HEIGHT){
/*            fprintf(f,"80 x: %d, y: %d, %04x\n", x, y+i, bitmap[i]);*/
            if (x & 7 == 0 && x > 0 && x < SCREEN_WIDTH)
                *(base + (y+i) * 80 + col) ^= bitmap[i];
            else{
                if (x > 0 && x < SCREEN_WIDTH){
                    LHalf = bitmap[i] >> L_Offset;
/*                    *(base + (y+i) * 80 + col) &= Lmask;
*/                    *(base + (y+i) * 80 + col) ^= LHalf;
                }
                if (x+8 > 0 && x+8 < SCREEN_WIDTH){
                    RHalf = bitmap[i] << R_Offset;
/*                    *(base + (y+i) * 80 + col+1) &= Rmask;
*/                    *(base + (y+i) * 80 + col+1) ^= RHalf;
                }
            }
        }
    }
/*    fclose(f);*/
}

/*clear screen*/
void clr_scrn(UINT8 base[])
{
    int x,y;
    UINT32 *clrBase = (UINT32*)base;/*fewer ops in 32 bit;*/
    for (y = 0;y < 400;y++)
        for (x = 0;x < 20;x++)
            *(clrBase + y* 20 + x) = 0;
}