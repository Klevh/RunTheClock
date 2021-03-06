#include "joueur.h"

void action_player(ElementSDL2 *this){
  static float speed = 0;
  static int bouge =0;
  static int aig=0;
  static int diff=0;
  Player * data;
  Score_D * ds;
  float y,a;
  float cs,sn;
  ElementSDL2 * aiguille;
  ElementSDL2 * eleScore;
  int i=0,j;
  char s[]="          ";

  initIterateurElementSDL2(this);
  data=getDataElementSDL2(this);
  getAngleElementSDL2(this,&a);
  if(data->score>(diff+1)*(A_SPEED_MAX+aig)){
    diff++;
    if(aig<3){
      nextIterateurElementSDL2(this);
      aiguille=nextIterateurElementSDL2(this);
      i=0;
      while(aiguille && i<aig){
	++i;
	aiguille=nextIterateurElementSDL2(this);
      }
      if(diff>(aig+1)*A_AIG){
	aig++;
	if(aig<3){
	  aiguille=nextIterateurElementSDL2(this);
	  setRotationSpeedElementSDL2(aiguille,1.f);
	  setActionElementSDL2(aiguille,add_score);
	  setAngleElementSDL2(aiguille,a+45.f);
	}
      }else{
	addRotationSpeedElementSDL2(aiguille,1.f);
      }
      initIterateurElementSDL2(this);
    }
  }
  if(data->newGame>0){
    if(a < P_SPEED || a > 360-P_SPEED){
      nextIterateurElementSDL2(this);
      i=0;
      while(i<3 && (aiguille=nextIterateurElementSDL2(this))){
	++i;
	setRotationSpeedElementSDL2(aiguille,0.f);
	setActionElementSDL2(aiguille,NULL);
      }
      setActionElementSDL2(this,NULL);
      setKeyPressElementSDL2(this,start_game);
      data->newGame=-60;
      diff=0;
      aiguille=nextIterateurElementSDL2(this);
      eleScore=nextIterateurElementSDL2(aiguille);
      ds=getDataElementSDL2(eleScore);
      update_top_score(ds,data->score);
      for(i=0;i<3;++i){
	sprintf(s,"          ");
	sprintf(s,"%d : %d",i+1,ds->scores[i]);
	j=4;
	while(s[++j]);
	if(j<10){
	  s[j]=' ';
	}
	setTextElementSDL2(eleScore,s);
	eleScore=nextIterateurElementSDL2(aiguille);
      }
      initIterateurElementSDL2(aiguille);
      data->score=0;
      aig=0;
      cs=cosf(M_PI*(a+90)/180);
      sn=sinf(M_PI*(a+90)/180);
      speed+=P_SPEED;
      moveElementSDL2(this,speed*cs,speed*sn);
      while(speed<P_SPEED*21){
	speed+=P_SPEED;
	moveElementSDL2(this,speed*cs,speed*sn);
      }
      bouge = 0;
      data->up=0;
      data->descente=0;
      speed=0;
      replaceElementSDL2(this,P_X,P_Y);
      Mix_FadeOutMusic(500);
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
	  cs=cosf(M_PI*(a+90)/180);
	  sn=sinf(M_PI*(a+90)/180);
	  speed+=P_SPEED;
	  moveElementSDL2(this,speed*cs,speed*sn);
	  getCoordElementSDL2(this,NULL,&y);
	  if(speed>=P_SPEED*20){
	    bouge = 0;
	    data->up=0;
	    data->descente=0;
	    replaceElementSDL2(this,P_X,P_Y);
	    speed=0;
	    Mix_PlayChannel(1,data->son,0);
	  }
	}
      }
    }
  }else if(data->newGame<0){
    data->newGame++;
  }else{
    speed=0;
    bouge=0;
    diff=0;
    aig=0;
    data->newGame=1;
    setActionElementSDL2(this,action_player);
    setKeyPressElementSDL2(this,click_player);
    nextIterateurElementSDL2(this);
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
	changeDisplayWindowSDL2(MENU);
	Mix_FadeOutMusic(500);
	break;
      }
    }
  }
}

void update_score(ElementSDL2 * this,int score){
  char s[]="SCORE :                   ";
  int i=8;

  sprintf(s+i,"%d",score);
  while(s[++i]);
  if(i<25){
    s[i]=' ';
  }

  setTextElementSDL2(this,s);
}

void add_score(ElementSDL2 * this){
  float a1,a2,a;
  ElementSDL2 * p;
  Player * data;
  float x1,y1,x2,y2,tmp,px,py,cs,sn;
  int w1,h1,w2,h2;
  int touche=0;
  
  initIterateurElementSDL2(this);
  getAngleElementSDL2(this,&a1);
  p=nextIterateurElementSDL2(this);
  getAngleElementSDL2(p,&a2);

  getCoordElementSDL2(this,&x1,&y1);
  getDimensionElementSDL2(this,&w1,&h1);
  getCoordElementSDL2(p,&x2,&y2);
  getDimensionElementSDL2(p,&w2,&h2);
  getRotationPointElementSDL2(p,&px,&py);
  if(y2+h2>=y1){
    a=a1-a2;
    if(a>-25.f){
      px=px*w2+x2;
      py=py*h2+y2;

      cs=cosf(-M_PI*a/180);
      sn=sinf(-M_PI*a/180);

      tmp=px+(x2-px)*cs-(y2-py)*sn;
      y2=py+(x2-px)*sn+(y2-py)*cs;
      x2=tmp;

      if(y2<HEIGHT/2.f-RAYON && x2+.3f*w2>x1 && x2<x1+w1){
	getRotationSpeedElementSDL2(this,&a);
	printf("1\n");
	addAngleElementSDL2(p,a);
      }else{
	touche=1;
      }
    }
  }else{
    touche=1;
  }

  if(touche){
    if(a1>a2){
      addAngleElementSDL2(this,-360.f);
      data=getDataElementSDL2(p);
      data->score++;
      initIterateurElementSDL2(p);
      update_score(nextIterateurElementSDL2(p),data->score);
    }
  }
}

void start_game(ElementSDL2 * this,SDL_Keycode c){
  ElementSDL2 * aiguille;
  Player * p;

  switch(c){
  case 32:
    p=getDataElementSDL2(this);
    p->score=-1;
    setActionElementSDL2(this,action_player);
    setKeyPressElementSDL2(this,click_player);
    initIterateurElementSDL2(this);
    update_score(nextIterateurElementSDL2(this),0);
    aiguille=nextIterateurElementSDL2(this);
    setAngleElementSDL2(this,30.f);
    setAngleElementSDL2(aiguille,75.f);
    setRotationSpeedElementSDL2(aiguille,1.f);
    setActionElementSDL2(aiguille,add_score);
    Mix_PlayMusic(p->music,-1);
    break;
  case 27:
    changeDisplayWindowSDL2(MENU);
    break;
  }
}
