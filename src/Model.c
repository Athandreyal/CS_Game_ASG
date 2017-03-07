#include "Model.h"
#incude "TYPES.h"


void init(Model *model){
    model->user->life =                     PLAYERLIVES;
    model->user->user =                     True;    
    model->user->life =                     PLAYERLIVES;
    model->user->user =                     False;
    reset(model);
    }
}

void reset(Model *model){
    int i;
    model->active = False;
    model->user->segments =                  0;    
    model->user->segments =                  0;
    
    for(i=0;i < LIGHTPATHMAX;i++){
        model->user->cycle->HPATH_ar[i] =    0;
        model->user->cycle->VPATH_ar[i] =    0;
        model->program->cycle->HPATH_ar[i] = 0;
        model->program->cycle->VPATH_ar[i] = 0;    
    }
}

void matchStart(Model *model){
    model->user->cycle->x =                 P1STARTX;
    model->user->cycle->y =                 P1STARTY;
    model->user->cycle->speed =             0
    model->user->cycle->direction[0] =     -1;
    model->user->cycle->direction[0] =      0;
 
    model->program->cycle->x =              P2STARTX;
    model->program->cycle->y =              P2STARTY;
    model->program->cycle->speed =          0
    model->program->cycle->direction[0] =   1;
    model->program->cycle->direction[0] =   0;
}

/*used to initiate watching for player key presses
  input should be supressed until this occurs*/
void release(Model *model){
    model->active = True;
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
    if (model->user->crashed)
        model->user->life     -= 1;
    if (model->program->crashed)
        model->program->life  -= 1;
}
