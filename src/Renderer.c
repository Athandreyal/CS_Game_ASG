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

#include <stdio.h>

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
    uRndrCyc(base, &(model->user));
    uRndrCyc(base, &(model->program));
    rndr_lw(base, &(model->user.cycle));
    rndr_lw(base, &(model->program.cycle));
    setLPos(&(model->user.cycle));
    setLPos(&(model->program.cycle));
    rndr_cyc(base, &(model->user));
    rndr_cyc(base, &(model->program));
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
    cycle->lastPos2[0] = cycle->lastPos1[0];
    cycle->lastPos2[1] = cycle->lastPos1[1];
    cycle->lastPos2[2] = cycle->lastPos1[2];
    cycle->lastPos2[3] = cycle->lastPos1[3];
    cycle->lastPos1[0] = cycle->x;
    cycle->lastPos1[1] = cycle->y;
    cycle->lastPos1[2] = cycle->direction[0];
    cycle->lastPos1[3] = cycle->direction[1];
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
void rndr_lw(UINT8 *base, Cycle *cycle)
{
    int x, y, length;
    if (cycle->lastPos2[0] > 0 && cycle->lastPos2[1] > 0){
        if (cycle->lastPos1[0] == cycle->lastPos2[0]){
            x = cycle->lastPos1[0];
            y = (cycle->lastPos1[1]<cycle->lastPos2[1]?cycle->lastPos1[1]:cycle->lastPos2[1]);
            length = (cycle->lastPos1[1]>cycle->lastPos2[1]?cycle->lastPos1[1]:cycle->lastPos2[1]) - y;/* + (cycle->lastPos2[3]==1);*/
            p_v_ln(base, x, y, length);
            }
        else{
            x = (cycle->lastPos1[0]<cycle->lastPos2[0]?cycle->lastPos1[0]:cycle->lastPos2[0]);
            y = cycle->lastPos1[1];
            length = (cycle->lastPos1[0]>cycle->lastPos2[0]?cycle->lastPos1[0]:cycle->lastPos2[0]) - x;/* + (cycle->lastPos2[2]==1);*/
            p_h_ln(base, x, y, length);
            }
        }
        /*funky math to figure this out*/
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  uRndrCyc
// Purpose:        un-renders light cycle using positional history to determine position and orientation
// Inputs:         UINT8 *base  :  the frame buffer
//                 Player *player :  the current player whose cycle will be removed
///////////////////////////////////////////////////////////////////
*/
void uRndrCyc(UINT8 *base, Player *player){
    /*[n,e,s,w]*/
    /*undraw at current locale*/
                                        /*  y   */
    if      (player->cycle.lastPos1[3] ==  1){             /*SOUTH*/
        p_btmp_8(base, player->cycle.lastPos1[0]+BMP_OFFSET,player->cycle.lastPos1[1]+BMP_OFFSET,(player->isUser?CYCLE2[2]:CYCLE1[2]));
        }                                /*  x   */
    else if (player->cycle.lastPos1[2] ==  1){             /*EAST*/
        p_btmp_8(base, player->cycle.lastPos1[0]+BMP_OFFSET,player->cycle.lastPos1[1]+BMP_OFFSET,(player->isUser?CYCLE2[1]:CYCLE1[1]));
        }                                /*  y   */
    else if (player->cycle.lastPos1[3] == -1){             /*NORTH*/
        p_btmp_8(base, player->cycle.lastPos1[0]+BMP_OFFSET,player->cycle.lastPos1[1]+BMP_OFFSET,(player->isUser?CYCLE2[0]:CYCLE1[0]));
        }                                /*  x   */
    else if (player->cycle.lastPos1[2] == -1){             /*WEST*/
        p_btmp_8(base, player->cycle.lastPos1[0]+BMP_OFFSET,player->cycle.lastPos1[1]+BMP_OFFSET,(player->isUser?CYCLE2[3]:CYCLE1[3]));    
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
void rndr_cyc(UINT8 *base, Player *player)
{  /*[n,e,s,w]*/
    /*draw at new locale*/
    if      (player->cycle.direction[1] ==  1){             /*SOUTH*/
        p_btmp_8(base, player->cycle.x+BMP_OFFSET,player->cycle.y+BMP_OFFSET,(player->isUser?CYCLE2[2]:CYCLE1[2]));
        }                                /*  x   */
    else if (player->cycle.direction[0] ==  1){             /*EAST*/
        p_btmp_8(base, player->cycle.x+BMP_OFFSET,player->cycle.y+BMP_OFFSET,(player->isUser?CYCLE2[1]:CYCLE1[1]));
        }                                /*  y   */
    else if (player->cycle.direction[1] == -1){             /*NORTH*/
        p_btmp_8(base, player->cycle.x+BMP_OFFSET,player->cycle.y+BMP_OFFSET,(player->isUser?CYCLE2[0]:CYCLE1[0]));
        }                                /*  x   */
    else if (player->cycle.direction[0] == -1){             /*WEST*/
        p_btmp_8(base, player->cycle.x+BMP_OFFSET,player->cycle.y+BMP_OFFSET,(player->isUser?CYCLE2[3]:CYCLE1[3]));    
        }
}