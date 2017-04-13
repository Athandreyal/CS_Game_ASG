#ifndef ISR_ASM_H
#define ISR_ASM_H

void trap70_isr(); /*  KBD  */ 
int set_ipl(int mask);

#endif