#include "Master.h"

#ifndef  DEF_BLOCK
#define  DEF_BLOCK

class Block
{

public :
   
  Block(int X,int Y,int COLOR);

  void move_right();
  void move_left();
  void move_down();
  void move_up();

  void set_x(int X);
  void set_y(int Y);
  void set_color(int COLOR);

  int  get_x();
  int  get_y();
  int  get_color();


 private:
  
  int x;
  int y;
  int color;  
};

#endif
