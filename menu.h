#ifndef _RTC_BOU_AUBIN_KLEVH_
#define _RTC_BOU_AUBIN_KLEVH_

#include "joueur.h"

#define F_SPEED 90.f

typedef struct{
  int * run;
  float aim;
  float speed;
  float dep;
  int tourne;
  Mix_Chunk * son;
}Menu_D;
  
void click_menu(ElementSDL2 * this,SDL_Keycode c);
void action_menu(ElementSDL2 * this);

#endif
