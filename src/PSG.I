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


UINT8 readPsg(UINT16 reg);
void allmOn();
void writePsg(UINT8 reg, UINT8 val);
void setEnvlp(UINT8 shape, UINT16 period);
void chngVol(UINT8 channel, UINT8 volume);
void setMix(int channel, UINT8 device);
void stop_sound();
void setNote(UINT8,UINT32,UINT8);
void setNoise(UINT8 freq);
UINT16 getTDVal(UINT32);
void tstSound();
# 2 "PSG.c" 2
# 1 "./TYPES.H" 1
# 3 "PSG.c" 2
# 50 "PSG.c"
UINT8 readPsg(UINT16 reg)
{
    long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
    volatile UINT16 *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_read  = 0xFF8802;
    UINT8 psgVal;


    *PSG_reg_select = (reg | 0x0300);
     psgVal = *PSG_reg_read;

     _trap_1_wl((short)0x20,(long)(old_ssp)) ;

    return psgVal;
}


void setEnvlp(UINT8 shape, UINT16 period)
{
    UINT8 fine = period;
    UINT8 course = (period >> 8);
    writePsg(11 , fine);
    writePsg(12 , course);

    writePsg(13 , (shape & 0x0F));

}

void chngVol(UINT8 channel, UINT8 volume)
{
    writePsg(vChannel, (volume & 0x0F));
}

void allmOn()
{

     writePsg(7 , 0xC0 );
}
void setMix(int channel, UINT8 device)
{
    UINT8 Setting;
    UINT8 offset;
    UINT8 psgVal;
    UINT8 newPsgVal;

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
    newPsgVal = psgVal | (0x01 << offset);
    writePsg(7 , newPsgVal);
}

void stop_sound()
{
    UINT8 blackout = 0x00;
    chngVol(0 ,0);
    chngVol(2 ,0);
    chngVol(4 ,0);
# 143 "PSG.c"
}

void writePsg(UINT8 reg, UINT8 val)
{
    long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
    volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

    *PSG_reg_select = reg;
    *PSG_reg_write  = val;

     _trap_1_wl((short)0x20,(long)(old_ssp)) ;
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

void setNote(UINT8 channel, UINT32 freq, UINT8 volume)
{
    UINT16 TD = getTDVal(freq);
    UINT8 course;
    UINT8 cChannel;
    UINT8 vChannel;
    UINT8 fine;


    FILE *f = fopen("log.txt", "a");
     fprintf(f,"Set note TD Val: %i\n",TD);
     fprintf(f,"Channel before switch: %i\n",channel);

    switch(channel){
        case 0 : cChannel = 1 ;
                     vChannel = 8 ;
                     break;
        case 2 : cChannel = 3 ;
                     vChannel = 9 ;
                     break;
        case 4 : cChannel =;
                     vChannel = 10 ;
                     break;
    }

    fprintf(f,"cChannel: %i\n", cChannel);
    fprintf(f,"vChannel: %i\n", vChannel);

    fine = TD;
    course = (TD >> 8) & 0x0F;

    fprintf(f,"Course: %i\n",course );
    fprintf(f,"Fine: %i\n", fine);


    writePsg(channel,fine);


    writePsg(cChannel,course);


    writePsg(vChannel,(volume & 0x0F));


    fclose(f);
}
UINT16 getTDVal(UINT32 freq)
{

   UINT32 clckSpd = 2000000;
   UINT16 TD = 0;
   FILE *f = fopen("log.txt", "a");
   TD = (clckSpd / (16*freq));
   fprintf(f,"\n");

   fprintf(f,"GetTDVal output in DEC: %i\n", TD);
   fprintf(f,"GetTDVal output in HEX: %X\n", TD);
   fclose(f);

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
# 277 "PSG.c"
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
