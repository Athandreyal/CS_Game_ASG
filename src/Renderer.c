#include"Renderer.h"
#include "RASTER.H"

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
	rndr_lw(base, model->grid);
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

void rndr_lw(UINT8 *base, UINT8 grid[][])
{
    ;
}

/* Render Cycle*/
void rndr_cyc(UINT8 *base, Player *player)
{  /*[n,e,s,w]*/
    UINT8 (*bmp)[8]; /*agnostic array pointer*/
    if (player->isUser) bmp = CYCLE1;
    else                bmp = CYCLE2;

    if      (player->cycle.direction[1] ==  1)             /*NORTH*/
        p_btmp_8(base, player->cycle.x,player->cycle.y,bmp[0]);
    else if (player->cycle.direction[1] == -1)             /*SOUTH*/
        p_btmp_8(base, player->cycle.x,player->cycle.y,bmp[2]);
    else if (player->cycle.direction[0] ==  1)             /*EAST*/
        p_btmp_8(base, player->cycle.x,player->cycle.y,bmp[1]);
    else if (player->cycle.direction[0] == -1)             /*WEST*/
        p_btmp_8(base, player->cycle.x,player->cycle.y,bmp[3]);    
}