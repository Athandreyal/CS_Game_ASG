/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    Primary model manipulations, initialisation, resetting, etc.
*/

#include "Model.h"
#include "Events.h"

/*
///////////////////////////////////////////////////////////////////
// Function Name:  init
// Purpose:        model initialisation, triggers reset to finish off initialisation
// Inputs:         Model *model:    the current game model for initiaisation and updating
// Outputs:        Model *model:    the updated game model.
///////////////////////////////////////////////////////////////////
*/
void init(Model *model){
    model->user.life =                     PLAYER_LIVES;
    model->user.isUser =                     true;
    model->program.life =                  PLAYER_LIVES;
    model->program.isUser =                  false;
    model->ghost.isUser =                    false;
    reset(model);
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  reset
// Purpose:        resets the position history of the cycles.
// Inputs:         Model *model:    the current game model for updating
// Outputs:        Model *model:    the updated game model.
///////////////////////////////////////////////////////////////////
*/
void reset(Model *model){
    int i;
    model->active = false;
    for(i = 0;i<4;i++){
        model->user.cycle.lastPos1[i]=0;
        model->user.cycle.lastPos2[i]=0;
        model->program.cycle.lastPos1[i]=0;
        model->program.cycle.lastPos2[i]=0;
    }
    model->user.cycle.player = 0;
    model->program.cycle.player = 1;
    model->ghost.cycle.player = 2;
    
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  matchStart
// Purpose:        sets the intiial state of the cycles for beginning a match, primes them with invalid history to avoid its bing used prematurely.
// Inputs:         Model *model:    the current game model for manipulation and updating
// Outputs:        Model *model:    the updated game model.
///////////////////////////////////////////////////////////////////
*/
void matchStart(Model *model){
    model->user.crashed=false;
    model->ghost.crashed=false;
    model->program.crashed=false;
    model->user.cycle.x =                 P1STARTX;
    model->user.cycle.y =                 P1STARTY;
    model->user.cycle.speed =             norm;
    model->user.cycle.direction[0] =      0;
    model->user.cycle.direction[1] =      -1;
 
    model->program.cycle.x =              P2STARTX;
    model->program.cycle.y =              P2STARTY;
    model->program.cycle.speed =          norm;
    model->program.cycle.direction[0] =   0;
    model->program.cycle.direction[1] =   1;
/*
    model->ghost.cycle.x =              P2STARTX + model->program.cycle.direction[0] * norm;
    model->ghost.cycle.y =              P2STARTY + model->program.cycle.direction[1] * norm;
    model->ghost.cycle.speed =          norm;
    model->ghost.cycle.direction[0] =   0;
    model->ghost.cycle.direction[1] =   1;
*/
    model->user.cycle.lastPos1[0]    =  -100;
    model->user.cycle.lastPos1[1]    =  -100;
    model->user.cycle.lastPos1[2]    =  0;
    model->user.cycle.lastPos1[3]    =  -1;
    model->user.cycle.lastPos2[0]    =  -100;
    model->user.cycle.lastPos2[1]    =  -100;
    model->user.cycle.lastPos2[2]    =  0;
    model->user.cycle.lastPos2[3]    =  -1;
    model->program.cycle.lastPos1[0] =  -100;
    model->program.cycle.lastPos1[1] =  -100;
    model->program.cycle.lastPos1[2] =  0;
    model->program.cycle.lastPos1[3] =  1;
    model->program.cycle.lastPos2[0] =  -100;
    model->program.cycle.lastPos2[1] =  -100;
    model->program.cycle.lastPos2[2] =  0;
    model->program.cycle.lastPos2[3] =  1;
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  crashed
// Purpose:        detects crashes and updates the model accordingly if found
// Inputs:         UINT8 *base :    the frame buffer
//                 Model *model:    the current game model for manipulation and updating
// Outputs:        Model *model:    the updated game model.
///////////////////////////////////////////////////////////////////
*/
bool crashed(UINT8 *base, Model *model){
    if(model->user.crashed    = collide(base, &(model->user.cycle)))    sub_life(&(model->user));
    if(model->program.crashed = collide(base, &(model->program.cycle))) sub_life(&(model->program));
    model->ghost.crashed = collide(base, &(model->ghost.cycle));
    return (model->user.crashed || model->program.crashed);
}
