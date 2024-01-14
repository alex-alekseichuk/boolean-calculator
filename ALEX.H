/*
               Header for ALEX.OBJ
*/

/*----------------------------------------------------------------------------
  MainMenu Colors
-----------------------------------------------------------------------------*/
#define ColCh      0   /*   */
#define ColBack    7
#define ColSc      15
#define ColSkip    3
#define ColAcCh    15
#define ColAcBack  0

/*----------------------------------------------------------------------------
  Control Panel Colors
-----------------------------------------------------------------------------*/
#define ColDW1     15
#define ColDW2     7
#define ColDW3     14
#define ColDCh     0
#define ColDAcCh   15
#define ColDSc     14

#define ColDB1     15
#define ColDB2     2
#define ColDB3     14
#define ColDB4     5

#define ColDI1     15
#define ColDI2     0
#define ColDI3     14

#define ColDP1     15
#define ColDP2     3
#define ColDP3     14
#define ColDP4     1

#define ColDC1     15
#define ColDC2     3
#define ColDC3     14
#define ColDC4     1


extern char *border1,*border2;                     /*  Single & Double Frames */
struct Textel {char c,a;};
extern struct Textel far *Screen;                /*  Pointer to Screen Memory */

struct Win                                                        /*  Window  */
       { unsigned char x1,y1,x2,y2;
	 char *title;
	 char *border;
     unsigned char c1,c2,c3;  /*  Ch,Back,TitleCh   */
	 void *shadow;
	 void *desk,*back;};

struct Win *definewin(struct Win *w,unsigned char x1,unsigned char y1,
    unsigned char x2,unsigned char y2,char *title,unsigned char c1,
    unsigned char c2,unsigned char c3,char *border);
void releasewin(struct Win *w);
void showwin(struct Win *w);
void hidewin(struct Win *w);
void clipwin(struct Win *w);
void unclipwin(void);

void desktop(char c);
void fillarea(unsigned char x1,unsigned char y1,unsigned char x2,
	  unsigned char y2,char c,char a);
void drawbox(unsigned char x1,unsigned char y1,unsigned char x2,
    unsigned char y2,char *s,unsigned char c1,unsigned char c2);
void strmake(char *s,char c,unsigned char n);
void setcursorsize(unsigned char cstart,unsigned char cend);
void setnormalcursor(void);
void setnocursor(void);

/***************************************************************
	   MAIN
	      MENU
******************************************************************/
extern unsigned char
     curopc,              /* Текущее поле MainMenu 1 - maincount */
     flor,                /* 1-SubMenu  0-MainMenu ONLY */
     maincount;           /* Кол-во опций MainMenu */



struct MAINMENU
      {
	char *s;
	unsigned char x,c,n,rskip;
	char sc;
	struct Win *w;
	char key;
	struct Popmenu
	 {char *s;
	  unsigned char y,exi,genk,skip,rskip;
	  char key;
	  char sc;
	 }*pop;
      };
extern  struct MAINMENU *mainmenu;


void drawgenka(void);           /* Чертит гориз. раздел. линию */
void activatebar(void);
void deactivatebar(void);
void deactivatepad(void);
unsigned char activatepad(void);
void showmainmenu(void);
unsigned char domenu(void);                     /* Return 1-Enter 0-Esc */
void setskippad(unsigned char pad,unsigned char k);
void setskipbar(unsigned char pad,unsigned char bar,unsigned char k);
void addmainopc(unsigned char m,char *s,char sc,unsigned char x,
    unsigned char rskip,char key,unsigned char n,unsigned char x1,
    unsigned char y1,unsigned char x2,unsigned char y2);
void addmainpopupopc(unsigned char m,unsigned char n,char *s,char sc,
     unsigned char y,unsigned char exi,unsigned char genk,unsigned char rskip,
     char key);
/***************************************************************
   CONTROL  PANEL
******************************************************************/
struct Control
  { unsigned char n,c,cycle;              /* Если cycle=1 , то CP-Циклич.*/
    struct Controlopc
     { enum TControl
	{BUTTON,INPUTLINE,RADIOBUTTON,CHACKBOX,POPUP}t; void*p;
     } *opcs;
  };

