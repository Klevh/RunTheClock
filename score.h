#ifndef _SCORES_RTC_BOU_AUBIN_KLEVH_
#define _SCORES_RTC_BOU_AUBIN_KLEVH_

#include "input.h"

#include "SANDAL2/SANDAL2.h"
#include <SDL2/SDL_mixer.h>

#define SCORE 2
#define JEU 1
#define MENU 0

struct Player;

typedef struct{
  int scores[3];
}Score_D;

void update_top_score(Score_D * scores, int s);
Score_D * load_score(char * file);
void save_score(char * file, Score_D * d);
void return_from_score(ElementSDL2 * this,SDL_Keycode c);

#endif
