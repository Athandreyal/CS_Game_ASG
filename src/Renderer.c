
#include"Renderer.h"

void render(Model *model, UINT8 *base){
	/*render black */
	rndr_blk
	/*render field*/
	rnder_fd
	
	rndr_cyc(model->player->cycle,base);
	rndr_lw(model->p_lw);
	rndr_cyc(model->pc->cycle,base);
	rndr_lw(model->pc_lw);
	rndr_lif(model->player,base);
	
	
}

void rndr_blk(UINT8 *base)
{
	
}

void rnder_fd(UINT8 *base)
{
	
}

void rndr_lif(Player *player, UINT8 *base)
{
	/*print life bitmap for number of lives left for player*/
}

void rndr_lw(lgt_walls *lw, UINT8 *base)
{
	
}
/* Render Cycle*/
void rndr_cyc(Cycle cycle, UINT8 *base)
{
	/*direction left*/
	
	/*direction right*/
	
	
}