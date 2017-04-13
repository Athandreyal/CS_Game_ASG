/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    raster graphics functions
*/
#include "raster.h"
#include "constant.h"


/*
///////////////////////////////////////////////////////////////////
// Function Name:  MIN
// Purpose:        small wrapper for ternary to determine smaller of two ints
// Inputs:         int x, y : the values to be compared    
// Outputs:        int ans: the smaller of x and y
///////////////////////////////////////////////////////////////////
*/
int MIN(int x, int y){/*move me soon!*/
    int ans = (x<y)?x:y;
    return ans;
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  plot_pix
// Purpose:        enable selected bit via masking
// Inputs:         UINT8 *base: the screen buffer
//                 int x, y   : the x and y co-ordinate to enable
///////////////////////////////////////////////////////////////////
*/
void plot_pix(UINT8 *base, int x, int y)
{/* x is int 0-640, y is int 0-200.  Bytes imply width*/ 
    if (x >= 0 && x < SCREEN_WIDTH_PIX && y >= 0 && y < SCREEN_HEIGHT_PIX)
        *(base + y * SCREEN_WIDTH + (x >> SHIFT)) |= MSB >> (x & REMAINDER_MAX);
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  p_h_ln
// Purpose:        enable a series of bits via masking to draw a horizontal line
// Inputs:         UINT8 *base: the screen buffer
//                 int x, y   : the x and y co-ordinate to begin at
//                 int size   : the length of the line to draw
///////////////////////////////////////////////////////////////////
*/
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

/*
///////////////////////////////////////////////////////////////////
// Function Name:  p_v_ln
// Purpose:        enable a pattern of bits via masking to draw a vertical line
// Inputs:         UINT8 *base: the screen buffer
//                 int x, y   : the x and y co-ordinate to begin at
//                 int size   : the length of the line to draw
///////////////////////////////////////////////////////////////////
*/
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

/*
///////////////////////////////////////////////////////////////////
// Function Name:  p_btmp_8
// Purpose:        toggle a pattern of bits to enable or disable a bitmap.
// Inputs:         UINT8 *base: the screen buffer
//                 int x, y   : the x and y co-ordinate to begin at
//                 const UINT8 bitmap:  the bitmap to be drawn, assumed 8x8;
///////////////////////////////////////////////////////////////////
*/
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


/*
///////////////////////////////////////////////////////////////////
// Function Name:  clr_scrn
// Purpose:        obliterates all screen content to achieve a fresh state
// Inputs:         UINT8 *base: the screen buffer
///////////////////////////////////////////////////////////////////
*/
void clr_scrn(UINT8 base[])
{
    int x,y;
    UINT32 *clrBase = (UINT32*)base;/*fewer ops in 32 bit;*/
    for (y = 0;y < SCREEN_HEIGHT_PIX;y++)
        for (x = 0;x < SCREEN_WIDTH_LONG;x++)
            *(clrBase + y* SCREEN_WIDTH_LONG + x) = 0;
}

void plotSplsh(UINT8 *base,UINT32 bitmap[])
{
    UINT32 *rebase = (UINT32*)base;
    int longs = 0;
    while(longs < 8000){
        *rebase^=bitmap[longs++];
        rebase++;
    }
}