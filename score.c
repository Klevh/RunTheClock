#include "score.h"

void update_top_score(Score_D * scores, int s){
  int i=0,j;

  if(scores){
    while(i<3 && scores->scores[i]>=s){
      ++i;
    }
    if(i<3){
      for(j=2;j>i;--j){
	scores->scores[j]=scores->scores[j-1];
      }
      scores->scores[i]=s;
    }
  }
}

Score_D * load_score(char * file){
  Score_D * d = malloc(sizeof(*d));
  FILE * fp;
  int i;

  if(d){
    fp=fopen(file,"rb");
    if(fp){
      fread(d,sizeof(*d),1,fp);
      fclose(fp);
    }else{
      fp=fopen(file,"wb");
      if(fp){
	for(i=0;i<3;++i){
	  d->scores[i]=24-8*i;
	}
	fwrite(d,sizeof(*d),1,fp);
	fclose(fp);
      }
    }
  }

  return d;
}

void save_score(char * file,Score_D * d){
  FILE * fp=fopen(file,"wb");

  if(fp){
    fwrite(d,sizeof(*d),1,fp);
    fclose(fp);
  }
}

void return_from_score(ElementSDL2 * this,SDL_Keycode c){
  if(c==27){
    changeDisplayWindowSDL2(MENU);
  }
}
