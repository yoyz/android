#include "Master.h"

#include "Shape.h"
#include "GameBoard.h"
#include "GameSdl.h"
#include "DrawSdl.h"



using namespace std;


SDL_Event event;
GameBoard GB;

Shape * current_shape = NULL;
Shape * next_shape    = NULL;   

int current_sdl_time  = 0;
int previous_sdl_time = 0;

int cont              = 1;
int level_number      = 1;
int number_of_seconds = 0;
int last_score        = 0;
int current_score     = 0;
int number_of_line    = 0;  


void setup_new_game()
{
  level_number=1;
  number_of_seconds=0;
  last_score=0;
  current_score=0;
  number_of_line=0;
}


void check_and_increment_level()
{
  if (current_score-last_score>500)
    {
      last_score=current_score;
      level_number++;
    }
}

void create_two_shape()
{
 current_shape = new  Shape((rand() % 5)+1,rand() %7); 
 next_shape    = new  Shape((rand() % 5)+1,rand() %7); 
}


void provide_next_shape()
{
  delete current_shape; 
  current_shape = next_shape;
  next_shape    = new Shape((rand() % 5)+1,rand() % 7);
}

void free_shapes()
{
 delete current_shape;
 delete next_shape;
}


int game_play(DrawSdl on_screen)
{    
  int delay=50;
  bool event_to_draw=true;
  bool shape_to_insert=false;

  cont=1;
  create_two_shape();   
  
  while (cont)
    {
      delay=50;
      current_sdl_time = SDL_GetTicks();

      shape_to_insert=current_sdl_time-previous_sdl_time>1000/level_number;
      
      SDL_PollEvent(&event);

      switch(event.type)
	{
	case SDL_QUIT:
	  cont = 0;
	  break;

	case SDL_KEYDOWN:
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      on_screen.clean_screen();
	      on_screen.draw_splash_screen();
	      on_screen.refresh();
	      cont = 0;
	      return 0;
	      break;
	      
	    case SDLK_DOWN:
	      if (GB.can_shape_move_down(current_shape))
		current_shape->move_down();
	      event_to_draw=true;
	      break;
	      
	    case SDLK_RIGHT:
	      delay=delay+25;
	      if (GB.can_shape_move_right(current_shape))
		current_shape->move_right();
	      event_to_draw=true;
	      break;
	      
	    case SDLK_LEFT:
	      delay=delay+25;
	      if (GB.can_shape_move_left(current_shape))
		current_shape->move_left();
	      event_to_draw=true;
	      break;
	      
	    case SDLK_UP:
	      delay=delay+150;
	      if (GB.can_shape_rotate(current_shape))
		current_shape->rotate_clockwize();
	      event_to_draw=true;
	      break;
	      
	    case SDLK_SPACE:
	      delay=delay+150;
	      while (GB.can_shape_move_down(current_shape))
		current_shape->move_down();
	      event_to_draw=true;
	      break;
	    }
	}
	  
      
      if (!(GB.can_shape_move_down(current_shape)) &&
	  shape_to_insert)
	
	{
	  GB.insert_shape(current_shape);
	  provide_next_shape();
	  for (int i=0;i<4;i++)
	    number_of_line+=GB.clean_full_line(current_score);

	  check_and_increment_level();
	  event_to_draw=true;
	  shape_to_insert=false;
	}
      
      
      if (shape_to_insert)
	{	  	    
	  previous_sdl_time = current_sdl_time;
	  number_of_seconds++;
	  
	  if (GB.can_shape_move_down(current_shape))
	    current_shape->move_down();
	  event_to_draw=true;
	}
      
      
      if (GB.is_full())
	{
	  GB.zero_map();

	  cont=0;
	  on_screen.clean_screen();
	  on_screen.game_over(current_score,level_number,number_of_line);
	  on_screen.refresh();
	  setup_new_game();
	  return 0;
	}
      
      
      
      //Delay the loop
      SDL_Delay(delay);
      if (event_to_draw)
	{
	  on_screen.clean_screen();
	  
	  on_screen.draw_border();
	  on_screen.draw_game_board(GB);
	  
	  on_screen.draw_score(current_score);
	  on_screen.draw_level_number(level_number);
	  on_screen.draw_time(number_of_seconds);
	  on_screen.draw_number_of_line(number_of_line);
	  
	  on_screen.draw_shape_on_board(current_shape);
	  on_screen.draw_next_shape(next_shape);
	  
	  on_screen.refresh();
	  event_to_draw=false;
	}
    }  
  free_shapes();
}




int game_start()
{
  bool state = true;
  bool userWantedToQuit=false;

  DrawSdl on_screen;  


  on_screen.enable_sdl_and_ttf();
  on_screen.load_ttf_data();
  on_screen.load_sdl_screen_data();
  on_screen.screen_activate();  
  on_screen.draw_splash_screen();
  on_screen.draw_press_enter_to_play();
  //  on_screen.initColors();  
  on_screen.refresh();

  while (!userWantedToQuit)
    {
      SDL_Delay(200);
      current_sdl_time = SDL_GetTicks();      
      if(SDL_PollEvent(&event)==true)
	{ 	  
	  switch(event.type)
	    {
	    case SDL_QUIT:
	      userWantedToQuit=true;
	      break;
	    case SDL_FINGERDOWN: 
	      SDL_Delay(100);
	      setup_new_game();
	      GB.zero_map();
	      game_play(on_screen);
	      break;                  

	    case SDL_KEYDOWN:
	      switch(event.key.keysym.sym)
		{
		  //Want to quit ?
		case SDLK_ESCAPE: 
		  userWantedToQuit=true;
		  break;

		  //Want to play ?
		}
	      break;
	    }
	}
    }
 
  on_screen.free_sdl_screen_data();
  on_screen.free_ttf_data();
  on_screen.disable_sdl_and_ttf();
    
  return EXIT_SUCCESS;
}
