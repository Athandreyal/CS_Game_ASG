#include "Events.h"

int main()
{
	void *base = Physbase();
	int direction[1];
	
	Cycle cycle;
	Player player;
	
	cycle.x = 320;
	cycle.y = 200;
	cycle.speed = 4;
	cycle.direction[0] = 0;
	cycle.direction[1] = 0;
	
	player.life = 3;
	
	
	chng_dir(Cycle *cycle, int *direction);
	
	sub_life(Player *player);
	
	collide(UINT8 *base);
	
	lay_trl(Uint *base);

	
	return 0;
}