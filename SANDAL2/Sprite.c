#include "Sprite.h"

/* -----------------------------------------------------
 * ListSprite
 */
ListSprite * initListSprite(int code){
  ListSprite * l = malloc(sizeof(*l));

  if(l){
    l->current = NULL;
    l->first = NULL;
    l->size = 0;
    l->sens = 0;
    l->wasChanged=0;
    l->next=NULL;
    l->prev=NULL;
    l->code=code;
  }

  return l;
}

void freeListSprite(ListSprite * l){
  unsigned i;
  Sprite * tmp;

  if(l){
    for(i = 0;i < l->size; ++i){
      tmp=l->first;
      l->first=l->first->next;
      free(tmp);
    }

    free(l);
  }
}

int addSprite(ListSprite * l,int x,int y,int width,int height,unsigned lifespan){
  Sprite *s;
  int error = 1;
  
  if(l){
    s=malloc(sizeof(*s));
    if(s){
      s->coords[0]=x;
      s->coords[1]=y;
      s->coords[2]=width;
      s->coords[3]=height;
      s->lifespan=lifespan;
      if(l->size){
	s->next=l->first;
	s->prev=l->first->prev;
	l->first->prev->next=s;
	l->first->prev=s;
      }else{
	s->next=s;
	s->prev=s;
	l->first=s;
	l->current=s;
	l->wasChanged=0;
      }
      l->size++;
      error = 0;
    }
  }

  return error;
}

int removeSprite(ListSprite * l,int x,int y,int width,int height){
  unsigned i = 0;
  int error = 1;
  Sprite * s;

  if(l && l->size){
    s=l->first;
    while(i < l->size && (s->coords[0]!=x || s->coords[1]!=y || s->coords[2]!=width || s->coords[3]!=height)){
      ++i;
      s=s->next;
    }
    if(i<l->size){
      error = 0;
      s->prev->next=s->next;
      s->next->prev=s->prev;
      if(l->current == s){
	if(l->sens == -1){
	  l->current=s->prev;
	}else{
	  l->current=s->next;
	}
	l->wasChanged=0;
      }
      free(s);
      l->size--;
    }
  }
  
  return error;
}

int setLifeSpanSprite(ListSprite * l,int x,int y,int width,int height,unsigned lifespan){
  unsigned i = 0;
  int error = 1;
  Sprite * s;

  if(l && l->size){
    s=l->first;
    while(i < l->size && (s->coords[0]!=x || s->coords[1]!=y || s->coords[2]!=width || s->coords[3]!=height)){
      ++i;
      s=s->next;
    }
    if(i<l->size){
      error = 0;
      s->lifespan = lifespan;
    }
  }
  
  return error;
}
/* ----------------------------------------------------- */



/* -----------------------------------------------------
 * ListAnimation
 */
ListAnimation * initListAnimation(){
  ListAnimation * l = malloc(sizeof(*l));

  if(l){
    l->first=NULL;
    l->current=NULL;
    l->size=0;
  }

  return l;
}

void freeListAnimation(ListAnimation *l){
  ListSprite *ls;
  unsigned i;

  if(l){
    i=0;
    while(i<l->size){
      ls=l->first;
      l->first=l->first->next;
      freeListSprite(ls);
      ++i;
    }
    free(l);
  }
}

int createAnimation(ListAnimation *l,int code){
  ListSprite *ls;
  int error = 1;

  if(l){
    ls=initListSprite(code);
    if(ls){
      error=0;
      if(l->size){
	ls->next=l->first;
	ls->prev=l->first->prev;
	l->first->prev->next=ls;
	l->first->prev=ls;
      }else{
	ls->next=ls;
	ls->prev=ls;
	l->first=ls;
	l->current=ls;
      }
      l->size++;
    }
  }

  return error;
}

int removeAnimation(ListAnimation *l,int code){
  ListSprite *ls;
  int error = 1;
  unsigned i = 0;

  if(l){
    ls=l->first;
    while(i<l->size && ls->code!=code){
      ls=ls->next;
      ++i;
    }
    if(i<l->size){
      error = 0;
      ls->next->prev=ls->prev;
      ls->prev->next=ls->next;
      freeListSprite(ls);
      l->size--;
    }
  }

  return error;
}

int addSpriteAnimation(ListAnimation *l,int code,int x,int y,int width,int height,unsigned lifespan){
  ListSprite *ls;
  int error = 1;
  unsigned i = 0;

  if(l){
    ls=l->first;
    while(i<l->size && ls->code!=code){
      ls=ls->next;
      ++i;
    }
    if(i<l->size){
      error=addSprite(ls,x,y,width,height,lifespan);
    }
  }

  return error;
}

int removeSpriteAnimation(ListAnimation *l,int code,int x,int y,int width,int height){
  ListSprite *ls;
  int error = 1;
  unsigned i = 0;

  if(l){
    ls=l->first;
    while(i<l->size && ls->code!=code){
      ls=ls->next;
      ++i;
    }
    if(i<l->size){
      error=removeSprite(ls,x,y,width,height);
    }
  }

  return error;
}

int setLifeSpanSpriteAnimation(ListAnimation *l,int code,int x,int y,int width,int height,unsigned lifespan){
  ListSprite *ls;
  int error = 1;
  unsigned i = 0;

  if(l){
    ls=l->first;
    while(i<l->size && ls->code!=code){
      ls=ls->next;
      ++i;
    }
    if(i<l->size){
      error=setLifeSpanSprite(ls,x,y,width,height,lifespan);
    }
  }

  return error;
}

int setAnimation(ListAnimation *l,int code){
  ListSprite *ls;
  int error = 1;
  unsigned i = 0;

  if(l){
    ls=l->first;
    while(i<l->size && ls->code!=code){
      ls=ls->next;
      ++i;
    }
    if(i<l->size){
      l->current=ls;
      error=0;
    }
  }

  return error;
}
/* ----------------------------------------------------- */
