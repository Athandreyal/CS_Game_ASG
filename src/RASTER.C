#include "raster.h"
#include "constant.h"
/*#include <stdio.h>*/


int MIN(int x, int y){/*move me soon!*/
    int ans = (x<y)?x:y;
    return ans;
}

/*plot pixel*/
void plot_pix(UINT8 *base, int x, int y)
{/* x is int 0-640, y is int 0-200.  Bytes imply width*/ 
    if (x >= 0 && x < SCREEN_WIDTH_PIX && y >= 0 && y < SCREEN_HEIGHT_PIX)
        *(base + y * SCREEN_WIDTH + (x >> SHIFT)) |= MSB >> (x & REMAINDER_MAX);
}

/*plot Horizontal line*/
void p_h_ln(UINT8 *base, int x, int y, int size)
{
    int col=0;
    UINT8 head = LINE_BODY;
    UINT8 body = LINE_BODY;
    UINT8 tail = LINE_BODY;
    if (size > 0 && x < SCREEN_WIDTH_PIX && y >= 0 && y < SCREEN_HEIGHT_PIX){
        if (x < 0){
            size += x;
            x = 0;
            }
        size = MIN(size, SCREEN_WIDTH_PIX - x);
        if (size > 0){/*work to do*/
            head = head >> (x & REMAINDER_MAX);
            tail = tail << (BITS_PER - ((x + size) & REMAINDER_MAX));
            col = x >> SHIFT;
            if ((size + x) >> SHIFT == col){/*then we start and end in same block, special case, mask both ends*/
                body = head & tail;
                *(base + y * SCREEN_WIDTH + col) ^= body; 
            }
            else {/*start mask, body, end mask*/
                *(base + y * SCREEN_WIDTH + col) ^= head;
                size -= MIN(size,BITS_PER-(x & REMAINDER_MAX));
                while(size > REMAINDER_MAX){
                    col++;
                    *(base + (y * SCREEN_WIDTH + col)) ^= body;
                    size -= BITS_PER;
                }
                col++;
                *(base + y * SCREEN_WIDTH + col) ^= tail;
            }
        }
     }
}

/*Plot Vertical Line*/
void p_v_ln(UINT8 *base, int x, int y, int size)
{
    int i;
    UINT8 col = x >> SHIFT;
    UINT8 pix = MSB >> (x & REMAINDER_MAX);
    if (x >= 0 && x < SCREEN_WIDTH_PIX){
        if (y < 0){
            size += y;
            y = 0;
        }
        size = MIN(size, SCREEN_HEIGHT_PIX - y);
        for(i = 0;i < size;i++)
            *(base + (y+i) * SCREEN_WIDTH + col) ^= pix;
    }
}

/*plot 8*8 bitmap*/
void p_btmp_8(UINT8 *base, int x, int y, const UINT8 bitmap[])
{/*plotted from upper left corner as (0,0) to (7,7) at lower right*/
    int i;
    UINT8 LHalf;                        UINT8 RHalf;
    UINT8 L_Offset = x & REMAINDER_MAX; UINT8 R_Offset = BITS_PER - (x & REMAINDER_MAX);
    UINT8 Lmask = LINE_BODY << R_Offset;     UINT8 Rmask = LINE_BODY >> L_Offset;
    UINT8 col = x >> SHIFT;
    for (i = 0;i < 8;i++){
        if (y + i > 0 && y + i < SCREEN_HEIGHT_PIX){
            if (x & REMAINDER_MAX == 0 && x > 0 && x < SCREEN_WIDTH_PIX)
                *(base + (y+i) * SCREEN_WIDTH + col) ^= bitmap[i];
            else{
                if (x > 0 && x < SCREEN_WIDTH_PIX){
                    LHalf = bitmap[i] >> L_Offset;
                    *(base + (y+i) * SCREEN_WIDTH + col) ^= LHalf;
                }
                if (x+BITS_PER > 0 && x+BITS_PER < SCREEN_WIDTH_PIX){
                    RHalf = bitmap[i] << R_Offset;
                    *(base + (y+i) * SCREEN_WIDTH + col+1) ^= RHalf;
                }
            }
        }
    }
}

/*clear screen*/
void clr_scrn(UINT8 base[])
{
    int x,y;
    UINT32 *clrBase = (UINT32*)base;/*fewer ops in 32 bit;*/
    for (y = 0;y < SCREEN_HEIGHT_PIX;y++)
        for (x = 0;x < SCREEN_WIDTH_LONG;x++)
            *(clrBase + y* SCREEN_WIDTH_LONG + x) = 0;
}