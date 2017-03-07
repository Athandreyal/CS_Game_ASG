
#include"Renderer.h"

void render(Model *model, UINT8 *base){
	/*render black */
	rndr_blk(base, model);
	/*render field*/
	rndr_fld(base, model);    /*gifting this control over the paths, since its a field thing*/
}

void rndr_blk(UINT8* base, Model *model){/*square corners, overwrites whatever it finds along border!*/
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
        
	rndr_lif(model->user,base);
	rndr_lif(model->program,base);
}

void rndr_fld(UINT8 *base, Model *model)
{/*field?  should handle the paths then*/
    /*need to implement the field manipulation in here*/
    /*field involves cycles and walls, maybe explosions if we implement*/
	rndr_cyc(model->user->cycle,base);
	rndr_cyc(model->program->cycle,base);
	rndr_lw(model->user->VPATH_ar);
	rndr_lw(model->user->HPATH_ar);
	rndr_lw(model->program->VPATH_ar);
	rndr_lw(model->program->HPATH_ar);
}

void rndr_lif(Player *player, UINT8 *base)
{
    int i;
	for (i = 0;i < player->life;i++){
        if (player->user)
            p_btmp_8(base, P1LIFEX + (i<<3),P1LIFEY, STICKMAN);
        else
            p_btmp_8(base, P2LIFEX + (i<<3),P2LIFEY, STICKMAN);
	}
}

void rndr_lw(lgt_walls *lw, UINT8 *base)
{
    LGTPATH VPTH_P0array[LIGHTPATHMAX];/*hoping 1000 is adequate - vertical lengths only*/
    LGTPATH HPTH_P0array[LIGHTPATHMAX];/*hoping 1000 is adequate - horizontal lengths only*/
    LGTPATH VPTH_P1array[LIGHTPATHMAX];/*hoping 1000 is adequate - vertical lengths only*/
    LGTPATH HPTH_P1array[LIGHTPATHMAX];/*hoping 1000 is adequate - horizontal lengths only*/
}

/* Render Cycle*/
void rndr_cyc(Cycle cycle, UINT8 *base)
{  /*[n,e,s,w]*/
    UINT8 *bmp;       /*agnostic pointer*/
    
    if (cycle->user)    bmp = CYCLE1;
    else                bmp = CYCLE2;
    
    if      (cycle->direction[1] ==  1)             /*NORTH*/
        p_btmp_8(base, cycle->x,cycle->y,bmp[0]);
    else if (cycle->direction[1] == -1)             /*SOUTH*/
        p_btmp_8(base, cycle->x,cycle->y,bmp[2]);
    else if (cycle->direction[0] ==  1)             /*EAST*/
        p_btmp_8(base, cycle->x,cycle->y,bmp[1]);
    else    (cycle->direction[0] == -1)             /*WEST*/
        p_btmp_8(base, cycle->x,cycle->y,bmp[3]);    
}