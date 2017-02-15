
#include "Events.h"
void chng_dir(Cycle *cycle, int *direction)
{
	cycle->direction[0] = *direction[0];
	cycle->direction[1] = *direction[1];
}

void chng_spd(Cycle *cycle, int speed)
{
	cycle->speed *= speed;
}

/*returns 1 as true for no life left*/
int sub_life(Player *player)
{
	player->life -= 1;
}

int collide(UINT8 *base)
{
	
}

/*lay Trail*/
void lay_trl(Uint *base)
{
	
}

