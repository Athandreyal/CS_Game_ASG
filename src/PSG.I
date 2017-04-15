# 1 "PSG.c" 1
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
# 1 "PSG.c" 2
# 1 "./PSG.h" 1
# 1 "./TYPES.H" 1
# 13 "./TYPES.H"
typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
typedef enum bool{ false, true } bool;

typedef enum velocity {norm = 4, fast=6} velocity;
typedef enum accelerate {slower,faster} accelerate;
typedef enum Turn {left,right} Turn;
typedef enum menuPosition {ONE=0, TWO=40, ESCAPE=80} menuPosition;
typedef void (*Vector)();
# 4 "./PSG.h" 2
# 1 "C:/c68/include/stdio.h" 1
# 20 "C:/c68/include/stdio.h"
typedef unsigned long  size_t;
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 5 "./PSG.h" 2


UINT32 getTime();
void wait(UINT32 time,UINT32 divisor);
UINT8 readPsg(UINT16 reg);
void allmOn();
void writePsg(UINT8 reg, UINT8 val);
void setEnvlp(UINT8 shape, UINT16 period);
void setEnvSt(UINT8 levelChannel,UINT8 envState);
void chngVol(UINT8 channel, UINT8 volume);
void setMix(int channel, UINT8 device, UINT8 onOFF);
void stop_sound();
void setNote(UINT8,UINT32);
void setNoise(UINT8 freq);
UINT16 getTDVal(UINT32);
void tstSound();

typedef struct RegState {
	UINT32 currentTime;

    UINT8 chanAfine;
    UINT8 chanAcourse;

    UINT8 chanBfine;
    UINT8 chanBcourse;

    UINT8 chanCfine;
    UINT8 chanCcourse;

    UINT8 noise;

    UINT8 mixer;

    UINT8 chanAlevel;
    UINT8 chanBlevel;
    UINT8 chanClevel;

    UINT8 envFreq;
    UINT8 envShape;

}RegState;
# 2 "PSG.c" 2
# 1 "./TYPES.H" 1
# 3 "PSG.c" 2
# 1 "./globals.h" 1
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
extern UINT32 SPLASH[];
void drawBackground(UINT8* base);
void drawLives(UINT8* base, int lives, int player);
# 46 "./Objects.h"
typedef struct Cycle {
    int x;
    int y;
    int speed;
    int direction[2];
    int last[4][4];
    int player;
    UINT8 *bmp;
    UINT8 *lastbmp[4];
}Cycle;

typedef struct Player {
    Cycle cycle;
    int life;
    bool isUser;
    bool crashed;
}Player;

