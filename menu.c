#include "menu.h"

void click_menu(ElementSDL2 * this,SDL_Keycode c){
  Menu_D * m=getDataElementSDL2(this);
  float a;

  getAngleElementSDL2(this,&a);
  switch(c){
  case 79:
  case 94:
    if(a>=90.f && a<270.f){
      m->speed=270.f-a;
      m->tourne=1;
    }else if(a>=270.f){
      m->speed=a-270.f;
    }else{
      m->speed=-a-90.f;
      m->tourne=-1;
    }
    m->dep=abs(m->speed);
    m->speed/=F_SPEED;
    m->aim=270.f;
    break;
  case 92:
  case 80:
    if(a<90.f){
      m->speed=90.f-a;
      m->tourne=1;
    }else if(a>270.f){
      m->speed=360.f-a+90.f;
    }else{
      m->speed=90.f-a;
      m->tourne=-1;
    }
    m->dep=abs(m->speed);
    m->speed/=F_SPEED;
    m->aim=90.f;
    break;
  case 96:
    if(a<180.f){
      m->speed=180.f-a;
      m->tourne=1;
    }else{
      m->speed=180.f-a;
      m->tourne=-1;
    }
    m->dep=abs(m->speed);
    m->speed/=F_SPEED;
    m->aim=180.f;
    break;
  case 90:
  case 81:
    if(a>180.f){
      m->speed=360.f-a;
      m->tourne=1;
    }else{
      m->speed=-a;
      m->tourne=-1;
    }
    m->dep=abs(m->speed);
    m->speed/=F_SPEED;
    m->aim=0.f;
    break;
  case 13:
    if(m->aim==270.f){
      changeDisplayWindowSDL2(JEU);
    }else if(m->aim==90.f){
      *(m->run)=0;
    }
    break;
  case 27:
    *(m->run)=0;
    break;
  }
}

void action_menu(ElementSDL2 * this){
  Menu_D * m=getDataElementSDL2(this);
  float a;
  
  if(m->tourne){
    m->dep-=abs(m->speed);
    addAngleElementSDL2(this,m->speed);
    getAngleElementSDL2(this,&a);
    if(a<0.f){
      a+=360.f;
    }
    if(a>=360.f){
      a-=360.f;
    }
    if(m->dep<=0.f){
      m->tourne=0;
      a=m->aim;
    }
    setAngleElementSDL2(this,a);
  }
}
