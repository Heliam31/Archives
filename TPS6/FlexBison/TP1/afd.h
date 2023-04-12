/**
 * @file afd.h     
 * @author Michel Meynard
 * @brief Définition d'un AFD
 */
#define EINIT 0
#define EI 1
#define EIF 2
#define EID 3
#define EINT 4
#define EFLOAT 5
#define E0 6
#define EPT 7
#define ESP 8
#define ESL 9
#define EDBSL 10
#define ECOMEND 11
#define E* 12
#define EEND* 13
#define ECOMEND2 14
#define NBETAT 15

void class (int ed, unsigned char cd, unsigned char cf, int ef){
	for (i=cd; i<=cf; i++){
		TRANS[ed][i]=ef;		
		}
}

int TRANS[NBETAT][256];		/* table de transition : état suivant */
int JETON[NBETAT];		/* jeton à retourner */

int creerAfd(){			/* Construction de l'AFD */
  int i;int j;			/* variables locales */
  for (i=0;i<NBETAT;i++){
    for(j=0;j<256;j++) TRANS[i][j]=-1; /* init vide */
    JETON[i]=0;			/* init tous états non finaux */
  }
  /* Transitions de l'AFD */
  TRANS[EINIT]['i']=EI; 
  TRANS [EI]['f']= EIF; 
  class(EI, 'A', 'Z', EID);
  class(EI, 'a', 'z', EID);
  class(EI, 0, 9, EID);

  class(EINIT,'A', 'Z', EID); 
  class(EINIT, 'a', 'h', EID); 
  class(EINIT, 'j', 'z', EID);

  class(EID, 'A', 'Z', EID);
  class(EID, 'a', 'z', EID);
  class(EID, 0, 9, EID); 
  TRANS[EID]['_']= EID;

  class(EINIT, 1, 9, EINT); 

  class(EINT, 0, 9, EINT); 
  TRANS[EINT]['.']=EFLOAT;

  TRANS[EINIT][0]=E0; 

  TRANS[E0]['.']=EFLOAT; 

  TRANS[EINIT]['.']=EPT;

  class(EPT, 0, 9, EFLOAT);

  class(EFLOAT, 0, 9, EFLOAT);

  TRANS[EINIT]['\t']=ESP;
  TRANS[EINIT]['\n']=ESP;
  TRANS[EINIT]['\r']=ESP;

  TRANS[ESP]['\t']=ESP;
  TRANS[ESP]['\n']=ESP;
  TRANS[ESP]['\r']=ESP;

  TRANS[EINIT]['/'] = ESL; 

  TRANS[ESL]['/'] = EDBSL;

  TRANS[EDBSL]['^\n'] = EDBSL; 
  TRANS[EDBSL]['\n'] = ECOMEND;

  TRANS[ESL]['*'] = E* ; 

  TRANS[E*]['^*']=E*; 
  TRANS[E*]['*'] = EEND*; 

  TRANS[EEND*]['*'] = EEND*; 
  TRANS[EEND*]["^/*"]=E*;
  TRANS[EEND*]['/'] = ECOMEND2;


  JETON[EI]= 300 + EI;
  JETON[EIF]= 300+EIF;
  JETON[EID] = 300+EID; 
  JETON[EINT] = 300+EINT;
  JETON[EFLOAT] = 300+EFLOAT;
  JETON[E0] = 300+E0;
  JETON[ESP] = 300+ESP;
  JETON[ECOMEND]=300+ECOMEND;
  JETON[ECOMEND2] = 300+ECOMEND2;
  /* états finaux */
}



