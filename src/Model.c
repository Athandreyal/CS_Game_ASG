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
// Function Name:  menuInit()
// Purpose:       Inits menu screen 
///////////////////////////////////////////////////////////////////
*/
void menuInit(){
    model.ghost.cycle.x=CHOICE_X;
    model.ghost.cycle.y=CHOICE_Y;
    model.mode=1;
    model.mode2=-1;
    mouse_x = 320;
    mouse_y = 200;
    mouse_x_old = -1;
    mouse_y_old = -1;
    model.menu = true;
}


/*
///////////////////////////////////////////////////////////////////
// Function Name:  init
// Purpose:        model initialisation, triggers reset to finish off initialisation
///////////////////////////////////////////////////////////////////
*/
void init(){
    model.user.life =                     PLAYER_LIVES;
    model.user.isUser =                     true;
    model.program.life =                  PLAYER_LIVES;
    model.program.isUser =                  false;
    model.ghost.isUser =                    false;
    reset(model);
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  reset
// Purpose:        resets the position history of the cycles.
///////////////////////////////////////////////////////////////////
*/
void reset(){
    int i;
    for(i = 0;i<4;i++){
        model.user.cycle.last[0][i]=0;
        model.user.cycle.last[1][i]=0;
        model.user.cycle.last[2][i]=0;
        model.user.cycle.last[3][i]=0;
        model.program.cycle.last[0][i]=0;
        model.program.cycle.last[1][i]=0;
        model.program.cycle.last[2][i]=0;
        model.program.cycle.last[3][i]=0;
    }
    model.user.cycle.player = 0;
    model.program.cycle.player = 1;
    model.ghost.cycle.player = 2;
    
    model.user.cycle.bmp = (UINT8*)CYCLE2[0];
    model.ghost.cycle.bmp = (UINT8*)CYCLE1[2];
    model.program.cycle.bmp = (UINT8*)CYCLE1[2];
    model.user.cycle.lastbmp[0] = (UINT8*)CYCLE2[0];
    model.ghost.cycle.lastbmp[0] = (UINT8*)CYCLE1[2];
    model.program.cycle.lastbmp[0] = (UINT8*)CYCLE1[2];

    model.user.crashed=false;
    model.ghost.crashed=false;
    model.program.crashed=false;
}

/*
///////////////////////////////////////////////////////////////////
// Function Name:  matchStart
// Purpose:        sets the intiial state of the cycles for beginning a match, primes 
					them with invalid history to avoid its bing used prematurely.
///////////////////////////////////////////////////////////////////
*/
void matchStart(){
    model.user.cycle.x =                 P1STARTX;
    model.user.cycle.y =                 P1STARTY;
    model.user.cycle.speed =             norm;
    model.user.cycle.direction[0] =      0;
    model.user.cycle.direction[1] =      -1;
 
    model.program.cycle.x =              P2STARTX;
    model.program.cycle.y =              P2STARTY;
    model.program.cycle.speed =          norm;
    model.program.cycle.direction[0] =   0;
    model.program.cycle.direction[1] =   1;

    model.user.cycle.last[0][0] = -100;
    model.user.cycle.last[0][1] = -100;
    model.user.cycle.last[0][2] = 0;
    model.user.cycle.last[0][3] = -1;
    model.user.cycle.last[1][0] = -100;
    model.user.cycle.last[1][1] = -100;
    model.user.cycle.last[1][2] = 0;
    model.user.cycle.last[1][3] = -1;
    model.user.cycle.last[2][0] = -100;
    model.user.cycle.last[2][1] = -100;
    model.user.cycle.last[2][2] = 0;
    model.user.cycle.last[2][3] = -1;
    model.user.cycle.last[3][0] = -100;
    model.user.cycle.last[3][1] = -100;
    model.user.cycle.last[3][2] = 0;
    model.user.cycle.last[3][3] = -1;
    
    model.program.cycle.last[0][0] = -100;
    model.program.cycle.last[0][1] = -100;
    model.program.cycle.last[0][2] = 0;
    model.program.cycle.last[0][3] = 1;
    model.program.cycle.last[1][0] = -100;
    model.program.cycle.last[1][1] = -100;
    model.program.cycle.last[1][2] = 0;
    model.program.cycle.last[1][3] = 1;
    model.program.cycle.last[2][0] = -100;
    model.program.cycle.last[2][1] = -100;
    model.program.cycle.last[2][2] = 0;
    model.program.cycle.last[2][3] = 1;
    model.program.cycle.last[3][0] = -100;
    model.program.cycle.last[3][1] = -100;
    model.program.cycle.last[3][2] = 0;
    model.program.cycle.last[3][3] = 1;
    model.menu = false;
    model.doCrash = false;
}