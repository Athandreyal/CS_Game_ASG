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

#define LARW_KEY  0x4B
#define RARW_KEY  0x4D
#define UARW_KEY  0x48
#define DARW_KEY  0x50

/*
///////////////////////////////////////////////////////////////////
// Function Name:  maneuver
// Purpose:        determine if player tried to turn, or change speed
// Inputs:         UINT8 key   :the key they pressed
//                 Cycle *cycle :their cycle struct         
///////////////////////////////////////////////////////////////////
*/
void maneuver(UINT8 key, Cycle* cycle){
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
// Inputs:         UINT8 key   :the key they pressed
//                 Cycle *cycle :their cycle struct         
///////////////////////////////////////////////////////////////////
*/
void setTurn(Cycle *cycle, UINT8 key){
    switch(key){
        case LARW_KEY:
            cycle->direction[0] = -1;
            cycle->direction[1] = 0;
            cycle->bmp = (cycle->player==0?CYCLE2[3]:CYCLE1[3]);
            break;
        case RARW_KEY:
            cycle->direction[0] = 1;
            cycle->direction[1] = 0;
            cycle->bmp = (cycle->player==0?CYCLE2[1]:CYCLE1[1]);
            break;
        case UARW_KEY:
            cycle->direction[0] = 0;
            cycle->direction[1] = -1;
            cycle->bmp = (cycle->player==0?CYCLE2[0]:CYCLE1[0]);
            break;
        case DARW_KEY:
            cycle->direction[0] = 0;
            cycle->direction[1] = 1;
            cycle->bmp = (cycle->player==0?CYCLE2[2]:CYCLE1[2]);
    }
}


/*
///////////////////////////////////////////////////////////////////
// Function Name:  setSpd2
// Purpose:        apply the speed change as determined by setSpd
// Inputs:         accelerate accel :enum for speed changes
//                 Cycle *cycle     :their cycle struct         
///////////////////////////////////////////////////////////////////
*/
void setSpd2(Cycle *cycle, accelerate accel){
    if (accel == faster){
        if      (cycle->speed == norm) chng_spd(cycle, fast);
/*        else if (cycle->speed == slow) chng_spd(cycle, norm);*/
        }
    else{
        if      (cycle->speed == fast) chng_spd(cycle, norm);
/*        else if (cycle->speed == norm) chng_spd(cycle, slow);*/
        }
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  setSpd
// Purpose:        determine if the speed change results in acceleration or deceleration
// Inputs:         UINT8 key   :the key they pressed
//                 Cycle *cycle :their cycle struct         
///////////////////////////////////////////////////////////////////
*/
void setSpd(Cycle *cycle, UINT8 key){
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
    }
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  chng_dir
// Purpose:        apply change of direciton as chosen by setTurn
// Inputs:         int direction :the chosen direction
//                 Cycle *cycle  :their cycle struct         
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
// Outputs:        true if collision
///////////////////////////////////////////////////////////////////
*/
bool collide(Cycle *cycle){
    int x, y,i, length, depth, detected;
    bool crash = false;
    if      (cycle->direction[0] > 0){/*east */
        length = cycle->speed;
        depth = 7;
        x = cycle->x + 4;
        y = cycle->y - 3;
        }
    else if (cycle->direction[0] < 0){/*west*/
        length = cycle->speed;
        depth = 7;
        x = cycle->x - 3 - length;
        y = cycle->y - 3;
        }
    else if (cycle->direction[1] > 0){/*south*/
        length = 7;
        depth = cycle->speed;
        x = cycle->x - 3;
        y = cycle->y + 4;
        }
    else if (cycle->direction[1] < 0){/*north*/
        length = 7;
        depth = cycle->speed;
        x = cycle->x - 3;
        y = cycle->y - 3 - depth;
        }
    detected=0;
    for (i=0;i<depth && detected == 0;i++)
        detected += readGrid(x, y+i, length);
    crash = (detected > 0);
    return crash;
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  readGrid
// Purpose:        reads grid to detect if collision ahead will occur this results in crash signal
	outputs: int 0 or 1 detection of collision or not.
///////////////////////////////////////////////////////////////////
*/

int readGrid(int x, int y,int length){
    /*out of bounds detection is unecessary because the grid border is large enough to prevent us getting there*/
    UINT8 detected = 0;
    int column = x >> SHIFT;
    UINT8 head = LINE_BODY;
    UINT8 tail = LINE_BODY;
    head = head >> (x & REMAINDER_MAX);
    tail = tail << (BITS_PER - (x + length) & REMAINDER_MAX);
    
    if (column == (x + length-1) >> SHIFT){/*easy case, all within one byte */
        detected += *(base + y * SCREEN_WIDTH + column) & (head & tail);
        }
    else{/*harder case, not all within one byte*/
        detected += *(base + y * SCREEN_WIDTH + column) & head;
        detected += *(base + y * SCREEN_WIDTH + column + 1) & tail;
        }
    return detected;
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  move
// Purpose:        applies position change
// Inputs:         Cycle *cycle  :their cycle struct         
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
///////////////////////////////////////////////////////////////////
*/
void setGhost(){
    model.ghost.crashed = false;
    model.ghost.cycle.speed = model.program.cycle.speed;
    model.ghost.cycle.x = model.program.cycle.x;
    model.ghost.cycle.y = model.program.cycle.y;
    model.ghost.cycle.direction[0] = model.program.cycle.direction[0];
    model.ghost.cycle.direction[1] = model.program.cycle.direction[1];
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  AITurn
// Purpose:        apply a change of direction as chosen by AIChoice
// Inputs:         Turn dir      :turn direction enum;
//                 Cycle *cycle  :their cycle struct         
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
    if      (cycle->direction[0] == -1)
        cycle->bmp = CYCLE1[3];
    else if (cycle->direction[0] ==  1)
        cycle->bmp = CYCLE1[1];
    else if (cycle->direction[1] == -1)
        cycle->bmp = CYCLE1[0];
    else if (cycle->direction[1] ==  1)
        cycle->bmp = CYCLE1[2];
}


/*
///////////////////////////////////////////////////////////////////
// Function Name:  ghostTurns
// Purpose:        Assist in predicting collision events in the AI
// Outputs:       Returns int that specifies available turns for the ai as stated below
///////////////////////////////////////////////////////////////////
*/
/*
uses ghost to check for turn collisions
    0 none 
    1 left
    2 right
    3 both
*/    
int ghostTurns(){
    bool crashLeft, crashRight;
    int result;
    Cycle *ghost = &(model.ghost.cycle);
    setGhost(); /* re-attach ghost*/
    AITurn(ghost,left);/*turn ghost left*/
    move(&(model.ghost.cycle));
    crashLeft = collide(ghost);/*test ghost crash*/
    setGhost();
    AITurn(ghost,right);/*turn ghost right*/
    move(&(model.ghost.cycle));
    crashRight = collide(ghost);/*test ghost crash*/
    if      (crashLeft && crashRight)   result = 0;
    else if (crashRight)                result = 1;
    else if (crashLeft)                 result = 2;
    else                                result = 3;
    return result;
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  AIChoice
// Purpose:        determine if collision will occur, choose to turn if so, potentially turn 
                   or change speed as well
// Outputs:       N/A
///////////////////////////////////////////////////////////////////
*/
void AIChoice(){
    double random;
    int turns;
    random = ((double)rand())/RAND_MAX;
    if (random > 0.97)             /*fast*/
        chng_spd(&(model.program.cycle), fast);
    else
        chng_spd(&(model.program.cycle), norm);
/*    else if (random < 0.03)        /*slow*/
/*        chng_spd(&(model->program.cycle), slow);*/
    model.ghost.crashed = collide(&(model.ghost.cycle));
    if ((model.ghost.crashed) || random > 0.98){
        random = ((double)rand())/RAND_MAX;
        turns = ghostTurns();
        if (turns == 3){
            if(random > 0.5)
                AITurn(&(model.program.cycle),left);
            else
                AITurn(&(model.program.cycle),right);
            }
        else if (turns == 2)
            AITurn(&(model.program.cycle),right);
        else if (turns == 1)
            AITurn(&(model.program.cycle),left);
    }
    setGhost();
}