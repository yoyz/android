#include "Master.h"

#ifndef  GAME_BOARD
#define  GAME_BOARD
#include "Shape.h"



class GameBoard
{
public :
  
  GameBoard();
  
  int  clean_full_line(int &compteur);

  bool can_shape_move_down(Shape * current_shape);
  bool can_shape_move_left(Shape * current_shape);
  bool can_shape_move_right(Shape * current_shape);
  bool can_shape_rotate(Shape * current_shape);

  bool insert_shape(Shape * current_shape);
  
  
  void display_map();
  
  bool is_full();
   
  
  int ** get_map();
  
  void zero_map();
  

  int map[BLOCK_LENGTH][BLOCK_WIDTH];  
  

};
#endif
