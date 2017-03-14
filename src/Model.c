#include "Model.h"
#include "Events.h"

void init(Model *model){
    model->user.life =                     PLAYER_LIVES;
    model->user.isUser =                     true;    
    model->program.life =                  PLAYER_LIVES;
    model->program.isUser =                  false;
    model->ghost.isUser =                    false;
    reset(model);
}

void reset(Model *model){
    int i;
    model->active = false;
    for(i = 0;i<4;i++){
        model->user.cycle.lastPos1[i]=0;
        model->user.cycle.lastPos2[i]=0;
        model->program.cycle.lastPos1[i]=0;
        model->program.cycle.lastPos2[i]=0;
    }
}

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

    model->ghost.cycle.x =              P2STARTX + model->program.cycle.direction[0] * norm;
    model->ghost.cycle.y =              P2STARTY + model->program.cycle.direction[1] * norm;
    model->ghost.cycle.speed =          norm;
    model->ghost.cycle.direction[0] =   0;
    model->ghost.cycle.direction[1] =   1;

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

/*used to initiate watching for player key presses
  input should be supressed until this occurs*/
void release(Model *model){
    model->active = true;
    /*  anything else?....maybe once we hijack the keyboard*/
}

bool crashed(UINT8 *base, Model *model){
    bool crash = false;
    if(collide(base, &(model->user.cycle)) != 0){
        sub_life(&(model->user));
        model->user.crashed = true;
        crash = true;
    }
    
    if(collide(base, &(model->ghost.cycle)) != 0){
        model->ghost.crashed = true;
    }
    
    if(collide(base, &(model->program.cycle)) != 0){
        sub_life(&(model->program));
        model->program.crashed = true;
        crash = true;
    }
    return crash;
}
