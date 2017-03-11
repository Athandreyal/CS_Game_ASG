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
    rndr_cyc(base, &(model->user));
    rndr_cyc(base, &(model->program));
/*    rndr_lw(base, model->grid);
*/}

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

void rndr_lw(UINT8 *base, UINT8 grid[][])
{
    ;
}

/* Render Cycle*/
void rndr_cyc(UINT8 *base, Player *player)
{  /*[n,e,s,w]*/
/*    UINT8 (*bmp)[8]; /*agnostic array pointer*/
/*    if (player->isUser) bmp = CYCLE1;
    else                  bmp = CYCLE2;
*/
    FILE *f = fopen("log.txt", "a");
    fprintf(f,"63 isUser: %d, x: %d, y: %d, dir: {%d,%d}\n", player->isUser, player->cycle.x, player->cycle.y, player->cycle.direction[0], player->cycle.direction[1]);
    fclose(f);
    /*undraw at current locale*/
                                        /*  y   */
    if      (player->cycle.lastPos[3] ==  1){             /*SOUTH*/
        p_btmp_8(base, player->cycle.lastPos[0],player->cycle.lastPos[1],(player->isUser?CYCLE2[2]:CYCLE1[2]));
        }                                /*  x   */
    else if (player->cycle.lastPos[2] ==  1){             /*EAST*/
        p_btmp_8(base, player->cycle.lastPos[0],player->cycle.lastPos[1],(player->isUser?CYCLE2[1]:CYCLE1[1]));
        }                                /*  y   */
    else if (player->cycle.lastPos[3] == -1){             /*NORTH*/
        p_btmp_8(base, player->cycle.lastPos[0],player->cycle.lastPos[1],(player->isUser?CYCLE2[0]:CYCLE1[0]));
        }                                /*  x   */
    else if (player->cycle.lastPos[2] == -1){             /*WEST*/
        p_btmp_8(base, player->cycle.lastPos[0],player->cycle.lastPos[1],(player->isUser?CYCLE2[3]:CYCLE1[3]));    
        }
    /*draw at new locale*/
                                        /*  y   */
    if      (player->cycle.direction[1] ==  1){             /*SOUTH*/
        p_btmp_8(base, player->cycle.x,player->cycle.y,(player->isUser?CYCLE2[2]:CYCLE1[2]));
        }                                /*  x   */
    else if (player->cycle.direction[0] ==  1){             /*EAST*/
        p_btmp_8(base, player->cycle.x,player->cycle.y,(player->isUser?CYCLE2[1]:CYCLE1[1]));
        }                                /*  y   */
    else if (player->cycle.direction[1] == -1){             /*NORTH*/
        p_btmp_8(base, player->cycle.x,player->cycle.y,(player->isUser?CYCLE2[0]:CYCLE1[0]));
        }                                /*  x   */
    else if (player->cycle.direction[0] == -1){             /*WEST*/
        p_btmp_8(base, player->cycle.x,player->cycle.y,(player->isUser?CYCLE2[3]:CYCLE1[3]));    
        }
}