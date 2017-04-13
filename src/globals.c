#include "globals.h"

volatile unsigned char tail;
volatile unsigned char head;
int mouse_x_old;
int mouse_y_old;
int mouse_x;
int mouse_y;
volatile unsigned char keyRegister;
unsigned char buffer[256];
volatile unsigned char mouseState;
volatile unsigned char mouseKeys;
volatile bool keyWaiting;
volatile bool rndrRqst;

volatile UINT8 *base;
Model model;

