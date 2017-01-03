#include "Master.h"
#include "GameBoard.h"

#ifndef  DEF_SHAPE
#define  DEF_SHAPE
#include "Block.h"


//Shape


enum 
  {
    F_S,
    F_iS,
    F_L,
    F_iL,
    F_O,  
    F_I,
    F_T
  };



class Shape
{
public :
  
  Shape(int COLOR,int TYPE);


  void rotate_clockwize();
  void rotate_counterclockwize();

  void move_right();
  void move_left();
  void move_down();

  int  get_x();
  int  get_y();
  int  get_color();

  void set_x(int X);
  void set_y(int Y);
  void set_color(int COLOR);
  
  std::vector<Block> block_v;

 protected:

  void O_O();
  void O_T();
  void O_I();
  void O_L();
  void O_iL();
  void O_S();
  void O_iS();
  
  int x;
  int y;
  int color;

  
};

#endif
