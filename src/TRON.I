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
typedef enum menuPosition {ONE=0, TWO=40, ESCAPE=80} menuPosition;
typedef void (*Vector)();
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
# 1 "./Model.h" 1
# 3 "./globals.h" 2
# 1 "./types.h" 1
# 4 "./globals.h" 2
# 1 "C:/c68/include/stdio.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 11 "C:/c68/include/stdio.h" 2
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
# 6 "./Model.h" 2



void menuInit();
void init();
void reset();
bool crashed();
void matchStart();
bool crashed2(int x, int y, const UINT8 bitmap[]);

void doMove();
# 10 "./Tron.h" 2


UINT32 getTime();

void gameLoop();
bool onKey();
void getScreen(bool *buffer, UINT8 **base0, UINT8 **base1);
void setBuffer(UINT8 *baseX);
void toggleScreen(bool *buffer, UINT8 *base0, UINT8 *base1);
void doReset();
void getKey(UINT8 *key);
# 10 "Tron.c" 2
# 1 "C:/c68/include/osbind.h" 1
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
# 1 "C:/c68/include/stdlib.h" 1
# 23 "C:/c68/include/stdlib.h"
typedef char  wchar_t;
# 44 "C:/c68/include/stdlib.h"
typedef struct {
    int		quot;
    int		rem;
} div_t;

typedef struct {
    long	quot;
    long	rem;
} ldiv_t;

 double atof (const char *s) ;
 int atoi (const char *str) ;
 long atol (const char *str) ;
 long int strtol (const char *nptr, char **endptr, int base) ;
 unsigned long int strtoul (const char *nptr, char **endptr, int base) ;
 double strtod (const char *s, char **endptr) ;

 void srand (unsigned int seed) ;
 int rand (void) ;

 void *malloc (size_t n) ;
 void free (void *param) ;
 void *realloc (void *_r, size_t n) ;
 void *calloc (size_t n, size_t sz) ;





 void *alloca (size_t) ;
# 89 "C:/c68/include/stdlib.h"
 void  abort (void) ;


 int atexit (void (*)(void)) ;

 void  exit (int) ;

 char *getenv (const char *tag) ;
 int system (const char *s) ;

 void *bsearch (const void *key, const void *base, size_t num, size_t size, int (*cmp )(const void *, const void *)) ;
 void qsort (void *base, size_t total_elems, size_t size, int (*cmp )(const void *, const void *)) ;

 int abs (int x) ;
 long labs (long x) ;

 div_t div (int num, int denom) ;
 ldiv_t ldiv (long num, long denom) ;

 int mblen (const char *, size_t) ;
 size_t mbstowcs (wchar_t *, const char *, size_t) ;
 int mbtowc (wchar_t *, const char *, size_t) ;
 size_t wcstombs (char *, const wchar_t *, size_t) ;
 int wctomb (char *, wchar_t) ;

 wchar_t *wcscat (wchar_t *, const wchar_t *) ;
 int wcscmp (const wchar_t *, const wchar_t *) ;
 wchar_t *wcscpy (wchar_t *, const wchar_t *) ;
 size_t wcslen (const wchar_t *) ;
 wchar_t *wcsncat (wchar_t *, const wchar_t *, size_t) ;
 int wcsncmp (const wchar_t *, const wchar_t *, size_t) ;
 wchar_t *wcsncpy (wchar_t *, const wchar_t *, size_t) ;
# 12 "Tron.c" 2
# 1 "./Model.h" 1
# 13 "Tron.c" 2
# 1 "./Events.h" 1
# 1 "./types.h" 1
# 10 "./Events.h" 2
# 1 "./Model.h" 1
# 11 "./Events.h" 2


void setSpd2(Cycle *cycle, accelerate accel);
void setSpd(Cycle *cycle, UINT8 key);
void setTurn(Cycle *cycle,UINT8 key);
void chng_dir(Cycle *cycle, int *direction);
void chng_spd(Cycle *cycle, int speed);
void sub_life(Player *player);
void maneuver(UINT8 key, Cycle* cycle);
void move(Cycle* cycle);

bool collide(Cycle *cycle);
int readGrid(int x, int y,int length);
void AITurn(Cycle *cycle,Turn dir);
void AIChoice();
void setGhost();
# 14 "Tron.c" 2
# 1 "./Renderer.h" 1
# 1 "./Model.h" 1
# 3 "./Renderer.h" 2
# 1 "./TYPES.H" 1
# 4 "./Renderer.h" 2
# 1 "./Objects.h" 1
# 5 "./Renderer.h" 2


void render();
void rndr_bak();
void rndr_fld();
void rndr_lif(Player *player);
void rndr_lw(Cycle *cycle, int index);
void rndr_cyc(Player *player, int index);
void setLPos(Cycle* cycle);
void uRndrCyc(Player *player);
# 15 "Tron.c" 2
# 1 "./mSetScrn.h" 1
# 1 "./types.h" 1
# 1 "./mSetScrn.h" 2


void mySetScreen(UINT8 *baseX);
void myPhysBase(UINT8 *baseX);
void fst_blk(UINT8 *baseX);
# 16 "Tron.c" 2
# 1 "./raster.h" 1
# 1 "./TYPES.H" 1
# 9 "./raster.h" 2
# 1 "./globals.h" 1
# 10 "./raster.h" 2




int MIN(int x, int y);
void plot_pix(int x, int y);
void p_h_ln(int x, int y, int size);
void p_v_ln(int x, int y, int size);
void p_btmp_8(int x, int y, const UINT8 bitmap[]);
void clr_scrn();
void plotSplsh(UINT32 bitmap[]);
# 17 "Tron.c" 2
# 1 "./Menu.h" 1
# 1 "./Model.h" 1
# 1 "./Menu.h" 2
# 1 "./Types.h" 1
# 2 "./Menu.h" 2
# 1 "./globals.h" 1
# 3 "./Menu.h" 2


