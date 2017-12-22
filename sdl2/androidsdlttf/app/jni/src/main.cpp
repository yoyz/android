#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SDL.h"
#include "opensl_io.h"
#include "SDL_GUI.h"
#define BUFFERFRAMES 1024
#define VECSAMPS_MONO 64
#define VECSAMPS_STEREO 128
#define SR 44100


static int on;
float  touch_x;
float  touch_y;

int32_t pal0[MAXCOLOR]={0x0,      0xC8A0A8, 0x59AADA, 0xFFA11C, 0x39CE90, 0x36B82B, 0x3E789A, 0xFFFFFF, 0x0 };
int32_t * pal=pal0;


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
  SDL_GUI      SG;
  SG.initVideo();
  int i=0;
  /*
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
       SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
       exit(1);
   }
  joystick = SDL_JoystickOpen(0);
  
  if(SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0)
    exit(2);
  */
  /*
  Sprite sprite = LoadSprite("image.bmp", renderer);
  if(sprite.texture == NULL)
    exit(2);
  */
  
  
  // if (audio_started==0)
  //   {
  //     //start_process();
  //     thread = SDL_CreateThread(thread_start_process, "TestThread", (void *)NULL);
  //     audio_started=1;
  //   }
  
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

	  //if (event.type == SDL_FINGERDOWN)
	  if (event.type == SDL_FINGERMOTION)
	    {
	      touch_x = event.tfinger.x;
	      touch_y = event.tfinger.y;
	      i++;
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
      //SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
      //SDL_RenderClear(renderer);
      
      //draw(window, renderer, sprite);
      
      /* Update the screen! */
      
      SG.clearScreen();                 // remove all 
      SG.drawBoxNumber(i,pal[ENABLEDBOX_COLOR]);
      SG.refresh();
      
      //SDL_Delay(1);
      //i++;
      if (i>4) i=0;
      
    }
  //stop_process();
  //SDL_WaitThread(thread, &threadReturnValue);
  
  exit(0);
}
