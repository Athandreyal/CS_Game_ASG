/*
Name:       Phillip Renwick, Jaden McConkey
Email:      prenw499@mtroyal.ca
Course:     COMP 2659-001
Instructor: Paul pospisil

Purpose:    Primary model manipulations, initialisation, resetting, etc.
*/

#include "Model.h"
#include "Events.h"

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
// Inputs:         Model *model:    the current game model for initiaisation and updating
// Outputs:        Model *model:    the updated game model.
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
// Inputs:         Model *model:    the current game model for updating
// Outputs:        Model *model:    the updated game model.
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
// Purpose:        sets the intiial state of the cycles for beginning a match, primes them with invalid history to avoid its bing used prematurely.
// Inputs:         Model *model:    the current game model for manipulation and updating
// Outputs:        Model *model:    the updated game model.
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

    fprintf(f,"reset,    user   : %d   x: %3d  y: %3d  horizontal: %d  Vertical: %d\n",model.user.crashed,model.user.cycle.x,model.user.cycle.y,model.user.cycle.direction[0],model.user.cycle.direction[1]);fflush(f);
    fprintf(f,"reset,    program: %d   x: %3d  y: %3d  horizontal: %d  Vertical: %d\n\n",model.program.crashed,model.program.cycle.x,model.program.cycle.y,model.program.cycle.direction[0],model.program.cycle.direction[1]);fflush(f);
    
}

bool crashed2(int x, int y, const UINT8 bitmap[]){
    int i;
    bool same = true;
    UINT8 found;
    UINT8 LHalf;                            UINT8 RHalf;
    UINT8 L_Offset = x & REMAINDER_MAX;     UINT8 R_Offset = BITS_PER - (x & REMAINDER_MAX);
    UINT8 Lmask = LINE_BODY << R_Offset;    UINT8 Rmask = LINE_BODY >> L_Offset;
    UINT8 col = x >> SHIFT;
    for (i = 0;i < 8 && same;i++){
        if (x & REMAINDER_MAX == 0){
            fprintf(f,"%02x = ",bitmap[i]);
            found = *(base + (y+i) * SCREEN_WIDTH + col) & bitmap[i];
            fprintf(f,"%02x ",found);
            same &= found == bitmap[i];
            fprintf(f,"%s\n",(same?"same":"different"));fflush(f);
            }
        else{
            LHalf = bitmap[i] >> L_Offset;
            fprintf(f,"%02x",LHalf);
            found = *(base + (y+i) * SCREEN_WIDTH + col) & LHalf;
            same &= found == LHalf;
            RHalf = bitmap[i] << R_Offset;
            fprintf(f,"%02x = %02x",RHalf,found);
            
            found = *(base + (y+i) * SCREEN_WIDTH + col+1) & RHalf;
            same &= found == RHalf;
            fprintf(f,"%02x %s\n",found,(same?"same":"different"));
        }
    }
    fprintf(f,"\n");fflush(f);
    return !same;
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
bool crashed(){
    fprintf(f,"crashed2, user   : %d   x: %3d  y: %3d  horizontal: %d  Vertical: %d\n",model.user.crashed,model.user.cycle.x,model.user.cycle.y,model.user.cycle.direction[0],model.user.cycle.direction[1]);fflush(f);
    fprintf(f,"crashed2, program: %d   x: %3d  y: %3d  horizontal: %d  Vertical: %d\n\n",model.program.crashed,model.program.cycle.x,model.program.cycle.y,model.program.cycle.direction[0],model.program.cycle.direction[1]);fflush(f);
    if(model.user.crashed    = crashed2(model.user.cycle.last[0][0]+BMP_OFFSET,model.user.cycle.last[0][1]+BMP_OFFSET,model.user.cycle.lastbmp[0]))
        sub_life(&(model.user));
    if(model.program.crashed = crashed2(model.program.cycle.last[0][0]+BMP_OFFSET,model.program.cycle.last[0][1]+BMP_OFFSET,model.program.cycle.lastbmp[0])) 
        sub_life(&(model.program));
    model.ghost.crashed = collide(&(model.ghost.cycle));
    return (model.user.crashed || model.program.crashed);
/*    return false;*/
}
