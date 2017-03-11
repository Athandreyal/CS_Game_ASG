#include "Model.h"
#include "TYPES.H"

void init(Model *model){
    model->user.life =                     5;
    model->user.isUser =                     true;    
    model->program.life =                  5;
    model->program.isUser =                  false;
    reset(model);
}

void reset(Model *model){
    int i;
    model->active = false;
    model->user.segments =                  0;    
    model->program.segments =               0;
    for(i = 0;i<4;i++){
        model->user.cycle.lastPos[i]=0;
        model->program.cycle.lastPos[i]=0;
    }
}

void matchStart(Model *model){
    model->user.cycle.x =                 P1STARTX;
    model->user.cycle.y =                 P1STARTY;
    model->user.cycle.speed =             norm;
    model->user.cycle.direction[0] =      0;
    model->user.cycle.direction[1] =      1;
 
    model->program.cycle.x =              P2STARTX;
    model->program.cycle.y =              P2STARTY;
    model->program.cycle.speed =          norm;
    model->program.cycle.direction[0] =   0;
    model->program.cycle.direction[1] =  -1;

    model->user.cycle.lastPos[0]    =  -100;
    model->user.cycle.lastPos[1]    =  -100;
    model->user.cycle.lastPos[2]    =  0;
    model->user.cycle.lastPos[3]    =  1;
    model->program.cycle.lastPos[0] =  -100;
    model->program.cycle.lastPos[1] =  -100;
    model->program.cycle.lastPos[2] =  0;
    model->program.cycle.lastPos[3] = -1;
}

/*used to initiate watching for player key presses
  input should be supressed until this occurs*/
void release(Model *model){
    model->active = true;
    /*  anything else?....maybe once we hijack the keyboard*/
}

bool collision (Model *model){
    /*check for player collides with other player or path or boundary
      should probably switch to 5x7 for cycles!....grrr....they took a while.
      5x7 allows a central location pixel, so we can have 'center mass' for location.*/
      
    /*TODO -- STUBBED FOR NOW --*/
    return true;
}

void crash(Model *model){
    if (model->user.crashed)
        model->user.life     -= 1;
    if (model->program.crashed)
        model->program.life  -= 1;
}