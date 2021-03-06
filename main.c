#include "menu.h"

int main(){
  int           i,j;
  int           run;
  /* couleurs */
  int           noir[]={0,0,0,0};
  int           blanc[]={255,255,255,0};
  /* reglage du nombre de frame (timer) */
  int           tps = 0, ticks = 0;
  /* elements */
  ElementSDL2 * aiguille;
  ElementSDL2 * joueur;
  ElementSDL2 * score;
  /* information du joueur */
  Player      * dataP;
  /* information du menu */
  Menu_D      * dataM;
  /* information des meilleurs scores */
  Score_D     * dataS;
  char          s[]="          ";

  /*init SDL2*/
  if(initAllSDL2(0)){
    fprintf(stderr,"Erreur d'initialisation de la SDL2.\n");
    return -1;
  }

  /* init audio */
  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
    fprintf(stderr,"Erreur init audio\n");
    closeAllSDL2();
    return -1;
  }
  Mix_AllocateChannels(16);

  /* init Fenetre */
  initWindowSDL2(WIDTH,HEIGHT+60,"Run The Clock",IMG_INIT_PNG,blanc,MENU);
  if(initIteratorWindowSDL2()){
    fprintf(stderr,"Erreur de creation de la fenetre\n");
    Mix_CloseAudio();
    closeAllSDL2();
    return -1;
  }

  /* -- init objets partie jeu -- */
  /* fond du jeu */
  createBlock(HEIGHT/2.f-3,5.f,6,HEIGHT/2.f,noir,JEU,30);
  createBlock(HEIGHT/2.f-1,5.f,2,HEIGHT/2.f,blanc,JEU,30);
  createImage(-20.f,-20.f,WIDTH+40,HEIGHT+40,"ressources/horloge2.png",JEU,20);
  createImage(WIDTH/2.f-RAYON,HEIGHT/2.f-RAYON,2*RAYON,2*RAYON,"ressources/fond.png",JEU,20);

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
  dataP->music=Mix_LoadMUS("ressources/tictac.mp3");
  dataP->son=Mix_LoadWAV("ressources/bong.wav");
  Mix_VolumeChunk(dataP->son, MIX_MAX_VOLUME/2);
  setDataElementSDL2(joueur,dataP);
  setRotationPointElementSDL2(joueur,.5f,1.f+1.f*RAYON/P_WIDTH/1.1f);
  setAngleElementSDL2(joueur,30.f);

  /* score */
  createImage(0.f,HEIGHT,WIDTH,60.f,"ressources/bande.png",JEU,20);
  score=createTexte(WIDTH/8.f,HEIGHT+15,3*WIDTH/4.f,30,"ressources/alarm_clock.ttf","SCORE : 0                 ",noir,JEU,0);
  addElementToElementSDL2(joueur,score);

  /* aiguille des heures */
  aiguille=createImage(WIDTH*1.f/2-A_WIDTH*1.f/2,144.f,A_WIDTH,190.f,"ressources/aiguille3.png",JEU,1);
  setRotationPointElementSDL2(aiguille,0.5f,0.825f);
  addElementToElementSDL2(aiguille,joueur);
  addElementToElementSDL2(joueur,aiguille);
  
  /* aiguille des minutes */
  aiguille=createImage(WIDTH*1.f/2-A_WIDTH*1.f/2,106.f,A_WIDTH,230.f,"ressources/aiguille2.png",JEU,1);
  setRotationPointElementSDL2(aiguille,0.5f,0.845f);
  addElementToElementSDL2(aiguille,joueur);
  addElementToElementSDL2(joueur,aiguille);
  


  /* aiguille des secondes */
  aiguille=createImage(WIDTH*1.f/2-A_WIDTH*1.f/2,69.f,A_WIDTH,270.f,"ressources/aiguille1.png",JEU,1);
  setRotationPointElementSDL2(aiguille,0.5f,0.855f);
  addElementToElementSDL2(aiguille,joueur);
  addElementToElementSDL2(joueur,aiguille);

  /* -- init objets partie menu -- */
  /* fond du jeu */
  aiguille=createImage(-20.f,10.f,WIDTH+40.f,HEIGHT+40.f,"ressources/horloge2.png",MENU,20);
  addDisplayCodeElementSDL2(aiguille,SCORE,20);
  createImage(WIDTH/2.f-RAYON,HEIGHT/2.f-RAYON+30,2*RAYON,2*RAYON,"ressources/fond.png",MENU,20);
  
  /* titre */
  createImage(WIDTH/6.f,115,2*WIDTH/3.f,150,"ressources/titre.png",MENU,0);

  /* "bouton" quitter */
  createImage(10.f,HEIGHT/2.f+5,70,50,"ressources/quit.png",MENU,0);
  createBlock(30.f,HEIGHT/2.f+10.f,40.f,40.f,blanc,MENU,19);

  /* "bouton" jouer */
  createImage(WIDTH-80.f,HEIGHT/2.f+5,70,50,"ressources/play.png",MENU,0);
  createBlock(WIDTH-70.f,HEIGHT/2.f+10.f,40.f,40.f,blanc,MENU,19);

  /* "bouton" score */
  createTexte(WIDTH/2.f-35,HEIGHT-40,70,50,"ressources/CurlyStars.ttf","Scores",noir,MENU,0);
  createBlock(WIDTH/2.f-25,HEIGHT-35,40,40,blanc,MENU,19);
  
  /* aiguille */
  aiguille=createImage(WIDTH*1.f/2-A_WIDTH*2,310.f,A_WIDTH*4,190.f,"ressources/aiguille4.png",MENU,0);
  setAngleElementSDL2(aiguille,270.f);
  setRotationPointElementSDL2(aiguille,0.49f,0.106f);
  setKeyPressElementSDL2(aiguille,click_menu);
  setActionElementSDL2(aiguille,action_menu);
  dataM=malloc(sizeof(*dataM));
  dataM->run=&(dataP->run);
  dataM->aim=270.f;
  dataM->tourne=0;
  dataM->speed=0.f;
  dataM->dep=0.f;
  dataM->son=Mix_LoadWAV("ressources/grince.wav");
  Mix_VolumeChunk(dataM->son, MIX_MAX_VOLUME/2);
  setDataElementSDL2(aiguille,dataM);
  addElementToElementSDL2(joueur,aiguille);

  /* -- menu score -- */
  dataS=load_score("save.sb");
  for(i=0;i<3;++i){
    sprintf(s,"%d : %d",i+1,dataS->scores[i]);
    j=4;
    while(s[++j]);
    if(j<10){
      s[j]=' ';
    }
    score=createTexte(200,175.f+100*i,200.f,50.f,"ressources/CurlyStars.ttf",s,noir,SCORE,0);
    setDataElementSDL2(score,dataS);
    addElementToElementSDL2(aiguille,score);
  }
  setKeyPressElementSDL2(score,return_from_score);
  
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

  save_score("save.sb",dataS);
  
  Mix_FreeChunk(dataM->son);
  Mix_FreeChunk(dataP->son);
  Mix_FreeMusic(dataP->music);
  closeAllWindowSDL2();
  Mix_CloseAudio();
  closeAllSDL2();
}