struct Chackbox
  { unsigned char x,y,n,x2;
    char dir;
    struct Chackboxopc {
       char f,*s,sc,key;
    }*opcs;};

struct Radiobutton
  { unsigned char x,y,n,c,x2;
    char dir;
    struct Radiobuttonopc {
       char *s,sc,key;
    }*opcs;};

struct Button
  { unsigned char n,c,dir,attr;   /* dir : 0-None 1-Horiz 2-Vert */
    struct Buttonopc
      { char *s,sc;
	unsigned char x,y,exi;
	unsigned char key;
	void (*proc)(void);                      /* Pointer to Function */
       } *opcs;};

struct Inputline {
  unsigned char x,y,n,f,dir;
  char *s;
};


struct Popup
  { unsigned char x1,y1,x2,y2;
    unsigned int n,top;
    char c,**p;};

struct Control *definecontrol(struct Control *p,unsigned char n,
			      unsigned char cycle);
void showcontrol(struct Control *cont);
char docontrol(struct Control *cont);           /* Return : 0-Esc 3-Enter */
void releasecontrol(struct Control *p,char full);

struct Button *definebutton(struct Button *b,unsigned char n,unsigned char dir);
void releasebutton(struct Button *b,char full);
void addbutton(struct Button *b,unsigned char n,unsigned char x,unsigned char y,
     unsigned char exi,char *s,char sc,char key,void (*proc)(void));
void showacbutton(struct Button *b);
void showdeacbutton(struct Button *b,unsigned char act);
void showpushbutton(struct Button *b);
void showdrawbutton(struct Button *b);
void showbutton(struct Button *b);
char dobutton(struct Button *b);  /* Return : 0-Esc 1-Prev 2-Next 3-Enter */


unsigned char message(char *mes,char *title,unsigned char c,unsigned char n,...);
/*  ----------------------  Very Good Thing  ---------------------------
   c - TextBackground in Window
   ... - { char * s, char sh, char key, ... }
*/

struct Inputline *defineinputline(struct Inputline *il,unsigned char x,
   unsigned char y,unsigned char  f,unsigned char n,unsigned char dir);
void releaseinputline(struct Inputline *il,char full);
showinputline(struct Inputline *il);
void putinputline(char *s,struct Inputline *il);
char doinputline(struct Inputline *il);

struct Popup *definepopup(struct Popup *pop,unsigned char x1,unsigned char y1,
   unsigned char x2,unsigned char y2,unsigned int n);
void releasepopup(struct Popup *pop,char full);
void showpopup(struct Popup *pop);
void showpopupopc(struct Popup *pop,unsigned int n,unsigned char f);
void popupscroll(struct Popup *pop,unsigned char f);
char dopopup(struct Popup *pop);  /* Return : 0-Esc 1-Prev 2-Next 3-Enter */

struct Chackbox *definechackbox(struct Chackbox *p,unsigned char n,
     unsigned char x,unsigned char y,unsigned char x2,char dir);
void addchackbox(struct Chackbox *p,unsigned char n,char *s,char sc,char key,char f);
void releasechackbox(struct Chackbox *p,char full);
void showchackbox(struct Chackbox *p);
void showchackboxopc(struct Chackbox *p,unsigned char n,char act);
char dochackbox(struct Chackbox *p);

struct Radiobutton *defineradiobutton(struct Radiobutton *p,unsigned char n,
  unsigned char x,unsigned char y,unsigned char x2,unsigned char c,char dir);
void addradiobutton(struct Radiobutton *p,unsigned char n,char *s,char sc,char key);
void releaseradiobutton(struct Radiobutton *p,char full);
void showradiobutton(struct Radiobutton *p);
void showradiobuttonopc(struct Radiobutton *p,unsigned char n,char act);
char doradiobutton(struct Radiobutton *p);


char *loader(char *title,char *bs,char bsc,char bkey,char *s,char St);
/*			 └─────── for button ───────┘
   St = 0   for   LOAD      St = 1   for   SAVE  */


/*---------------------------------------------------------------------------
		HELP SYSTEM
----------------------------------------------------------------------------*/
void dohelp(char *helppath);
