#include "joueur.h"

void action_player(ElementSDL2 *this){
  static float speed = 0;
  static int bouge =0;
  static int diff=0;
  Player * data;
  float y,a;
  float cs,sn;
  ElementSDL2 * aiguille;

  initIterateurElementSDL2(this);
  data=getDataElementSDL2(this);
  if(!data->newGame){
    getAngleElementSDL2(this,&a);
    if(a==0){
      while((aiguille=nextIterateurElementSDL2(this))){
	setRotationSpeedElementSDL2(aiguille,0.f);
	setActionElementSDL2(aiguille,NULL);
      }
      setActionElementSDL2(this,NULL);
      setKeyPressElementSDL2(this,start_game);
    }else{
      if(data->up){
	if(data->up==1){
	  speed=-P_SPEED*21;
	  data->up=-1;
	  bouge = 1;
	}
	if(speed<P_SPEED && speed>-P_SPEED && bouge){
	  data->descente=1;
	}
	if(data->descente && data->time){
	  data->time--;
	}else{
	  cs=cosf(-M_PI*a/180);
	  sn=cosf(-M_PI*a/180);
	  speed+=P_SPEED;
	  moveElementSDL2(this,-speed*sn,speed*cs);
	  getCoordElementSDL2(this,NULL,&y);
	  if(speed>=P_SPEED*21){
	    bouge = 0;
	    data->up=0;
	    data->descente=0;
	    speed=0;
	    replaceElementSDL2(this,P_X,P_Y);
	  }
	}
      }
    }
  }else{
    speed=0;
    bouge=0;
    diff=0;
    setActionElementSDL2(this,action_player);
    setKeyPressElementSDL2(this,click_player);
    aiguille=nextIterateurElementSDL2(this);
    setActionElementSDL2(aiguille,add_score);
    setRotationPointElementSDL2(aiguille,0.5f,0.145f);
    setRotationSpeedElementSDL2(aiguille,1.f);
  }
}

void click_player(ElementSDL2 * this,SDL_Keycode c){
  Player * data;
  
  if(this){
    data=getDataElementSDL2(this);
    if(data && c==32){
      if(!data->up){
	data->up=1;
	data->time=10;
      }
    }
  }
}

void update_score(ElementSDL2 * this,int score){
  char s[]="Score :                      ";
  int i=8;

  sprintf(s+i,"%d",score);
  while(s[++i]);
  if(i<28){
    s[i]=' ';
  }

  setTextElementSDL2(this,s);
}

void add_score(ElementSDL2 * this){
  float a1,a2;
  ElementSDL2 * p;
  Player * data;
  float x1,y1,y1b,x2,y2,x3,y3,xt,yt,cs,sn;
  int w1,h1,w2,h2,res;
  
  getCoordElementSDL2(this,&x1,&y1);
  getDimensionElementSDL2(this,&w1,&h1);

  x1+=w1*0.5f;
  y1b=y1+h1;
  
  initIterateurElementSDL2(this);
  getAngleElementSDL2(this,&a1);
  p=nextIterateurElementSDL2(this);
  getAngleElementSDL2(p,&a2);

  getRotationPointElementSDL2(p,&x3,&y3);

  x3=x3*w2+x2;
  y3=y3*h2+y2;

  cs=cosf(a2-a1);
  sn=sinf(a2-a1);
  
  xt=x3+(x2-x3)*cs-(y2-y3)*sn;
  yt=y3+(x2-x3)*sn-(y2-y3)*cs;

  x2=xt + w2*0.5f;  /*coordonnée x du cercle joueur*/
  y2=yt + w2*0.5f;  /*coordonnée y du cercle joueur*/
  

  if(collisionCercleSegment(x1,y1,x1,y1+h1,x2,y2,w2)){
    addAngleElementSDL2(p,P_SPEED);
  }
  
  
  
  if(a1 < a2){
    data=getDataElementSDL2(p);
    data->score++;
    initIterateurElementSDL2(p);
    update_score(nextIterateurElementSDL2(p),data->score);
    addAngleElementSDL2(this,360);
  }
}

void start_game(ElementSDL2 * this,SDL_Keycode c){
  Player * p=getDataElementSDL2(this);
  ElementSDL2 * aiguille;
  
  switch(c){
  case 32:
    setActionElementSDL2(this,action_player);
    setKeyPressElementSDL2(this,click_player);
    break;
  case 27:
    p->run=0;
    break;
  }
}






int pointDansCercle(float x, float y, float xc, float yc, float rayon) {
  int res = 1;
  int d2 = (x-xc)*(x-xc) + (y-yc)*(y-yc);
   if (d2>rayon*rayon)
     res=0;
   return res;
}




int collisionCercleDroite(float xa, float ya, float xb, float yb, float xc, float yc, float rayon){

  int res = 0;
  float xt, yt, xac, yac;
  float numerateur, denominateur, CI;
  
   xt = xb - xa;
   yt = yb - ya;

   xac = xc - xa;
   yac = yc - ya;

   numerateur = xt*yac - yt*xac;   /* norme du vecteur v*/

   if (numerateur <0)
     numerateur = -numerateur ;   /* valeur absolue ; si c'est négatif, on prend l'opposé.*/

   denominateur = sqrt(xt*xt + yt*yt);  /* norme de u*/
   CI = numerateur / denominateur;
   if (CI<rayon)
     res=1;

   return res;
}



int collisionCercleSegment(float xa, float ya, float xb, float yb, float xc, float yc, float rayon) {

  int res = 1;
  float xab, yab, xac, yac,xbc,ybc;
  float prodscal1, prodscal2;
  
  
  if (!collisionCercleDroite(xa,ya,xb,yb,xc,yc,rayon))
    res=0;  /* si on ne touche pas la droite, on ne touchera jamais le segment*/

  else {

    res = 0;
    xab = xb - xa;
    yab = yb - ya;
    xac = xc - xa;
    yac = yc - ya;
    xbc = xc - xb;
    ybc = yc - yb;
    
    prodscal1 = xab*xac + yab*yac;  /* produit scalaire*/
    prodscal2 = (-xab)*xbc + (-yab)*ybc;  /* produit scalaire*/

    if (prodscal1>=0 && prodscal2>=0)
      res = 1;   /* I entre A et B, ok.*/
    /*dernière possibilité, A ou B dans le cercle*/
    if (pointDansCercle(xa,ya,xc,yc,rayon))
      res=1;
    if (pointDansCercle(xb,yb,xc,yc,rayon))
      res=1;
  }

  return res;
  
}
