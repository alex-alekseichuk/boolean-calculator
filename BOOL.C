#include<alloc.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include"alex.h"

void initmenu(void)
{mainmenu=calloc((maincount=3),sizeof(struct MAINMENU));

addmainopc(1," ���� "         ,1,2 ,0,'�',3,2 ,2,19,7);
addmainopc(2," ���.��ࠦ���� ",1,9 ,0,'�',2,9 ,2,34,6);
addmainopc(3," ������ "       ,1,25,0,'�',2,25,2,44,6);

addmainpopupopc(1,1," ����㧨��...   ",1,3,0,0,0,'�');
addmainpopupopc(1,2," ���࠭���...   ",1,4,0,1,0,'�');
addmainpopupopc(1,3," ��室    Alt-X ",1,6,0,0,0,'�');

addmainpopupopc(2,1," ��������...      Enter ",1,3,0,1,0,'�');
addmainpopupopc(2,2," ���᫨��...        F5 ",1,5,0,0,0,'�');

addmainpopupopc(3,1," ������...     F1 ",1,3,0,1,0,'�');
addmainpopupopc(3,2," � �ணࠬ��...   ",1,5,0,0,0,'�');

return;}


#include"bool.h"


char TOP=0,CUR=0;  /*  ======== �祭� ����� ���-� -----------*/


void About(void)
{struct Win w;struct Button b;char di;
definebutton(&b,1,0);addbutton(&b,1,15,8,1,"   Ok   ",3,'o',NULL);
definewin(&w,18,7,58,17,"� �ணࠬ��",0,7,9,border1);
showwin(&w);clipwin(&w);showbutton(&b);textbackground(7);
textcolor(13);gotoxy(14,2);cprintf("BOOLCALC  1.0");
textcolor(10);gotoxy(10,3);cprintf("�����᪨� ��������");
textcolor(9);gotoxy(3,5);cprintf("Copyright (c) ����ᥩ�� ����ᠭ��");
gotoxy(17,6);cprintf("1996 �.");
while((di=dobutton(&b))==1 || di==2);
releasebutton(&b,0);
unclipwin();hidewin(&w);releasewin(&w);
}



void Exitor(void) /* ��楤�� ��夠 � DOS ==============================*/
{if(1==message("��� � DOS ?","��������",7,2,"   ��室   ",
                                3,'�',"  �⬥����  ",2,'�')) {
	          textcolor(7);textbackground(0);clrscr();
                  puts("  BoolCalc  1.0   Copyright (c) Alexandr Alexeychuk      December 31 1996\n");
                  setnormalcursor();exit(0);}}

/* ���⮥ ���᫥��� �����䨪���----------------------------------- */
void SimpleCalc(void)
		  { struct Win w;
		   char res=Calcul(Vars[CUR+TOP].p),di;
		   struct Button b;
		   definebutton(&b,1,0);addbutton(&b,1,15,4,1,"   Ok   ",3,'o',NULL);
		   definewin(&w,10,10,50,16,"�������",15,3,14,border2);
		   showwin(&w);clipwin(&w);
		   textcolor(15);textbackground(3);
		   gotoxy(16,2);cprintf("%c = ",'A'+CUR+TOP);
		   textcolor(14);cprintf("%s",res?"True":"False");
		   showbutton(&b);
		   while((di=dobutton(&b))==1||di==2);
		   unclipwin();hidewin(&w);releasewin(&w);releasebutton(&b,0);
		    /* end of ���᫥��� */  }

/* �� ��楤�� �஢�ન �� ��横������� ���᫥��� */
/* c-char ('D') ; i-Identif ,��� �ॡ� �㪠�� ('G') */
char CycleError(char c,char i)
{unsigned char j;char ret;
if(i=='T' || i=='F') return(0);
for(j=0;j<strlen(Vars[i-'A'].i);j++)
  if(Vars[i-'A'].i[j]>='A' && Vars[i-'A'].i[j]<='Z') {
    if(Vars[i-'A'].i[j]==c) return(1);
    else if(ret=CycleError(c,Vars[i-'A'].i[j])) return(ret);
  }
return(0);}

void ShowLine(char a)
{char i;
for(i=0;i<78;i++) Screen[(CUR+2)*80+1+i].a=Screen[(CUR+2)*80+1+i].a%16+a*16;
}

void ShowPage(void)
{char i,c,attr;
c='A'+TOP;textbackground(9);
fillarea(2,3,79,23,' ',15+16);
for(i=0;i<21;i++) {
   textcolor(15);gotoxy(3,i+3);cprintf("%c= ",c);
   textcolor((c=='F'||c=='T')?14:12);cprintf("%s",Vars[TOP+i].i);
   c++;
}}


