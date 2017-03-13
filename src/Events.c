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
void sub_life(Player *player)
{
    player->life -= 1;
}

bool collide(UINT8 *base, Cycle *cycle)
{/*read in the cycles planned memory location, check for non zero in the cells the cycle's will occupy.*/
    int x = cycle->x - 4;/*offset from center pix to upper left corner of bitmap tile*/
    int y = cycle->y - 4;
    x += cycle->speed * cycle->direction[0];/*new location to investigate*/
    y += cycle->speed * cycle->direction[1];
}

/*lay Trail
void lay_trl(UINT8 *base, Cycle *cycle)
{/*lay trail, 3 px wide, length as per move rate.  location is offset by 4 from location pix.
}*/

void move(Cycle* cycle){
    cycle->x = cycle->x + cycle->direction[0] * cycle->speed;
    cycle->y = cycle->y + cycle->direction[1] * cycle->speed;
}

