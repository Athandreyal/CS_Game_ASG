#include "Events.h"
#include TYPES.H"
#include "Objects.h"


bool inbounds(int x1, int x2, int y1, int y2)
    return x1 > 


int main()
{
    int x1,x2,y1,y2;
    void *base = Physbase();
    bool init = true;
    Model model;
    Model* model_ptr;
    init(model_ptr);
    matchStart(model_ptr);


    
    
    do{
        x1 = model.user.cycle.x;
        x2 = model.program.cycle.x;
        y1 = model.user.cycle.y;
        y2 = model.program.cycle.y;
        move(model.user.cycle);
        move(model.program.cycle);
        if (init && y2 < y1){
            chng_dir(model.user.cycle, [0,1]);
            chng_dir(model.program.cycle, [0,-1]);
            sub_life(model.user);
            sub_life(model.program);
            }
        rndr_render(base,model);
    while(){


/*    collide(UINT8 *base);

/*    lay_trl(Uint *base);*/

    
    return 0;
}