/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    Event handlers, various model manipulations

*/


#include "TYPES.H"
#include "Events.h"
#include <stdlib.h>
#include "Constant.h"


#define LARW_KEY  0x004B0000
#define RARW_KEY  0x004D0000
#define UARW_KEY  0x00480000
#define DARW_KEY  0x00500000

/*
///////////////////////////////////////////////////////////////////
// Function Name:  maneuver
// Purpose:        determine if player tried to turn, or change speed
// Inputs:         UINT32 key   :the key they pressed
//                 Cycle *cycle :their cycle struct         
// Outputs:        Cycle *cycle :their cycle struct
///////////////////////////////////////////////////////////////////
*/
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

/*
///////////////////////////////////////////////////////////////////
// Function Name:  setTurn
// Purpose:        determine which direction the decision to turn results in
// Inputs:         UINT32 key   :the key they pressed
//                 Cycle *cycle :their cycle struct         
// Outputs:        Cycle *cycle :their cycle struct
///////////////////////////////////////////////////////////////////
*/
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


/*
///////////////////////////////////////////////////////////////////
// Function Name:  setSpd2
// Purpose:        apply the speed change as determined by setSpd
// Inputs:         accelerate accel :enum for speed changes
//                 Cycle *cycle     :their cycle struct         
// Outputs:        Cycle *cycle     :their cycle struct
///////////////////////////////////////////////////////////////////
*/
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

/*
///////////////////////////////////////////////////////////////////
// Function Name:  setTurn
// Purpose:        determine if the speed change results in acceleration or deceleration
// Inputs:         UINT32 key   :the key they pressed
//                 Cycle *cycle :their cycle struct         
// Outputs:        Cycle *cycle :their cycle struct
///////////////////////////////////////////////////////////////////
*/
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


/*
///////////////////////////////////////////////////////////////////
// Function Name:  chng_dir
// Purpose:        apply change of direciton as chosen by setTurn
// Inputs:         int direction :the chosen direction
//                 Cycle *cycle  :their cycle struct         
// Outputs:        Cycle *cycle  :their cycle struct
///////////////////////////////////////////////////////////////////
*/
void chng_dir(Cycle *cycle, int direction[])
{
    cycle->direction[0] = direction[0];
    cycle->direction[1] = direction[1];
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  chng_spd
// Purpose:        apply change of speed as chosen by setSpd2
// Inputs:         velocity speed:enum for speed changes
//                 Cycle *cycle  :their cycle struct         
// Outputs:        Cycle *cycle  :their cycle struct
///////////////////////////////////////////////////////////////////
*/
void chng_spd(Cycle *cycle, velocity speed)
{
    cycle->speed = speed;
}


/*
///////////////////////////////////////////////////////////////////
// Function Name:  sub_life
// Purpose:        subtracts one life from given player
// Inputs:         Player *player: player struct which loses a life
// Outputs:        Player *player: player struct which loses a life
///////////////////////////////////////////////////////////////////
*/
void sub_life(Player *player)
{
    player->life -= 1;
}


/*
///////////////////////////////////////////////////////////////////
// Function Name:  collide
// Purpose:        determine if collision has occured or not.
// Inputs:         base          :the frame buffer, since collision is determined by the pressence of enabled bits int he path.
//                 Cycle *cycle  :their cycle struct         
// Outputs:        Cycle *cycle  :their cycle struct
///////////////////////////////////////////////////////////////////
*/

UINT32 collide(UINT8 *base, Cycle *cycle)
{
    int col=0;
    int x1, x2, y1, y2;
    UINT8 head = LINE_BODY;
    UINT8 tail = LINE_BODY;
    UINT32 collision = 0;
    if (cycle->direction[1] == 0){/*horizontal*/
        y1 = cycle->y - 2;
        y2 = cycle->y + 3;
        if      (cycle->direction[0] == -1){
            x2 = cycle->x - 2;
            x1 = x2 - cycle->speed;
            }
        else if (cycle->direction[0] ==  1){
            x1 = cycle->x + 3;
            x2 = x1 + cycle->speed;
            }
        }
    else{/*vertical*/
        x1 = cycle->x - 3;
        x2 = cycle->x + 3;
        if      (cycle->direction[1] == -1){
            y2 = cycle->y - 2;
            y1 = y2 - cycle->speed;
            }
        else if (cycle->direction[1] ==  1){
            y1 = cycle->y + 3;
            y2 = y1 + cycle->speed;
            }
        }

    for(;y1<=y2;y1++){
        if (x1 > 0 && x2 < SCREEN_WIDTH_PIX && y1 >= 0 && y2 < SCREEN_HEIGHT_PIX){
            head = head >> (x1 & REMAINDER_MAX);
            tail = tail << (BITS_PER - (x2 & REMAINDER_MAX));
            col = x1 >> SHIFT;
            if (x2 >> SHIFT == col){/*then we start and end in same block, special case, mask both ends*/
                collision += *(base + y1 * SCREEN_WIDTH + col) & head & tail; 
            }
            else {/*start mask, body, end mask*/
                collision += (*(base + y1 * SCREEN_WIDTH + col) & head) + (*(base + y1 * SCREEN_WIDTH + (col+1)) & tail);
            }
        }
    }
    return collision;
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  move
// Purpose:        applies position change
// Inputs:         Cycle *cycle  :their cycle struct         
// Outputs:        Cycle *cycle  :their cycle struct
///////////////////////////////////////////////////////////////////
*/
void move(Cycle* cycle){
    cycle->x = cycle->x + cycle->direction[0] * cycle->speed;
    cycle->y = cycle->y + cycle->direction[1] * cycle->speed;
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  setGhost
// Purpose:        ties the ghost cycle to the program cycle - used for collision prediction
// Inputs:         Model *model  :the current model, so the cost and program structs can be manipulated         
// Outputs:        Model *model  :the current model, updated
///////////////////////////////////////////////////////////////////
*/
void setGhost(Model *model){
    model->ghost.crashed = false;
    model->ghost.cycle.speed = model->program.cycle.speed;
    model->ghost.cycle.x = model->program.cycle.x;
    model->ghost.cycle.y = model->program.cycle.y;
    model->ghost.cycle.direction[0] = model->program.cycle.direction[0];
    model->ghost.cycle.direction[1] = model->program.cycle.direction[1];
    move(&(model->ghost.cycle));
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  AITurn
// Purpose:        apply a change of direction as chosen by AIChoice
// Inputs:         Turn dir      :turn direction enum;
//                 Cycle *cycle  :their cycle struct         
// Outputs:        Cycle *cycle  :their cycle struct
///////////////////////////////////////////////////////////////////
*/
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

/*
///////////////////////////////////////////////////////////////////
// Function Name:  AIChoice
// Purpose:        determine if collision will occur, choose to turn if so, potentially turn 
                   or change speed as well
// Inputs:         long time     :a seed for rand to make a decision with
//                 Model *model  :the current game model, so that the ghost and 
                   program can be accessed
//
// Outputs:        Model *model  :the current game model, so that the ghost and program can be accessed
///////////////////////////////////////////////////////////////////
*/
void AIChoice(Model *model, long time){
    double random;
    srand((unsigned)time);
    random = ((double)rand())/RAND_MAX;
    if ((model->ghost.crashed) || random > 0.98){
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
}