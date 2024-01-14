
#define FALSE 0
#define TRUE  1
#define VAR   2

#define NLog 26  /*  Kol-vo log. parametrov */

enum INTYPE { SKOBA_IN , SKOBA_OUT , SYMBOL , NEG , BIN , INDEF };
enum POSTTYPE {Hash,Neg,Kon,Diz,Imp,Equ,Skoba_In,Skoba_Out,Symbol,Indef};

struct Var {char *i,*p,x;} Vars[NLog];


char Checkit(char *s)
{char  RelatMatrix[5][5]={{1,0,1,1,0},
			 {0,1,0,1,1},
			 {0,1,0,0,1},
			 {1,0,1,1,0},
			 {1,0,1,1,0}};
char WhatInFix(char c),skobki,i,t1,t2;

skobki=0;t1=0;
for(i=0;i<strlen(s);i++) if(s[i]!=' ') {
  if((t2=WhatInFix(s[i]))==INDEF) return(0);
  if(!RelatMatrix[t1][t2]) return(0);
  if(t2==SKOBA_IN) skobki++;
  if(t2==SKOBA_OUT) skobki--;
  if(skobki<0) return(0);
  t1=t2;}
if(skobki || (t1!=1&&t1!=2)) return(0);
return(1);}


char * Analysis(char *s)
{char i,j,c,
      *STACK=calloc(strlen(s)+1,1),
      *sp=calloc(strlen(s)+1,1),

      MakeMatrix[7][8]={{5,1,1,1,1,1,1,4},
			{2,2,2,2,2,2,1,2},
			{2,1,2,2,2,2,1,2},
			{2,1,2,2,2,2,1,2},
			{2,1,1,1,2,2,1,2},
			{2,1,1,1,2,2,1,2},
			{4,1,1,1,1,1,1,3}};

char WhatPostFix(char c);



j=-1;c=0;
for(i=0;i<=strlen(s);i++) if(s[i]!=' ') {
  if(WhatPostFix(s[i])==Symbol) sp[c++]=s[i];
  else switch(MakeMatrix[j<0?Hash:WhatPostFix(STACK[j])]
			[i<strlen(s)?WhatPostFix(s[i]):Hash]) {
	  case 1 : j++;STACK[j]=s[i];break;
	  case 2 : sp[c++]=STACK[j--];i--;break;
	  case 3 : j--;break;
	  case 4 : goto Fire_Exit;
       }
}
goto Normal_Exit;
Fire_Exit : free(sp);sp=NULL;
Normal_Exit : free(STACK);return(sp);}


char Calcul(char *s)
{char *STACK=calloc(strlen(s)+1,1);
char i,j;
char WhatPostFix(char c);

j=0;
for(i=0;i<strlen(s);i++)
  switch(WhatPostFix(s[i])) {
    case Symbol :
      switch(Vars[s[i]-'A'].x) {
	case TRUE  : STACK[j++]=TRUE;break;
	case FALSE : STACK[j++]=FALSE;break;
        default :
          STACK[j++]=Calcul(Vars[s[i]-'A'].p);
      }
    continue;
    case Neg    : STACK[j-1]=STACK[j-1]?0:1; continue;
    case Kon    : j--;STACK[j-1]=STACK[j-1] & STACK[j]; continue;
    case Diz    : j--;STACK[j-1]=STACK[j-1] | STACK[j]; continue;
    case Equ    : j--;STACK[j-1]=(STACK[j-1] == STACK[j]); continue;
    case Imp    : j--;STACK[j-1]=(STACK[j-1]&&!STACK[j])?0:1;continue;
  }
j=STACK[0];free(STACK);
return(j);}





char WhatPostFix(char c)
{switch(c){
  case '#' : return(Hash);
  case '(' : return(Skoba_In);
  case ')' : return(Skoba_Out);
  case '~' : return(Neg);
  case '&' : return(Kon);
  case '|' : return(Diz);
  case '>' : return(Imp);
  case '=' : return(Equ);
  default : if(c>='A' && c<='Z') return(Symbol);
}return(Indef);}

char WhatInFix(char c)
{switch(c){
  case '(' : return(SKOBA_IN);
  case ')' : return(SKOBA_OUT);
  case '~' : return(NEG);
  default : if(c>='A' && c<='Z') return(SYMBOL);
	    if(c=='&' || c=='|' || c=='>' || c=='=') return(BIN);
}return(INDEF);}



