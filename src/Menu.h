#include "Model.h"
#include "Types.h"
extern unsigned char tail;
extern unsigned char head;
extern int mouse_x_old;
extern int mouse_y_old;
extern int mouse_x;
extern int mouse_y;
extern unsigned char keyRegister;
extern unsigned char buffer[256];
extern unsigned char mouseState;
extern unsigned char mouseKeys;
extern bool keyWaiting;

bool menuLoop(bool *buffer, UINT8 **base, UINT8 *base0, UINT8 *base1, Model *model);
void renderSplashChoice(UINT8 *base, Model *model);
void renderFullSplash(UINT8* base, Model *model);
void setMenuChoice(UINT8 key, Model *model);
void renderMouse();
