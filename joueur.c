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
    if(a < P_SPEED || a > 360-P_SPEED){
      nextIterateurElementSDL2(this);
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
	  cs=cosf(-M_PI*(a-180)/180);
	  sn=sinf(-M_PI*(a-180)/180);
	  speed+=P_SPEED;
	  moveElementSDL2(this,speed*cs,speed*sn);
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
    data->newGame=0;
    setActionElementSDL2(this,action_player);
    setKeyPressElementSDL2(this,click_player);
    aiguille=nextIterateurElementSDL2(this);
    setActionElementSDL2(aiguille,add_score);
    setRotationSpeedElementSDL2(aiguille,1.f);
  }
}

void click_player(ElementSDL2 * this,SDL_Keycode c){
  Player * data;
  
  if(this){
    data=getDataElementSDL2(this);
    if(data){
      switch(c){
      case 32:
	if(!data->up){
	  data->up=1;
	  data->time=10;
	}
	break;
      case 27:
	data->run=0;
	break;
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

  initIterateurElementSDL2(this);
  getAngleElementSDL2(this,&a1);
  p=nextIterateurElementSDL2(this);
  getAngleElementSDL2(p,&a2);

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
    initIterateurElementSDL2(this);
    nextIterateurElementSDL2(this);
    aiguille=nextIterateurElementSDL2(this);
    setAngleElementSDL2(aiguille,180.f);
    setRotationSpeedElementSDL2(aiguille,1.f);
    break;
  case 27:
    p->run=0;
    break;
  }
}
