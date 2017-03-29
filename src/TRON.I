# 1 "Tron.c" 1
# 1 "./Tron.h" 1
# 1 "./TYPES.H" 1
# 13 "./TYPES.H"
typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
typedef enum bool{ false, true } bool;

typedef enum velocity {norm = 4, fast=6} velocity;
typedef enum accelerate {slower,faster} accelerate;
typedef enum Turn {left,right} Turn;
# 9 "./Tron.h" 2
# 1 "./Model.h" 1
# 1 "./TYPES.H" 1
# 3 "./Model.h" 2
# 1 "./Objects.h" 1
# 1 "./TYPES.H" 1
# 12 "./Objects.h" 2
# 21 "./Objects.h"
extern UINT8 STICKMAN[];
extern UINT8 CYCLE1[4][8];
extern UINT8 CYCLE2[4][8];
void drawBackground(UINT8* base);
void drawLives(UINT8* base, int lives, int player);




typedef struct Cycle {
    int x;
    int y;
    int speed;
    int direction[2];
    int lastPos1[4];
    int lastPos2[4];
    int player;
    UINT8 *bmp;
}Cycle;

typedef struct Player {
    Cycle cycle;
    int life;
    bool isUser;
    bool crashed;
}Player;

typedef struct Model{
    int active;
    Player user;
    Player ghost;
    Player program;
}Model;
# 4 "./Model.h" 2
# 1 "./Constant.h" 1
# 1 "./TYPES.H" 1
# 9 "./Constant.h" 2



extern UINT8 SCREEN_WIDTH;
extern UINT8 MSB;
extern UINT8 REMAINDER_MAX;
extern UINT8 BITS_PER;
extern UINT8 SHIFT;
extern UINT8 LINE_BODY;



extern UINT16 SCREEN_WIDTH_PIX;
extern UINT16 SCREEN_HEIGHT_PIX;
extern int    BMP_OFFSET;
extern UINT8  VBORDER_BITS;
extern UINT8  HBORDER_BITS;
extern UINT8  SCREEN_WIDTH_WORD;
extern UINT8  SCREEN_WIDTH_LONG;
extern UINT8  SHIFT_WORD;
extern UINT16 LINE_BODY_WORD;

extern int P1STARTX;
extern int P1STARTY;
extern int P2STARTX;
extern int P2STARTY;

extern int PLAYER_LIVES;
# 5 "./Model.h" 2


void init(Model *model);
void reset(Model *model);
bool crashed(UINT8 *base, Model *model);
void matchStart(Model *model);
bool crashed2(UINT8 *base, int x, int y, const UINT8 bitmap[]);
# 10 "./Tron.h" 2


UINT32 getTime();
bool onKey(UINT32 key, Model *model);
bool doMove(UINT8 *base, Model *model, long timeNow);
# 10 "Tron.c" 2
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/osbind.h" 2
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 11 "Tron.c" 2
# 1 "./Model.h" 1
# 12 "Tron.c" 2
# 1 "./Events.h" 1
# 1 "./types.h" 1
# 10 "./Events.h" 2
# 1 "./Model.h" 1
# 11 "./Events.h" 2


void setSpd2(Cycle *cycle, accelerate accel);
void setSpd(Cycle *cycle, UINT32 key);
void setTurn(Cycle *cycle,UINT32 key);
void chng_dir(Cycle *cycle, int *direction);
void chng_spd(Cycle *cycle, int speed);
void sub_life(Player *player);
void maneuver(UINT32 key, Cycle* cycle);
void move(Cycle* cycle);

bool collide(UINT8 *base, Cycle *cycle);
int readGrid(UINT8 *base, int x, int y,int length);
void AITurn(Cycle *cycle,Turn dir);
void AIChoice(UINT8 *base, Model *model, long time);
void setGhost(Model *model);
# 13 "Tron.c" 2
# 1 "./Renderer.h" 1
# 1 "./Model.h" 1
# 3 "./Renderer.h" 2
# 1 "./TYPES.H" 1
# 4 "./Renderer.h" 2
# 1 "./Objects.h" 1
# 5 "./Renderer.h" 2


void render(UINT8 *base, Model *model);
void rndr_bak(UINT8 *base, Model *model);
void rndr_fld(UINT8 *base, Model *model);
void rndr_lif(UINT8 *base, Player *player);
void rndr_lw(UINT8 *base, Cycle *cycle);
void rndr_cyc(UINT8 *base, Player *player);
void setLPos(Cycle* cycle);
void uRndrCyc(UINT8 *base, Player *player);
# 14 "Tron.c" 2
# 28 "Tron.c"
UINT8 framebuffer2[32255];

void main(){
    Model model;
	UINT8 *base = (void*)_trap_14_w((short)0x2) ;

    bool quit = false;
    long timeNow, timeThen, timeElapsed;
    bool noCrash = false;
    timeNow = timeThen = timeElapsed = 0;

    init(&model);
    render(base, &model);
    _trap_1_w((short)0x08) ;
    matchStart(&model);
    do{
        timeNow = getTime();
        timeElapsed = timeNow - timeThen;
        if ((short)_trap_1_w((short)0x0B) )
            quit = onKey(_trap_1_w((short)0x08) , &(model));
        if (timeElapsed > 1){
            doMove(base, &model,timeNow);
            rndr_fld(base, &model);
            if(crashed(base, &model)){
                _trap_1_w((short)0x08) ;
                reset(&model);
                matchStart(&model);
                (void)_trap_14_w((short)0x25) ;
                render(base, &model);
            }
            timeThen = timeNow;
            }
    }while (!quit && model.user.life > 0 && model.program.life > 0);

}
# 71 "Tron.c"
UINT32 getTime(){
    long *timer = (long*)0x462;
    long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
    UINT32 timeNow;
    timeNow = (UINT32)*timer;
    _trap_1_wl((short)0x20,(long)(old_ssp)) ;
    return timeNow;
}
# 90 "Tron.c"
bool doMove(UINT8 *base, Model *model, long timeNow){
    bool noCrash = true;
    move(&(model->user.cycle));
    setGhost(model);
    move(&(model->ghost.cycle));
    AIChoice(base, model, timeNow);
    move(&(model->program.cycle));
    return noCrash;
}
# 109 "Tron.c"
bool onKey(UINT32 key, Model *model){
    bool quit = false;
    switch(key){
        case 0x0001001B :
            quit = true;
            break;
        case 0x004B0000 :
        case 0x004D0000 :
        case 0x00480000 :
        case 0x00500000 :
            maneuver(key, &(model->user.cycle));
    }
    return quit;
}
