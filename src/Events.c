#include "TYPES.H"
#include "Events.h"

void chng_dir(Cycle *cycle, int direction[])
{
    cycle->direction[0] = direction[0];
    cycle->direction[1] = direction[1];
}

void chng_spd(Cycle *cycle, velocity speed)
{
    cycle->speed = speed;
}

/*returns 1 as true for no life left*/
int sub_life(Player *player)
{
    player->life -= 1;
}

int collide(UINT8 *base)
{
        ;
}

/*lay Trail*/
void lay_trl(UINT8 *base)
{
    ;
}

void move(Cycle* cycle){
    cycle->x = cycle->x + cycle->direction[0] * cycle->speed;
    cycle->y = cycle->y + cycle->direction[1] * cycle->speed;
}