typedef struct Model{
    int mode;
    int mode2;
    bool menu;
    bool doCrash;
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

extern UINT16 CHOICE_X;
extern UINT16 CHOICE_Y;
# 5 "./Model.h" 2
# 1 "./globals.h" 1
# 6 "./Model.h" 2



void menuInit();
void init();
void reset();
bool crashed();
void matchStart();
bool crashed2(int x, int y, const UINT8 bitmap[]);

void doMove();
# 3 "./globals.h" 2
# 1 "./types.h" 1
# 4 "./globals.h" 2
# 1 "C:/c68/include/stdio.h" 1
# 5 "./globals.h" 2


extern volatile unsigned char tail;
extern volatile unsigned char head;
extern int mouse_x_old;
extern int mouse_y_old;
extern int mouse_x;
extern int mouse_y;
extern  unsigned char keyRegister;
extern  unsigned char buffer[256];
extern  unsigned char mouseState;
extern  unsigned char mouseKeys;
extern  bool keyWaiting;
extern  bool rndrRqst;
extern UINT8 *base;
extern Model model;
extern FILE *f;
extern UINT32 ticks;
# 4 "PSG.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 5 "PSG.c" 2
# 1 "./isr.h" 1
# 1 "./types.h" 1
# 3 "./isr.h" 2
# 1 "C:/c68/include/osbind.h" 1
# 4 "./isr.h" 2
# 1 "C:/c68/include/stdio.h" 1
# 5 "./isr.h" 2
# 1 "./globals.h" 1
# 10 "./isr.h" 2


UINT32 getTime();

void keyboard();
Vector install_vector(int num, Vector vector);
void initKeyboard();
void VBL();
# 6 "PSG.c" 2
# 1 "./isr_asm.h" 1



void trap70_isr();
void trap28_isr();
int set_ipl(int mask);
# 7 "PSG.c" 2
# 71 "PSG.c"
UINT32 getTime(){
    long *timer = (long*)0x462;
    long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
    UINT32 timeNow;
    timeNow = (UINT32)*timer;
    _trap_1_wl((short)0x20,(long)(old_ssp)) ;
    return timeNow;
}

void wait(UINT32 time,UINT32 divisor)
{
    UINT32 originalTime = 0;
    UINT32 elapsedTime = 0;
	Vector orig_vector28 = install_vector(28 ,trap28_isr);
    originalTime = ticks;

    while(ticks <= (originalTime + (divisor*time))){
		fprintf(f,"ticks: %5d  originalTime:  %5d  divisor: %2d  time: %5d   result: %5d\n",ticks,originalTime,divisor,time,(originalTime + (divisor*time)));
		fflush(f);
	}
	install_vector(28 ,orig_vector28);
}

void writePsg(UINT8 reg, UINT8 val)
{
    long old_ssp;
    volatile char *PSG_reg_select = 0xFF8800;
    volatile char *PSG_reg_write  = 0xFF8802;

    old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
    *PSG_reg_select = reg;
    *PSG_reg_write  = val;

	_trap_1_wl((short)0x20,(long)(old_ssp)) ;

}

UINT8 readPsg(UINT16 reg)
{
    long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
    volatile UINT16 *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_read  = 0xFF8802;
    UINT8 psgVal;


    *PSG_reg_select = (reg | 0x0300);

    if(reg == 7 )
    {
        *PSG_reg_read  = 0xFF8800;
        psgVal = *PSG_reg_read;
    }
    else
    {
        psgVal = *PSG_reg_read;
    }

     _trap_1_wl((short)0x20,(long)(old_ssp)) ;

    return psgVal;
}

void setNote(UINT8 channel, UINT32 freq)
{
    UINT16 TD = 0;
    UINT8 course;
    UINT8 cChannel;
    UINT8 vChannel;
    UINT8 fine;
	fprintf(f,"line 138 TD: %d\n",TD);
	fprintf(f,"line 139 freq: %ld\n",freq);    	fflush(f);
	TD = getTDVal(freq);
	fprintf(f,"line 141 set note: %5ld\n",freq);
    	fflush(f);
	fprintf(f,"line 143 set note hex: %4x\n",TD);
	fprintf(f,"line 144 set note dec: %d\n",TD);
	fflush(f);

    switch(channel){
        case 0 : cChannel = 1 ;
                     vChannel = 8 ;
                     break;
        case 2 : cChannel = 3 ;
                     vChannel = 9 ;
                     break;
        case 4 : cChannel = 5 ;
                     vChannel = 10 ;
                     break;
    }

    fprintf(f,"cChannel: %i\n", cChannel);
    fprintf(f,"vChannel: %i\n", vChannel);

    fine = (TD & 0x00ff);
    course = (TD >> 8) & 0x0F;

    fprintf(f,"Course: %x\n",course );
    fprintf(f,"Fine: %x\n", fine);


    writePsg(channel,fine);


    writePsg(cChannel,course);




}

void setEnvSt(UINT8 levelChannel,UINT8 envState)
{
    UINT8 oldData = 0;
    UINT8 newState = 0;
    oldData = readPsg(levelChannel);


    writePsg(levelChannel, ((oldData & 0x00) | 0x10));
}
# 210 "PSG.c"
void chngVol(UINT8 channel, UINT8 volume)
{
        writePsg(channel, (volume & 0x0F));
}

void setMix(int channel, UINT8 device, UINT8 onOFF)
{
    UINT8 Setting = 0;
    UINT8 offset = 0;
    UINT8 psgVal = 0;
    UINT8 newPsgVal = 0;

    switch(device){
        case 1 : offset += 0;
                     break;
        case 2 : offset += 3;
                     break;
    }
    switch(channel){
        case 0 : offset += 0;
                     break;
        case 2 : offset += 1;
                     break;

        case 4 : offset += 2;
                     break;
    }

    psgVal = readPsg(7 );

    newPsgVal = psgVal & (~(1 << offset) | (onOFF << offset));
# 247 "PSG.c"
    writePsg(7 , newPsgVal);
}

void stop_sound()
{
    UINT8 blackout = 0x00;
    UINT8 whiteout = 0xFF;

    chngVol(0 ,0);
    chngVol(2 ,0);
    chngVol(4 ,0);

    writePsg(0 ,blackout);
    writePsg(0 ,blackout);

    writePsg(2 ,blackout);
    writePsg(2 ,blackout);

    writePsg(4 ,blackout);
    writePsg(4 ,blackout);

    writePsg(6 ,blackout);

    writePsg(7 ,whiteout);

    writePsg(8 ,blackout);
    writePsg(9 ,blackout);
    writePsg(9 ,blackout);

    writePsg(11 ,blackout);
    writePsg(12 ,blackout);
    writePsg(13 ,blackout);
}


void setNoise(UINT8 freq)
{
    long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
    volatile char *PSG_reg_select = 0xFF8800;
    volatile char *PSG_reg_write  = 0xFF8802;

    *PSG_reg_select = 6 ;
    *PSG_reg_write = (freq & 0x1F);
     _trap_1_wl((short)0x20,(long)(old_ssp)) ;
}
# 306 "PSG.c"
void setEnvlp(UINT8 shape, UINT16 period)
{
    UINT8 fine = 0;
    UINT8 course = 0;

    fine = period;
    course = (period >> 8);
    writePsg(11 , fine);
    writePsg(12 , course);

    writePsg(13 , (shape & 0x0F));
}

void allmOn()
{

     writePsg(7 , 0xC0 );
}

UINT16 getTDVal(UINT32 freq)
{

   UINT32 clckSpd = 125000;
   UINT16 TD = 0;
   TD = (UINT16)(clckSpd / freq);
   fprintf(f,"\n");


   fprintf(f,"GetTDVal output in DEC: %d\n", TD);
   fprintf(f,"GetTDVal output in HEX: %X\n", TD);

   return TD;
}

void tstSound()
{
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

    long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
    FILE *f = fopen("log.txt", "a");
    fprintf(f,"Test the fuck out of this shit\n");
    fclose(f);
# 383 "PSG.c"
    *PSG_reg_select = 0;
	*PSG_reg_write  = 0xEB;

	*PSG_reg_select = 1;
	*PSG_reg_write  = 0x01;





	*PSG_reg_select = 8;
	*PSG_reg_write  = 3;

	while (!(short)_trap_1_w((short)0x0B) )
		;

	*PSG_reg_select = 8;
	*PSG_reg_write  = 0;

	_trap_1_w((short)0x08) ;
	_trap_1_wl((short)0x20,(long)(old_ssp)) ;
}
