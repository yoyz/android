#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../pbsynth/synthengine.h"
#include "SDL.h"
#include "opensl_io.h"


#define NBSAMPLE        64
#define BUFFERFRAMES    1024
#define VECSAMPS_MONO   NBSAMPLE
#define VECSAMPS_STEREO NBSAMPLE*2
#define SR              44100



static int on;
float  touch_x=0.5;
float  touch_y=0.5;
int    trig=0;
int    trigged=0;
int    motion=0;
/*
void start_process()
{
  OPENSL_STREAM  *p;
  int samps, i, j;
  float  inbuffer[VECSAMPS_MONO], outbuffer[VECSAMPS_STEREO];
  p = android_OpenAudioDevice(SR,1,2,BUFFERFRAMES);
  if(p == NULL) return;
  on = 1;
  while(on) {
    samps = android_AudioIn(p,inbuffer,VECSAMPS_MONO);
    for(i = 0, j=0; i < samps; i++, j+=2)
      outbuffer[j] = outbuffer[j+1] = inbuffer[i];
    android_AudioOut(p,outbuffer,samps*2);
  }
  android_CloseAudioDevice(p);
}
*/
/*
void start_process()
{
  int nbuff=NBSAMPLE;
  int sample=0; 
  SynthEngine SE(nbuff,NBSAMPLE);
  SE.init();
  //int tab[12]={0,1,2,3,4,5,6,7,8,9,10,11};
  int tab[12]={0,0,2,3,3,5,5,7,8,8,10,10};
  int index;


  SE.setParameter(SENGINE_FILTFREQ,0.9f);
  SE.setParameter(SENGINE_FILTRESO,0.1f);

  SE.getEnvelope(0)->setADSR(-1.0f, -0.0f, 1.0f, -0.4f);
  SE.getEnvelope(1)->setADSR(-1.0f, -0.0f, 0.5f, -0.8f);


  OPENSL_STREAM  *p;
  int samps, i, j;
  float  inbuffer[VECSAMPS_MONO], outbuffer[VECSAMPS_STEREO];
  //p = android_OpenAudioDevice(SR,1,2,BUFFERFRAMES);
  //p = android_OpenAudioDevice(SR,0,2,BUFFERFRAMES);
  p = android_OpenAudioDevice(SR,1,2,BUFFERFRAMES);
  if(p == NULL) return;
  on = 1;
  while(on) {
    if (trig==1 && trigged==0)
      {
	index=touch_x*12;
	SE.triggerNote(42+(tab[index]));
	//SE.setParameter(SENGINE_FILTFREQ,(touch_y*1.5)-1.5);
	//SE.setParameter(SENGINE_FILTFREQ,(touch_y*1.5)-1.5);
	trigged=1;
      }
    if (motion)
      {
	//SE.setParameter(SENGINE_FILTFREQ,(touch_y*1.5)-1.5);
	//SE.setParameter(SENGINE_FILTFREQ,(touch_y*1.5)-1.5);
	motion=0;
      }
    //SE.setParameter(SENGINE_FILTFREQ,(touch_y*1.5)-1.5);
    SE.setParameter(SENGINE_FILTFREQ,(touch_y*1.0)-0.8);
    samps = android_AudioIn(p,inbuffer,VECSAMPS_MONO);
    SE.process(inbuffer,nbuff);
    
    for(i = 0, j=0; i < nbuff; i++, j+=2)
      outbuffer[j] = outbuffer[j+1] = inbuffer[i];
    android_AudioOut(p,outbuffer,samps*2);
    sample=sample+nbuff;

    if (trig==0 && trigged==1)
      {
	SE.releaseNote();
	trigged=0;
      }
  }
  android_CloseAudioDevice(p);
}
*/

void start_process()
{
  int nbuff=NBSAMPLE;
  int sample=0;
  SynthEngine * SE[4];
  int samps, i, j,k;
  int ce=0;
  int oldce=0;
  //SynthEngine ** SE;
  //SE=new SynthEngine 
  //int tab[12]={0,1,2,3,4,5,6,7,8,9,10,11};
  int tab[12]={0,0,2,3,3,5,5,7,8,8,10,10};
  int index;
  for (i=0;i<4;i++)
    {
      SE[i] = new SynthEngine(nbuff,NBSAMPLE);
      SE[i]->init();
      
      SE[i]->setParameter(SENGINE_FILTFREQ,0.9f);
      SE[i]->setParameter(SENGINE_FILTRESO,0.1f);

      SE[i]->getEnvelope(0)->setADSR(-1.0f, -0.0f, 1.0f, -0.1f);
      SE[i]->getEnvelope(1)->setADSR(-1.0f, -0.0f, 0.5f, -0.1f);

      SE[i]->getEcho()->setLevel(float(-0.5));
      SE[i]->getEcho()->setLevel(float(0.3));
    }



  OPENSL_STREAM  *p;

  float  inbuffer[VECSAMPS_MONO];
  float tmpbuffer[VECSAMPS_MONO];
  float outbuffer[VECSAMPS_STEREO];
  //p = android_OpenAudioDevice(SR,1,2,BUFFERFRAMES);
  //p = android_OpenAudioDevice(SR,0,2,BUFFERFRAMES);
  p = android_OpenAudioDevice(SR,1,2,BUFFERFRAMES);
  if(p == NULL) return;
  on = 1;
  while(on) {
    if (trig==1 && trigged==0)
      {
	index=touch_x*12;
	SE[ce]->triggerNote(42+(tab[index]));
	SE[ce]->setParameter(SENGINE_FILTFREQ,(touch_y*1.0)-0.8);
	//SE.setParameter(SENGINE_FILTFREQ,(touch_y*1.5)-1.5);
	//SE.setParameter(SENGINE_FILTFREQ,(touch_y*1.5)-1.5);
	trigged=1;
	oldce=ce;
	ce++;

      }
    if (motion)
      {
	//SE.setParameter(SENGINE_FILTFREQ,(touch_y*1.5)-1.5);
	//SE.setParameter(SENGINE_FILTFREQ,(touch_y*1.5)-1.5);
	motion=0;
	SE[oldce]->setParameter(SENGINE_FILTFREQ,(touch_y*1.0)-0.8);
      }
    //SE.setParameter(SENGINE_FILTFREQ,(touch_y*1.5)-1.5);
    //SE[ce]->setParameter(SENGINE_FILTFREQ,(touch_y*1.0)-0.8);
    if (ce>=3)
      ce=0;

    samps = android_AudioIn(p,inbuffer,VECSAMPS_MONO);

    // cleanup buffer
    for(i = 0 ; i < nbuff; i++)
      for (k=0;k<4;k++)
	tmpbuffer[i]=0;
	
    for (k=0;k<4;k++)
      {
	SE[k]->process(inbuffer,nbuff);    

	for(i = 0 ; i < nbuff; i++)
	  tmpbuffer[i]=tmpbuffer[i]+(inbuffer[i]/2.0);	
      }

    for(i = 0 ; i < nbuff; i++)
      {
	if (tmpbuffer[i]>=1) tmpbuffer[i]=0.99;
	if (tmpbuffer[i]<=-1.0) tmpbuffer[i]=-0.99;
      }

    for(i = 0, j=0; i < nbuff; i++, j+=2)
      outbuffer[j] = outbuffer[j+1] = tmpbuffer[i];

    android_AudioOut(p,outbuffer,samps*2);
    sample=sample+nbuff;

    if (trig==0 && trigged==1)
      {
	SE[oldce]->releaseNote();
	trigged=0;
      }
  }
  android_CloseAudioDevice(p);
}

