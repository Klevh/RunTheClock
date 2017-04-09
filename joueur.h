#ifndef _RTC_PLAYER_BOU_AUBIN_KLEVH_
#define _RTC_PLAYER_BOU_AUBIN_KLEVH_

#include "score.h"

#define abs(a) (a<0?-a:a)

#define RAYON 50

#define WIDTH 600
#define HEIGHT 600

#define P_WIDTH 50
#define P_HEIGHT 50
#define P_SPEED 1.f
#define P_X .5f*WIDTH-P_WIDTH*.5f
#define P_Y HEIGHT/2.f-P_HEIGHT-RAYON+5

#define A_SPEED_MAX 6
#define A_WIDTH 20
#define A_AIG 3

typedef struct Player{
  int up;
  int time;
  int descente;
  int score;
  int newGame;
  int run;
  Mix_Music * music;
  Mix_Chunk * son;
}Player;

void action_player(ElementSDL2 * this);
void click_player(ElementSDL2 * this,SDL_Keycode c);
void update_score(ElementSDL2 * this,int score);
void add_score(ElementSDL2 * this);
void start_game(ElementSDL2 * this,SDL_Keycode c);

#endif
