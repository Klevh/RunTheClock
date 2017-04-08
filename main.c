#include "menu.h"

#define A_WIDTH 20

int main(){
  int           run;
  /* couleurs */
  int           gris[]={80,80,80,0};
  int           blanc[]={255,255,255,0};
  /* reglage du nombre de frame (timer) */
  int           tps = 0, ticks = 0;
  /* elements */
  ElementSDL2 * aiguille;
  ElementSDL2 * joueur;
  ElementSDL2 * score;
  /* information du joueur */
  Player * dataP;
  /* information du menu */
  Menu_D * dataM;

  /*init SDL2*/
  if(initAllSDL2(0)){
    fprintf(stderr,"Erreur d'initialisation de la SDL2.\n");
    return -1;
  }

  /* init Fenetre */
  initWindowSDL2(WIDTH,HEIGHT+30,"Run The Clock",IMG_INIT_PNG,blanc,JEU);
  if(initIteratorWindowSDL2()){
    fprintf(stderr,"Erreur de creation de la fenetre\n");
    closeAllSDL2();
    return -1;
  }

  /* -- init objets partie jeu -- */
  /* fond du jeu */
  createImage(0.f,0.f,WIDTH,HEIGHT,"ressources/horloge.png",JEU,20);
  createImage(WIDTH/2.f-RAYON,HEIGHT/2.f-RAYON,2*RAYON,2*RAYON,"ressources/centre.png",JEU,20);

  /* joueur */
  joueur=createImage(P_X,P_Y,P_WIDTH,P_HEIGHT,"ressources/player.png",JEU,0);
  setKeyPressElementSDL2(joueur,start_game);
  dataP=malloc(sizeof(*dataP));
  dataP->up=0;
  dataP->score=0;
  dataP->time=0;
  dataP->descente=0;
  dataP->newGame=0;
  dataP->run=1;
  setDataElementSDL2(joueur,dataP);
  setRotationPointElementSDL2(joueur,.5f,1.f+1.f*RAYON/P_WIDTH/1.1f);
  setAngleElementSDL2(joueur,30.f);

  /* score */
  createBlock(0.f,HEIGHT,WIDTH,30.f,gris,JEU,20);
  score=createTexte(WIDTH/8.f,HEIGHT,3*WIDTH/4.f,30,"ressources/CurlyStars.ttf","Score : 0                    ",blanc,JEU,0);
  addElementToElementSDL2(joueur,score);

  /* aiguille des heures */
  aiguille=createImage(WIDTH*1.f/2-A_WIDTH*1.f/2,266.f,A_WIDTH,190.f,"ressources/aiguille3.png",JEU,1);
  setRotationPointElementSDL2(aiguille,0.5f,0.175f);
  setAngleElementSDL2(aiguille,180.f);
  addElementToElementSDL2(aiguille,joueur);
  addElementToElementSDL2(joueur,aiguille);
  
  /* aiguille des minutes */
  aiguille=createImage(WIDTH*1.f/2-A_WIDTH*1.f/2,265.f,A_WIDTH,230.f,"ressources/aiguille2.png",JEU,1);
  setRotationPointElementSDL2(aiguille,0.5f,0.155f);
  setAngleElementSDL2(aiguille,180.f);
  addElementToElementSDL2(aiguille,joueur);
  addElementToElementSDL2(joueur,aiguille);
  
  /* aiguille des secondes */
  aiguille=createImage(WIDTH*1.f/2-A_WIDTH*1.f/2,261.f,A_WIDTH,270.f,"ressources/aiguille1.png",JEU,1);
  setRotationPointElementSDL2(aiguille,0.5f,0.145f);
  setAngleElementSDL2(aiguille,180.f);
  addElementToElementSDL2(aiguille,joueur);
  addElementToElementSDL2(joueur,aiguille);

  /* -- init objets partie menu -- */
  /* fond du jeu */
  createImage(0.f,30.f,WIDTH,HEIGHT,"ressources/horloge.png",MENU,20);
  
  /* titre */
  createTexte(WIDTH/8.f,0,3*WIDTH/4.f,70,"ressources/CurlyStars.ttf","Run The Clock",gris,MENU,0);

  /* "bouton" quitter */
  createTexte(0.f,HEIGHT/2.f,70,60,"ressources/CurlyStars.ttf","Quit",gris,MENU,0);

  /* "bouton" jouer */
  createTexte(WIDTH-70.f,HEIGHT/2.f,70,60,"ressources/CurlyStars.ttf","Play",gris,MENU,0);
  
  /* aiguille */
  aiguille=createImage(WIDTH*1.f/2-A_WIDTH*1.f/2,296.f,A_WIDTH,190.f,"ressources/aiguille4.png",MENU,0);
  setAngleElementSDL2(aiguille,180.f);
  setRotationPointElementSDL2(aiguille,0.5f,0.175f);
  setKeyPressElementSDL2(aiguille,click_menu);
  setActionElementSDL2(aiguille,action_menu);
  dataM=malloc(sizeof(*dataM));
  dataM->run=&(dataP->run);
  dataM->aim=0.f;
  dataM->tourne=0;
  dataM->speed=0.f;
  dataM->dep=0.f;
  setDataElementSDL2(aiguille,dataM);
  
  while(dataP->run){
    tps = SDL_GetTicks();
    
    run=!PollEventSDL2();
    dataP->run=run && dataP->run;
    updateWindowSDL2();
    displayWindowSDL2();

    /* delai pour 60 frames/secondes */
    ticks = 16 - SDL_GetTicks() + tps;
    if(ticks>0){
      SDL_Delay(ticks);
    }
  }

  closeAllWindowSDL2();
  closeAllSDL2();
}