static int thread_start_process(void *ptr)
{
  start_process();
}


void stop_process(){
  on = 0;
}


typedef struct Sprite
{
  SDL_Texture* texture;
  Uint16 w;
  Uint16 h;
} Sprite;

/* Adapted from SDL's testspriteminimal.c */
Sprite LoadSprite(const char* file, SDL_Renderer* renderer)
{
  Sprite result;
  result.texture = NULL;
  result.w = 0;
  result.h = 0;
  
  SDL_Surface* temp;
  
  /* Load the sprite image */
  temp = SDL_LoadBMP(file);
  if (temp == NULL)
    {
      fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
      return result;
    }
  result.w = temp->w;
  result.h = temp->h;
  
  /* Create texture from the image */
  result.texture = SDL_CreateTextureFromSurface(renderer, temp);
  if (!result.texture) {
    fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
    SDL_FreeSurface(temp);
    return result;
  }
  SDL_FreeSurface(temp);
  
  return result;
}

void draw(SDL_Window* window, SDL_Renderer* renderer, const Sprite sprite)
{
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  //SDL_Rect destRect = {w/2 - sprite.w/2, h/2 - sprite.h/2, sprite.w, sprite.h};
  //SDL_Rect destRect = {w/2 - sprite.w/2, h/2 - sprite.h/2, (sprite.w*(touch_x*100.0))/100, (sprite.h*(touch_y*100.0))};
  SDL_Rect destRect = {touch_x*w, touch_y*h, sprite.w, sprite.h };
  /* Blit the sprite onto the screen */
  SDL_RenderCopy(renderer, sprite.texture, NULL, &destRect);
}

int main(int argc, char *argv[])
{
  SDL_Window   *window;
  SDL_Renderer *renderer;
  SDL_Thread   *thread;
  int           threadReturnValue;
  Uint8         done = 0;
  SDL_Event     event;
  int           audio_started=0;

  SDL_Joystick *joystick;

   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
       SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
       exit(1);
   }
   //joystick = SDL_JoystickOpen(0);
  
  if(SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0)
    exit(2);
  
  Sprite sprite = LoadSprite("image.bmp", renderer);
  if(sprite.texture == NULL)
    exit(2);
  


  if (audio_started==0)
    {
      //start_process();
      thread = SDL_CreateThread(thread_start_process, "TestThread", (void *)NULL);
      audio_started=1;
    }
  
  /* Main render loop */  
  while(!done)
    {
      /* Check for events */
      while(SDL_PollEvent(&event))
	{
	  /*
	  if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN)
	    {
	      done = 1;
	    }
	  */
	  if(event.type == SDL_QUIT)
	    done=1;

	  if (event.type == SDL_FINGERDOWN)
	    {
	      touch_x = event.tfinger.x;
	      touch_y = event.tfinger.y;
	      trig=1;
	    }
	  if (event.type == SDL_FINGERUP)
	    {
	      touch_x = event.tfinger.x;
	      touch_y = event.tfinger.y;
	      trig=0;
	    }

	  if (event.type == SDL_FINGERMOTION)
	    {
	      touch_x = event.tfinger.x;
	      touch_y = event.tfinger.y;
	      motion=1;
	    }
          if (event.type == SDL_JOYAXISMOTION)
            { 
              if(event.jaxis.axis == 0 && event.jaxis.value < - 100)
                done=1;
            }
          if (event.type == SDL_JOYBUTTONDOWN)
            { 
                done=1;
            }

	}
      
      
      /* Draw a gray background */
      SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
      SDL_RenderClear(renderer);
      
      draw(window, renderer, sprite);
      
      /* Update the screen! */
      SDL_RenderPresent(renderer);      
      SDL_Delay(1);
      
    }
  stop_process();
  SDL_WaitThread(thread, &threadReturnValue);
  
  exit(0);
}
