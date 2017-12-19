#ifndef  DRAWSDL
#define  DRAWSDL
#include "Shape.h"
#include "Block.h"


class DrawSdl
{

 public:

  DrawSdl();

  
  void load_ttf_data();
  void free_ttf_data();

  void load_sdl_screen_data();
  void free_sdl_screen_data();

  void enable_sdl_and_ttf();
  void disable_sdl_and_ttf();

  void screen_activate();

  void init_game_info();

  void draw_press_enter_to_play();

  void draw_score(int score);
  void draw_time(int number_of_seconds);
  void draw_level_number(int level_number);
  void draw_number_of_line(int number_of_line);
  void clean_screen();


  void draw_shape_on_board(Shape * shape);
  void draw_next_shape(Shape * shape);

  void refresh();

  void draw_border();

  void draw_game_board(GameBoard GB);

  void draw_splash_screen();
  
  void init_colors(void);

  void game_over(int score, int level_number,int number_of_line);
  
 private:

  char clock[20];
  char score[20];
  char level[20];

  char game_over_1[50];
  char game_over_2[50];
  char game_over_3[50];
  char game_over_4[50];

  Uint32 couleurs[NB_COLORS];

  char nb_line[20];  

  SDL_Surface *screen;  
  SDL_Surface *carre;
  SDL_Surface *text;
  SDL_Surface *texte;
  SDL_Surface *texte1;
  SDL_Surface *txt_msg;
  SDL_Surface *score_surface;
  SDL_Surface *clock_surface;
  SDL_Surface *level_surface; 
  SDL_Surface *line_number_surface;
  
  SDL_Surface *tetris_splash;
  SDL_Surface *tetris_blocks;
  SDL_Surface *grey_box;

  

  SDL_Rect position;
  SDL_Rect board_position;

  TTF_Font * font_large;
  TTF_Font * font_medium;
  TTF_Font * font_small;
  
  SDL_Color sdl_color_black;
  SDL_Color sdl_color_white;  


#ifdef __SDL20__
  SDL_Window * window;
#endif



};
#endif
