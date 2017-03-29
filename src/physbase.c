#include "TYPES.H"
#include <osbind.h>
#include <stdio.h>
#include "pb_asm.h"

void getScreen(bool *buffer, UINT8 **base, UINT8 **base0, UINT8 **base1);
void cleanUp(UINT8 *base0);
void toggleScreen(bool *buffer, UINT8 **base, UINT8 *base0, UINT8 *base1);
UINT8 framebuffer2[32255];

int main(){
    FILE *f = fopen("log.txt","a");
    UINT8 *midByte, *highByte;
    long old_ssp;
    UINT8 *base, *base0, *base1;
    bool buffer = false;
    getScreen(&buffer, &base, &base0, &base1);
    fprintf(f,"\n\n\nphysbase\n");
    base = Physbase();
    fprintf(f,"base: %p\n",base);
    highByte = (UINT8*)0xff8201;
    midByte  = (UINT8*)0xff8203;
    
    fprintf(f,"high : %p\n",highByte);

    old_ssp = Super(0);
    fprintf(f,"*high: %04x\n",*highByte);
    Super(old_ssp);
    fprintf(f,"mid  : %p\n",midByte);
    old_ssp = Super(0);
    fprintf(f,"*mid : %04x\n",*midByte);
    Super(old_ssp);

    getScreen(&buffer,&base, &base0, &base1);
    fprintf(f, "getscreen\n");
    fprintf(f,"buffer1: %s\n",(buffer?"true":"false"));
    fprintf(f,"physbase says: %p\n",Physbase());
    fprintf(f,"base : %p\n",base);
    fprintf(f,"base0: %p\n",base0);
    fprintf(f,"base1: %p\n",base1);
    Cnecin();
    Vsync();
    toggleScreen(&buffer,&base, base0, base1);
    fprintf(f, "toggle\n");
    fprintf(f,"buffer1: %s\n",(buffer?"true":"false"));
    fprintf(f,"physbase says: %p\n",Physbase());
    fprintf(f,"base : %p\n",base);
    fprintf(f,"base0: %p\n",base0);
    fprintf(f,"base1: %p\n",base1);
    fclose(f);
    cleanUp(base0);
    f = fopen("log.txt","a");
    fprintf(f, "cleanup\n");
    fprintf(f,"physbase says: %p\n",Physbase());
    fprintf(f,"base : %p\n",base);
    fprintf(f,"base0: %p\n",base0);
    fprintf(f,"base1: %p\n",base1);
    fclose(f);
}

void getScreen(bool *buffer, UINT8 **base, UINT8 **base0, UINT8 **base1){
	*base0 = Physbase();
    *base1 = (UINT8*)((((long)(&framebuffer2)) + 255) & 0xffffff00);
    *base = *base1;
    *buffer = true;
}


void cleanUp(UINT8 *base0){
    FILE *f = fopen("log.txt","a");
    long old_ssp;
    fprintf(f,"cleanup called with %p\n",base0);
    fclose(f);
    old_ssp = Super(0);
    mySetScreen(base0);
    Super(old_ssp);
/*    Setscreen(-1,base0,-1);/*restore the screen*/
}

void toggleScreen(bool *buffer, UINT8 **base, UINT8 *base0, UINT8 *base1){
    if (*buffer){
        Setscreen(-1, base1, -1);
        *base = base0;
        }
    else{
        Setscreen(-1, base0, -1);
        *base = base1;
        }
    *buffer = !(*buffer);
    Vsync();
}
