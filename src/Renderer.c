#include"Renderer.h"
#include "RASTER.H"

#include <stdio.h>

void render(UINT8 *base, Model *model){
    /*render black */
    rndr_blk(base, model);
    /*render field*/
    rndr_fld(base, model);    /*gifting this control over the paths, since its a field thing*/
}

void rndr_blk(UINT8 *base, Model *model){/*square corners, overwrites whatever it finds along border!*/
    UINT16* rebase = (UINT16*)base;
    int Vmin = 20;/*why can't I use #define values here??*/
    int Vmax = SCREEN_HEIGHT - 20;
    int Hmin = 80>>4;
    int Hmax = (SCREEN_WIDTH - 80) >> 4;
    int x,y;
    clr_scrn(base);
    for(x = 0;x < 40;x++){
        for (y = 0;y < 400;y++){
            if (y < Vmin || y >= Vmax || x < Hmin || x >= Hmax)
                *(rebase + y * 40 + x) = 0xFFFF;
            }
        }
        
    rndr_lif(base, &(model->user));
    rndr_lif(base, &(model->program));
}

void rndr_fld(UINT8 *base, Model *model)
{/*field?  should handle the paths then*/
    /*need to implement the field manipulation in here*/
    /*field involves cycles and walls, maybe explosions if we implement*/
    uRndrCyc(base, &(model->user));
    uRndrCyc(base, &(model->program));
    rndr_lw(base, &(model->user.cycle));
    rndr_lw(base, &(model->program.cycle));
    setLPos(&(model->user.cycle));
    setLPos(&(model->program.cycle));
    rndr_cyc(base, &(model->user));
    rndr_cyc(base, &(model->program));
}

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

void rndr_lif(UINT8 *base, Player *player)
{
    int i;
    for (i = 0;i < player->life;i++){
        if (player->isUser)
            p_btmp_8(base, P1LIFEX + (i<<3),P1LIFEY, STICKMAN);
        else
            p_btmp_8(base, P2LIFEX + (i<<3),P2LIFEY, STICKMAN);
    }
}

void rndr_lw(UINT8 *base, Cycle *cycle)
{
    int x, y, length;
    if (cycle->lastPos2[0] > 0 && cycle->lastPos2[1] > 0){
        if (cycle->lastPos1[0] == cycle->lastPos2[0]){
            x = cycle->lastPos1[0];
            y = (cycle->lastPos1[1]<cycle->lastPos2[1]?cycle->lastPos1[1]:cycle->lastPos2[1]);
            length = (cycle->lastPos1[1]>cycle->lastPos2[1]?cycle->lastPos1[1]:cycle->lastPos2[1]) - y + (cycle->lastPos2[3]==1);
            p_v_ln(base, x, y, length);
            }
        else{
            x = (cycle->lastPos1[0]<cycle->lastPos2[0]?cycle->lastPos1[0]:cycle->lastPos2[0]);
            y = cycle->lastPos1[1];
            length = (cycle->lastPos1[0]>cycle->lastPos2[0]?cycle->lastPos1[0]:cycle->lastPos2[0]) - x + (cycle->lastPos2[2]==1);
            p_h_ln(base, x, y, length);
            }
        }
        /*funky math to figure this out*/
}

void uRndrCyc(UINT8 *base, Player *player){
    /*[n,e,s,w]*/
    int o = -4;/*from center pixel to upper left pixel for both x and y
    /*undraw at current locale*/
                                        /*  y   */
    if      (player->cycle.lastPos1[3] ==  1){             /*SOUTH*/
        p_btmp_8(base, player->cycle.lastPos1[0]+o,player->cycle.lastPos1[1]+o,(player->isUser?CYCLE2[2]:CYCLE1[2]));
        }                                /*  x   */
    else if (player->cycle.lastPos1[2] ==  1){             /*EAST*/
        p_btmp_8(base, player->cycle.lastPos1[0]+o,player->cycle.lastPos1[1]+o,(player->isUser?CYCLE2[1]:CYCLE1[1]));
        }                                /*  y   */
    else if (player->cycle.lastPos1[3] == -1){             /*NORTH*/
        p_btmp_8(base, player->cycle.lastPos1[0]+o,player->cycle.lastPos1[1]+o,(player->isUser?CYCLE2[0]:CYCLE1[0]));
        }                                /*  x   */
    else if (player->cycle.lastPos1[2] == -1){             /*WEST*/
        p_btmp_8(base, player->cycle.lastPos1[0]+o,player->cycle.lastPos1[1]+o,(player->isUser?CYCLE2[3]:CYCLE1[3]));    
        }
}

/* Render Cycle*/
void rndr_cyc(UINT8 *base, Player *player)
{  /*[n,e,s,w]*/
    int o = -4;/*from center pixel to upper left pixel for both x and y*/
    /*draw at new locale*/
    if      (player->cycle.direction[1] ==  1){             /*SOUTH*/
        p_btmp_8(base, player->cycle.x+o,player->cycle.y+o,(player->isUser?CYCLE2[2]:CYCLE1[2]));
        }                                /*  x   */
    else if (player->cycle.direction[0] ==  1){             /*EAST*/
        p_btmp_8(base, player->cycle.x+o,player->cycle.y+o,(player->isUser?CYCLE2[1]:CYCLE1[1]));
        }                                /*  y   */
    else if (player->cycle.direction[1] == -1){             /*NORTH*/
        p_btmp_8(base, player->cycle.x+o,player->cycle.y+o,(player->isUser?CYCLE2[0]:CYCLE1[0]));
        }                                /*  x   */
    else if (player->cycle.direction[0] == -1){             /*WEST*/
        p_btmp_8(base, player->cycle.x+o,player->cycle.y+o,(player->isUser?CYCLE2[3]:CYCLE1[3]));    
        }
}