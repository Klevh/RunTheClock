/*
 * Fait par Baptiste PRUNIER
 * dernière modification le 21/03/2017
 */

#include "input.h"



/* ----------------------------------------------------
 * Lecture d'une chaine de caractere de taille inconnue
 */
void freeListChar(ListChar l){
  Element *e=l.first,*nxt;
  while(e!=NULL){
    nxt=e->nxt;
    free(e);
    e=nxt;
  }
}

char* ltoa(ListChar l){
  char *s=NULL;
  int i;
  Element *e;

  if(l.taille>-1 || (l.taille>0 && l.first)){
    s=malloc((l.taille+1)*sizeof(*s));
    e=l.first;
    i=0;
    while(i<l.taille && e){
      *(s+i)=e->c;
      e=e->nxt;
      ++i;
    }
    if(i<l.taille){
      free(s);
      s=NULL;
    }else{
      s[i]='\0';
    }
  }

  return s;
}

char* fread_str_(FILE *stream,int *n,char end){
  ListChar l;
  char c,*s=NULL;
  Element *e;

  if(stream){
    /*init de la liste*/
    l.taille=0;
    l.first=NULL;

    /*lecture*/
    c=getc(stream);
    if(c!=end){
      l.first=malloc(sizeof(*(l.first)));
      e=l.first;
      e->c=c;
      l.taille=1;
      c=getc(stream);
      while(c!=end){
	e->nxt=malloc(sizeof(*(e->nxt)));
	e=e->nxt;
	e->c=c;
	++(l.taille);
	c=getc(stream);
      }
      e->nxt=NULL;
    }

    if(n){
      *n=l.taille;
    }

    /*convertion en chaine de caractere*/
    s=ltoa(l);

    /*liberation de la liste*/
    freeListChar(l);
  }

  return s;
}

char * fread_str(FILE *stream){
  if(stream==stdin){
    return fread_str_(stream,NULL,'\n');
  }else{
    return fread_str_(stream,NULL,EOF);
  }
}

char * read_str(){
  return fread_str_(stdin,NULL,'\n');
}

char * ofread_str(char * path){
  FILE * fp=fopen(path,"r");
  char * res=NULL;

  if(fp){
    res=fread_str_(fp,NULL,EOF);
    fclose(fp);
  }

  return res;
}
/* ------------------------------------------- */



/* -------------------------------------------
 * Lecture d'un nombre
 */
int* read_int(FILE *stream){
  int signe=1;
  int *val=NULL;
  char c=getc(stream);

  if(stream){
    c=getc(stream);
    val=malloc(sizeof(*val));
    if(c=='-' || c=='+'){
      if(c=='-'){
	signe*=-1;
      }
      c=getc(stream);
    }
    if(c==EOF || c=='\n'){
      free(val);
      val=NULL;
    }
    
    while(val!=NULL && c!='\n' && c!=EOF){
      if(c>='0' && c<='9'){
	*val*=10;
	*val+=(int)c-(int)('0');
      }else{
	if(c!='\n' && c!=EOF){
	  free(val);
	  val=NULL;
	}
      }
      c=getc(stream);
    }

    if(c!='\n' && c!=EOF){
      viderBuffer(stream);
    }
    if(val!=NULL){
      *val*=signe;
    }
  }

  return val;
}

float* read_float(FILE *stream){
  int signe=1,virgule=0; /*virgule vaut 1 une fois passe sur la virgule (releve l erreur de 2 virgules*/
  float *val=NULL,puissDneg=1; /*puissDneg : puissance de dix negatif (droite de la virgule)*/
  char c;

  if(stream){
    c=getc(stream);
    val=malloc(sizeof(*val));
    if(c=='-' || c=='+' || c=='.' || c==','){
      if(c=='-'){
	signe*=-1;
      }else{
	if(c=='.' || c==','){
	  virgule=1;
	}
      }
      c=getc(stream);
    }
    if(c==EOF || c=='\n'){
      free(val);
      val=NULL;
    }
    
    while(val!=NULL && c!='\n' && c!=EOF){
      if((c=='.' || c==',') && !virgule){
	virgule=1;
      }else{
	if(c>='0' && c<='9'){
	  if(virgule){
	    puissDneg/=10;
	    *val+=((int)c-(int)('0'))*1.0*puissDneg;
	  }else{
	    *val*=10;
	    *val+=(int)c-(int)('0');
	  }
	}else{
	  if(!(c==EOF || c=='\n')){
	    free(val);
	    val=NULL;
	  }
	}
      }
      c=getc(stream);
    }

    if(c!='\n' && c!=EOF){
      viderBuffer(stream);
    }
    if(val!=NULL){
      *val*=signe;
    }
  }
  return val;
}
/* ------------------------------------------- */



/* -------------------------------------------
 * Utilitaires
 */
void viderBuffer(FILE *stream){
  if(stream==stdin){
    char c=getc(stream);
    while(c!=EOF && c!='\n'){
      c=getc(stream);
    }
  }
}
/* ------------------------------------------- */