bool menuLoop(bool *buffer, UINT8 *base0, UINT8 *base1);
void renderSplashChoice();
void renderFullSplash();
void setMenuChoice(UINT8 key);
void renderMouse();
# 18 "Tron.c" 2
# 1 "C:/c68/include/time.h" 1
# 26 "C:/c68/include/time.h"
typedef long 		time_t;
# 34 "C:/c68/include/time.h"
typedef unsigned long	clock_t;

struct tm
{
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
};



struct timeval {
	long	tv_sec;
	long	tv_usec;
};

struct timezone {
	int	tz_minuteswest;
	int	tz_dsttime;
};


 clock_t	clock	 (void) ;
 double		difftime (time_t, time_t) ;
 time_t		mktime	 (const struct tm *) ;
 time_t		time	 (time_t *) ;
 char * 	asctime	 (const struct tm *) ;
 char *		ctime	 (const time_t *) ;
 struct tm *	gmtime   (const time_t *) ;
 struct tm *	localtime (const time_t *) ;
 unsigned long  strftime (	char *s, size_t maxsize, const char *format, const struct tm *timeptr) ;



 void		tzset	(void) ;


 clock_t	_clock	 (void) ;
 int	gettimeofday (struct timeval *, struct timezone *) ;
 int	settimeofday (struct timeval *, struct timezone *) ;



typedef unsigned long  fd_set;


 int	select	(int, fd_set *, fd_set *, fd_set *,					struct timeval *) ;
# 19 "Tron.c" 2
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
# 20 "Tron.c" 2
# 1 "./isr_asm.h" 1



void trap70_isr();
void trap28_isr();
int set_ipl(int mask);
# 21 "Tron.c" 2
# 1 "./globals.h" 1
# 22 "Tron.c" 2
# 32 "Tron.c"
UINT8 framebuffer2[32255];
# 40 "Tron.c"
void main(){
    UINT8 *base0, *base1;
    bool buffer, quit;
	Vector orig_vector70 = install_vector(70 ,trap70_isr);
	Vector orig_vector28 = install_vector(28 ,trap28_isr);
    rndrRqst = false;
    f = fopen("log.txt","w");
    fclose(f);
    f = fopen("log.txt","a");

    initKeyboard();
    buffer = quit = false;
    getScreen(&buffer, &base0, &base1);
    buffer = true;
    quit = false;
    srand(time(((void *)0) ));
    while(!quit){
        menuInit();
        quit = menuLoop(&buffer, base0, base1);
        if (!quit){
            init();
            gameLoop(&buffer, base0, base1);
        }
    }
    setBuffer(base0);
	install_vector(70 ,orig_vector70);
	install_vector(28 ,orig_vector28);
}

void gameLoop(bool *buffer, UINT8 *base0, UINT8 *base1){
    bool endMatch = false;
    bool crash = false;
    while (!endMatch && (model.user.life > 0 && model.program.life > 0)){
        doReset();
        render();
        toggleScreen(buffer, base0, base1);
        render();
        do{
            if (keyWaiting)
                endMatch = onKey();
            if (rndrRqst){
                toggleScreen(buffer, base0, base1);
                rndr_fld();
                crash = (model.program.crashed || model.user.crashed);
                rndrRqst = false;
            }
        }while (!endMatch && !crash);
    }
}
# 97 "Tron.c"
UINT32 getTime(){
    long *timer = (long*)0x462;
    long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
    UINT32 timeNow;
    timeNow = (UINT32)*timer;
    _trap_1_wl((short)0x20,(long)(old_ssp)) ;
    return timeNow;
}

void getScreen(bool *buffer, UINT8 **base0, UINT8 **base1){
    long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
	*base0 = (void*)_trap_14_w((short)0x2) ;
    myPhysBase(*base0);
    _trap_1_wl((short)0x20,(long)(old_ssp)) ;
    *base1 = (UINT8*)((((long)(&framebuffer2)) + 255) & 0xffffff00);
    base = *base1;
    *buffer = true;
    setBuffer(base);
}

void setBuffer(UINT8 *baseX){
    long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
    mySetScreen(baseX);
    _trap_1_wl((short)0x20,(long)(old_ssp)) ;
}

void toggleScreen(bool *buffer, UINT8 *base0, UINT8 *base1){
    long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
    if (*buffer){
        mySetScreen(base1);
        base = base0;
        }
    else{
        mySetScreen(base0);
        base = base1;
        }
    _trap_1_wl((short)0x20,(long)(old_ssp)) ;
    *buffer = !(*buffer);
}

void doReset(Model *model){
    reset(model);
    matchStart(model);
}
# 152 "Tron.c"
bool onKey(){
    int origSsp;
    int origIpl;
    bool quit = false;
    UINT8 key;
    getKey(&key);
    switch(key){
        case 0x01 :
            quit = true;
            break;
        case 0x4B :
        case 0x4D :
        case 0x48 :
        case 0x50 :
            maneuver(key, &(model.user.cycle));
    }


    return quit;
}

void getKey(UINT8 *key){
    int origSsp;
    int origIpl;
    while(!keyWaiting);

    origSsp = _trap_1_wl((short)0x20,(long)(0)) ;
    origIpl = set_ipl(7);
    *key = buffer[tail];
    keyWaiting = head == tail;
    head++;
    set_ipl(origIpl);
    _trap_1_wl((short)0x20,(long)(origSsp)) ;
}