void Editor(void) /* �� ��楤�� ।-��� ���. ���-��� ---------- */
{      if(CUR+TOP!='T'-'A'&&CUR+TOP!='F'-'A')
       {char di,s[80],FLAg,j;
	struct Inputline il;
	il.s=Vars[TOP+CUR].i;strcpy(s,il.s);
	il.x=5;il.n=il.f=73;il.dir=0;il.y=CUR+3;
       showinputline(&il);
st:    while((di=doinputline(&il))==1||di==2);
       FLAg=1;     /*  �஢�ઠ �� ������  */
       if(strlen(il.s)) for(j=0;j<strlen(il.s);j++) if(il.s[j]!=' ') FLAg=0;
       if(FLAg) strcpy(il.s,"F");
       for(j=0;j<strlen(il.s);j++) /* �८�ࠧ㥬 � ����. ॣ���� */
	 if(il.s[j]<='z' && il.s[j]>='a') il.s[j]='A'+il.s[j]-'a';
       if(!di) strcpy(Vars[TOP+CUR].i,s);/* Esc - ����� */
       else {
         /* �஢�ઠ �� ᨭ⠪�� */
         if(!Checkit(il.s)){message("���⠪��᪠� �訡��","��������",4,1,
                                    "   Ok   ",3,'o');goto st;}
         /* �஢�ઠ �� ��横������� ���᫥��� */
         if(CycleError('A'+CUR+TOP,'A'+CUR+TOP)){
           char *s="�����䨪��� $ ��ࠦ����� �१ ᠬ��� ᥡ�";
           s[14]='A'+CUR+TOP;
           message(s,"�����४⭮� ��ࠦ����",4,1,"   Ok   ",3,'o');
           goto st;
         }
       } /* else � Esc */

       /* �⠪, �� ������� ��� */
       free(Vars[CUR+TOP].p);
       Vars[CUR+TOP].p=Analysis(il.s);
       fillarea(6,CUR+3,79,CUR+3,' ',10+16);
       gotoxy(6,CUR+3);textcolor(12);cprintf("%s",Vars[TOP+CUR].i);
       ShowLine(7);
       } /* Enter */
}



