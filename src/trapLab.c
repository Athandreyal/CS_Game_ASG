#include <stdio.h>
#include <osbind.h>
#include "globals.h"
#include "isr.h"
#include "isr_asm.h"

#define TRAP_70 70


int main(){
    long i = 1000000;
    int origSsp;
    Vector orig_vector70;
    while(i>0)i--;
    tail=0;
    head=0;    
	orig_vector70 = install_vector(TRAP_70,trap70_isr);  /*  kybd  */

    while(1){
        origSsp = Super(0);
        origIpl = set_ipl(7);
        if(head != tail){
            head++;
        }
        set_ipl(origIpl);
        Super(origSsp);
        printf("h: %3d  t: %3d  code: %02x   mState: %d  mKey: %d   mX: %3d   mY: %3d\n",head,tail,buffer[tail],mouseState,mouseKeys,mouse_x, mouse_y);
            
    }

	install_vector(TRAP_70,orig_vector70);
	return 0;
}