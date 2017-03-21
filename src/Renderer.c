/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    raster driver functions: access the model and call the appropriate raster code to display it.
*/

#include"Renderer.h"
#include "RASTER.H"
#include "Constant.h"


/*
///////////////////////////////////////////////////////////////////
// Function Name:  render
// Purpose:        top level render call to generate a full frame
// Inputs:         UINT8 *base  :  the frame buffer
//                 Model *model :  the current game model, to be drawn
///////////////////////////////////////////////////////////////////
*/
void render(UINT8 *base, Model *model){
    /*render black */
    rndr_bak(base, model);
    /*render field*/
    rndr_fld(base, model);    /*gifting this control over the paths, since its a field thing*/
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  rndr_bak
// Purpose:        renders full background, effectively all details not part of the active game grid
// Inputs:         UINT8 *base  :  the frame buffer
//                 Model *model :  the current game model, to be drawn
///////////////////////////////////////////////////////////////////
*/
void rndr_bak(UINT8 *base, Model *model){/*square corners, overwrites whatever it finds along border!*/
    UINT16* rebase = (UINT16*)base;
    int Vmin = VBORDER_BITS;/*why can't I use #define values here??*/
    int Vmax = SCREEN_HEIGHT_PIX - VBORDER_BITS;
    int Hmin = HBORDER_BITS >> SHIFT_WORD;
    int Hmax = (SCREEN_WIDTH_PIX - HBORDER_BITS) >> SHIFT_WORD;
    int x,y;
	printf("\033f");
	fflush(stdout);
    clr_scrn(base);
    for(x = 0;x < SCREEN_WIDTH_WORD;x++){
        for (y = 0;y < SCREEN_HEIGHT_PIX;y++){
            if (y < Vmin || y >= Vmax || x < Hmin || x >= Hmax)
                *(rebase + y * SCREEN_WIDTH_WORD + x) = LINE_BODY_WORD;
            }
        }
        
    rndr_lif(base, &(model->user));
    rndr_lif(base, &(model->program));
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  rndr_fld
// Purpose:        renders game grid incrementally: calls to unrender the current cycles from their old positions using position history
//                                                  calls to render the lightwalls they produce using position history
//                                                  calls to update the position history
//                                                  calls to render the cycles in their new positions
// Inputs:         UINT8 *base  :  the frame buffer
//                 Model *model :  the current game model, to be drawn
///////////////////////////////////////////////////////////////////
*/
void rndr_fld(UINT8 *base, Model *model)
{
    rndr_cyc(base, &(model->user),1);
    rndr_cyc(base, &(model->program),1);
    rndr_lw(base, &(model->user.cycle),0);
    rndr_lw(base, &(model->user.cycle),1);
    rndr_lw(base, &(model->program.cycle),0);
    rndr_lw(base, &(model->program.cycle),1);
    setLPos(&(model->user.cycle));
    setLPos(&(model->program.cycle));
    rndr_cyc(base, &(model->user),-1);
    rndr_cyc(base, &(model->program),-1);
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  setLPos
// Purpose:        Position history, used to know where to unrender the cycles, and where to draw light walls
// Inputs:         UINT8 *base  :  the frame buffer
//                 Model *model :  the current game model, to be drawn
///////////////////////////////////////////////////////////////////
*/
void setLPos(Cycle* cycle){
    cycle->last[2][0] = cycle->last[1][0];
    cycle->last[2][1] = cycle->last[1][1];
    cycle->last[2][2] = cycle->last[1][2];
    cycle->last[2][3] = cycle->last[1][3];
    cycle->last[1][0] = cycle->last[0][0];
    cycle->last[1][1] = cycle->last[0][1];
    cycle->last[1][2] = cycle->last[0][2];
    cycle->last[1][3] = cycle->last[0][3];
    cycle->last[0][0] = cycle->x;
    cycle->last[0][1] = cycle->y;
    cycle->last[0][2] = cycle->direction[0];
    cycle->last[0][3] = cycle->direction[1];
    cycle->lastbmp[2] = cycle->lastbmp[1];
    cycle->lastbmp[1] = cycle->lastbmp[0];
    cycle->lastbmp[0] = cycle->bmp;
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  rndr_lif
// Purpose:        renders the given player's lives
// Inputs:         UINT8 *base    :  the frame buffer
//                 Player *player :  the current player whose lives will be drawn
///////////////////////////////////////////////////////////////////
*/
void rndr_lif(UINT8 *base, Player *player)
{
    int i;
    for (i = 0;i < player->life;i++){
        if (player->isUser)
            p_btmp_8(base, P1LIFEX + (i<<SHIFT),P1LIFEY, STICKMAN);
        else
            p_btmp_8(base, P2LIFEX + (i<<SHIFT),P2LIFEY, STICKMAN);
    }
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  rndr_lw
// Purpose:        renders game grid light walls using positional history
// Inputs:         UINT8 *base  :  the frame buffer
//                 Cycle *cycle :  the current cycle whose light wall will be drawn
///////////////////////////////////////////////////////////////////
*/
void rndr_lw(UINT8 *base, Cycle *cycle, int index)
{  /*index will be either 1 or 2 for last*/
    int x, y, length;
    if (cycle->last[index+1][0] > 0 && cycle->last[index+1][1] > 0){
        if (cycle->last[index][0] == cycle->last[index+1][0]){
            x = cycle->last[index][0];
            y = (cycle->last[index][1]<cycle->last[index+1][1]?cycle->last[index][1]:cycle->last[index+1][1]);
            length = (cycle->last[index][1]>cycle->last[index+1][1]?cycle->last[index][1]:cycle->last[index+1][1]) - y;
            p_v_ln(base, x, y, length);
            }
        else{
            x = (cycle->last[index][0]<cycle->last[index+1][0]?cycle->last[index][0]:cycle->last[index+1][0]);
            y = cycle->last[index][1];
            length = (cycle->last[index][0]>cycle->last[index+1][0]?cycle->last[index][0]:cycle->last[index+1][0]) - x;
            p_h_ln(base, x, y, length);
            }
        }
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  rndr_cyc
// Purpose:        renders light cycle using the models co-ordinates for the cycle to position it
// Inputs:         UINT8 *base  :  the frame buffer
//                 Player *player :  the current player whose cycle will be rendered
///////////////////////////////////////////////////////////////////
*/
void rndr_cyc(UINT8 *base, Player *player, int index)
{  /*[n,e,s,w]*/
    /*draw at new locale*/
    if (index < 0)
        p_btmp_8(base, player->cycle.x+BMP_OFFSET,player->cycle.y+BMP_OFFSET,player->cycle.bmp);
    else
        p_btmp_8(base, player->cycle.last[index][0]+BMP_OFFSET,player->cycle.last[index][1]+BMP_OFFSET,player->cycle.lastbmp[index]);
}