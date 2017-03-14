#include "TYPES.H"
#include "Events.h"
#include <stdio.h>
#include <stdlib.h>

#define LARW_KEY  0x004B0000
#define RARW_KEY  0x004D0000
#define UARW_KEY  0x00480000
#define DARW_KEY  0x00500000

void maneuver(UINT32 key, Cycle* cycle){
    /*speed changes*/
    if     ((key == LARW_KEY && cycle->direction[0]) ||
            (key == RARW_KEY && cycle->direction[0]) ||
            (key == UARW_KEY && cycle->direction[1]) ||
            (key == DARW_KEY && cycle->direction[1]))
        setSpd(cycle, key);
    /*direction changes*/
    else if((key == LARW_KEY && cycle->direction[1]) ||
            (key == RARW_KEY && cycle->direction[1]) ||
            (key == UARW_KEY && cycle->direction[0]) ||
            (key == DARW_KEY && cycle->direction[0]))
        setTurn(cycle, key);
}

void setTurn(Cycle *cycle, UINT32 key){
    switch(key){
        case LARW_KEY:
            cycle->direction[0] = -1;
            cycle->direction[1] = 0;
            break;
        case RARW_KEY:
            cycle->direction[0] = 1;
            cycle->direction[1] = 0;
            break;
        case UARW_KEY:
            cycle->direction[0] = 0;
            cycle->direction[1] = -1;
            break;
        case DARW_KEY:
            cycle->direction[0] = 0;
            cycle->direction[1] = 1;
            break;
    }
}


void setSpd2(Cycle *cycle, accelerate accel){
    if (accel == faster){
        if      (cycle->speed == norm) chng_spd(cycle, fast);
        else if (cycle->speed == slow) chng_spd(cycle, norm);
        }
    else{
        if      (cycle->speed == fast) chng_spd(cycle, norm);
        else if (cycle->speed == norm) chng_spd(cycle, slow);
        }
}

void setSpd(Cycle *cycle, UINT32 key){
    switch(key){
        case LARW_KEY:
            if (cycle->direction[0] == -1)
                setSpd2(cycle, faster);
            else
                setSpd2(cycle, slower);
            break;
        case RARW_KEY:
            if (cycle->direction[0] == 1)
                setSpd2(cycle, faster);
            else
                setSpd2(cycle, slower);
            break;
        case UARW_KEY:
            if (cycle->direction[1] == -1)
                setSpd2(cycle, faster);
            else
                setSpd2(cycle, slower);
            break;
        case DARW_KEY:
            if (cycle->direction[1] == 1)
                setSpd2(cycle, faster);
            else
                setSpd2(cycle, slower);
            break;
    }
}

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

UINT32 collide(UINT8 *base, Cycle *cycle)
{
    int col=0;
    int x1, x2, y1, y2;
    UINT8 head = 0xFF;
    UINT8 tail = 0xFF;
    UINT32 collision = 0;
    if (cycle->direction[1] == 0){/*horizontal*/
        y1 = cycle->y - 4;
        y2 = cycle->y + 4;
        if      (cycle->direction[0] == -1){
            x2 = cycle->x - 3;
            x1 = x2 - cycle->speed;
            }
        else if (cycle->direction[0] ==  1){
            x1 = cycle->x + 4;
            x2 = x1 + cycle->speed;
            }
        }
    else{/*vertical*/
        x1 = cycle->x - 4;
        x2 = cycle->x + 4;
        if      (cycle->direction[1] == -1){
            y2 = cycle->y - 3;
            y1 = y2 - cycle->speed;
            }
        else if (cycle->direction[1] ==  1){
            y1 = cycle->y + 4;
            y2 = y1 + cycle->speed;
            }
        }

    for(;y1<=y2;y1++){
        if (x1 > 0 && x2 < SCREEN_WIDTH && y1 >= 0 && y2 < SCREEN_HEIGHT){
            head = head >> (x1 & 7);
            tail = tail << (8 - (x2 & 7));
            col = x1 >> 3;
            if (x2 >> 3 == col){/*then we start and end in same block, special case, mask both ends*/
                collision += *(base + y1 * 80 + col) & head & tail; 
            }
            else {/*start mask, body, end mask*/
                collision += (*(base + y1 * 80 + col) & head) + (*(base + y1 * 80 + (col+1)) & tail);
            }
        }
    }
    return collision;
}

/*lay Trail
void lay_trl(UINT8 *base, Cycle *cycle)
{/*lay trail, 3 px wide, length as per move rate.  location is offset by 4 from location pix.
}*/

void move(Cycle* cycle){
    cycle->x = cycle->x + cycle->direction[0] * cycle->speed;
    cycle->y = cycle->y + cycle->direction[1] * cycle->speed;
}

void setGhost(Model *model){
    model->ghost.crashed = false;
    model->ghost.cycle.speed = model->program.cycle.speed;
    model->ghost.cycle.x = model->program.cycle.x;
    model->ghost.cycle.y = model->program.cycle.y;
    model->ghost.cycle.direction[0] = model->program.cycle.direction[0];
    model->ghost.cycle.direction[1] = model->program.cycle.direction[1];
    move(&(model->ghost.cycle));
}

void AITurn(Cycle *cycle,Turn dir){
        if (cycle->direction[0] == 1){
            cycle->direction[0] = 0;
            cycle->direction[1] = (dir==left?-1:1);
        }
        else if (cycle->direction[0] == -1){
            cycle->direction[0] = 0;
            cycle->direction[1] = (dir==left?1:-1);
        }
        else if (cycle->direction[1] == 1){
            cycle->direction[0] = (dir==left?1:-1);
            cycle->direction[1] = 0;
        }
        else if (cycle->direction[1] == -1){
            cycle->direction[0] = (dir==left?-1:1);
            cycle->direction[1] = 0;
        }
}

void AIChoice(Model *model, long time){
    double random;
    FILE *f = fopen("log.txt","a");
    srand((unsigned)time);
    random = ((double)rand())/RAND_MAX;
    if ((model->ghost.crashed) || random > 0.98){
        fprintf(f,"crashed because random? %f or crashed? %d\n",random, (model->ghost.crashed));
        random = ((double)rand())/RAND_MAX;
        if (random > 0.5)  /*AI needs to turn, NOW*/
            AITurn(&(model->program.cycle),left);
        else
            AITurn(&(model->program.cycle),right);
        setGhost(model);
    }
    if (random > 0.97){             /*fast*/
        chng_spd(&(model->program.cycle), fast);
        setGhost(model);
    }
    else if (random < 0.03){        /*slow*/
        chng_spd(&(model->program.cycle), slow);
        setGhost(model);
    }
    else{
        chng_spd(&(model->program.cycle), norm);
        setGhost(model);
    }
    fclose(f);
}