void main(void){
unsigned char j;
int k;

fillarea(1,1,80,1,' ',7*16);fillarea(1,25,80,25,' ',7*16);
drawbox(1,2,80,24,border2,14,1);setnocursor();
initmenu();showmainmenu();
CUR=TOP=0;
/* ���樠������ ���. �����䨪��஢ */
for(j=0;j<NLog;j++)if(j!='T'-'A' && j!='F'-'A')
  {Vars[j].i=calloc(80,1);strcpy(Vars[j].i,"F");
   Vars[j].p=Analysis(Vars[j].i);Vars[j].x=VAR; }
Vars['T'-'A'].i=calloc(6,1);strcpy(Vars['T'-'A'].i,"True");
Vars['T'-'A'].p="T";Vars['T'-'A'].x=TRUE;
Vars['F'-'A'].i=calloc(6,1);strcpy(Vars['F'-'A'].i,"False");
Vars['F'-'A'].p="F";Vars['F'-'A'].x=FALSE;

/* Hot Key's ----------------------------------------------------------- */
textbackground(7);gotoxy(3,25);
textcolor(4);cprintf("F1");textcolor(0);cprintf("-������  ");
textcolor(4);cprintf("F10");textcolor(0);cprintf("-����  ");
textcolor(4);cprintf("Enter");textcolor(0);cprintf("-��������  ");
textcolor(4);cprintf("F5");textcolor(0);cprintf("-���᫨��");

ShowPage();About();
ShowLine(7);

for(;;){k=bioskey(0);
  switch(k) {
     case 18432 : /* Up ------------------------------------------------ */
       if(CUR) {ShowLine(1);CUR--;ShowLine(7);}
       else if(TOP)
	  {char c;TOP--;ShowLine(1);window(2,3,79,23);
	   textbackground(1);gotoxy(1,1);insline();window(1,1,80,25);
	   c=TOP+'A';
	   textcolor(15);gotoxy(3,3);cprintf("%c= ",c);
	   textcolor((c=='F'||c=='T')?14:12);cprintf("%s",Vars[TOP].i);
	   ShowLine(7);}
       break;
     case 20480 : /* Down --------------------------------------------- */
       if(CUR<20) {ShowLine(1);CUR++;ShowLine(7);}
       else if(TOP<5)
	  {char c;TOP++;ShowLine(1);window(2,3,79,23);
	   textbackground(1);gotoxy(1,1);delline();window(1,1,80,25);
	   c='A'+TOP+20;
	   textcolor(15);gotoxy(3,23);cprintf("%c= ",c);
	   textcolor((c=='F'||c=='T')?14:12);cprintf("%s",Vars[TOP+20].i);
	   ShowLine(7);}
       break;
     case 18688 : /* PgUp --------------------------------------------- */
       if(TOP){TOP=CUR=0;ShowPage();ShowLine(7);}
       else if(CUR){ShowLine(1);CUR=0;ShowLine(7);}
       break;
     case 20736 : /* PgDown  ---------------------------------------- */
       if(TOP<5){TOP=5;CUR=20;ShowPage();ShowLine(7);}
       else if(CUR<20){ShowLine(1);CUR=20;ShowLine(7);}
       break;
     case 7181 : /* F4 - Edit Log. Param  ----------------------------- */
       Editor();
       break;
     case 16128 : /* F5 - ���᫥��� ���� �� �����. ���-�  */
       SimpleCalc();break;
     case 11520 : /* Alt-X - Exit to DOS -----------------*/
       Exitor();break;
     case 8448 : /* Alt-F SET Identif to False -------------------------*/
       if(CUR+TOP=='T'-'A' || CUR+TOP=='F'-'A') break;
       strcpy(Vars[CUR+TOP].i,"F");goto lab_1;
     case 5120 : /* Alt-T SET Identif to TRUE -------------------------*/
       if(CUR+TOP=='T'-'A' || CUR+TOP=='F'-'A') break;
       strcpy(Vars[CUR+TOP].i,"T");
lab_1: free(Vars[CUR+TOP].p);
       Vars[CUR+TOP].p=Analysis(Vars[CUR+TOP].i);
       fillarea(6,CUR+3,79,CUR+3,' ',10+16);
       gotoxy(6,CUR+3);textcolor(15);cprintf("%s",Vars[TOP+CUR].i);
       ShowLine(7);break;
     case 7680 : /* Alt-� -------------------------------------------*/
       curopc=1;goto Do_Menu;
     case 9472 : /* Alt-� -------------------------------------------*/
       curopc=2;goto Do_Menu;
     case 8704 : /* Alt-� -------------------------------------------*/
       curopc=3;goto Do_Menu;
/* ================  MAIN  MANU ============================ */
Do_Menu :
     case 17408 : /*  F10 -------------------------------------------  */
       if(domenu())
         switch(curopc){
            case 3 :  /* --------------- HELP ---------------- */
              switch(mainmenu[curopc-1].c) {
                 case 2 : About();break;

              }break; /* end of HELP ------------- */
	    case 1 :  /*  ------------ File -----------*/
              switch(mainmenu[curopc-1].c) {
                case 2 : /*  -------- Save ----------- */
		  { FILE *f;char s[81]="*.boo",j;
		    if(loader("���࠭����"," ���࠭���  ",1,'�',s,1))
		      if(f=fopen(s,"wb"))  {
			for(j=0;j<NLog;j++)
			  if(strlen(Vars[j].i)+1 !=
			     fwrite(Vars[j].i,1,strlen(Vars[j].i)+1,f) ||
			     strlen(Vars[j].p)+1 !=
			     fwrite(Vars[j].p,1,strlen(Vars[j].p)+1,f))
			       {message("�訡�� �����","��������",4,1,
					"   Ok   ",3,'o');break;}
		      fclose(f);}
		  } break; /* end of SAVE ------------------- */

                case 1 : /*  -------- LOAD ----------- */
		  { FILE *f;char s[81]="*.boo",j;
		    if(loader("�⥭��"," ����㧨��  ",1,'�',s,0))
		      if(f=fopen(s,"rb"))  {
			for(j=0;j<NLog;j++)
			  {char c=1,k=0;
			  while(c)
			    if((c=fgetc(f))!=EOF) Vars[j].i[k++]=c;
			    else goto o_ch;
			  c=1;k=0;
                          while(c)
			    if((c=fgetc(f))!=EOF) Vars[j].p[k++]=c;
			    else goto o_ch;
			  }
			goto O_k;
			o_ch: message("�訡�� �⥭��","��������",4,1,
				      "   Ok   ",3,'o');
			O_k:
		      fclose(f);TOP=CUR=0;ShowPage();ShowLine(7);}
		  } break; /* end of LOAD ----------------------*/
                case 3 : /*   ------- EXIT  -------- */
                  Exitor();
		  break; /* end of Exit */


	      } break; /* end of File */
            case 2 : /* ---------- ����������  --------------- */
              switch(mainmenu[curopc-1].c) {
		case 1:  /*   -------- Editor  ---------*/
		  Editor();break;
		case 2 : /*   ------- ���᫥���  -------- */
		  SimpleCalc();break;

	      } break; /* end of ���������� */

         } /* ----- switch(cuopc) ---- */
       break;
     default : /* ------------ ��. ������ ������ --------------*/
       if(((char)k>='a'&&(char)k<='z')) k='A'+(char)k-'a';
       if((char)k>='A'&&(char)k<='Z')
         {char c=(char)k-'A'; ShowLine(1);
          if(c<TOP || c>TOP+20) { if(c<TOP) TOP=0; else TOP=5;ShowPage(); }
          CUR=c-TOP;ShowLine(7);
         }
  } /* SWITCH  */
}   /* FOR(;;)  */

/*scanf("%s",s);
if(Checkit(s)) p=Analysis(s);
printf("\n\r s = %s \n\r p = %s \n\r",s,p);*/

}
